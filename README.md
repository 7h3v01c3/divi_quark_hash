# Divi Quark Hash

Python 3 module for Divi Quark proof-of-work hashing.

## Overview

The Quark algorithm is a chained hash function used for proof-of-work verification. It chains 9 hash operations using 6 different cryptographic primitives (Blake, BMW, Groestl, JH, Keccak, Skein) with conditional branching based on intermediate hash values.

**Important: Divi uses Quark hash ONLY for the genesis block.** All other blocks use double SHA256 on 112-byte headers (80 bytes standard + 32 bytes acc_checkpoint). This library is specifically needed for validating the Divi genesis block.

## Installation

### From Source

Requires Python 3.8+ and a C compiler.

```bash
pip install .
```

Or for development:

```bash
pip install -e .
```

### Build Only

```bash
python setup.py build_ext --inplace
```

## Usage

```python
import divi_quark_hash

# Block header as bytes (80 bytes)
header = bytes.fromhex('0100000000000000...')

# Compute PoW hash
pow_hash = divi_quark_hash.getPoWHash(header)

# Result is 32 bytes (256 bits)
print(pow_hash.hex())
```

## Testing

Run the test suite:

```bash
# Using pytest (recommended)
pip install pytest
pytest tests/ -v
```

## API Reference

### `getPoWHash(header) -> bytes`

Compute the Quark proof-of-work hash of a block header.

**Parameters:**
- `header` (bytes): The block header data (typically 80 bytes)

**Returns:**
- `bytes`: 32-byte hash result

**Raises:**
- `TypeError`: If header is not a bytes object

## Algorithm

The Quark algorithm flow:

```
Blake512 → BMW512 → [Groestl512|Skein512] → Groestl512 → JH512 → 
[Blake512|BMW512] → Keccak512 → Skein512 → [Keccak512|JH512] → Output
```

Three decision points check bit 3 of intermediate hashes to select between two possible primitives, creating 8 possible execution paths.

## Project Structure

```
divi_quark_hash/
├── include/quark/        # Public headers
│   └── quark.h
├── src/
│   ├── core/             # Core algorithm
│   │   ├── constants.h
│   │   ├── hash_step.c/h
│   │   └── quark_algorithm.c/h
│   └── bindings/         # Language bindings
│       └── python_module.c
├── sha3/                 # SPH crypto primitives
├── tests/                # Test suite
└── docs/                 # Documentation
```

## Credits

This project has a long heritage in the cryptocurrency community:

- Originally written by @chaeplin (xcoin-hash).
- Adapted for PIVX by @gpdionisio (pivx_quark_hash).
- Re-envisioned and maintained for Divi by @7h3v01c3 (divi_quark_hash).

## License

MIT License - See [LICENSE](LICENSE) for details.

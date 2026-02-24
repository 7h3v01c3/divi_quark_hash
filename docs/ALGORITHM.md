# Quark Hash Algorithm

## Overview

The Quark algorithm is a chained hash function designed for proof-of-work verification. It provides security through the combination of multiple cryptographic primitives and introduces path diversity via conditional branching.

## Cryptographic Primitives

Quark uses six different 512-bit hash functions from the SHA-3 competition:

| Primitive | Description |
|-----------|-------------|
| **Blake-512** | Based on ChaCha stream cipher |
| **BMW-512** | Blue Midnight Wish |
| **Groestl-512** | AES-based construction |
| **JH-512** | Generalized AES |
| **Keccak-512** | SHA-3 winner (sponge construction) |
| **Skein-512** | Threefish block cipher based |

## Algorithm Flow

```
Input (80 bytes)
      │
      ▼
  ┌────────┐
  │Blake512│ Round 1
  └────┬───┘
       │
      ▼
  ┌────────┐
  │ BMW512 │ Round 2
  └────┬───┘
       │
       ▼
    ┌──────┐
    │bit 3?│ Round 3 (Conditional)
    └──┬───┘
   yes │  │ no
       ▼  ▼
┌─────────┐ ┌────────┐
│Groestl  │ │ Skein  │
└────┬────┘ └────┬───┘
     └─────┬─────┘
           │
          ▼
  ┌──────────┐
  │Groestl512│ Round 4
  └────┬─────┘
       │
      ▼
  ┌────────┐
  │ JH512  │ Round 5
  └────┬───┘
       │
       ▼
    ┌──────┐
    │bit 3?│ Round 6 (Conditional)
    └──┬───┘
   yes │  │ no
       ▼  ▼
┌────────┐ ┌────────┐
│ Blake  │ │  BMW   │
└────┬───┘ └────┬───┘
     └─────┬─────┘
           │
          ▼
  ┌──────────┐
  │Keccak512 │ Round 7
  └────┬─────┘
       │
      ▼
  ┌────────┐
  │Skein512│ Round 8
  └────┬───┘
       │
       ▼
    ┌──────┐
    │bit 3?│ Round 9 (Conditional)
    └──┬───┘
   yes │  │ no
       ▼  ▼
┌────────┐ ┌────────┐
│Keccak  │ │   JH   │
└────┬───┘ └────┬───┘
     └─────┬─────┘
           │
          ▼
   Output (32 bytes)
```

## Conditional Branching

At three points in the algorithm, bit 3 of the intermediate hash determines which primitive to use next:

| Round | If bit 3 = 1 | If bit 3 = 0 |
|-------|--------------|--------------|
| 3 | Groestl-512 | Skein-512 |
| 6 | Blake-512 | BMW-512 |
| 9 | Keccak-512 | JH-512 |

This creates 2³ = 8 possible execution paths, providing additional security through path diversity.

## Branch Condition

The branch condition checks bit 3 (value 8) of the first 32-bit word of the hash:

```c
#define QUARK_BRANCH_MASK  0x08  // bit 3

int should_branch = (hash[0] & QUARK_BRANCH_MASK) != 0;
```

## Input/Output

- **Input**: 80 bytes (standard block header)
- **Intermediate**: 64 bytes (512 bits) between each round
- **Output**: 32 bytes (256 bits, first half of final 512-bit hash)

## Security Properties

1. **Primitive Diversity**: Uses 6 different hash functions
2. **Path Diversity**: 8 possible execution paths
3. **Chained Construction**: Each round depends on the previous
4. **Proven Primitives**: All components from SHA-3 competition

## References

- [Quark: A Lightweight Hash](https://eprint.iacr.org/2010/261.pdf) - Original paper
- [Divi Technical Documentation](https://github.com/DiviProject/Divi)
- [SPH Library](http://www.saphir2.com/sphlib/) - Hash primitive implementations

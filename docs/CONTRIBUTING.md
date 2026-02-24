# Contributing to Divi Quark Hash

Thank you for your interest in contributing!

## Development Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/7h3v01c3/divi_quark_hash.git
   cd divi_quark_hash
   ```

2. Create a virtual environment:
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows: venv\Scripts\activate
   ```

3. Install development dependencies:
   ```bash
   pip install pytest
   ```

4. Build the extension:
   ```bash
   python setup.py build_ext --inplace
   ```

5. Run tests:
   ```bash
   pytest tests/ -v
   ```

## Code Style

### C Code

- Follow existing code style
- Use meaningful variable names
- Add comments for non-obvious logic
- Keep functions focused and small

### Python Code

- Follow PEP 8
- Use type hints where helpful
- Write docstrings for public functions

## Testing

All changes must pass the existing test suite:

```bash
pytest tests/ -v
```

When adding new features:
- Add corresponding tests
- Ensure tests are deterministic
- Include edge cases

## Pull Request Process

1. Create a feature branch from `master`
2. Make your changes
3. Ensure all tests pass
4. Update documentation if needed
5. Submit a pull request

## Critical Warning

This is **cryptographic code** used for blockchain consensus. Be extremely careful:

- Do NOT change the algorithm logic
- Do NOT "optimize" hash computations without extensive testing
- Do NOT modify the SPH primitives (sha3/ directory)
- ALWAYS verify hash outputs match test vectors

Changes that break blockchain consensus cannot be merged.

## Questions?

Open an issue for discussion before making significant changes.

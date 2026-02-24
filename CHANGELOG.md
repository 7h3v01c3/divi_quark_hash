# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-01-22

Full re-envisioning of the Quark hash library for Divi: clean architecture, Python 3 only, new project layout, and documentation. Not just a refactor—new structure, abstraction layers, and tests while preserving algorithm behavior.

### Changed
- Complete codebase restructuring following Martin Fowler's clean code principles
- Modernized build system (distutils → setuptools)
- Python 3.8+ only (dropped Python 2 support)

### Added
- Named constants for all magic numbers
- `hash_step.h/c` abstraction layer for hash primitives
- Comprehensive test suite using pytest with DIVI genesis block test vector
- Algorithm documentation
- Contributing guidelines
- Proper project structure:
  - `include/quark/` - Public headers
  - `src/core/` - Core algorithm
  - `src/bindings/` - Language bindings
  - `tests/` - Test suite
  - `docs/` - Documentation

### Documented
- DIVI uses Quark hash ONLY for genesis block (80 bytes)
- All other DIVI blocks use double SHA256 on 112-byte headers
- Test vectors updated to use authentic DIVI mainnet genesis block

### Removed
- Python 2 support and compatibility code
- Legacy distutils build configuration
- Old source files (`quarkhash.c`, `quarkhash.h`, `quarkmodule.c`, `MANIFEST`)

### Fixed
- Consistent code formatting throughout
- Windows/MSVC compiler compatibility (`__attribute__` in groestl.c)
- Python 3.10+ compatibility (`PY_SSIZE_T_CLEAN` macro)

## History (prior codebase)

### Where this code came from
- Re-envisioned from the pivx_quark_hash project (by @gpdionisio), which built on xcoin-hash and related implementations
- See README.md for credits
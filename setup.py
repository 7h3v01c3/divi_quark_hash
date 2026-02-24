"""
Divi Quark Hash - Build Configuration

Python 3 module for Divi Quark proof-of-work hashing.

Originally written by @chaeplin (xcoin-hash).
Adapted for PIVX by @gpdionisio (pivx_quark_hash).
Re-envisioned and maintained for Divi by @7h3v01c3 (divi_quark_hash).
See README.md for full credits.
"""

import re
from pathlib import Path

from setuptools import setup, Extension

# Single source of truth for version (pyproject.toml)
def _version_from_pyproject():
    pyproject = Path(__file__).parent / "pyproject.toml"
    if not pyproject.exists():
        return "1.0.0"
    text = pyproject.read_text(encoding="utf-8")
    m = re.search(r'version\s*=\s*["\']([^"\']+)["\']', text)
    return m.group(1) if m else "1.0.0"

# C extension module
quark_hash_module = Extension(
    'divi_quark_hash',
    sources=[
        # Python bindings
        'src/bindings/python_module.c',
        # Core algorithm
        'src/core/quark_algorithm.c',
        'src/core/hash_step.c',
        # Crypto primitives (SPH library)
        'sha3/blake.c',
        'sha3/bmw.c',
        'sha3/groestl.c',
        'sha3/jh.c',
        'sha3/keccak.c',
        'sha3/skein.c',
    ],
    include_dirs=[
        '.',
        './include',
        './src/core',
        './sha3',
    ],
)

setup(
    name='divi_quark_hash',
    version=_version_from_pyproject(),
    description='Divi Quark hash for proof-of-work verification.',
    long_description=(Path(__file__).parent / 'README.md').read_text(encoding='utf-8'),
    long_description_content_type='text/markdown',
    author='TheVoice',
    url='https://github.com/7h3v01c3/divi_quark_hash',
    
    license='MIT',
    
    ext_modules=[quark_hash_module],
    
    python_requires='>=3.8',
    
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Programming Language :: C',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Programming Language :: Python :: 3.11',
        'Programming Language :: Python :: 3.12',
        'Programming Language :: Python :: 3.13',
        'Topic :: Security :: Cryptography',
    ],
    
    keywords='divi quark hash cryptocurrency proof-of-work',
    
    # Include header files in source distribution
    package_data={
        '': ['*.h'],
    },
)

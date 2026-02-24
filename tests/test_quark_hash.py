"""
Divi Quark Hash Test Suite

Test vectors derived from Divi Blockchain.
These tests verify that the hash function produces correct,
reproducible results matching the blockchain consensus.

NOTE: Divi Blockchain uses Quark hash ONLY for the genesis block.
All other blocks use double SHA256 on 112-byte headers.
"""

import sys
from pathlib import Path

# Add project root so "import divi_quark_hash" works when run as py tests/test_quark_hash.py
_root = Path(__file__).resolve().parent.parent
if str(_root) not in sys.path:
    sys.path.insert(0, str(_root))

import pytest
from binascii import hexlify, unhexlify

import divi_quark_hash


class TestVectors:
    """
    Known-good test vectors from the Divi blockchain.
    
    IMPORTANT: Divi uses different hashing for genesis vs other blocks:
    - Genesis block: Quark hash on 80-byte header
    - Other blocks: Double SHA256 on 112-byte header
    
    This library implements the Quark hash, which is only used for genesis.
    """
    
    # Divi Genesis Block (height 0)
    # Raw 80-byte header from: divi-cli getblockheader <hash> false
    # This is the ONLY block that uses Quark hash in Divi!
    GENESIS_HEADER_HEX = (
        "01000000"  # version (1)
        "00000000000000000000000000000000"
        "00000000000000000000000000000000"  # prev_block (zeros)
        "d68b88086910db479631619df8523189"
        "d2b65411cb1701ec2887e6b5c63c80ec"  # merkle_root
        "fc95ab5b"  # timestamp (1537971708)
        "f0ff0f1e"  # bits (1e0ffff0)
        "15710b00"  # nonce (749845)
    )
    GENESIS_HASH = "00000e258596876664989374c7ee36445cf5f4f80889af415cc32478214394ea"
    
    @classmethod
    def get_genesis_header(cls) -> bytes:
        """Get the genesis block header (80 bytes)."""
        return unhexlify(cls.GENESIS_HEADER_HEX)[:80]


class TestQuarkHash:
    """Core functionality tests for Quark hash algorithm."""
    
    def test_genesis_block_hash(self):
        """Verify Divi genesis block produces correct PoW hash.
        
        This is the critical test - Divi only uses Quark hash for genesis.
        """
        header = TestVectors.get_genesis_header()
        result = divi_quark_hash.getPoWHash(header)
        
        # Hash is little-endian, reverse for display
        result_hex = hexlify(result[::-1]).decode('utf-8')
        
        assert result_hex == TestVectors.GENESIS_HASH, (
            f"Genesis block hash mismatch:\n"
            f"  Expected: {TestVectors.GENESIS_HASH}\n"
            f"  Got:      {result_hex}"
        )
    
    def test_output_length(self):
        """Output should always be 32 bytes (256 bits)."""
        header = TestVectors.get_genesis_header()
        result = divi_quark_hash.getPoWHash(header)
        
        assert len(result) == 32, f"Expected 32 bytes, got {len(result)}"
    
    def test_output_is_bytes(self):
        """Output should be a bytes object."""
        header = TestVectors.get_genesis_header()
        result = divi_quark_hash.getPoWHash(header)
        
        assert isinstance(result, bytes), f"Expected bytes, got {type(result)}"
    
    def test_deterministic(self):
        """Same input should always produce same output."""
        header = TestVectors.get_genesis_header()
        
        result1 = divi_quark_hash.getPoWHash(header)
        result2 = divi_quark_hash.getPoWHash(header)
        
        assert result1 == result2, "Hash function is not deterministic"
    
    def test_different_inputs_different_outputs(self):
        """Different inputs should produce different outputs."""
        header1 = TestVectors.get_genesis_header()
        # Modify one byte to create different input
        header2 = bytearray(header1)
        header2[0] ^= 0xFF  # Flip bits in version byte
        header2 = bytes(header2)
        
        result1 = divi_quark_hash.getPoWHash(header1)
        result2 = divi_quark_hash.getPoWHash(header2)
        
        assert result1 != result2, "Different inputs produced same hash"


class TestInputValidation:
    """Input validation and error handling tests."""
    
    def test_accepts_bytes(self):
        """Should accept bytes input."""
        header = TestVectors.get_genesis_header()
        result = divi_quark_hash.getPoWHash(header)
        assert result is not None
    
    def test_rejects_string(self):
        """Should reject string (non-bytes) input."""
        with pytest.raises(TypeError):
            divi_quark_hash.getPoWHash("not bytes")
    
    def test_rejects_none(self):
        """Should reject None input."""
        with pytest.raises(TypeError):
            divi_quark_hash.getPoWHash(None)
    
    def test_rejects_integer(self):
        """Should reject integer input."""
        with pytest.raises(TypeError):
            divi_quark_hash.getPoWHash(12345)
    
    def test_rejects_list(self):
        """Should reject list input."""
        with pytest.raises(TypeError):
            divi_quark_hash.getPoWHash([1, 2, 3])


class TestEdgeCases:
    """Edge case tests."""
    
    def test_empty_bytes(self):
        """Should handle empty bytes input without crashing."""
        # Note: Empty input is not a valid block header,
        # but the function should not crash
        result = divi_quark_hash.getPoWHash(b'')
        assert len(result) == 32
    
    def test_short_input(self):
        """Should handle input shorter than 80 bytes."""
        # Note: Short input is not a valid block header,
        # but the function should not crash
        result = divi_quark_hash.getPoWHash(b'short')
        assert len(result) == 32
    
    def test_long_input(self):
        """Should handle input longer than 80 bytes."""
        header = TestVectors.get_genesis_header()
        long_input = header + b'\x00' * 100
        result = divi_quark_hash.getPoWHash(long_input)
        assert len(result) == 32
    
    def test_all_zeros(self):
        """Should handle all-zero input."""
        zeros = b'\x00' * 80
        result = divi_quark_hash.getPoWHash(zeros)
        assert len(result) == 32
    
    def test_all_ones(self):
        """Should handle all-ones input."""
        ones = b'\xff' * 80
        result = divi_quark_hash.getPoWHash(ones)
        assert len(result) == 32


class TestModuleAttributes:
    """Test module-level attributes and documentation."""
    
    def test_module_has_getpowhash(self):
        """Module should expose getPoWHash function."""
        assert hasattr(divi_quark_hash, 'getPoWHash')
        assert callable(divi_quark_hash.getPoWHash)
    
    def test_module_has_docstring(self):
        """Module should have a docstring."""
        assert divi_quark_hash.__doc__ is not None
        assert len(divi_quark_hash.__doc__) > 0
    
    def test_function_has_docstring(self):
        """getPoWHash function should have a docstring."""
        assert divi_quark_hash.getPoWHash.__doc__ is not None
        assert len(divi_quark_hash.getPoWHash.__doc__) > 0


if __name__ == '__main__':
    pytest.main([__file__, '-v'])

/*
 * Divi Quark Hash - Public API
 * 
 * This is the public header for the Divi Quark hash library.
 * Include this header in your application to use the quark_hash function.
 * 
 * Example:
 *   #include "quark/quark.h"
 *   
 *   char header[80];  // Block header data
 *   char hash[32];    // Output buffer
 *   quark_hash(header, hash);
 * adapted for PIVX by @gpdionisio
 * Originally written by @chaeplin, 
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

#ifndef QUARK_H
#define QUARK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Size constants for external use */
#define QUARK_INPUT_SIZE    80   /* Block header size in bytes */
#define QUARK_DIGEST_SIZE   32   /* Output hash size in bytes */

/*
 * Compute the Quark proof-of-work hash.
 * 
 * The Quark algorithm chains 9 hash operations using 6 different
 * cryptographic primitives (Blake, BMW, Groestl, JH, Keccak, Skein).
 * 
 * IMPORTANT: Divi uses Quark hash ONLY for the genesis block.
 * All other Divi blocks use double SHA256 on 112-byte headers.
 * 
 * Parameters:
 *   input  - Pointer to the block header (80 bytes for genesis)
 *   output - Buffer to receive the hash result (32 bytes)
 * 
 * Note: The caller is responsible for ensuring the output buffer
 *       is at least QUARK_DIGEST_SIZE (32) bytes.
 */
void quark_hash(const char *input, char *output);

#ifdef __cplusplus
}
#endif

#endif /* QUARK_H */

/*
 * Hash Step Abstraction Layer
 * 
 * Provides a consistent interface for all hash primitives used
 * in the Quark algorithm. Each function performs the complete
 * init → update → finalize sequence.
 * 
 * Originally written by @chaeplin, adapted for PIVX by @gpdionisio
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

#ifndef QUARK_HASH_STEP_H
#define QUARK_HASH_STEP_H

#include <stdint.h>
#include <stddef.h>
#include "constants.h"

/*
 * Hash512 - Type alias for a 512-bit hash buffer
 * 16 × uint32_t for Quark intermediate hashes
 */
typedef uint32_t Hash512[HASH_BUFFER_UINT32_LEN];

/*
 * Check if the branch condition is met for a given hash.
 * Returns non-zero if bit 3 of the first word is set.
 * 
 * This determines which hash primitive to use at conditional
 * points in the Quark algorithm.
 */
static inline int quark_should_branch(const Hash512 hash) {
    return (hash[0] & QUARK_BRANCH_MASK) != 0;
}

/*
 * Hash step functions - each performs init → update → finalize
 * These are thin wrappers providing a consistent interface
 * to the underlying SPH (sphlib) implementations.
 * 
 * Parameters:
 *   input  - Pointer to input data
 *   len    - Length of input data in bytes
 *   output - Buffer to receive the 512-bit hash result
 */
void hash_blake512(const void *input, size_t len, Hash512 output);
void hash_bmw512(const void *input, size_t len, Hash512 output);
void hash_groestl512(const void *input, size_t len, Hash512 output);
void hash_jh512(const void *input, size_t len, Hash512 output);
void hash_keccak512(const void *input, size_t len, Hash512 output);
void hash_skein512(const void *input, size_t len, Hash512 output);

#endif /* QUARK_HASH_STEP_H */

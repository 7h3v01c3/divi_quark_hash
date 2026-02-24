/*
 * Quark Hash Algorithm - Internal Header
 * 
 * This header is for internal use within the library.
 * External users should include "quark/quark.h" instead.
 * 
 * Originally written by @chaeplin, adapted for PIVX by @gpdionisio
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

#ifndef QUARK_ALGORITHM_H
#define QUARK_ALGORITHM_H

#include "constants.h"

/*
 * Compute the Quark proof-of-work hash.
 * 
 * The Quark algorithm chains 9 hash operations using 6 different
 * cryptographic primitives (Blake, BMW, Groestl, JH, Keccak, Skein).
 * 
 * Three decision points use bit 3 of intermediate hashes to select
 * between two possible primitives, creating 8 possible execution paths.
 * 
 * Flow:
 *   Blake → BMW → [Groestl|Skein] → Groestl → JH → 
 *   [Blake|BMW] → Keccak → Skein → [Keccak|JH] → Output
 * 
 * Parameters:
 *   input  - Pointer to the block header (80 bytes)
 *   output - Buffer to receive the hash result (32 bytes)
 */
void quark_hash(const char *input, char *output);

#endif /* QUARK_ALGORITHM_H */

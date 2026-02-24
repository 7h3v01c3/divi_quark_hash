/*
 * Quark Hash Algorithm Implementation
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
 * Originally written by @chaeplin, adapted for PIVX by @gpdionisio
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

#include <string.h>
#include "quark_algorithm.h"
#include "hash_step.h"

void quark_hash(const char *input, char *output)
{
    /* Working buffers for intermediate hash values */
    Hash512 state;
    Hash512 next_state;

    /* 
     * Round 1: Blake512
     * Initial compression of the 80-byte block header 
     */
    hash_blake512(input, QUARK_BLOCK_HEADER_SIZE, state);

    /* 
     * Round 2: BMW512
     */
    hash_bmw512(state, QUARK_INTERMEDIATE_SIZE, next_state);

    /* 
     * Round 3: Conditional - Groestl512 or Skein512
     * Branch based on bit 3 of previous hash
     */
    if (quark_should_branch(next_state)) {
        hash_groestl512(next_state, QUARK_INTERMEDIATE_SIZE, state);
    } else {
        hash_skein512(next_state, QUARK_INTERMEDIATE_SIZE, state);
    }

    /* 
     * Round 4: Groestl512
     */
    hash_groestl512(state, QUARK_INTERMEDIATE_SIZE, next_state);

    /* 
     * Round 5: JH512
     */
    hash_jh512(next_state, QUARK_INTERMEDIATE_SIZE, state);

    /* 
     * Round 6: Conditional - Blake512 or BMW512
     */
    if (quark_should_branch(state)) {
        hash_blake512(state, QUARK_INTERMEDIATE_SIZE, next_state);
    } else {
        hash_bmw512(state, QUARK_INTERMEDIATE_SIZE, next_state);
    }

    /* 
     * Round 7: Keccak512
     */
    hash_keccak512(next_state, QUARK_INTERMEDIATE_SIZE, state);

    /* 
     * Round 8: Skein512
     */
    hash_skein512(state, QUARK_INTERMEDIATE_SIZE, next_state);

    /* 
     * Round 9: Conditional - Keccak512 or JH512
     */
    if (quark_should_branch(next_state)) {
        hash_keccak512(next_state, QUARK_INTERMEDIATE_SIZE, state);
    } else {
        hash_jh512(next_state, QUARK_INTERMEDIATE_SIZE, state);
    }

    /* 
     * Output: First 256 bits of final 512-bit hash
     */
    memcpy(output, state, QUARK_OUTPUT_SIZE);
}

/*
 * Quark Hash Algorithm Constants
 * 
 * The Quark algorithm is a chained hash function using 6 different
 * cryptographic primitives with conditional branching based on
 * intermediate hash values.
 * 
 * Originally written by @chaeplin, adapted for PIVX by @gpdionisio
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

#ifndef QUARK_CONSTANTS_H
#define QUARK_CONSTANTS_H

/* Input/Output sizes in bytes */
#define QUARK_BLOCK_HEADER_SIZE     80   /* Standard block header */
#define QUARK_INTERMEDIATE_SIZE     64   /* 512-bit intermediate hash */
#define QUARK_OUTPUT_SIZE           32   /* 256-bit final output */

/* Internal buffer configuration */
#define HASH_BUFFER_UINT32_LEN      16   /* uint32_t[16] = 512 bits */

/* 
 * Branch condition mask
 * The Quark algorithm checks bit 3 of intermediate hashes
 * to determine which primitive to use at decision points.
 * This creates path diversity in the hash computation.
 */
#define QUARK_BRANCH_BIT            3
#define QUARK_BRANCH_MASK           (1u << QUARK_BRANCH_BIT)  /* 0x08 */

/* Number of rounds in the algorithm */
#define QUARK_TOTAL_ROUNDS          9
#define QUARK_CONDITIONAL_ROUNDS    3    /* Rounds with branching */

#endif /* QUARK_CONSTANTS_H */

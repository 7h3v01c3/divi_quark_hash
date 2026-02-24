/*
 * Hash Step Abstraction Layer - Implementation
 * 
 * Wraps the SPH (sphlib) hash primitives with a consistent interface.
 * Each function performs the complete hash operation in one call.
 * 
 * Originally written by @chaeplin, adapted for PIVX by @gpdionisio
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

#include "hash_step.h"

/* SPH library headers */
#include "sph_blake.h"
#include "sph_bmw.h"
#include "sph_groestl.h"
#include "sph_jh.h"
#include "sph_keccak.h"
#include "sph_skein.h"

/*
 * Blake-512 hash step
 */
void hash_blake512(const void *input, size_t len, Hash512 output)
{
    sph_blake512_context ctx;
    sph_blake512_init(&ctx);
    sph_blake512(&ctx, input, len);
    sph_blake512_close(&ctx, output);
}

/*
 * BMW-512 (Blue Midnight Wish) hash step
 */
void hash_bmw512(const void *input, size_t len, Hash512 output)
{
    sph_bmw512_context ctx;
    sph_bmw512_init(&ctx);
    sph_bmw512(&ctx, input, len);
    sph_bmw512_close(&ctx, output);
}

/*
 * Groestl-512 hash step
 */
void hash_groestl512(const void *input, size_t len, Hash512 output)
{
    sph_groestl512_context ctx;
    sph_groestl512_init(&ctx);
    sph_groestl512(&ctx, input, len);
    sph_groestl512_close(&ctx, output);
}

/*
 * JH-512 hash step
 */
void hash_jh512(const void *input, size_t len, Hash512 output)
{
    sph_jh512_context ctx;
    sph_jh512_init(&ctx);
    sph_jh512(&ctx, input, len);
    sph_jh512_close(&ctx, output);
}

/*
 * Keccak-512 hash step
 */
void hash_keccak512(const void *input, size_t len, Hash512 output)
{
    sph_keccak512_context ctx;
    sph_keccak512_init(&ctx);
    sph_keccak512(&ctx, input, len);
    sph_keccak512_close(&ctx, output);
}

/*
 * Skein-512 hash step
 */
void hash_skein512(const void *input, size_t len, Hash512 output)
{
    sph_skein512_context ctx;
    sph_skein512_init(&ctx);
    sph_skein512(&ctx, input, len);
    sph_skein512_close(&ctx, output);
}

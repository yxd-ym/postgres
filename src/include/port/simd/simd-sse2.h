/*-------------------------------------------------------------------------
 *
 * simd-sse2.h
 *	  SIMD support via SSE2 instructions of 64-bit x86.
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/port/simd/simd-sse2.h
 *
 *-------------------------------------------------------------------------
 */

#ifndef _INSIDE_SIMD_H
#error "should be included via simd.h"
#endif

#define _INSIDE_SIMD_IMPLEMENTATION

#include <emmintrin.h>
typedef __m128i Vector8;
typedef __m128i Vector32;

#include "port/simd/simd_funcs.h"

static inline void
vector8_load(Vector8 *v, const uint8 *s)
{
    *v = _mm_loadu_si128((const __m128i *) s);
}

static inline void
vector32_load(Vector32 *v, const uint32 *s)
{
    *v = _mm_loadu_si128((const __m128i *) s);
}

static inline Vector8
vector8_broadcast(const uint8 c)
{
    return _mm_set1_epi8(c);
}

static inline Vector32
vector32_broadcast(const uint32 c)
{
    return _mm_set1_epi32(c);
}

static inline bool
vector8_has(const Vector8 v, const uint8 c)
{
    return vector8_is_highbit_set(vector8_eq(v, vector8_broadcast(c)));
}

static inline bool
vector8_has_zero(const Vector8 v)
{
    return vector8_has(v, 0);
}

static inline bool
vector8_has_le(const Vector8 v, const uint8 c)
{
    return vector8_has_zero(vector8_ssub(v, vector8_broadcast(c)));
}

static inline bool
vector8_is_highbit_set(const Vector8 v)
{
    return _mm_movemask_epi8(v) != 0;
}

static inline uint32
vector8_highbit_mask(const Vector8 v)
{
    return (uint32) _mm_movemask_epi8(v);
}

static inline bool
vector32_is_highbit_set(const Vector32 v)
{
    return vector8_is_highbit_set(v);
}

static inline Vector8
vector8_or(const Vector8 v1, const Vector8 v2)
{
    return _mm_or_si128(v1, v2);
}

static inline Vector32
vector32_or(const Vector32 v1, const Vector32 v2)
{
    return _mm_or_si128(v1, v2);
}

static inline Vector8
vector8_ssub(const Vector8 v1, const Vector8 v2)
{
    return _mm_subs_epu8(v1, v2);
}

static inline Vector8
vector8_eq(const Vector8 v1, const Vector8 v2)
{
    return _mm_cmpeq_epi8(v1, v2);
}

static inline Vector8
vector8_min(const Vector8 v1, const Vector8 v2)
{
    return _mm_min_epu8(v1, v2);
}

static inline Vector32
vector32_eq(const Vector32 v1, const Vector32 v2)
{
    return _mm_cmpeq_epi32(v1, v2);
}

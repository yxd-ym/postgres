#ifndef INSIDE_SIMD_H
#error "should be included via simd.h"
#endif

/*
 * If no SIMD instructions are available, we can in some cases emulate vector
 * operations using bitwise operations on unsigned integers.  Note that many
 * of the functions in this file presently do not have non-SIMD
 * implementations.  In particular, none of the functions involving Vector32
 * are implemented without SIMD since it's likely not worthwhile to represent
 * two 32-bit integers using a uint64.
 */
#define USE_NO_SIMD
typedef uint64 Vector8;

#include "port/simd/simd_funcs.h"

static inline void
vector8_load(Vector8 *v, const uint8 *s)
{
    memcpy(v, s, sizeof(Vector8));
}

static inline Vector8
vector8_broadcast(const uint8 c)
{
    return ~UINT64CONST(0) / 0xFF * c;
}

static inline bool
vector8_has(const Vector8 v, const uint8 c)
{
    return vector8_has_zero(v ^ vector8_broadcast(c));
}

static inline bool
vector8_has_zero(const Vector8 v)
{
    return vector8_has_le(v, 0);
}

static inline bool
vector8_has_le(const Vector8 v, const uint8 c)
{
    bool		result = false;

	/*
	 * To find bytes <= c, we can use bitwise operations to find bytes < c+1,
	 * but it only works if c+1 <= 128 and if the highest bit in v is not set.
	 * Adapted from
	 * https://graphics.stanford.edu/~seander/bithacks.html#HasLessInWord
	 */
	if ((int64) v >= 0 && c < 0x80)
		result = (v - vector8_broadcast(c + 1)) & ~v & vector8_broadcast(0x80);
	else
	{
		/* one byte at a time */
		for (Size i = 0; i < sizeof(Vector8); i++)
		{
			if (((const uint8 *) &v)[i] <= c)
			{
				result = true;
				break;
			}
		}
	}

    return result;
}

static inline bool
vector8_is_highbit_set(const Vector8 v)
{
    return v & vector8_broadcast(0x80);
}

static inline Vector8
vector8_or(const Vector8 v1, const Vector8 v2)
{
    return v1 | v2;
}

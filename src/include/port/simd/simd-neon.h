#ifndef INSIDE_SIMD_H
#error "should be included via simd.h"
#endif

/*
 * We use the Neon instructions if the compiler provides access to them (as
 * indicated by __ARM_NEON) and we are on aarch64.  While Neon support is
 * technically optional for aarch64, it appears that all available 64-bit
 * hardware does have it.  Neon exists in some 32-bit hardware too, but we
 * could not realistically use it there without a run-time check, which seems
 * not worth the trouble for now.
 */
#include <arm_neon.h>
typedef uint8x16_t Vector8;
typedef uint32x4_t Vector32;

#include "port/simd/simd_funcs.h"

static inline void
vector8_load(Vector8 *v, const uint8 *s)
{
    *v = vld1q_u8(s);
}

static inline void
vector32_load(Vector32 *v, const uint32 *s)
{
    *v = vld1q_u32(s);
}

static inline Vector8
vector8_broadcast(const uint8 c)
{
    return vdupq_n_u8(c);
}

static inline Vector32
vector32_broadcast(const uint32 c)
{
    return vdupq_n_u32(c);
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
    return vmaxvq_u8(v) > 0x7F;
}

static inline uint32
vector8_highbit_mask(const Vector8 v)
{
    /*
     * Note: It would be faster to use vget_lane_u64 and vshrn_n_u16, but that
     * returns a uint64, making it inconvenient to combine mask values from
     * multiple vectors.
     */
    static const uint8 mask[16] = {
        1 << 0, 1 << 1, 1 << 2, 1 << 3,
        1 << 4, 1 << 5, 1 << 6, 1 << 7,
        1 << 0, 1 << 1, 1 << 2, 1 << 3,
        1 << 4, 1 << 5, 1 << 6, 1 << 7,
    };

    uint8x16_t	masked = vandq_u8(vld1q_u8(mask), (uint8x16_t) vshrq_n_s8((int8x16_t) v, 7));
    uint8x16_t	maskedhi = vextq_u8(masked, masked, 8);

    return (uint32) vaddvq_u16((uint16x8_t) vzip1q_u8(masked, maskedhi));
}

static inline bool
vector32_is_highbit_set(const Vector32 v)
{
    return vector8_is_highbit_set((Vector8) v);
}

static inline Vector8
vector8_or(const Vector8 v1, const Vector8 v2)
{
    return vorrq_u8(v1, v2);
}

static inline Vector32
vector32_or(const Vector32 v1, const Vector32 v2)
{
    return vorrq_u32(v1, v2);
}

static inline Vector8
vector8_ssub(const Vector8 v1, const Vector8 v2)
{
    return vqsubq_u8(v1, v2);
}

static inline Vector8
vector8_eq(const Vector8 v1, const Vector8 v2)
{
    return vceqq_u8(v1, v2);
}

static inline Vector8
vector8_min(const Vector8 v1, const Vector8 v2)
{
    return vminq_u8(v1, v2);
}

static inline Vector32
vector32_eq(const Vector32 v1, const Vector32 v2)
{
    return vceqq_u32(v1, v2);
}


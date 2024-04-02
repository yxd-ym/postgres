#ifndef INSIDE_SIMD_H
#error "should be included via simd.h"
#endif

/*
 *
 */
#include <lsxintrin.h>
typedef __m128i Vector8;
typedef __m128i Vector32;

#include "port/simd/simd_funcs.h"

static inline void
vector8_load(Vector8 *v, const uint8 *s)
{
    *v = __lsx_vld(s, 0);
}

static inline void
vector32_load(Vector32 *v, const uint32 *s)
{
    *v = __lsx_vld(s, 0);
}

static inline Vector8
vector8_broadcast(const uint8 c)
{
    return __lsx_vldrepl_b(&c, 0);
}

static inline Vector32
vector32_broadcast(const uint32 c)
{
    return __lsx_vldrepl_w(&c, 0);
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
    return __lsx_vpickve2gr_h(__lsx_vmskltz_b(v), 0) != 0;
}

static inline uint32
vector8_highbit_mask(const Vector8 v)
{
    return (uint32) __lsx_vpickve2gr_h(__lsx_vmskltz_b(v), 0);
}

static inline bool
vector32_is_highbit_set(const Vector32 v)
{
    return __lsx_vpickve2gr_h(__lsx_vmskltz_w(v), 0) != 0;
}

static inline Vector8
vector8_or(const Vector8 v1, const Vector8 v2)
{
    return __lsx_vor_v(v1, v2);
}

static inline Vector32
vector32_or(const Vector32 v1, const Vector32 v2)
{
    return __lsx_vor_v(v1, v2);
}

static inline Vector8
vector8_ssub(const Vector8 v1, const Vector8 v2)
{
    return __lsx_vssub_bu(v1, v2);
}

static inline Vector8
vector8_eq(const Vector8 v1, const Vector8 v2)
{
    return __lsx_vseq_b(v1, v2);
}

static inline Vector8
vector8_min(const Vector8 v1, const Vector8 v2)
{
    return __lsx_vmin_bu(v1, v2);
}

static inline Vector32
vector32_eq(const Vector32 v1, const Vector32 v2)
{
    return __lsx_vseq_w(v1, v2);
}

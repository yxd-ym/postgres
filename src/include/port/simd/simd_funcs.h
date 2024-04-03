/*-------------------------------------------------------------------------
 *
 * simd_funcs.h
 *	  Declaration of functions of platform-specific vector operations.
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/port/simd/simd_funcs.h
 *
 *-------------------------------------------------------------------------
 */

#ifndef _INSIDE_SIMD_IMPLEMENTATION
#error "should be included in one of the simd implementation header file"
#endif

/* load/store operations */

/*
 * Load a chunk of memory into the given vector.
 */
static inline void vector8_load(Vector8 *v, const uint8 *s);

#ifndef USE_NO_SIMD
/*
 * Load a chunk of memory into the given vector.
 */
static inline void vector32_load(Vector32 *v, const uint32 *s);
#endif


/* assignment operations */

/*
 * Create a vector with all elements set to the same value.
 */
static inline Vector8 vector8_broadcast(const uint8 c);

#ifndef USE_NO_SIMD
/*
 * Create a vector with all elements set to the same value.
 */
static inline Vector32 vector32_broadcast(const uint32 c);
#endif


/* element-wise comparisons to a scalar */

/*
 * Return true if any elements in the vector are equal to the given scalar.
 */
static inline bool vector8_has(const Vector8 v, const uint8 c);

/*
 * Convenience function equivalent to vector8_has(v, 0)
 */
static inline bool vector8_has_zero(const Vector8 v);

/*
 * Return true if any elements in the vector are less than or equal to the
 * given scalar.
 */
static inline bool vector8_has_le(const Vector8 v, const uint8 c);

/*
 * Return true if the high bit of any element is set
 */
static inline bool vector8_is_highbit_set(const Vector8 v);

#ifndef USE_NO_SIMD
/*
 * Return a bitmask formed from the high-bit of each element.
 */
static inline uint32 vector8_highbit_mask(const Vector8 v);

/*
 * Exactly like vector8_is_highbit_set except for the input type, so it
 * looks at each byte separately.
 *
 * XXX x86 uses the same underlying type for 8-bit, 16-bit, and 32-bit
 * integer elements, but Arm does not, hence the need for a separate
 * function. We could instead adopt the behavior of Arm's vmaxvq_u32(), i.e.
 * check each 32-bit element, but that would require an additional mask
 * operation on x86.
 */
static inline bool vector32_is_highbit_set(const Vector32 v);
#endif


/* arithmetic operations */

/*
 * Return the bitwise OR of the inputs
 */
static inline Vector8 vector8_or(const Vector8 v1, const Vector8 v2);

#ifndef USE_NO_SIMD
/*
 * Return the bitwise OR of the inputs
 */
static inline Vector32 vector32_or(const Vector32 v1, const Vector32 v2);

/*
 * Return the result of subtracting the respective elements of the input
 * vectors using saturation (i.e., if the operation would yield a value less
 * than zero, zero is returned instead).  For more information on saturation
 * arithmetic, see https://en.wikipedia.org/wiki/Saturation_arithmetic
 */
static inline Vector8 vector8_ssub(const Vector8 v1, const Vector8 v2);
#endif


/*
 * comparisons between vectors
 *
 * Note: These return a vector rather than boolean, which is why we don't
 * have non-SIMD implementations.
 */
#ifndef USE_NO_SIMD
/*
 * Return a vector with all bits set in each lane where the corresponding
 * lanes in the inputs are equal.
 */
static inline Vector8 vector8_eq(const Vector8 v1, const Vector8 v2);

/*
 * Given two vectors, return a vector with the minimum element of each.
 */
static inline Vector8 vector8_min(const Vector8 v1, const Vector8 v2);

/*
 * Return a vector with all bits set in each lane where the corresponding
 * lanes in the inputs are equal.
 */
static inline Vector32 vector32_eq(const Vector32 v1, const Vector32 v2);
#endif

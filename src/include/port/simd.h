/*-------------------------------------------------------------------------
 *
 * simd.h
 *	  Support for platform-specific vector operations.
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/port/simd.h
 *
 * NOTES
 * - VectorN in this file refers to a register where the element operands
 * are N bits wide. The vector width is platform-specific, so users that care
 * about that will need to inspect "sizeof(VectorN)".
 *
 *-------------------------------------------------------------------------
 */
#ifndef SIMD_H
#define SIMD_H

#define INSIDE_SIMD_H

#if (defined(__x86_64__) || defined(_M_AMD64))
#include "port/simd/simd-sse2.h"
#elif defined(__aarch64__) && defined(__ARM_NEON)
#include "port/simd/simd-neon.h"
#elif defined(__loongarch__) && defined(__loongarch_sx)
#include "port/simd/simd-lsx.h"
#else
#include "port/simd/simd-none.h"
#endif

#endif							/* SIMD_H */

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
 * - VectorN used in SIMD implementation refers to a register where the
 * element operands are N bits wide. The vector width is platform-specific,
 * so users that care about that will need to inspect "sizeof(VectorN)".
 *
 *-------------------------------------------------------------------------
 */
#ifndef SIMD_H
#define SIMD_H

/*
 * Make sure SIMD related headers are included from this file.
 */
#define _INSIDE_SIMD_H

#if (defined(__x86_64__) || defined(_M_AMD64))
/*
 * SSE2 instructions are part of the spec for the 64-bit x86 ISA. We assume
 * that compilers targeting this architecture understand SSE2 intrinsics.
 *
 * We use emmintrin.h rather than the comprehensive header immintrin.h in
 * order to exclude extensions beyond SSE2. This is because MSVC, at least,
 * will allow the use of intrinsics that haven't been enabled at compile
 * time.
 */
#include "port/simd/simd-sse2.h"
#elif defined(__aarch64__) && defined(__ARM_NEON)
/*
 * We use the Neon instructions if the compiler provides access to them (as
 * indicated by __ARM_NEON) and we are on aarch64.  While Neon support is
 * technically optional for aarch64, it appears that all available 64-bit
 * hardware does have it.  Neon exists in some 32-bit hardware too, but we
 * could not realistically use it there without a run-time check, which seems
 * not worth the trouble for now.
 */
#include "port/simd/simd-neon.h"
#elif defined(__loongarch__) && defined(__loongarch_sx)
/*
 * We use the LSX instructions if the compiler provides access to them
 * (as indicated by __loongarch_sx) and we are on loongarch64.
 * See the following documentation for how to enable LSX:
 * - https://gcc.gnu.org/onlinedocs/gcc/LoongArch-Options.html#index-ml_005ba_005dsx
 * - https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-mlsx
 */
#include "port/simd/simd-lsx.h"
#else
/*
 * If no SIMD instructions are available, we can in some cases emulate vector
 * operations using bitwise operations on unsigned integers.  Note that many
 * of the functions in this file presently do not have non-SIMD
 * implementations.  In particular, none of the functions involving Vector32
 * are implemented without SIMD since it's likely not worthwhile to represent
 * two 32-bit integers using a uint64.
 */
#include "port/simd/simd-none.h"
#endif

#endif							/* SIMD_H */

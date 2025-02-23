/// @ref core
/// @file glm/glm.hpp
///
/// @defgroup core Core features
///
/// @brief Features that implement in C++ the GLSL specification as closely as possible.
///
/// The GLM core consists of C++ types that mirror GLSL types and
/// C++ functions that mirror the GLSL functions.
///
/// The best documentation for GLM Core is the current GLSL specification,
/// <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.clean.pdf">version 4.2
/// (pdf file)</a>.
///
/// GLM core functionalities require <glm/glm.hpp> to be included to be used.
///
///
/// @defgroup core_vector Vector types
///
/// Vector types of two to four components with an exhaustive set of operators.
///
/// @ingroup core
///
///
/// @defgroup core_vector_precision Vector types with precision qualifiers
///
/// @brief Vector types with precision qualifiers which may result in various precision in term of ULPs
///
/// GLSL allows defining qualifiers for particular variables.
/// With OpenGL's GLSL, these qualifiers have no effect; they are there for compatibility,
/// with OpenGL ES's GLSL, these qualifiers do have an effect.
///
/// C++ has no language equivalent to qualifier qualifiers. So GLM provides the next-best thing:
/// a number of typedefs that use a particular qualifier.
///
/// None of these types make any guarantees about the actual qualifier used.
///
/// @ingroup core
///
///
/// @defgroup core_matrix Matrix types
///
/// Matrix types of with C columns and R rows where C and R are values between 2 to 4 included.
/// These types have exhaustive sets of operators.
///
/// @ingroup core
///
///
/// @defgroup core_matrix_precision Matrix types with precision qualifiers
///
/// @brief Matrix types with precision qualifiers which may result in various precision in term of ULPs
///
/// GLSL allows defining qualifiers for particular variables.
/// With OpenGL's GLSL, these qualifiers have no effect; they are there for compatibility,
/// with OpenGL ES's GLSL, these qualifiers do have an effect.
///
/// C++ has no language equivalent to qualifier qualifiers. So GLM provides the next-best thing:
/// a number of typedefs that use a particular qualifier.
///
/// None of these types make any guarantees about the actual qualifier used.
///
/// @ingroup core
///
///
/// @defgroup ext Stable extensions
///
/// @brief Additional features not specified by GLSL specification.
///
/// EXT extensions are fully tested and documented.
///
/// Even if it's highly unrecommended, it's possible to include all the extensions at once by
/// including <glm/ext.hpp>. Otherwise, each extension needs to be included  a specific file.
///
///
/// @defgroup gtc Recommended extensions
///
/// @brief Additional features not specified by GLSL specification.
///
/// GTC extensions aim to be stable with tests and documentation.
///
/// Even if it's highly unrecommended, it's possible to include all the extensions at once by
/// including <glm/ext.hpp>. Otherwise, each extension needs to be included  a specific file.
///
///
/// @defgroup gtx Experimental extensions
///
/// @brief Experimental features not specified by GLSL specification.
///
/// Experimental extensions are useful functions and types, but the development of
/// their API and functionality is not necessarily stable. They can change
/// substantially between versions. Backwards compatibility is not much of an issue
/// for them.
///
/// Even if it's highly unrecommended, it's possible to include all the extensions
/// at once by including <glm/ext.hpp>. Otherwise, each extension needs to be
/// included  a specific file.
///
/// @mainpage OpenGL Mathematics (GLM)
/// - Website: <a href="https://glm.g-truc.net">glm.g-truc.net</a>
/// - <a href="modules.html">GLM API documentation</a>
/// - <a href="https://github.com/g-truc/glm/blob/master/manual.md">GLM Manual</a>

// todo go through and add #define directives for various files that get included from this and other glm stuff

#pragma once

// ---------- #include "detail/_fixes.hpp" ----------

#include <cmath>

//! Workaround for compatibility with other libraries
#ifdef max
#undef max
#endif

//! Workaround for compatibility with other libraries
#ifdef min
#undef min
#endif

//! Workaround for Android
#ifdef isnan
#undef isnan
#endif

//! Workaround for Android
#ifdef isinf
#undef isinf
#endif

//! Workaround for Chrone Native Client
#ifdef log2
#undef log2
#endif

// --------------------------------------------------

// ---------- #include "detail/setup.hpp" ----------

#ifndef GLM_SETUP_INCLUDED

#include <cassert>
#include <cstddef>

#define GLM_VERSION_MAJOR			0
#define GLM_VERSION_MINOR			9
#define GLM_VERSION_PATCH			9
#define GLM_VERSION_REVISION		8
#define GLM_VERSION					998
#define GLM_VERSION_MESSAGE			"GLM: version 0.9.9.8"

#define GLM_SETUP_INCLUDED			GLM_VERSION

///////////////////////////////////////////////////////////////////////////////////
// Active states

#define GLM_DISABLE		0
#define GLM_ENABLE		1

///////////////////////////////////////////////////////////////////////////////////
// Messages

#if defined(GLM_FORCE_MESSAGES)
#	define GLM_MESSAGES GLM_ENABLE
#else
#	define GLM_MESSAGES GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Detect the platform

///////////////////////////////////////////////////////////////////////////////////
// Platform

#define GLM_PLATFORM_UNKNOWN		0x00000000
#define GLM_PLATFORM_WINDOWS		0x00010000
#define GLM_PLATFORM_LINUX			0x00020000
#define GLM_PLATFORM_APPLE			0x00040000
//#define GLM_PLATFORM_IOS			0x00080000
#define GLM_PLATFORM_ANDROID		0x00100000
#define GLM_PLATFORM_CHROME_NACL	0x00200000
#define GLM_PLATFORM_UNIX			0x00400000
#define GLM_PLATFORM_QNXNTO			0x00800000
#define GLM_PLATFORM_WINCE			0x01000000
#define GLM_PLATFORM_CYGWIN			0x02000000

#ifdef GLM_FORCE_PLATFORM_UNKNOWN
#	define GLM_PLATFORM GLM_PLATFORM_UNKNOWN
#elif defined(__CYGWIN__)
#	define GLM_PLATFORM GLM_PLATFORM_CYGWIN
#elif defined(__QNXNTO__)
#	define GLM_PLATFORM GLM_PLATFORM_QNXNTO
#elif defined(__APPLE__)
#	define GLM_PLATFORM GLM_PLATFORM_APPLE
#elif defined(WINCE)
#	define GLM_PLATFORM GLM_PLATFORM_WINCE
#elif defined(_WIN32)
#	define GLM_PLATFORM GLM_PLATFORM_WINDOWS
#elif defined(__native_client__)
#	define GLM_PLATFORM GLM_PLATFORM_CHROME_NACL
#elif defined(__ANDROID__)
#	define GLM_PLATFORM GLM_PLATFORM_ANDROID
#elif defined(__linux)
#	define GLM_PLATFORM GLM_PLATFORM_LINUX
#elif defined(__unix)
#	define GLM_PLATFORM GLM_PLATFORM_UNIX
#else
#	define GLM_PLATFORM GLM_PLATFORM_UNKNOWN
#endif//

///////////////////////////////////////////////////////////////////////////////////
// Compiler

#define GLM_COMPILER_UNKNOWN		0x00000000

// Intel
#define GLM_COMPILER_INTEL			0x00100000
#define GLM_COMPILER_INTEL14		0x00100040
#define GLM_COMPILER_INTEL15		0x00100050
#define GLM_COMPILER_INTEL16		0x00100060
#define GLM_COMPILER_INTEL17		0x00100070

// Visual C++ defines
#define GLM_COMPILER_VC				0x01000000
#define GLM_COMPILER_VC12			0x01000001
#define GLM_COMPILER_VC14			0x01000002
#define GLM_COMPILER_VC15			0x01000003
#define GLM_COMPILER_VC15_3			0x01000004
#define GLM_COMPILER_VC15_5			0x01000005
#define GLM_COMPILER_VC15_6			0x01000006
#define GLM_COMPILER_VC15_7			0x01000007
#define GLM_COMPILER_VC15_8			0x01000008
#define GLM_COMPILER_VC15_9			0x01000009
#define GLM_COMPILER_VC16			0x0100000A

// GCC defines
#define GLM_COMPILER_GCC			0x02000000
#define GLM_COMPILER_GCC46			0x020000D0
#define GLM_COMPILER_GCC47			0x020000E0
#define GLM_COMPILER_GCC48			0x020000F0
#define GLM_COMPILER_GCC49			0x02000100
#define GLM_COMPILER_GCC5			0x02000200
#define GLM_COMPILER_GCC6			0x02000300
#define GLM_COMPILER_GCC7			0x02000400
#define GLM_COMPILER_GCC8			0x02000500

// CUDA
#define GLM_COMPILER_CUDA			0x10000000
#define GLM_COMPILER_CUDA75			0x10000001
#define GLM_COMPILER_CUDA80			0x10000002
#define GLM_COMPILER_CUDA90			0x10000004

// SYCL
#define GLM_COMPILER_SYCL			0x00300000

// Clang
#define GLM_COMPILER_CLANG			0x20000000
#define GLM_COMPILER_CLANG34		0x20000050
#define GLM_COMPILER_CLANG35		0x20000060
#define GLM_COMPILER_CLANG36		0x20000070
#define GLM_COMPILER_CLANG37		0x20000080
#define GLM_COMPILER_CLANG38		0x20000090
#define GLM_COMPILER_CLANG39		0x200000A0
#define GLM_COMPILER_CLANG40		0x200000B0
#define GLM_COMPILER_CLANG41		0x200000C0
#define GLM_COMPILER_CLANG42		0x200000D0

// Build model
#define GLM_MODEL_32				0x00000010
#define GLM_MODEL_64				0x00000020

// Force generic C++ compiler
#ifdef GLM_FORCE_COMPILER_UNKNOWN
#	define GLM_COMPILER GLM_COMPILER_UNKNOWN

#elif defined(__INTEL_COMPILER)
#	if __INTEL_COMPILER >= 1700
#		define GLM_COMPILER GLM_COMPILER_INTEL17
#	elif __INTEL_COMPILER >= 1600
#		define GLM_COMPILER GLM_COMPILER_INTEL16
#	elif __INTEL_COMPILER >= 1500
#		define GLM_COMPILER GLM_COMPILER_INTEL15
#	elif __INTEL_COMPILER >= 1400
#		define GLM_COMPILER GLM_COMPILER_INTEL14
#	elif __INTEL_COMPILER < 1400
#		error "GLM requires ICC 2013 SP1 or newer"
#	endif

// CUDA
#elif defined(__CUDACC__)
#	if !defined(CUDA_VERSION) && !defined(GLM_FORCE_CUDA)
#		include <cuda.h>  // make sure version is defined since nvcc does not define it itself!
#	endif
#	if CUDA_VERSION >= 8000
#		define GLM_COMPILER GLM_COMPILER_CUDA80
#	elif CUDA_VERSION >= 7500
#		define GLM_COMPILER GLM_COMPILER_CUDA75
#	elif CUDA_VERSION >= 7000
#		define GLM_COMPILER GLM_COMPILER_CUDA70
#	elif CUDA_VERSION < 7000
#		error "GLM requires CUDA 7.0 or higher"
#	endif

// SYCL
#elif defined(__SYCL_DEVICE_ONLY__)
#	define GLM_COMPILER GLM_COMPILER_SYCL

// Clang
#elif defined(__clang__)
#	if defined(__apple_build_version__)
#		if (__clang_major__ < 6)
#			error "GLM requires Clang 3.4 / Apple Clang 6.0 or higher"
#		elif __clang_major__ == 6 && __clang_minor__ == 0
#			define GLM_COMPILER GLM_COMPILER_CLANG35
#		elif __clang_major__ == 6 && __clang_minor__ >= 1
#			define GLM_COMPILER GLM_COMPILER_CLANG36
#		elif __clang_major__ >= 7
#			define GLM_COMPILER GLM_COMPILER_CLANG37
#		endif
#	else
#		if ((__clang_major__ == 3) && (__clang_minor__ < 4)) || (__clang_major__ < 3)
#			error "GLM requires Clang 3.4 or higher"
#		elif __clang_major__ == 3 && __clang_minor__ == 4
#			define GLM_COMPILER GLM_COMPILER_CLANG34
#		elif __clang_major__ == 3 && __clang_minor__ == 5
#			define GLM_COMPILER GLM_COMPILER_CLANG35
#		elif __clang_major__ == 3 && __clang_minor__ == 6
#			define GLM_COMPILER GLM_COMPILER_CLANG36
#		elif __clang_major__ == 3 && __clang_minor__ == 7
#			define GLM_COMPILER GLM_COMPILER_CLANG37
#		elif __clang_major__ == 3 && __clang_minor__ == 8
#			define GLM_COMPILER GLM_COMPILER_CLANG38
#		elif __clang_major__ == 3 && __clang_minor__ >= 9
#			define GLM_COMPILER GLM_COMPILER_CLANG39
#		elif __clang_major__ == 4 && __clang_minor__ == 0
#			define GLM_COMPILER GLM_COMPILER_CLANG40
#		elif __clang_major__ == 4 && __clang_minor__ == 1
#			define GLM_COMPILER GLM_COMPILER_CLANG41
#		elif __clang_major__ == 4 && __clang_minor__ >= 2
#			define GLM_COMPILER GLM_COMPILER_CLANG42
#		elif __clang_major__ >= 4
#			define GLM_COMPILER GLM_COMPILER_CLANG42
#		endif
#	endif

// Visual C++
#elif defined(_MSC_VER)
#	if _MSC_VER >= 1920
#		define GLM_COMPILER GLM_COMPILER_VC16
#	elif _MSC_VER >= 1916
#		define GLM_COMPILER GLM_COMPILER_VC15_9
#	elif _MSC_VER >= 1915
#		define GLM_COMPILER GLM_COMPILER_VC15_8
#	elif _MSC_VER >= 1914
#		define GLM_COMPILER GLM_COMPILER_VC15_7
#	elif _MSC_VER >= 1913
#		define GLM_COMPILER GLM_COMPILER_VC15_6
#	elif _MSC_VER >= 1912
#		define GLM_COMPILER GLM_COMPILER_VC15_5
#	elif _MSC_VER >= 1911
#		define GLM_COMPILER GLM_COMPILER_VC15_3
#	elif _MSC_VER >= 1910
#		define GLM_COMPILER GLM_COMPILER_VC15
#	elif _MSC_VER >= 1900
#		define GLM_COMPILER GLM_COMPILER_VC14
#	elif _MSC_VER >= 1800
#		define GLM_COMPILER GLM_COMPILER_VC12
#	elif _MSC_VER < 1800
#		error "GLM requires Visual C++ 12 - 2013 or higher"
#	endif//_MSC_VER

// G++
#elif defined(__GNUC__) || defined(__MINGW32__)
#	if __GNUC__ >= 8
#		define GLM_COMPILER GLM_COMPILER_GCC8
#	elif __GNUC__ >= 7
#		define GLM_COMPILER GLM_COMPILER_GCC7
#	elif __GNUC__ >= 6
#		define GLM_COMPILER GLM_COMPILER_GCC6
#	elif __GNUC__ >= 5
#		define GLM_COMPILER GLM_COMPILER_GCC5
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 9
#		define GLM_COMPILER GLM_COMPILER_GCC49
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 8
#		define GLM_COMPILER GLM_COMPILER_GCC48
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 7
#		define GLM_COMPILER GLM_COMPILER_GCC47
#	elif __GNUC__ == 4 && __GNUC_MINOR__ >= 6
#		define GLM_COMPILER GLM_COMPILER_GCC46
#	elif ((__GNUC__ == 4) && (__GNUC_MINOR__ < 6)) || (__GNUC__ < 4)
#		error "GLM requires GCC 4.6 or higher"
#	endif

#else
#	define GLM_COMPILER GLM_COMPILER_UNKNOWN
#endif

#ifndef GLM_COMPILER
#	error "GLM_COMPILER undefined, your compiler may not be supported by GLM. Add #define GLM_COMPILER 0 to ignore this message."
#endif//GLM_COMPILER

///////////////////////////////////////////////////////////////////////////////////
// Instruction sets

// User defines: GLM_FORCE_PURE GLM_FORCE_INTRINSICS GLM_FORCE_SSE2 GLM_FORCE_SSE3 GLM_FORCE_AVX GLM_FORCE_AVX2 GLM_FORCE_AVX2

#define GLM_ARCH_MIPS_BIT	  (0x10000000)
#define GLM_ARCH_PPC_BIT	  (0x20000000)
#define GLM_ARCH_ARM_BIT	  (0x40000000)
#define GLM_ARCH_ARMV8_BIT  (0x01000000)
#define GLM_ARCH_X86_BIT	  (0x80000000)

#define GLM_ARCH_SIMD_BIT	(0x00001000)

#define GLM_ARCH_NEON_BIT	(0x00000001)
#define GLM_ARCH_SSE_BIT	(0x00000002)
#define GLM_ARCH_SSE2_BIT	(0x00000004)
#define GLM_ARCH_SSE3_BIT	(0x00000008)
#define GLM_ARCH_SSSE3_BIT	(0x00000010)
#define GLM_ARCH_SSE41_BIT	(0x00000020)
#define GLM_ARCH_SSE42_BIT	(0x00000040)
#define GLM_ARCH_AVX_BIT	(0x00000080)
#define GLM_ARCH_AVX2_BIT	(0x00000100)

#define GLM_ARCH_UNKNOWN	(0)
#define GLM_ARCH_X86		(GLM_ARCH_X86_BIT)
#define GLM_ARCH_SSE		(GLM_ARCH_SSE_BIT | GLM_ARCH_SIMD_BIT | GLM_ARCH_X86)
#define GLM_ARCH_SSE2		(GLM_ARCH_SSE2_BIT | GLM_ARCH_SSE)
#define GLM_ARCH_SSE3		(GLM_ARCH_SSE3_BIT | GLM_ARCH_SSE2)
#define GLM_ARCH_SSSE3		(GLM_ARCH_SSSE3_BIT | GLM_ARCH_SSE3)
#define GLM_ARCH_SSE41		(GLM_ARCH_SSE41_BIT | GLM_ARCH_SSSE3)
#define GLM_ARCH_SSE42		(GLM_ARCH_SSE42_BIT | GLM_ARCH_SSE41)
#define GLM_ARCH_AVX		(GLM_ARCH_AVX_BIT | GLM_ARCH_SSE42)
#define GLM_ARCH_AVX2		(GLM_ARCH_AVX2_BIT | GLM_ARCH_AVX)
#define GLM_ARCH_ARM		(GLM_ARCH_ARM_BIT)
#define GLM_ARCH_ARMV8		(GLM_ARCH_NEON_BIT | GLM_ARCH_SIMD_BIT | GLM_ARCH_ARM | GLM_ARCH_ARMV8_BIT)
#define GLM_ARCH_NEON		(GLM_ARCH_NEON_BIT | GLM_ARCH_SIMD_BIT | GLM_ARCH_ARM)
#define GLM_ARCH_MIPS		(GLM_ARCH_MIPS_BIT)
#define GLM_ARCH_PPC		(GLM_ARCH_PPC_BIT)

#if defined(GLM_FORCE_ARCH_UNKNOWN) || defined(GLM_FORCE_PURE)
#	define GLM_ARCH GLM_ARCH_UNKNOWN
#elif defined(GLM_FORCE_NEON)
#	if __ARM_ARCH >= 8
#		define GLM_ARCH (GLM_ARCH_ARMV8)
#	else
#		define GLM_ARCH (GLM_ARCH_NEON)
#	endif
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_AVX2)
#	define GLM_ARCH (GLM_ARCH_AVX2)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_AVX)
#	define GLM_ARCH (GLM_ARCH_AVX)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_SSE42)
#	define GLM_ARCH (GLM_ARCH_SSE42)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_SSE41)
#	define GLM_ARCH (GLM_ARCH_SSE41)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_SSSE3)
#	define GLM_ARCH (GLM_ARCH_SSSE3)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_SSE3)
#	define GLM_ARCH (GLM_ARCH_SSE3)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_SSE2)
#	define GLM_ARCH (GLM_ARCH_SSE2)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_SSE)
#	define GLM_ARCH (GLM_ARCH_SSE)
#	define GLM_FORCE_INTRINSICS
#elif defined(GLM_FORCE_INTRINSICS) && !defined(GLM_FORCE_XYZW_ONLY)
#	if defined(__AVX2__)
#		define GLM_ARCH (GLM_ARCH_AVX2)
#	elif defined(__AVX__)
#		define GLM_ARCH (GLM_ARCH_AVX)
#	elif defined(__SSE4_2__)
#		define GLM_ARCH (GLM_ARCH_SSE42)
#	elif defined(__SSE4_1__)
#		define GLM_ARCH (GLM_ARCH_SSE41)
#	elif defined(__SSSE3__)
#		define GLM_ARCH (GLM_ARCH_SSSE3)
#	elif defined(__SSE3__)
#		define GLM_ARCH (GLM_ARCH_SSE3)
#	elif defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86_FP)
#		define GLM_ARCH (GLM_ARCH_SSE2)
#	elif defined(__i386__)
#		define GLM_ARCH (GLM_ARCH_X86)
#	elif defined(__ARM_ARCH) && (__ARM_ARCH >= 8)
#		define GLM_ARCH (GLM_ARCH_ARMV8)
#	elif defined(__ARM_NEON)
#		define GLM_ARCH (GLM_ARCH_ARM | GLM_ARCH_NEON)
#	elif defined(__arm__ ) || defined(_M_ARM)
#		define GLM_ARCH (GLM_ARCH_ARM)
#	elif defined(__mips__ )
#		define GLM_ARCH (GLM_ARCH_MIPS)
#	elif defined(__powerpc__ ) || defined(_M_PPC)
#		define GLM_ARCH (GLM_ARCH_PPC)
#	else
#		define GLM_ARCH (GLM_ARCH_UNKNOWN)
#	endif
#else
#	if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86) || defined(__i386__)
#		define GLM_ARCH (GLM_ARCH_X86)
#	elif defined(__arm__) || defined(_M_ARM)
#		define GLM_ARCH (GLM_ARCH_ARM)
#	elif defined(__powerpc__) || defined(_M_PPC)
#		define GLM_ARCH (GLM_ARCH_PPC)
#	elif defined(__mips__)
#		define GLM_ARCH (GLM_ARCH_MIPS)
#	else
#		define GLM_ARCH (GLM_ARCH_UNKNOWN)
#	endif
#endif

#if GLM_ARCH & GLM_ARCH_AVX2_BIT
#	include <immintrin.h>
#elif GLM_ARCH & GLM_ARCH_AVX_BIT
#	include <immintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE42_BIT
#	if GLM_COMPILER & GLM_COMPILER_CLANG
#		include <popcntintrin.h>
#	endif
#	include <nmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE41_BIT
#	include <smmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSSE3_BIT
#	include <tmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE3_BIT
#	include <pmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE2_BIT
#	include <emmintrin.h>
#elif GLM_ARCH & GLM_ARCH_NEON_BIT
#	include "neon.h"
#endif//GLM_ARCH

#if GLM_ARCH & GLM_ARCH_SSE2_BIT
	typedef __m128			glm_f32vec4;
	typedef __m128i			glm_i32vec4;
	typedef __m128i			glm_u32vec4;
	typedef __m128d			glm_f64vec2;
	typedef __m128i			glm_i64vec2;
	typedef __m128i			glm_u64vec2;

	typedef glm_f32vec4		glm_vec4;
	typedef glm_i32vec4		glm_ivec4;
	typedef glm_u32vec4		glm_uvec4;
	typedef glm_f64vec2		glm_dvec2;
#endif

#if GLM_ARCH & GLM_ARCH_AVX_BIT
	typedef __m256d			glm_f64vec4;
	typedef glm_f64vec4		glm_dvec4;
#endif

#if GLM_ARCH & GLM_ARCH_AVX2_BIT
	typedef __m256i			glm_i64vec4;
	typedef __m256i			glm_u64vec4;
#endif

#if GLM_ARCH & GLM_ARCH_NEON_BIT
	typedef float32x4_t			glm_f32vec4;
	typedef int32x4_t			glm_i32vec4;
	typedef uint32x4_t			glm_u32vec4;
#endif

///////////////////////////////////////////////////////////////////////////////////
// Build model

#if defined(_M_ARM64) || defined(__LP64__) || defined(_M_X64) || defined(__ppc64__) || defined(__x86_64__)
#	define GLM_MODEL	GLM_MODEL_64
#elif defined(__i386__) || defined(__ppc__) || defined(__ILP32__) || defined(_M_ARM)
#	define GLM_MODEL	GLM_MODEL_32
#else
#	define GLM_MODEL	GLM_MODEL_32
#endif//

#if !defined(GLM_MODEL) && GLM_COMPILER != 0
#	error "GLM_MODEL undefined, your compiler may not be supported by GLM. Add #define GLM_MODEL 0 to ignore this message."
#endif//GLM_MODEL

///////////////////////////////////////////////////////////////////////////////////
// C++ Version

// User defines: GLM_FORCE_CXX98, GLM_FORCE_CXX03, GLM_FORCE_CXX11, GLM_FORCE_CXX14, GLM_FORCE_CXX17, GLM_FORCE_CXX2A

#define GLM_LANG_CXX98_FLAG			(1 << 1)
#define GLM_LANG_CXX03_FLAG			(1 << 2)
#define GLM_LANG_CXX0X_FLAG			(1 << 3)
#define GLM_LANG_CXX11_FLAG			(1 << 4)
#define GLM_LANG_CXX14_FLAG			(1 << 5)
#define GLM_LANG_CXX17_FLAG			(1 << 6)
#define GLM_LANG_CXX2A_FLAG			(1 << 7)
#define GLM_LANG_CXXMS_FLAG			(1 << 8)
#define GLM_LANG_CXXGNU_FLAG		(1 << 9)

#define GLM_LANG_CXX98			GLM_LANG_CXX98_FLAG
#define GLM_LANG_CXX03			(GLM_LANG_CXX98 | GLM_LANG_CXX03_FLAG)
#define GLM_LANG_CXX0X			(GLM_LANG_CXX03 | GLM_LANG_CXX0X_FLAG)
#define GLM_LANG_CXX11			(GLM_LANG_CXX0X | GLM_LANG_CXX11_FLAG)
#define GLM_LANG_CXX14			(GLM_LANG_CXX11 | GLM_LANG_CXX14_FLAG)
#define GLM_LANG_CXX17			(GLM_LANG_CXX14 | GLM_LANG_CXX17_FLAG)
#define GLM_LANG_CXX2A			(GLM_LANG_CXX17 | GLM_LANG_CXX2A_FLAG)
#define GLM_LANG_CXXMS			GLM_LANG_CXXMS_FLAG
#define GLM_LANG_CXXGNU			GLM_LANG_CXXGNU_FLAG

#if (defined(_MSC_EXTENSIONS))
#	define GLM_LANG_EXT GLM_LANG_CXXMS_FLAG
#elif ((GLM_COMPILER & (GLM_COMPILER_CLANG | GLM_COMPILER_GCC)) && (GLM_ARCH & GLM_ARCH_SIMD_BIT))
#	define GLM_LANG_EXT GLM_LANG_CXXMS_FLAG
#else
#	define GLM_LANG_EXT 0
#endif

#if (defined(GLM_FORCE_CXX_UNKNOWN))
#	define GLM_LANG 0
#elif defined(GLM_FORCE_CXX2A)
#	define GLM_LANG (GLM_LANG_CXX2A | GLM_LANG_EXT)
#	define GLM_LANG_STL11_FORCED
#elif defined(GLM_FORCE_CXX17)
#	define GLM_LANG (GLM_LANG_CXX17 | GLM_LANG_EXT)
#	define GLM_LANG_STL11_FORCED
#elif defined(GLM_FORCE_CXX14)
#	define GLM_LANG (GLM_LANG_CXX14 | GLM_LANG_EXT)
#	define GLM_LANG_STL11_FORCED
#elif defined(GLM_FORCE_CXX11)
#	define GLM_LANG (GLM_LANG_CXX11 | GLM_LANG_EXT)
#	define GLM_LANG_STL11_FORCED
#elif defined(GLM_FORCE_CXX03)
#	define GLM_LANG (GLM_LANG_CXX03 | GLM_LANG_EXT)
#elif defined(GLM_FORCE_CXX98)
#	define GLM_LANG (GLM_LANG_CXX98 | GLM_LANG_EXT)
#else
#	if GLM_COMPILER & GLM_COMPILER_VC && defined(_MSVC_LANG)
#		if GLM_COMPILER >= GLM_COMPILER_VC15_7
#			define GLM_LANG_PLATFORM _MSVC_LANG
#		elif GLM_COMPILER >= GLM_COMPILER_VC15
#			if _MSVC_LANG > 201402L
#				define GLM_LANG_PLATFORM 201402L
#			else
#				define GLM_LANG_PLATFORM _MSVC_LANG
#			endif
#		else
#			define GLM_LANG_PLATFORM 0
#		endif
#	else
#		define GLM_LANG_PLATFORM 0
#	endif

#	if __cplusplus > 201703L || GLM_LANG_PLATFORM > 201703L
#		define GLM_LANG (GLM_LANG_CXX2A | GLM_LANG_EXT)
#	elif __cplusplus == 201703L || GLM_LANG_PLATFORM == 201703L
#		define GLM_LANG (GLM_LANG_CXX17 | GLM_LANG_EXT)
#	elif __cplusplus == 201402L || __cplusplus == 201500L || GLM_LANG_PLATFORM == 201402L
#		define GLM_LANG (GLM_LANG_CXX14 | GLM_LANG_EXT)
#	elif __cplusplus == 201103L || GLM_LANG_PLATFORM == 201103L
#		define GLM_LANG (GLM_LANG_CXX11 | GLM_LANG_EXT)
#	elif defined(__INTEL_CXX11_MODE__) || defined(_MSC_VER) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#		define GLM_LANG (GLM_LANG_CXX0X | GLM_LANG_EXT)
#	elif __cplusplus == 199711L
#		define GLM_LANG (GLM_LANG_CXX98 | GLM_LANG_EXT)
#	else
#		define GLM_LANG (0 | GLM_LANG_EXT)
#	endif
#endif

///////////////////////////////////////////////////////////////////////////////////
// Has of C++ features

// http://clang.llvm.org/cxx_status.html
// http://gcc.gnu.org/projects/cxx0x.html
// http://msdn.microsoft.com/en-us/library/vstudio/hh567368(v=vs.120).aspx

// Android has multiple STLs but C++11 STL detection doesn't always work #284 #564
#if GLM_PLATFORM == GLM_PLATFORM_ANDROID && !defined(GLM_LANG_STL11_FORCED)
#	define GLM_HAS_CXX11_STL 0
#elif GLM_COMPILER & GLM_COMPILER_CLANG
#	if (defined(_LIBCPP_VERSION) || (GLM_LANG & GLM_LANG_CXX11_FLAG) || defined(GLM_LANG_STL11_FORCED))
#		define GLM_HAS_CXX11_STL 1
#	else
#		define GLM_HAS_CXX11_STL 0
#	endif
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_CXX11_STL 1
#else
#	define GLM_HAS_CXX11_STL ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_GCC) && (GLM_COMPILER >= GLM_COMPILER_GCC48)) || \
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC12)) || \
		((GLM_PLATFORM != GLM_PLATFORM_WINDOWS) && (GLM_COMPILER & GLM_COMPILER_INTEL) && (GLM_COMPILER >= GLM_COMPILER_INTEL15))))
#endif

// N1720
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_STATIC_ASSERT __has_feature(cxx_static_assert)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_STATIC_ASSERT 1
#else
#	define GLM_HAS_STATIC_ASSERT ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_CUDA)) || \
		((GLM_COMPILER & GLM_COMPILER_VC))))
#endif

// N1988
#if GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_EXTENDED_INTEGER_TYPE 1
#else
#	define GLM_HAS_EXTENDED_INTEGER_TYPE (\
		((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (GLM_COMPILER & GLM_COMPILER_VC)) || \
		((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (GLM_COMPILER & GLM_COMPILER_CUDA)) || \
		((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (GLM_COMPILER & GLM_COMPILER_CLANG)))
#endif

// N2672 Initializer lists http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2672.htm
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_INITIALIZER_LISTS __has_feature(cxx_generalized_initializers)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_INITIALIZER_LISTS 1
#else
#	define GLM_HAS_INITIALIZER_LISTS ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC15)) || \
		((GLM_COMPILER & GLM_COMPILER_INTEL) && (GLM_COMPILER >= GLM_COMPILER_INTEL14)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

// N2544 Unrestricted unions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2544.pdf
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_UNRESTRICTED_UNIONS __has_feature(cxx_unrestricted_unions)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_UNRESTRICTED_UNIONS 1
#else
#	define GLM_HAS_UNRESTRICTED_UNIONS (GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		(GLM_COMPILER & GLM_COMPILER_VC) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA)))
#endif

// N2346
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_DEFAULTED_FUNCTIONS __has_feature(cxx_defaulted_functions)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_DEFAULTED_FUNCTIONS 1
#else
#	define GLM_HAS_DEFAULTED_FUNCTIONS ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC12)) || \
		((GLM_COMPILER & GLM_COMPILER_INTEL)) || \
		(GLM_COMPILER & GLM_COMPILER_CUDA)))
#endif

// N2118
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_RVALUE_REFERENCES 1
#else
#	define GLM_HAS_RVALUE_REFERENCES ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_VC)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

// N2437 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2437.pdf
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_EXPLICIT_CONVERSION_OPERATORS __has_feature(cxx_explicit_conversions)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_EXPLICIT_CONVERSION_OPERATORS 1
#else
#	define GLM_HAS_EXPLICIT_CONVERSION_OPERATORS ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_INTEL) && (GLM_COMPILER >= GLM_COMPILER_INTEL14)) || \
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC12)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

// N2258 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2258.pdf
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_TEMPLATE_ALIASES __has_feature(cxx_alias_templates)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_TEMPLATE_ALIASES 1
#else
#	define GLM_HAS_TEMPLATE_ALIASES ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_INTEL)) || \
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC12)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

// N2930 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2009/n2930.html
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_RANGE_FOR __has_feature(cxx_range_for)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_RANGE_FOR 1
#else
#	define GLM_HAS_RANGE_FOR ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_INTEL)) || \
		((GLM_COMPILER & GLM_COMPILER_VC)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

// N2341 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2341.pdf
#if GLM_COMPILER & GLM_COMPILER_CLANG
#	define GLM_HAS_ALIGNOF __has_feature(cxx_alignas)
#elif GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_ALIGNOF 1
#else
#	define GLM_HAS_ALIGNOF ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_INTEL) && (GLM_COMPILER >= GLM_COMPILER_INTEL15)) || \
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC14)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

// N2235 Generalized Constant Expressions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2235.pdf
// N3652 Extended Constant Expressions http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
#if (GLM_ARCH & GLM_ARCH_SIMD_BIT) // Compiler SIMD intrinsics don't support constexpr...
#	define GLM_HAS_CONSTEXPR 0
#elif (GLM_COMPILER & GLM_COMPILER_CLANG)
#	define GLM_HAS_CONSTEXPR __has_feature(cxx_relaxed_constexpr)
#elif (GLM_LANG & GLM_LANG_CXX14_FLAG)
#	define GLM_HAS_CONSTEXPR 1
#else
#	define GLM_HAS_CONSTEXPR ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && GLM_HAS_INITIALIZER_LISTS && (\
		((GLM_COMPILER & GLM_COMPILER_INTEL) && (GLM_COMPILER >= GLM_COMPILER_INTEL17)) || \
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC15))))
#endif

#if GLM_HAS_CONSTEXPR
#	define GLM_CONSTEXPR constexpr
#else
#	define GLM_CONSTEXPR
#endif

//
#if GLM_HAS_CONSTEXPR
# if (GLM_COMPILER & GLM_COMPILER_CLANG)
#	if __has_feature(cxx_if_constexpr)
#		define GLM_HAS_IF_CONSTEXPR 1
#	else
# 		define GLM_HAS_IF_CONSTEXPR 0
#	endif
# elif (GLM_LANG & GLM_LANG_CXX17_FLAG)
# 	define GLM_HAS_IF_CONSTEXPR 1
# else
# 	define GLM_HAS_IF_CONSTEXPR 0
# endif
#else
#	define GLM_HAS_IF_CONSTEXPR 0
#endif

#if GLM_HAS_IF_CONSTEXPR
# 	define GLM_IF_CONSTEXPR if constexpr
#else
#	define GLM_IF_CONSTEXPR if
#endif

//
#if GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_ASSIGNABLE 1
#else
#	define GLM_HAS_ASSIGNABLE ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC15)) || \
		((GLM_COMPILER & GLM_COMPILER_GCC) && (GLM_COMPILER >= GLM_COMPILER_GCC49))))
#endif

//
#define GLM_HAS_TRIVIAL_QUERIES 0

//
#if GLM_LANG & GLM_LANG_CXX11_FLAG
#	define GLM_HAS_MAKE_SIGNED 1
#else
#	define GLM_HAS_MAKE_SIGNED ((GLM_LANG & GLM_LANG_CXX0X_FLAG) && (\
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC12)) || \
		((GLM_COMPILER & GLM_COMPILER_CUDA))))
#endif

//
#if defined(GLM_FORCE_INTRINSICS)
#	define GLM_HAS_BITSCAN_WINDOWS ((GLM_PLATFORM & GLM_PLATFORM_WINDOWS) && (\
		((GLM_COMPILER & GLM_COMPILER_INTEL)) || \
		((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC14) && (GLM_ARCH & GLM_ARCH_X86_BIT))))
#else
#	define GLM_HAS_BITSCAN_WINDOWS 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// OpenMP
#ifdef _OPENMP
#	if GLM_COMPILER & GLM_COMPILER_GCC
#		if GLM_COMPILER >= GLM_COMPILER_GCC61
#			define GLM_HAS_OPENMP 45
#		elif GLM_COMPILER >= GLM_COMPILER_GCC49
#			define GLM_HAS_OPENMP 40
#		elif GLM_COMPILER >= GLM_COMPILER_GCC47
#			define GLM_HAS_OPENMP 31
#		else
#			define GLM_HAS_OPENMP 0
#		endif
#	elif GLM_COMPILER & GLM_COMPILER_CLANG
#		if GLM_COMPILER >= GLM_COMPILER_CLANG38
#			define GLM_HAS_OPENMP 31
#		else
#			define GLM_HAS_OPENMP 0
#		endif
#	elif GLM_COMPILER & GLM_COMPILER_VC
#		define GLM_HAS_OPENMP 20
#	elif GLM_COMPILER & GLM_COMPILER_INTEL
#		if GLM_COMPILER >= GLM_COMPILER_INTEL16
#			define GLM_HAS_OPENMP 40
#		else
#			define GLM_HAS_OPENMP 0
#		endif
#	else
#		define GLM_HAS_OPENMP 0
#	endif
#else
#	define GLM_HAS_OPENMP 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// nullptr

#if GLM_LANG & GLM_LANG_CXX0X_FLAG
#	define GLM_CONFIG_NULLPTR GLM_ENABLE
#else
#	define GLM_CONFIG_NULLPTR GLM_DISABLE
#endif

#if GLM_CONFIG_NULLPTR == GLM_ENABLE
#	define GLM_NULLPTR nullptr
#else
#	define GLM_NULLPTR 0
#endif

///////////////////////////////////////////////////////////////////////////////////
// Static assert

#if GLM_HAS_STATIC_ASSERT
#	define GLM_STATIC_ASSERT(x, message) static_assert(x, message)
#elif GLM_COMPILER & GLM_COMPILER_VC
#	define GLM_STATIC_ASSERT(x, message) typedef char __CASSERT__##__LINE__[(x) ? 1 : -1]
#else
#	define GLM_STATIC_ASSERT(x, message) assert(x)
#endif//GLM_LANG

///////////////////////////////////////////////////////////////////////////////////
// Qualifiers

#if GLM_COMPILER & GLM_COMPILER_CUDA
#	define GLM_CUDA_FUNC_DEF __device__ __host__
#	define GLM_CUDA_FUNC_DECL __device__ __host__
#else
#	define GLM_CUDA_FUNC_DEF
#	define GLM_CUDA_FUNC_DECL
#endif

#if defined(GLM_FORCE_INLINE)
#	if GLM_COMPILER & GLM_COMPILER_VC
#		define GLM_INLINE __forceinline
#		define GLM_NEVER_INLINE __declspec((noinline))
#	elif GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_CLANG)
#		define GLM_INLINE inline __attribute__((__always_inline__))
#		define GLM_NEVER_INLINE __attribute__((__noinline__))
#	elif GLM_COMPILER & GLM_COMPILER_CUDA
#		define GLM_INLINE __forceinline__
#		define GLM_NEVER_INLINE __noinline__
#	else
#		define GLM_INLINE inline
#		define GLM_NEVER_INLINE
#	endif//GLM_COMPILER
#else
#	define GLM_INLINE inline
#	define GLM_NEVER_INLINE
#endif//defined(GLM_FORCE_INLINE)

#define GLM_FUNC_DECL GLM_CUDA_FUNC_DECL
#define GLM_FUNC_QUALIFIER GLM_CUDA_FUNC_DEF GLM_INLINE

///////////////////////////////////////////////////////////////////////////////////
// Swizzle operators

// User defines: GLM_FORCE_SWIZZLE

#define GLM_SWIZZLE_DISABLED		0
#define GLM_SWIZZLE_OPERATOR		1
#define GLM_SWIZZLE_FUNCTION		2

#if defined(GLM_FORCE_XYZW_ONLY)
#	undef GLM_FORCE_SWIZZLE
#endif

#if defined(GLM_SWIZZLE)
#	pragma message("GLM: GLM_SWIZZLE is deprecated, use GLM_FORCE_SWIZZLE instead.")
#	define GLM_FORCE_SWIZZLE
#endif

#if defined(GLM_FORCE_SWIZZLE) && (GLM_LANG & GLM_LANG_CXXMS_FLAG)
#	define GLM_CONFIG_SWIZZLE GLM_SWIZZLE_OPERATOR
#elif defined(GLM_FORCE_SWIZZLE)
#	define GLM_CONFIG_SWIZZLE GLM_SWIZZLE_FUNCTION
#else
#	define GLM_CONFIG_SWIZZLE GLM_SWIZZLE_DISABLED
#endif

///////////////////////////////////////////////////////////////////////////////////
// Allows using not basic types as genType

// #define GLM_FORCE_UNRESTRICTED_GENTYPE

#ifdef GLM_FORCE_UNRESTRICTED_GENTYPE
#	define GLM_CONFIG_UNRESTRICTED_GENTYPE GLM_ENABLE
#else
#	define GLM_CONFIG_UNRESTRICTED_GENTYPE GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Clip control, define GLM_FORCE_DEPTH_ZERO_TO_ONE before including GLM
// to use a clip space between 0 to 1.
// Coordinate system, define GLM_FORCE_LEFT_HANDED before including GLM
// to use left handed coordinate system by default.

#define GLM_CLIP_CONTROL_ZO_BIT		(1 << 0) // ZERO_TO_ONE
#define GLM_CLIP_CONTROL_NO_BIT		(1 << 1) // NEGATIVE_ONE_TO_ONE
#define GLM_CLIP_CONTROL_LH_BIT		(1 << 2) // LEFT_HANDED, For DirectX, Metal, Vulkan
#define GLM_CLIP_CONTROL_RH_BIT		(1 << 3) // RIGHT_HANDED, For OpenGL, default in GLM

#define GLM_CLIP_CONTROL_LH_ZO (GLM_CLIP_CONTROL_LH_BIT | GLM_CLIP_CONTROL_ZO_BIT)
#define GLM_CLIP_CONTROL_LH_NO (GLM_CLIP_CONTROL_LH_BIT | GLM_CLIP_CONTROL_NO_BIT)
#define GLM_CLIP_CONTROL_RH_ZO (GLM_CLIP_CONTROL_RH_BIT | GLM_CLIP_CONTROL_ZO_BIT)
#define GLM_CLIP_CONTROL_RH_NO (GLM_CLIP_CONTROL_RH_BIT | GLM_CLIP_CONTROL_NO_BIT)

#ifdef GLM_FORCE_DEPTH_ZERO_TO_ONE
#	ifdef GLM_FORCE_LEFT_HANDED
#		define GLM_CONFIG_CLIP_CONTROL GLM_CLIP_CONTROL_LH_ZO
#	else
#		define GLM_CONFIG_CLIP_CONTROL GLM_CLIP_CONTROL_RH_ZO
#	endif
#else
#	ifdef GLM_FORCE_LEFT_HANDED
#		define GLM_CONFIG_CLIP_CONTROL GLM_CLIP_CONTROL_LH_NO
#	else
#		define GLM_CONFIG_CLIP_CONTROL GLM_CLIP_CONTROL_RH_NO
#	endif
#endif

///////////////////////////////////////////////////////////////////////////////////
// Qualifiers

#if (GLM_COMPILER & GLM_COMPILER_VC) || ((GLM_COMPILER & GLM_COMPILER_INTEL) && (GLM_PLATFORM & GLM_PLATFORM_WINDOWS))
#	define GLM_DEPRECATED __declspec(deprecated)
#	define GLM_ALIGNED_TYPEDEF(type, name, alignment) typedef __declspec(align(alignment)) type name
#elif GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_CLANG | GLM_COMPILER_INTEL)
#	define GLM_DEPRECATED __attribute__((__deprecated__))
#	define GLM_ALIGNED_TYPEDEF(type, name, alignment) typedef type name __attribute__((aligned(alignment)))
#elif GLM_COMPILER & GLM_COMPILER_CUDA
#	define GLM_DEPRECATED
#	define GLM_ALIGNED_TYPEDEF(type, name, alignment) typedef type name __align__(x)
#else
#	define GLM_DEPRECATED
#	define GLM_ALIGNED_TYPEDEF(type, name, alignment) typedef type name
#endif

///////////////////////////////////////////////////////////////////////////////////

#ifdef GLM_FORCE_EXPLICIT_CTOR
#	define GLM_EXPLICIT explicit
#else
#	define GLM_EXPLICIT
#endif

///////////////////////////////////////////////////////////////////////////////////
// SYCL

#if GLM_COMPILER==GLM_COMPILER_SYCL

#include <CL/sycl.hpp>
#include <limits>

namespace glm {
namespace std {
	// Import SYCL's functions into the namespace glm::std to force their usages.
	// It's important to use the math built-in function (sin, exp, ...)
	// of SYCL instead the std ones.
	using namespace cl::sycl;

	///////////////////////////////////////////////////////////////////////////////
	// Import some "harmless" std's stuffs used by glm into
	// the new glm::std namespace.
	template<typename T>
	using numeric_limits = ::std::numeric_limits<T>;

	using ::std::size_t;

	using ::std::uint8_t;
	using ::std::uint16_t;
	using ::std::uint32_t;
	using ::std::uint64_t;

	using ::std::int8_t;
	using ::std::int16_t;
	using ::std::int32_t;
	using ::std::int64_t;

	using ::std::make_unsigned;
	///////////////////////////////////////////////////////////////////////////////
} //namespace std
} //namespace glm

#endif

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// Length type: all length functions returns a length_t type.
// When GLM_FORCE_SIZE_T_LENGTH is defined, length_t is a typedef of size_t otherwise
// length_t is a typedef of int like GLSL defines it.

#define GLM_LENGTH_INT		1
#define GLM_LENGTH_SIZE_T	2

#ifdef GLM_FORCE_SIZE_T_LENGTH
#	define GLM_CONFIG_LENGTH_TYPE		GLM_LENGTH_SIZE_T
#else
#	define GLM_CONFIG_LENGTH_TYPE		GLM_LENGTH_INT
#endif

namespace glm
{
	using std::size_t;
#	if GLM_CONFIG_LENGTH_TYPE == GLM_LENGTH_SIZE_T
		typedef size_t length_t;
#	else
		typedef int length_t;
#	endif
}//namespace glm

///////////////////////////////////////////////////////////////////////////////////
// constexpr

#if GLM_HAS_CONSTEXPR
#	define GLM_CONFIG_CONSTEXP GLM_ENABLE

	namespace glm
	{
		template<typename T, std::size_t N>
		constexpr std::size_t countof(T const (&)[N])
		{
			return N;
		}
	}//namespace glm
#	define GLM_COUNTOF(arr) glm::countof(arr)
#elif defined(_MSC_VER)
#	define GLM_CONFIG_CONSTEXP GLM_DISABLE

#	define GLM_COUNTOF(arr) _countof(arr)
#else
#	define GLM_CONFIG_CONSTEXP GLM_DISABLE

#	define GLM_COUNTOF(arr) sizeof(arr) / sizeof(arr[0])
#endif

///////////////////////////////////////////////////////////////////////////////////
// uint

namespace glm{
namespace detail
{
	template<typename T>
	struct is_int
	{
		enum test {value = 0};
	};

	template<>
	struct is_int<unsigned int>
	{
		enum test {value = ~0};
	};

	template<>
	struct is_int<signed int>
	{
		enum test {value = ~0};
	};
}//namespace detail

	typedef unsigned int	uint;
}//namespace glm

///////////////////////////////////////////////////////////////////////////////////
// 64-bit int

#if GLM_HAS_EXTENDED_INTEGER_TYPE
#	include <cstdint>
#endif

namespace glm{
namespace detail
{
#	if GLM_HAS_EXTENDED_INTEGER_TYPE
		typedef std::uint64_t						uint64;
		typedef std::int64_t						int64;
#	elif (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) // C99 detected, 64 bit types available
		typedef uint64_t							uint64;
		typedef int64_t								int64;
#	elif GLM_COMPILER & GLM_COMPILER_VC
		typedef unsigned __int64					uint64;
		typedef signed __int64						int64;
#	elif GLM_COMPILER & GLM_COMPILER_GCC
#		pragma GCC diagnostic ignored "-Wlong-long"
		__extension__ typedef unsigned long long	uint64;
		__extension__ typedef signed long long		int64;
#	elif (GLM_COMPILER & GLM_COMPILER_CLANG)
#		pragma clang diagnostic ignored "-Wc++11-long-long"
		typedef unsigned long long					uint64;
		typedef signed long long					int64;
#	else//unknown compiler
		typedef unsigned long long					uint64;
		typedef signed long long					int64;
#	endif
}//namespace detail
}//namespace glm

///////////////////////////////////////////////////////////////////////////////////
// make_unsigned

#if GLM_HAS_MAKE_SIGNED
#	include <type_traits>

namespace glm{
namespace detail
{
	using std::make_unsigned;
}//namespace detail
}//namespace glm

#else

namespace glm{
namespace detail
{
	template<typename genType>
	struct make_unsigned
	{};

	template<>
	struct make_unsigned<char>
	{
		typedef unsigned char type;
	};

	template<>
	struct make_unsigned<signed char>
	{
		typedef unsigned char type;
	};

	template<>
	struct make_unsigned<short>
	{
		typedef unsigned short type;
	};

	template<>
	struct make_unsigned<int>
	{
		typedef unsigned int type;
	};

	template<>
	struct make_unsigned<long>
	{
		typedef unsigned long type;
	};

	template<>
	struct make_unsigned<int64>
	{
		typedef uint64 type;
	};

	template<>
	struct make_unsigned<unsigned char>
	{
		typedef unsigned char type;
	};

	template<>
	struct make_unsigned<unsigned short>
	{
		typedef unsigned short type;
	};

	template<>
	struct make_unsigned<unsigned int>
	{
		typedef unsigned int type;
	};

	template<>
	struct make_unsigned<unsigned long>
	{
		typedef unsigned long type;
	};

	template<>
	struct make_unsigned<uint64>
	{
		typedef uint64 type;
	};
}//namespace detail
}//namespace glm
#endif

///////////////////////////////////////////////////////////////////////////////////
// Only use x, y, z, w as vector type components

#ifdef GLM_FORCE_XYZW_ONLY
#	define GLM_CONFIG_XYZW_ONLY GLM_ENABLE
#else
#	define GLM_CONFIG_XYZW_ONLY GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of defaulted initialized types

#define GLM_CTOR_INIT_DISABLE		0
#define GLM_CTOR_INITIALIZER_LIST	1
#define GLM_CTOR_INITIALISATION		2

#if defined(GLM_FORCE_CTOR_INIT) && GLM_HAS_INITIALIZER_LISTS
#	define GLM_CONFIG_CTOR_INIT GLM_CTOR_INITIALIZER_LIST
#elif defined(GLM_FORCE_CTOR_INIT) && !GLM_HAS_INITIALIZER_LISTS
#	define GLM_CONFIG_CTOR_INIT GLM_CTOR_INITIALISATION
#else
#	define GLM_CONFIG_CTOR_INIT GLM_CTOR_INIT_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Use SIMD instruction sets

#if GLM_HAS_ALIGNOF && (GLM_LANG & GLM_LANG_CXXMS_FLAG) && (GLM_ARCH & GLM_ARCH_SIMD_BIT)
#	define GLM_CONFIG_SIMD GLM_ENABLE
#else
#	define GLM_CONFIG_SIMD GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of defaulted function

#if GLM_HAS_DEFAULTED_FUNCTIONS && GLM_CONFIG_CTOR_INIT == GLM_CTOR_INIT_DISABLE
#	define GLM_CONFIG_DEFAULTED_FUNCTIONS GLM_ENABLE
#	define GLM_DEFAULT = default
#else
#	define GLM_CONFIG_DEFAULTED_FUNCTIONS GLM_DISABLE
#	define GLM_DEFAULT
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of aligned gentypes

#ifdef GLM_FORCE_ALIGNED // Legacy define
#	define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#endif

#ifdef GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#	define GLM_FORCE_ALIGNED_GENTYPES
#endif

#if GLM_HAS_ALIGNOF && (GLM_LANG & GLM_LANG_CXXMS_FLAG) && (defined(GLM_FORCE_ALIGNED_GENTYPES) || (GLM_CONFIG_SIMD == GLM_ENABLE))
#	define GLM_CONFIG_ALIGNED_GENTYPES GLM_ENABLE
#else
#	define GLM_CONFIG_ALIGNED_GENTYPES GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Configure the use of anonymous structure as implementation detail

#if ((GLM_CONFIG_SIMD == GLM_ENABLE) || (GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR) || (GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE))
#	define GLM_CONFIG_ANONYMOUS_STRUCT GLM_ENABLE
#else
#	define GLM_CONFIG_ANONYMOUS_STRUCT GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Silent warnings

#ifdef GLM_FORCE_SILENT_WARNINGS
#	define GLM_SILENT_WARNINGS GLM_ENABLE
#else
#	define GLM_SILENT_WARNINGS GLM_DISABLE
#endif

///////////////////////////////////////////////////////////////////////////////////
// Precision

#define GLM_HIGHP		1
#define GLM_MEDIUMP		2
#define GLM_LOWP		3

#if defined(GLM_FORCE_PRECISION_HIGHP_BOOL) || defined(GLM_PRECISION_HIGHP_BOOL)
#	define GLM_CONFIG_PRECISION_BOOL		GLM_HIGHP
#elif defined(GLM_FORCE_PRECISION_MEDIUMP_BOOL) || defined(GLM_PRECISION_MEDIUMP_BOOL)
#	define GLM_CONFIG_PRECISION_BOOL		GLM_MEDIUMP
#elif defined(GLM_FORCE_PRECISION_LOWP_BOOL) || defined(GLM_PRECISION_LOWP_BOOL)
#	define GLM_CONFIG_PRECISION_BOOL		GLM_LOWP
#else
#	define GLM_CONFIG_PRECISION_BOOL		GLM_HIGHP
#endif

#if defined(GLM_FORCE_PRECISION_HIGHP_INT) || defined(GLM_PRECISION_HIGHP_INT)
#	define GLM_CONFIG_PRECISION_INT			GLM_HIGHP
#elif defined(GLM_FORCE_PRECISION_MEDIUMP_INT) || defined(GLM_PRECISION_MEDIUMP_INT)
#	define GLM_CONFIG_PRECISION_INT			GLM_MEDIUMP
#elif defined(GLM_FORCE_PRECISION_LOWP_INT) || defined(GLM_PRECISION_LOWP_INT)
#	define GLM_CONFIG_PRECISION_INT			GLM_LOWP
#else
#	define GLM_CONFIG_PRECISION_INT			GLM_HIGHP
#endif

#if defined(GLM_FORCE_PRECISION_HIGHP_UINT) || defined(GLM_PRECISION_HIGHP_UINT)
#	define GLM_CONFIG_PRECISION_UINT		GLM_HIGHP
#elif defined(GLM_FORCE_PRECISION_MEDIUMP_UINT) || defined(GLM_PRECISION_MEDIUMP_UINT)
#	define GLM_CONFIG_PRECISION_UINT		GLM_MEDIUMP
#elif defined(GLM_FORCE_PRECISION_LOWP_UINT) || defined(GLM_PRECISION_LOWP_UINT)
#	define GLM_CONFIG_PRECISION_UINT		GLM_LOWP
#else
#	define GLM_CONFIG_PRECISION_UINT		GLM_HIGHP
#endif

#if defined(GLM_FORCE_PRECISION_HIGHP_FLOAT) || defined(GLM_PRECISION_HIGHP_FLOAT)
#	define GLM_CONFIG_PRECISION_FLOAT		GLM_HIGHP
#elif defined(GLM_FORCE_PRECISION_MEDIUMP_FLOAT) || defined(GLM_PRECISION_MEDIUMP_FLOAT)
#	define GLM_CONFIG_PRECISION_FLOAT		GLM_MEDIUMP
#elif defined(GLM_FORCE_PRECISION_LOWP_FLOAT) || defined(GLM_PRECISION_LOWP_FLOAT)
#	define GLM_CONFIG_PRECISION_FLOAT		GLM_LOWP
#else
#	define GLM_CONFIG_PRECISION_FLOAT		GLM_HIGHP
#endif

#if defined(GLM_FORCE_PRECISION_HIGHP_DOUBLE) || defined(GLM_PRECISION_HIGHP_DOUBLE)
#	define GLM_CONFIG_PRECISION_DOUBLE		GLM_HIGHP
#elif defined(GLM_FORCE_PRECISION_MEDIUMP_DOUBLE) || defined(GLM_PRECISION_MEDIUMP_DOUBLE)
#	define GLM_CONFIG_PRECISION_DOUBLE		GLM_MEDIUMP
#elif defined(GLM_FORCE_PRECISION_LOWP_DOUBLE) || defined(GLM_PRECISION_LOWP_DOUBLE)
#	define GLM_CONFIG_PRECISION_DOUBLE		GLM_LOWP
#else
#	define GLM_CONFIG_PRECISION_DOUBLE		GLM_HIGHP
#endif

///////////////////////////////////////////////////////////////////////////////////
// Check inclusions of different versions of GLM

#elif ((GLM_SETUP_INCLUDED != GLM_VERSION) && !defined(GLM_FORCE_IGNORE_VERSION))
#	error "GLM error: A different version of GLM is already included. Define GLM_FORCE_IGNORE_VERSION before including GLM headers to ignore this error."
#elif GLM_SETUP_INCLUDED == GLM_VERSION

///////////////////////////////////////////////////////////////////////////////////
// Messages

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_MESSAGE_DISPLAYED)
#	define GLM_MESSAGE_DISPLAYED
#		define GLM_STR_HELPER(x) #x
#		define GLM_STR(x) GLM_STR_HELPER(x)

	// Report GLM version
#		pragma message (GLM_STR(GLM_VERSION_MESSAGE))

	// Report C++ language
#	if (GLM_LANG & GLM_LANG_CXX2A_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 2A with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX2A_FLAG)
#		pragma message("GLM: C++ 2A")
#	elif (GLM_LANG & GLM_LANG_CXX17_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 17 with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX17_FLAG)
#		pragma message("GLM: C++ 17")
#	elif (GLM_LANG & GLM_LANG_CXX14_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 14 with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX14_FLAG)
#		pragma message("GLM: C++ 14")
#	elif (GLM_LANG & GLM_LANG_CXX11_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 11 with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX11_FLAG)
#		pragma message("GLM: C++ 11")
#	elif (GLM_LANG & GLM_LANG_CXX0X_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 0x with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX0X_FLAG)
#		pragma message("GLM: C++ 0x")
#	elif (GLM_LANG & GLM_LANG_CXX03_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 03 with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX03_FLAG)
#		pragma message("GLM: C++ 03")
#	elif (GLM_LANG & GLM_LANG_CXX98_FLAG) && (GLM_LANG & GLM_LANG_EXT)
#		pragma message("GLM: C++ 98 with extensions")
#	elif (GLM_LANG & GLM_LANG_CXX98_FLAG)
#		pragma message("GLM: C++ 98")
#	else
#		pragma message("GLM: C++ language undetected")
#	endif//GLM_LANG

	// Report compiler detection
#	if GLM_COMPILER & GLM_COMPILER_CUDA
#		pragma message("GLM: CUDA compiler detected")
#	elif GLM_COMPILER & GLM_COMPILER_VC
#		pragma message("GLM: Visual C++ compiler detected")
#	elif GLM_COMPILER & GLM_COMPILER_CLANG
#		pragma message("GLM: Clang compiler detected")
#	elif GLM_COMPILER & GLM_COMPILER_INTEL
#		pragma message("GLM: Intel Compiler detected")
#	elif GLM_COMPILER & GLM_COMPILER_GCC
#		pragma message("GLM: GCC compiler detected")
#	else
#		pragma message("GLM: Compiler not detected")
#	endif

	// Report build target
#	if (GLM_ARCH & GLM_ARCH_AVX2_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with AVX2 instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_AVX2_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with AVX2 instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_AVX_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with AVX instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_AVX_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with AVX instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_SSE42_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with SSE4.2 instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_SSE42_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with SSE4.2 instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_SSE41_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with SSE4.1 instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_SSE41_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with SSE4.1 instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_SSSE3_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with SSSE3 instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_SSSE3_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with SSSE3 instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_SSE3_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with SSE3 instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_SSE3_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with SSE3 instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_SSE2_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits with SSE2 instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_SSE2_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits with SSE2 instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_X86_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: x86 64 bits build target")
#	elif (GLM_ARCH & GLM_ARCH_X86_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: x86 32 bits build target")

#	elif (GLM_ARCH & GLM_ARCH_NEON_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: ARM 64 bits with Neon instruction set build target")
#	elif (GLM_ARCH & GLM_ARCH_NEON_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: ARM 32 bits with Neon instruction set build target")

#	elif (GLM_ARCH & GLM_ARCH_ARM_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: ARM 64 bits build target")
#	elif (GLM_ARCH & GLM_ARCH_ARM_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: ARM 32 bits build target")

#	elif (GLM_ARCH & GLM_ARCH_MIPS_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: MIPS 64 bits build target")
#	elif (GLM_ARCH & GLM_ARCH_MIPS_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: MIPS 32 bits build target")

#	elif (GLM_ARCH & GLM_ARCH_PPC_BIT) && (GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: PowerPC 64 bits build target")
#	elif (GLM_ARCH & GLM_ARCH_PPC_BIT) && (GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: PowerPC 32 bits build target")
#	else
#		pragma message("GLM: Unknown build target")
#	endif//GLM_ARCH

	// Report platform name
#	if(GLM_PLATFORM & GLM_PLATFORM_QNXNTO)
#		pragma message("GLM: QNX platform detected")
//#	elif(GLM_PLATFORM & GLM_PLATFORM_IOS)
//#		pragma message("GLM: iOS platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_APPLE)
#		pragma message("GLM: Apple platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_WINCE)
#		pragma message("GLM: WinCE platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_WINDOWS)
#		pragma message("GLM: Windows platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_CHROME_NACL)
#		pragma message("GLM: Native Client detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_ANDROID)
#		pragma message("GLM: Android platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_LINUX)
#		pragma message("GLM: Linux platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_UNIX)
#		pragma message("GLM: UNIX platform detected")
#	elif(GLM_PLATFORM & GLM_PLATFORM_UNKNOWN)
#		pragma message("GLM: platform unknown")
#	else
#		pragma message("GLM: platform not detected")
#	endif

	// Report whether only xyzw component are used
#	if defined GLM_FORCE_XYZW_ONLY
#		pragma message("GLM: GLM_FORCE_XYZW_ONLY is defined. Only x, y, z and w component are available in vector type. This define disables swizzle operators and SIMD instruction sets.")
#	endif

	// Report swizzle operator support
#	if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
#		pragma message("GLM: GLM_FORCE_SWIZZLE is defined, swizzling operators enabled.")
#	elif GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
#		pragma message("GLM: GLM_FORCE_SWIZZLE is defined, swizzling functions enabled. Enable compiler C++ language extensions to enable swizzle operators.")
#	else
#		pragma message("GLM: GLM_FORCE_SWIZZLE is undefined. swizzling functions or operators are disabled.")
#	endif

	// Report .length() type
#	if GLM_CONFIG_LENGTH_TYPE == GLM_LENGTH_SIZE_T
#		pragma message("GLM: GLM_FORCE_SIZE_T_LENGTH is defined. .length() returns a glm::length_t, a typedef of std::size_t.")
#	else
#		pragma message("GLM: GLM_FORCE_SIZE_T_LENGTH is undefined. .length() returns a glm::length_t, a typedef of int following GLSL.")
#	endif

#	if GLM_CONFIG_UNRESTRICTED_GENTYPE == GLM_ENABLE
#		pragma message("GLM: GLM_FORCE_UNRESTRICTED_GENTYPE is defined. Removes GLSL restrictions on valid function genTypes.")
#	else
#		pragma message("GLM: GLM_FORCE_UNRESTRICTED_GENTYPE is undefined. Follows strictly GLSL on valid function genTypes.")
#	endif

#	if GLM_SILENT_WARNINGS == GLM_ENABLE
#		pragma message("GLM: GLM_FORCE_SILENT_WARNINGS is defined. Ignores C++ warnings from using C++ language extensions.")
#	else
#		pragma message("GLM: GLM_FORCE_SILENT_WARNINGS is undefined. Shows C++ warnings from using C++ language extensions.")
#	endif

#	ifdef GLM_FORCE_SINGLE_ONLY
#		pragma message("GLM: GLM_FORCE_SINGLE_ONLY is defined. Using only single precision floating-point types.")
#	endif

#	if defined(GLM_FORCE_ALIGNED_GENTYPES) && (GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE)
#		undef GLM_FORCE_ALIGNED_GENTYPES
#		pragma message("GLM: GLM_FORCE_ALIGNED_GENTYPES is defined, allowing aligned types. This prevents the use of C++ constexpr.")
#	elif defined(GLM_FORCE_ALIGNED_GENTYPES) && (GLM_CONFIG_ALIGNED_GENTYPES == GLM_DISABLE)
#		undef GLM_FORCE_ALIGNED_GENTYPES
#		pragma message("GLM: GLM_FORCE_ALIGNED_GENTYPES is defined but is disabled. It requires C++11 and language extensions.")
#	endif

#	if defined(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES)
#		if GLM_CONFIG_ALIGNED_GENTYPES == GLM_DISABLE
#			undef GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#			pragma message("GLM: GLM_FORCE_DEFAULT_ALIGNED_GENTYPES is defined but is disabled. It requires C++11 and language extensions.")
#		elif GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
#			pragma message("GLM: GLM_FORCE_DEFAULT_ALIGNED_GENTYPES is defined. All gentypes (e.g. vec3) will be aligned and padded by default.")
#		endif
#	endif

#	if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
#		pragma message("GLM: GLM_FORCE_DEPTH_ZERO_TO_ONE is defined. Using zero to one depth clip space.")
#	else
#		pragma message("GLM: GLM_FORCE_DEPTH_ZERO_TO_ONE is undefined. Using negative one to one depth clip space.")
#	endif

#	if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
#		pragma message("GLM: GLM_FORCE_LEFT_HANDED is defined. Using left handed coordinate system.")
#	else
#		pragma message("GLM: GLM_FORCE_LEFT_HANDED is undefined. Using right handed coordinate system.")
#	endif
#endif//GLM_MESSAGES

#endif//GLM_SETUP_INCLUDED

// -------------------------------------------------

#include <cmath>
#include <climits>
#include <cfloat>
#include <limits>
#include <cassert>

// ---------- #include "fwd.hpp" ----------

namespace glm
{
	/// Qualify GLM types in term of alignment (packed, aligned) and precision in term of ULPs (lowp, mediump, highp)
	enum qualifier
	{
		packed_highp, ///< Typed data is tightly packed in memory and operations are executed with high precision in term of ULPs
		packed_mediump, ///< Typed data is tightly packed in memory  and operations are executed with medium precision in term of ULPs for higher performance
		packed_lowp, ///< Typed data is tightly packed in memory  and operations are executed with low precision in term of ULPs to maximize performance

#		if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
			aligned_highp, ///< Typed data is aligned in memory allowing SIMD optimizations and operations are executed with high precision in term of ULPs
			aligned_mediump, ///< Typed data is aligned in memory allowing SIMD optimizations and operations are executed with high precision in term of ULPs for higher performance
			aligned_lowp, // ///< Typed data is aligned in memory allowing SIMD optimizations and operations are executed with high precision in term of ULPs to maximize performance
			aligned = aligned_highp, ///< By default aligned qualifier is also high precision
#		endif

		highp = packed_highp, ///< By default highp qualifier is also packed
		mediump = packed_mediump, ///< By default mediump qualifier is also packed
		lowp = packed_lowp, ///< By default lowp qualifier is also packed
		packed = packed_highp, ///< By default packed qualifier is also high precision

#		if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE && defined(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES)
			defaultp = aligned_highp
#		else
			defaultp = highp
#		endif
	};

	typedef qualifier precision;

	template<length_t L, typename T, qualifier Q = defaultp> struct vec;
	template<length_t C, length_t R, typename T, qualifier Q = defaultp> struct mat;
	template<typename T, qualifier Q = defaultp> struct qua;

#	if GLM_HAS_TEMPLATE_ALIASES
		template <typename T, qualifier Q = defaultp> using tvec1 = vec<1, T, Q>;
		template <typename T, qualifier Q = defaultp> using tvec2 = vec<2, T, Q>;
		template <typename T, qualifier Q = defaultp> using tvec3 = vec<3, T, Q>;
		template <typename T, qualifier Q = defaultp> using tvec4 = vec<4, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat2x2 = mat<2, 2, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat2x3 = mat<2, 3, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat2x4 = mat<2, 4, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat3x2 = mat<3, 2, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat3x3 = mat<3, 3, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat3x4 = mat<3, 4, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat4x2 = mat<4, 2, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat4x3 = mat<4, 3, T, Q>;
		template <typename T, qualifier Q = defaultp> using tmat4x4 = mat<4, 4, T, Q>;
		template <typename T, qualifier Q = defaultp> using tquat = qua<T, Q>;
#	endif

namespace detail
{
	template<glm::qualifier P>
	struct is_aligned
	{
		static const bool value = false;
	};

#	if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
		template<>
		struct is_aligned<glm::aligned_lowp>
		{
			static const bool value = true;
		};

		template<>
		struct is_aligned<glm::aligned_mediump>
		{
			static const bool value = true;
		};

		template<>
		struct is_aligned<glm::aligned_highp>
		{
			static const bool value = true;
		};
#	endif

	template<length_t L, typename T, bool is_aligned>
	struct storage
	{
		typedef struct type {
			T data[L];
		} type;
	};

#	if GLM_HAS_ALIGNOF
		template<length_t L, typename T>
		struct storage<L, T, true>
		{
			typedef struct alignas(L * sizeof(T)) type {
				T data[L];
			} type;
		};

		template<typename T>
		struct storage<3, T, true>
		{
			typedef struct alignas(4 * sizeof(T)) type {
				T data[4];
			} type;
		};
#	endif

#	if GLM_ARCH & GLM_ARCH_SSE2_BIT
	template<>
	struct storage<4, float, true>
	{
		typedef glm_f32vec4 type;
	};

	template<>
	struct storage<4, int, true>
	{
		typedef glm_i32vec4 type;
	};

	template<>
	struct storage<4, unsigned int, true>
	{
		typedef glm_u32vec4 type;
	};

	template<>
	struct storage<2, double, true>
	{
		typedef glm_f64vec2 type;
	};

	template<>
	struct storage<2, detail::int64, true>
	{
		typedef glm_i64vec2 type;
	};

	template<>
	struct storage<2, detail::uint64, true>
	{
		typedef glm_u64vec2 type;
	};
#	endif

#	if (GLM_ARCH & GLM_ARCH_AVX_BIT)
	template<>
	struct storage<4, double, true>
	{
		typedef glm_f64vec4 type;
	};
#	endif

#	if (GLM_ARCH & GLM_ARCH_AVX2_BIT)
	template<>
	struct storage<4, detail::int64, true>
	{
		typedef glm_i64vec4 type;
	};

	template<>
	struct storage<4, detail::uint64, true>
	{
		typedef glm_u64vec4 type;
	};
#	endif

#	if GLM_ARCH & GLM_ARCH_NEON_BIT
	template<>
	struct storage<4, float, true>
	{
		typedef glm_f32vec4 type;
	};

	template<>
	struct storage<4, int, true>
	{
		typedef glm_i32vec4 type;
	};

	template<>
	struct storage<4, unsigned int, true>
	{
		typedef glm_u32vec4 type;
	};
#	endif

	enum genTypeEnum
	{
		GENTYPE_VEC,
		GENTYPE_MAT,
		GENTYPE_QUAT
	};

	template <typename genType>
	struct genTypeTrait
	{};

	template <length_t C, length_t R, typename T>
	struct genTypeTrait<mat<C, R, T> >
	{
		static const genTypeEnum GENTYPE = GENTYPE_MAT;
	};

	template<typename genType, genTypeEnum type>
	struct init_gentype
	{
	};

	template<typename genType>
	struct init_gentype<genType, GENTYPE_QUAT>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static genType identity()
		{
			return genType(1, 0, 0, 0);
		}
	};

	template<typename genType>
	struct init_gentype<genType, GENTYPE_MAT>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static genType identity()
		{
			return genType(1);
		}
	};
}//namespace detail
}//namespace glm


namespace glm
{
#if GLM_HAS_EXTENDED_INTEGER_TYPE
	typedef std::int8_t				int8;
	typedef std::int16_t			int16;
	typedef std::int32_t			int32;
	typedef std::int64_t			int64;

	typedef std::uint8_t			uint8;
	typedef std::uint16_t			uint16;
	typedef std::uint32_t			uint32;
	typedef std::uint64_t			uint64;
#else
	typedef signed char				int8;
	typedef signed short			int16;
	typedef signed int				int32;
	typedef detail::int64			int64;

	typedef unsigned char			uint8;
	typedef unsigned short			uint16;
	typedef unsigned int			uint32;
	typedef detail::uint64			uint64;
#endif

	// Scalar int

	typedef int8					lowp_i8;
	typedef int8					mediump_i8;
	typedef int8					highp_i8;
	typedef int8					i8;

	typedef int8					lowp_int8;
	typedef int8					mediump_int8;
	typedef int8					highp_int8;

	typedef int8					lowp_int8_t;
	typedef int8					mediump_int8_t;
	typedef int8					highp_int8_t;
	typedef int8					int8_t;

	typedef int16					lowp_i16;
	typedef int16					mediump_i16;
	typedef int16					highp_i16;
	typedef int16					i16;

	typedef int16					lowp_int16;
	typedef int16					mediump_int16;
	typedef int16					highp_int16;

	typedef int16					lowp_int16_t;
	typedef int16					mediump_int16_t;
	typedef int16					highp_int16_t;
	typedef int16					int16_t;

	typedef int32					lowp_i32;
	typedef int32					mediump_i32;
	typedef int32					highp_i32;
	typedef int32					i32;

	typedef int32					lowp_int32;
	typedef int32					mediump_int32;
	typedef int32					highp_int32;

	typedef int32					lowp_int32_t;
	typedef int32					mediump_int32_t;
	typedef int32					highp_int32_t;
	typedef int32					int32_t;

	typedef int64					lowp_i64;
	typedef int64					mediump_i64;
	typedef int64					highp_i64;
	typedef int64					i64;

	typedef int64					lowp_int64;
	typedef int64					mediump_int64;
	typedef int64					highp_int64;

	typedef int64					lowp_int64_t;
	typedef int64					mediump_int64_t;
	typedef int64					highp_int64_t;
	typedef int64					int64_t;

	// Scalar uint

	typedef unsigned int			uint;

	typedef uint8					lowp_u8;
	typedef uint8					mediump_u8;
	typedef uint8					highp_u8;
	typedef uint8					u8;

	typedef uint8					lowp_uint8;
	typedef uint8					mediump_uint8;
	typedef uint8					highp_uint8;

	typedef uint8					lowp_uint8_t;
	typedef uint8					mediump_uint8_t;
	typedef uint8					highp_uint8_t;
	typedef uint8					uint8_t;

	typedef uint16					lowp_u16;
	typedef uint16					mediump_u16;
	typedef uint16					highp_u16;
	typedef uint16					u16;

	typedef uint16					lowp_uint16;
	typedef uint16					mediump_uint16;
	typedef uint16					highp_uint16;

	typedef uint16					lowp_uint16_t;
	typedef uint16					mediump_uint16_t;
	typedef uint16					highp_uint16_t;
	typedef uint16					uint16_t;

	typedef uint32					lowp_u32;
	typedef uint32					mediump_u32;
	typedef uint32					highp_u32;
	typedef uint32					u32;

	typedef uint32					lowp_uint32;
	typedef uint32					mediump_uint32;
	typedef uint32					highp_uint32;

	typedef uint32					lowp_uint32_t;
	typedef uint32					mediump_uint32_t;
	typedef uint32					highp_uint32_t;
	typedef uint32					uint32_t;

	typedef uint64					lowp_u64;
	typedef uint64					mediump_u64;
	typedef uint64					highp_u64;
	typedef uint64					u64;

	typedef uint64					lowp_uint64;
	typedef uint64					mediump_uint64;
	typedef uint64					highp_uint64;

	typedef uint64					lowp_uint64_t;
	typedef uint64					mediump_uint64_t;
	typedef uint64					highp_uint64_t;
	typedef uint64					uint64_t;

	// Scalar float

	typedef float					lowp_f32;
	typedef float					mediump_f32;
	typedef float					highp_f32;
	typedef float					f32;

	typedef float					lowp_float32;
	typedef float					mediump_float32;
	typedef float					highp_float32;
	typedef float					float32;

	typedef float					lowp_float32_t;
	typedef float					mediump_float32_t;
	typedef float					highp_float32_t;
	typedef float					float32_t;


	typedef double					lowp_f64;
	typedef double					mediump_f64;
	typedef double					highp_f64;
	typedef double					f64;

	typedef double					lowp_float64;
	typedef double					mediump_float64;
	typedef double					highp_float64;
	typedef double					float64;

	typedef double					lowp_float64_t;
	typedef double					mediump_float64_t;
	typedef double					highp_float64_t;
	typedef double					float64_t;

	// Vector bool

	typedef vec<1, bool, lowp>		lowp_bvec1;
	typedef vec<2, bool, lowp>		lowp_bvec2;
	typedef vec<3, bool, lowp>		lowp_bvec3;
	typedef vec<4, bool, lowp>		lowp_bvec4;

	typedef vec<1, bool, mediump>	mediump_bvec1;
	typedef vec<2, bool, mediump>	mediump_bvec2;
	typedef vec<3, bool, mediump>	mediump_bvec3;
	typedef vec<4, bool, mediump>	mediump_bvec4;

	typedef vec<1, bool, highp>		highp_bvec1;
	typedef vec<2, bool, highp>		highp_bvec2;
	typedef vec<3, bool, highp>		highp_bvec3;
	typedef vec<4, bool, highp>		highp_bvec4;

	typedef vec<1, bool, defaultp>	bvec1;
	typedef vec<2, bool, defaultp>	bvec2;
	typedef vec<3, bool, defaultp>	bvec3;
	typedef vec<4, bool, defaultp>	bvec4;

	// Vector int

	typedef vec<1, int, lowp>		lowp_ivec1;
	typedef vec<2, int, lowp>		lowp_ivec2;
	typedef vec<3, int, lowp>		lowp_ivec3;
	typedef vec<4, int, lowp>		lowp_ivec4;

	typedef vec<1, int, mediump>	mediump_ivec1;
	typedef vec<2, int, mediump>	mediump_ivec2;
	typedef vec<3, int, mediump>	mediump_ivec3;
	typedef vec<4, int, mediump>	mediump_ivec4;

	typedef vec<1, int, highp>		highp_ivec1;
	typedef vec<2, int, highp>		highp_ivec2;
	typedef vec<3, int, highp>		highp_ivec3;
	typedef vec<4, int, highp>		highp_ivec4;

	typedef vec<1, int, defaultp>	ivec1;
	typedef vec<2, int, defaultp>	ivec2;
	typedef vec<3, int, defaultp>	ivec3;
	typedef vec<4, int, defaultp>	ivec4;

	typedef vec<1, i8, lowp>		lowp_i8vec1;
	typedef vec<2, i8, lowp>		lowp_i8vec2;
	typedef vec<3, i8, lowp>		lowp_i8vec3;
	typedef vec<4, i8, lowp>		lowp_i8vec4;

	typedef vec<1, i8, mediump>		mediump_i8vec1;
	typedef vec<2, i8, mediump>		mediump_i8vec2;
	typedef vec<3, i8, mediump>		mediump_i8vec3;
	typedef vec<4, i8, mediump>		mediump_i8vec4;

	typedef vec<1, i8, highp>		highp_i8vec1;
	typedef vec<2, i8, highp>		highp_i8vec2;
	typedef vec<3, i8, highp>		highp_i8vec3;
	typedef vec<4, i8, highp>		highp_i8vec4;

	typedef vec<1, i8, defaultp>	i8vec1;
	typedef vec<2, i8, defaultp>	i8vec2;
	typedef vec<3, i8, defaultp>	i8vec3;
	typedef vec<4, i8, defaultp>	i8vec4;

	typedef vec<1, i16, lowp>		lowp_i16vec1;
	typedef vec<2, i16, lowp>		lowp_i16vec2;
	typedef vec<3, i16, lowp>		lowp_i16vec3;
	typedef vec<4, i16, lowp>		lowp_i16vec4;

	typedef vec<1, i16, mediump>	mediump_i16vec1;
	typedef vec<2, i16, mediump>	mediump_i16vec2;
	typedef vec<3, i16, mediump>	mediump_i16vec3;
	typedef vec<4, i16, mediump>	mediump_i16vec4;

	typedef vec<1, i16, highp>		highp_i16vec1;
	typedef vec<2, i16, highp>		highp_i16vec2;
	typedef vec<3, i16, highp>		highp_i16vec3;
	typedef vec<4, i16, highp>		highp_i16vec4;

	typedef vec<1, i16, defaultp>	i16vec1;
	typedef vec<2, i16, defaultp>	i16vec2;
	typedef vec<3, i16, defaultp>	i16vec3;
	typedef vec<4, i16, defaultp>	i16vec4;

	typedef vec<1, i32, lowp>		lowp_i32vec1;
	typedef vec<2, i32, lowp>		lowp_i32vec2;
	typedef vec<3, i32, lowp>		lowp_i32vec3;
	typedef vec<4, i32, lowp>		lowp_i32vec4;

	typedef vec<1, i32, mediump>	mediump_i32vec1;
	typedef vec<2, i32, mediump>	mediump_i32vec2;
	typedef vec<3, i32, mediump>	mediump_i32vec3;
	typedef vec<4, i32, mediump>	mediump_i32vec4;

	typedef vec<1, i32, highp>		highp_i32vec1;
	typedef vec<2, i32, highp>		highp_i32vec2;
	typedef vec<3, i32, highp>		highp_i32vec3;
	typedef vec<4, i32, highp>		highp_i32vec4;

	typedef vec<1, i32, defaultp>	i32vec1;
	typedef vec<2, i32, defaultp>	i32vec2;
	typedef vec<3, i32, defaultp>	i32vec3;
	typedef vec<4, i32, defaultp>	i32vec4;

	typedef vec<1, i64, lowp>		lowp_i64vec1;
	typedef vec<2, i64, lowp>		lowp_i64vec2;
	typedef vec<3, i64, lowp>		lowp_i64vec3;
	typedef vec<4, i64, lowp>		lowp_i64vec4;

	typedef vec<1, i64, mediump>	mediump_i64vec1;
	typedef vec<2, i64, mediump>	mediump_i64vec2;
	typedef vec<3, i64, mediump>	mediump_i64vec3;
	typedef vec<4, i64, mediump>	mediump_i64vec4;

	typedef vec<1, i64, highp>		highp_i64vec1;
	typedef vec<2, i64, highp>		highp_i64vec2;
	typedef vec<3, i64, highp>		highp_i64vec3;
	typedef vec<4, i64, highp>		highp_i64vec4;

	typedef vec<1, i64, defaultp>	i64vec1;
	typedef vec<2, i64, defaultp>	i64vec2;
	typedef vec<3, i64, defaultp>	i64vec3;
	typedef vec<4, i64, defaultp>	i64vec4;

	// Vector uint

	typedef vec<1, uint, lowp>		lowp_uvec1;
	typedef vec<2, uint, lowp>		lowp_uvec2;
	typedef vec<3, uint, lowp>		lowp_uvec3;
	typedef vec<4, uint, lowp>		lowp_uvec4;

	typedef vec<1, uint, mediump>	mediump_uvec1;
	typedef vec<2, uint, mediump>	mediump_uvec2;
	typedef vec<3, uint, mediump>	mediump_uvec3;
	typedef vec<4, uint, mediump>	mediump_uvec4;

	typedef vec<1, uint, highp>		highp_uvec1;
	typedef vec<2, uint, highp>		highp_uvec2;
	typedef vec<3, uint, highp>		highp_uvec3;
	typedef vec<4, uint, highp>		highp_uvec4;

	typedef vec<1, uint, defaultp>	uvec1;
	typedef vec<2, uint, defaultp>	uvec2;
	typedef vec<3, uint, defaultp>	uvec3;
	typedef vec<4, uint, defaultp>	uvec4;

	typedef vec<1, u8, lowp>		lowp_u8vec1;
	typedef vec<2, u8, lowp>		lowp_u8vec2;
	typedef vec<3, u8, lowp>		lowp_u8vec3;
	typedef vec<4, u8, lowp>		lowp_u8vec4;

	typedef vec<1, u8, mediump>		mediump_u8vec1;
	typedef vec<2, u8, mediump>		mediump_u8vec2;
	typedef vec<3, u8, mediump>		mediump_u8vec3;
	typedef vec<4, u8, mediump>		mediump_u8vec4;

	typedef vec<1, u8, highp>		highp_u8vec1;
	typedef vec<2, u8, highp>		highp_u8vec2;
	typedef vec<3, u8, highp>		highp_u8vec3;
	typedef vec<4, u8, highp>		highp_u8vec4;

	typedef vec<1, u8, defaultp>	u8vec1;
	typedef vec<2, u8, defaultp>	u8vec2;
	typedef vec<3, u8, defaultp>	u8vec3;
	typedef vec<4, u8, defaultp>	u8vec4;

	typedef vec<1, u16, lowp>		lowp_u16vec1;
	typedef vec<2, u16, lowp>		lowp_u16vec2;
	typedef vec<3, u16, lowp>		lowp_u16vec3;
	typedef vec<4, u16, lowp>		lowp_u16vec4;

	typedef vec<1, u16, mediump>	mediump_u16vec1;
	typedef vec<2, u16, mediump>	mediump_u16vec2;
	typedef vec<3, u16, mediump>	mediump_u16vec3;
	typedef vec<4, u16, mediump>	mediump_u16vec4;

	typedef vec<1, u16, highp>		highp_u16vec1;
	typedef vec<2, u16, highp>		highp_u16vec2;
	typedef vec<3, u16, highp>		highp_u16vec3;
	typedef vec<4, u16, highp>		highp_u16vec4;

	typedef vec<1, u16, defaultp>	u16vec1;
	typedef vec<2, u16, defaultp>	u16vec2;
	typedef vec<3, u16, defaultp>	u16vec3;
	typedef vec<4, u16, defaultp>	u16vec4;

	typedef vec<1, u32, lowp>		lowp_u32vec1;
	typedef vec<2, u32, lowp>		lowp_u32vec2;
	typedef vec<3, u32, lowp>		lowp_u32vec3;
	typedef vec<4, u32, lowp>		lowp_u32vec4;

	typedef vec<1, u32, mediump>	mediump_u32vec1;
	typedef vec<2, u32, mediump>	mediump_u32vec2;
	typedef vec<3, u32, mediump>	mediump_u32vec3;
	typedef vec<4, u32, mediump>	mediump_u32vec4;

	typedef vec<1, u32, highp>		highp_u32vec1;
	typedef vec<2, u32, highp>		highp_u32vec2;
	typedef vec<3, u32, highp>		highp_u32vec3;
	typedef vec<4, u32, highp>		highp_u32vec4;

	typedef vec<1, u32, defaultp>	u32vec1;
	typedef vec<2, u32, defaultp>	u32vec2;
	typedef vec<3, u32, defaultp>	u32vec3;
	typedef vec<4, u32, defaultp>	u32vec4;

	typedef vec<1, u64, lowp>		lowp_u64vec1;
	typedef vec<2, u64, lowp>		lowp_u64vec2;
	typedef vec<3, u64, lowp>		lowp_u64vec3;
	typedef vec<4, u64, lowp>		lowp_u64vec4;

	typedef vec<1, u64, mediump>	mediump_u64vec1;
	typedef vec<2, u64, mediump>	mediump_u64vec2;
	typedef vec<3, u64, mediump>	mediump_u64vec3;
	typedef vec<4, u64, mediump>	mediump_u64vec4;

	typedef vec<1, u64, highp>		highp_u64vec1;
	typedef vec<2, u64, highp>		highp_u64vec2;
	typedef vec<3, u64, highp>		highp_u64vec3;
	typedef vec<4, u64, highp>		highp_u64vec4;

	typedef vec<1, u64, defaultp>	u64vec1;
	typedef vec<2, u64, defaultp>	u64vec2;
	typedef vec<3, u64, defaultp>	u64vec3;
	typedef vec<4, u64, defaultp>	u64vec4;

	// Vector float

	typedef vec<1, float, lowp>			lowp_vec1;
	typedef vec<2, float, lowp>			lowp_vec2;
	typedef vec<3, float, lowp>			lowp_vec3;
	typedef vec<4, float, lowp>			lowp_vec4;

	typedef vec<1, float, mediump>		mediump_vec1;
	typedef vec<2, float, mediump>		mediump_vec2;
	typedef vec<3, float, mediump>		mediump_vec3;
	typedef vec<4, float, mediump>		mediump_vec4;

	typedef vec<1, float, highp>		highp_vec1;
	typedef vec<2, float, highp>		highp_vec2;
	typedef vec<3, float, highp>		highp_vec3;
	typedef vec<4, float, highp>		highp_vec4;

	typedef vec<1, float, defaultp>		vec1;
	typedef vec<2, float, defaultp>		vec2;
	typedef vec<3, float, defaultp>		vec3;
	typedef vec<4, float, defaultp>		vec4;

	typedef vec<1, float, lowp>			lowp_fvec1;
	typedef vec<2, float, lowp>			lowp_fvec2;
	typedef vec<3, float, lowp>			lowp_fvec3;
	typedef vec<4, float, lowp>			lowp_fvec4;

	typedef vec<1, float, mediump>		mediump_fvec1;
	typedef vec<2, float, mediump>		mediump_fvec2;
	typedef vec<3, float, mediump>		mediump_fvec3;
	typedef vec<4, float, mediump>		mediump_fvec4;

	typedef vec<1, float, highp>		highp_fvec1;
	typedef vec<2, float, highp>		highp_fvec2;
	typedef vec<3, float, highp>		highp_fvec3;
	typedef vec<4, float, highp>		highp_fvec4;

	typedef vec<1, f32, defaultp>		fvec1;
	typedef vec<2, f32, defaultp>		fvec2;
	typedef vec<3, f32, defaultp>		fvec3;
	typedef vec<4, f32, defaultp>		fvec4;

	typedef vec<1, f32, lowp>			lowp_f32vec1;
	typedef vec<2, f32, lowp>			lowp_f32vec2;
	typedef vec<3, f32, lowp>			lowp_f32vec3;
	typedef vec<4, f32, lowp>			lowp_f32vec4;

	typedef vec<1, f32, mediump>		mediump_f32vec1;
	typedef vec<2, f32, mediump>		mediump_f32vec2;
	typedef vec<3, f32, mediump>		mediump_f32vec3;
	typedef vec<4, f32, mediump>		mediump_f32vec4;

	typedef vec<1, f32, highp>			highp_f32vec1;
	typedef vec<2, f32, highp>			highp_f32vec2;
	typedef vec<3, f32, highp>			highp_f32vec3;
	typedef vec<4, f32, highp>			highp_f32vec4;

	typedef vec<1, f32, defaultp>		f32vec1;
	typedef vec<2, f32, defaultp>		f32vec2;
	typedef vec<3, f32, defaultp>		f32vec3;
	typedef vec<4, f32, defaultp>		f32vec4;

	typedef vec<1, f64, lowp>			lowp_dvec1;
	typedef vec<2, f64, lowp>			lowp_dvec2;
	typedef vec<3, f64, lowp>			lowp_dvec3;
	typedef vec<4, f64, lowp>			lowp_dvec4;

	typedef vec<1, f64, mediump>		mediump_dvec1;
	typedef vec<2, f64, mediump>		mediump_dvec2;
	typedef vec<3, f64, mediump>		mediump_dvec3;
	typedef vec<4, f64, mediump>		mediump_dvec4;

	typedef vec<1, f64, highp>			highp_dvec1;
	typedef vec<2, f64, highp>			highp_dvec2;
	typedef vec<3, f64, highp>			highp_dvec3;
	typedef vec<4, f64, highp>			highp_dvec4;

	typedef vec<1, f64, defaultp>		dvec1;
	typedef vec<2, f64, defaultp>		dvec2;
	typedef vec<3, f64, defaultp>		dvec3;
	typedef vec<4, f64, defaultp>		dvec4;

	typedef vec<1, f64, lowp>			lowp_f64vec1;
	typedef vec<2, f64, lowp>			lowp_f64vec2;
	typedef vec<3, f64, lowp>			lowp_f64vec3;
	typedef vec<4, f64, lowp>			lowp_f64vec4;

	typedef vec<1, f64, mediump>		mediump_f64vec1;
	typedef vec<2, f64, mediump>		mediump_f64vec2;
	typedef vec<3, f64, mediump>		mediump_f64vec3;
	typedef vec<4, f64, mediump>		mediump_f64vec4;

	typedef vec<1, f64, highp>			highp_f64vec1;
	typedef vec<2, f64, highp>			highp_f64vec2;
	typedef vec<3, f64, highp>			highp_f64vec3;
	typedef vec<4, f64, highp>			highp_f64vec4;

	typedef vec<1, f64, defaultp>		f64vec1;
	typedef vec<2, f64, defaultp>		f64vec2;
	typedef vec<3, f64, defaultp>		f64vec3;
	typedef vec<4, f64, defaultp>		f64vec4;

	// Matrix NxN

	typedef mat<2, 2, f32, lowp>		lowp_mat2;
	typedef mat<3, 3, f32, lowp>		lowp_mat3;
	typedef mat<4, 4, f32, lowp>		lowp_mat4;

	typedef mat<2, 2, f32, mediump>		mediump_mat2;
	typedef mat<3, 3, f32, mediump>		mediump_mat3;
	typedef mat<4, 4, f32, mediump>		mediump_mat4;

	typedef mat<2, 2, f32, highp>		highp_mat2;
	typedef mat<3, 3, f32, highp>		highp_mat3;
	typedef mat<4, 4, f32, highp>		highp_mat4;

	typedef mat<2, 2, f32, defaultp>	mat2;
	typedef mat<3, 3, f32, defaultp>	mat3;
	typedef mat<4, 4, f32, defaultp>	mat4;

	typedef mat<2, 2, f32, lowp>		lowp_fmat2;
	typedef mat<3, 3, f32, lowp>		lowp_fmat3;
	typedef mat<4, 4, f32, lowp>		lowp_fmat4;

	typedef mat<2, 2, f32, mediump>		mediump_fmat2;
	typedef mat<3, 3, f32, mediump>		mediump_fmat3;
	typedef mat<4, 4, f32, mediump>		mediump_fmat4;

	typedef mat<2, 2, f32, highp>		highp_fmat2;
	typedef mat<3, 3, f32, highp>		highp_fmat3;
	typedef mat<4, 4, f32, highp>		highp_fmat4;

	typedef mat<2, 2, f32, defaultp>	fmat2;
	typedef mat<3, 3, f32, defaultp>	fmat3;
	typedef mat<4, 4, f32, defaultp>	fmat4;

	typedef mat<2, 2, f32, lowp>		lowp_f32mat2;
	typedef mat<3, 3, f32, lowp>		lowp_f32mat3;
	typedef mat<4, 4, f32, lowp>		lowp_f32mat4;

	typedef mat<2, 2, f32, mediump>		mediump_f32mat2;
	typedef mat<3, 3, f32, mediump>		mediump_f32mat3;
	typedef mat<4, 4, f32, mediump>		mediump_f32mat4;

	typedef mat<2, 2, f32, highp>		highp_f32mat2;
	typedef mat<3, 3, f32, highp>		highp_f32mat3;
	typedef mat<4, 4, f32, highp>		highp_f32mat4;

	typedef mat<2, 2, f32, defaultp>	f32mat2;
	typedef mat<3, 3, f32, defaultp>	f32mat3;
	typedef mat<4, 4, f32, defaultp>	f32mat4;

	typedef mat<2, 2, f64, lowp>		lowp_dmat2;
	typedef mat<3, 3, f64, lowp>		lowp_dmat3;
	typedef mat<4, 4, f64, lowp>		lowp_dmat4;

	typedef mat<2, 2, f64, mediump>		mediump_dmat2;
	typedef mat<3, 3, f64, mediump>		mediump_dmat3;
	typedef mat<4, 4, f64, mediump>		mediump_dmat4;

	typedef mat<2, 2, f64, highp>		highp_dmat2;
	typedef mat<3, 3, f64, highp>		highp_dmat3;
	typedef mat<4, 4, f64, highp>		highp_dmat4;

	typedef mat<2, 2, f64, defaultp>	dmat2;
	typedef mat<3, 3, f64, defaultp>	dmat3;
	typedef mat<4, 4, f64, defaultp>	dmat4;

	typedef mat<2, 2, f64, lowp>		lowp_f64mat2;
	typedef mat<3, 3, f64, lowp>		lowp_f64mat3;
	typedef mat<4, 4, f64, lowp>		lowp_f64mat4;

	typedef mat<2, 2, f64, mediump>		mediump_f64mat2;
	typedef mat<3, 3, f64, mediump>		mediump_f64mat3;
	typedef mat<4, 4, f64, mediump>		mediump_f64mat4;

	typedef mat<2, 2, f64, highp>		highp_f64mat2;
	typedef mat<3, 3, f64, highp>		highp_f64mat3;
	typedef mat<4, 4, f64, highp>		highp_f64mat4;

	typedef mat<2, 2, f64, defaultp>	f64mat2;
	typedef mat<3, 3, f64, defaultp>	f64mat3;
	typedef mat<4, 4, f64, defaultp>	f64mat4;

	// Matrix MxN

	typedef mat<2, 2, f32, lowp>		lowp_mat2x2;
	typedef mat<2, 3, f32, lowp>		lowp_mat2x3;
	typedef mat<2, 4, f32, lowp>		lowp_mat2x4;
	typedef mat<3, 2, f32, lowp>		lowp_mat3x2;
	typedef mat<3, 3, f32, lowp>		lowp_mat3x3;
	typedef mat<3, 4, f32, lowp>		lowp_mat3x4;
	typedef mat<4, 2, f32, lowp>		lowp_mat4x2;
	typedef mat<4, 3, f32, lowp>		lowp_mat4x3;
	typedef mat<4, 4, f32, lowp>		lowp_mat4x4;

	typedef mat<2, 2, f32, mediump>		mediump_mat2x2;
	typedef mat<2, 3, f32, mediump>		mediump_mat2x3;
	typedef mat<2, 4, f32, mediump>		mediump_mat2x4;
	typedef mat<3, 2, f32, mediump>		mediump_mat3x2;
	typedef mat<3, 3, f32, mediump>		mediump_mat3x3;
	typedef mat<3, 4, f32, mediump>		mediump_mat3x4;
	typedef mat<4, 2, f32, mediump>		mediump_mat4x2;
	typedef mat<4, 3, f32, mediump>		mediump_mat4x3;
	typedef mat<4, 4, f32, mediump>		mediump_mat4x4;

	typedef mat<2, 2, f32, highp>		highp_mat2x2;
	typedef mat<2, 3, f32, highp>		highp_mat2x3;
	typedef mat<2, 4, f32, highp>		highp_mat2x4;
	typedef mat<3, 2, f32, highp>		highp_mat3x2;
	typedef mat<3, 3, f32, highp>		highp_mat3x3;
	typedef mat<3, 4, f32, highp>		highp_mat3x4;
	typedef mat<4, 2, f32, highp>		highp_mat4x2;
	typedef mat<4, 3, f32, highp>		highp_mat4x3;
	typedef mat<4, 4, f32, highp>		highp_mat4x4;

	typedef mat<2, 2, f32, defaultp>	mat2x2;
	typedef mat<3, 2, f32, defaultp>	mat3x2;
	typedef mat<4, 2, f32, defaultp>	mat4x2;
	typedef mat<2, 3, f32, defaultp>	mat2x3;
	typedef mat<3, 3, f32, defaultp>	mat3x3;
	typedef mat<4, 3, f32, defaultp>	mat4x3;
	typedef mat<2, 4, f32, defaultp>	mat2x4;
	typedef mat<3, 4, f32, defaultp>	mat3x4;
	typedef mat<4, 4, f32, defaultp>	mat4x4;

	typedef mat<2, 2, f32, lowp>		lowp_fmat2x2;
	typedef mat<2, 3, f32, lowp>		lowp_fmat2x3;
	typedef mat<2, 4, f32, lowp>		lowp_fmat2x4;
	typedef mat<3, 2, f32, lowp>		lowp_fmat3x2;
	typedef mat<3, 3, f32, lowp>		lowp_fmat3x3;
	typedef mat<3, 4, f32, lowp>		lowp_fmat3x4;
	typedef mat<4, 2, f32, lowp>		lowp_fmat4x2;
	typedef mat<4, 3, f32, lowp>		lowp_fmat4x3;
	typedef mat<4, 4, f32, lowp>		lowp_fmat4x4;

	typedef mat<2, 2, f32, mediump>		mediump_fmat2x2;
	typedef mat<2, 3, f32, mediump>		mediump_fmat2x3;
	typedef mat<2, 4, f32, mediump>		mediump_fmat2x4;
	typedef mat<3, 2, f32, mediump>		mediump_fmat3x2;
	typedef mat<3, 3, f32, mediump>		mediump_fmat3x3;
	typedef mat<3, 4, f32, mediump>		mediump_fmat3x4;
	typedef mat<4, 2, f32, mediump>		mediump_fmat4x2;
	typedef mat<4, 3, f32, mediump>		mediump_fmat4x3;
	typedef mat<4, 4, f32, mediump>		mediump_fmat4x4;

	typedef mat<2, 2, f32, highp>		highp_fmat2x2;
	typedef mat<2, 3, f32, highp>		highp_fmat2x3;
	typedef mat<2, 4, f32, highp>		highp_fmat2x4;
	typedef mat<3, 2, f32, highp>		highp_fmat3x2;
	typedef mat<3, 3, f32, highp>		highp_fmat3x3;
	typedef mat<3, 4, f32, highp>		highp_fmat3x4;
	typedef mat<4, 2, f32, highp>		highp_fmat4x2;
	typedef mat<4, 3, f32, highp>		highp_fmat4x3;
	typedef mat<4, 4, f32, highp>		highp_fmat4x4;

	typedef mat<2, 2, f32, defaultp>	fmat2x2;
	typedef mat<3, 2, f32, defaultp>	fmat3x2;
	typedef mat<4, 2, f32, defaultp>	fmat4x2;
	typedef mat<2, 3, f32, defaultp>	fmat2x3;
	typedef mat<3, 3, f32, defaultp>	fmat3x3;
	typedef mat<4, 3, f32, defaultp>	fmat4x3;
	typedef mat<2, 4, f32, defaultp>	fmat2x4;
	typedef mat<3, 4, f32, defaultp>	fmat3x4;
	typedef mat<4, 4, f32, defaultp>	fmat4x4;

	typedef mat<2, 2, f32, lowp>		lowp_f32mat2x2;
	typedef mat<2, 3, f32, lowp>		lowp_f32mat2x3;
	typedef mat<2, 4, f32, lowp>		lowp_f32mat2x4;
	typedef mat<3, 2, f32, lowp>		lowp_f32mat3x2;
	typedef mat<3, 3, f32, lowp>		lowp_f32mat3x3;
	typedef mat<3, 4, f32, lowp>		lowp_f32mat3x4;
	typedef mat<4, 2, f32, lowp>		lowp_f32mat4x2;
	typedef mat<4, 3, f32, lowp>		lowp_f32mat4x3;
	typedef mat<4, 4, f32, lowp>		lowp_f32mat4x4;
	
	typedef mat<2, 2, f32, mediump>		mediump_f32mat2x2;
	typedef mat<2, 3, f32, mediump>		mediump_f32mat2x3;
	typedef mat<2, 4, f32, mediump>		mediump_f32mat2x4;
	typedef mat<3, 2, f32, mediump>		mediump_f32mat3x2;
	typedef mat<3, 3, f32, mediump>		mediump_f32mat3x3;
	typedef mat<3, 4, f32, mediump>		mediump_f32mat3x4;
	typedef mat<4, 2, f32, mediump>		mediump_f32mat4x2;
	typedef mat<4, 3, f32, mediump>		mediump_f32mat4x3;
	typedef mat<4, 4, f32, mediump>		mediump_f32mat4x4;

	typedef mat<2, 2, f32, highp>		highp_f32mat2x2;
	typedef mat<2, 3, f32, highp>		highp_f32mat2x3;
	typedef mat<2, 4, f32, highp>		highp_f32mat2x4;
	typedef mat<3, 2, f32, highp>		highp_f32mat3x2;
	typedef mat<3, 3, f32, highp>		highp_f32mat3x3;
	typedef mat<3, 4, f32, highp>		highp_f32mat3x4;
	typedef mat<4, 2, f32, highp>		highp_f32mat4x2;
	typedef mat<4, 3, f32, highp>		highp_f32mat4x3;
	typedef mat<4, 4, f32, highp>		highp_f32mat4x4;

	typedef mat<2, 2, f32, defaultp>	f32mat2x2;
	typedef mat<3, 2, f32, defaultp>	f32mat3x2;
	typedef mat<4, 2, f32, defaultp>	f32mat4x2;
	typedef mat<2, 3, f32, defaultp>	f32mat2x3;
	typedef mat<3, 3, f32, defaultp>	f32mat3x3;
	typedef mat<4, 3, f32, defaultp>	f32mat4x3;
	typedef mat<2, 4, f32, defaultp>	f32mat2x4;
	typedef mat<3, 4, f32, defaultp>	f32mat3x4;
	typedef mat<4, 4, f32, defaultp>	f32mat4x4;

	typedef mat<2, 2, double, lowp>		lowp_dmat2x2;
	typedef mat<2, 3, double, lowp>		lowp_dmat2x3;
	typedef mat<2, 4, double, lowp>		lowp_dmat2x4;
	typedef mat<3, 2, double, lowp>		lowp_dmat3x2;
	typedef mat<3, 3, double, lowp>		lowp_dmat3x3;
	typedef mat<3, 4, double, lowp>		lowp_dmat3x4;
	typedef mat<4, 2, double, lowp>		lowp_dmat4x2;
	typedef mat<4, 3, double, lowp>		lowp_dmat4x3;
	typedef mat<4, 4, double, lowp>		lowp_dmat4x4;

	typedef mat<2, 2, double, mediump>	mediump_dmat2x2;
	typedef mat<2, 3, double, mediump>	mediump_dmat2x3;
	typedef mat<2, 4, double, mediump>	mediump_dmat2x4;
	typedef mat<3, 2, double, mediump>	mediump_dmat3x2;
	typedef mat<3, 3, double, mediump>	mediump_dmat3x3;
	typedef mat<3, 4, double, mediump>	mediump_dmat3x4;
	typedef mat<4, 2, double, mediump>	mediump_dmat4x2;
	typedef mat<4, 3, double, mediump>	mediump_dmat4x3;
	typedef mat<4, 4, double, mediump>	mediump_dmat4x4;

	typedef mat<2, 2, double, highp>	highp_dmat2x2;
	typedef mat<2, 3, double, highp>	highp_dmat2x3;
	typedef mat<2, 4, double, highp>	highp_dmat2x4;
	typedef mat<3, 2, double, highp>	highp_dmat3x2;
	typedef mat<3, 3, double, highp>	highp_dmat3x3;
	typedef mat<3, 4, double, highp>	highp_dmat3x4;
	typedef mat<4, 2, double, highp>	highp_dmat4x2;
	typedef mat<4, 3, double, highp>	highp_dmat4x3;
	typedef mat<4, 4, double, highp>	highp_dmat4x4;

	typedef mat<2, 2, double, defaultp>	dmat2x2;
	typedef mat<3, 2, double, defaultp>	dmat3x2;
	typedef mat<4, 2, double, defaultp>	dmat4x2;
	typedef mat<2, 3, double, defaultp>	dmat2x3;
	typedef mat<3, 3, double, defaultp>	dmat3x3;
	typedef mat<4, 3, double, defaultp>	dmat4x3;
	typedef mat<2, 4, double, defaultp>	dmat2x4;
	typedef mat<3, 4, double, defaultp>	dmat3x4;
	typedef mat<4, 4, double, defaultp>	dmat4x4;

	typedef mat<2, 2, f64, lowp>		lowp_f64mat2x2;
	typedef mat<2, 3, f64, lowp>		lowp_f64mat2x3;
	typedef mat<2, 4, f64, lowp>		lowp_f64mat2x4;
	typedef mat<3, 2, f64, lowp>		lowp_f64mat3x2;
	typedef mat<3, 3, f64, lowp>		lowp_f64mat3x3;
	typedef mat<3, 4, f64, lowp>		lowp_f64mat3x4;
	typedef mat<4, 2, f64, lowp>		lowp_f64mat4x2;
	typedef mat<4, 3, f64, lowp>		lowp_f64mat4x3;
	typedef mat<4, 4, f64, lowp>		lowp_f64mat4x4;

	typedef mat<2, 2, f64, mediump>		mediump_f64mat2x2;
	typedef mat<2, 3, f64, mediump>		mediump_f64mat2x3;
	typedef mat<2, 4, f64, mediump>		mediump_f64mat2x4;
	typedef mat<3, 2, f64, mediump>		mediump_f64mat3x2;
	typedef mat<3, 3, f64, mediump>		mediump_f64mat3x3;
	typedef mat<3, 4, f64, mediump>		mediump_f64mat3x4;
	typedef mat<4, 2, f64, mediump>		mediump_f64mat4x2;
	typedef mat<4, 3, f64, mediump>		mediump_f64mat4x3;
	typedef mat<4, 4, f64, mediump>		mediump_f64mat4x4;

	typedef mat<2, 2, f64, highp>		highp_f64mat2x2;
	typedef mat<2, 3, f64, highp>		highp_f64mat2x3;
	typedef mat<2, 4, f64, highp>		highp_f64mat2x4;
	typedef mat<3, 2, f64, highp>		highp_f64mat3x2;
	typedef mat<3, 3, f64, highp>		highp_f64mat3x3;
	typedef mat<3, 4, f64, highp>		highp_f64mat3x4;
	typedef mat<4, 2, f64, highp>		highp_f64mat4x2;
	typedef mat<4, 3, f64, highp>		highp_f64mat4x3;
	typedef mat<4, 4, f64, highp>		highp_f64mat4x4;

	typedef mat<2, 2, f64, defaultp>	f64mat2x2;
	typedef mat<3, 2, f64, defaultp>	f64mat3x2;
	typedef mat<4, 2, f64, defaultp>	f64mat4x2;
	typedef mat<2, 3, f64, defaultp>	f64mat2x3;
	typedef mat<3, 3, f64, defaultp>	f64mat3x3;
	typedef mat<4, 3, f64, defaultp>	f64mat4x3;
	typedef mat<2, 4, f64, defaultp>	f64mat2x4;
	typedef mat<3, 4, f64, defaultp>	f64mat3x4;
	typedef mat<4, 4, f64, defaultp>	f64mat4x4;

	// Signed integer matrix MxN

	typedef mat<2, 2, int, lowp>		lowp_imat2x2;
	typedef mat<2, 3, int, lowp>		lowp_imat2x3;
	typedef mat<2, 4, int, lowp>		lowp_imat2x4;
	typedef mat<3, 2, int, lowp>		lowp_imat3x2;
	typedef mat<3, 3, int, lowp>		lowp_imat3x3;
	typedef mat<3, 4, int, lowp>		lowp_imat3x4;
	typedef mat<4, 2, int, lowp>		lowp_imat4x2;
	typedef mat<4, 3, int, lowp>		lowp_imat4x3;
	typedef mat<4, 4, int, lowp>		lowp_imat4x4;

	typedef mat<2, 2, int, mediump>		mediump_imat2x2;
	typedef mat<2, 3, int, mediump>		mediump_imat2x3;
	typedef mat<2, 4, int, mediump>		mediump_imat2x4;
	typedef mat<3, 2, int, mediump>		mediump_imat3x2;
	typedef mat<3, 3, int, mediump>		mediump_imat3x3;
	typedef mat<3, 4, int, mediump>		mediump_imat3x4;
	typedef mat<4, 2, int, mediump>		mediump_imat4x2;
	typedef mat<4, 3, int, mediump>		mediump_imat4x3;
	typedef mat<4, 4, int, mediump>		mediump_imat4x4;

	typedef mat<2, 2, int, highp>		highp_imat2x2;
	typedef mat<2, 3, int, highp>		highp_imat2x3;
	typedef mat<2, 4, int, highp>		highp_imat2x4;
	typedef mat<3, 2, int, highp>		highp_imat3x2;
	typedef mat<3, 3, int, highp>		highp_imat3x3;
	typedef mat<3, 4, int, highp>		highp_imat3x4;
	typedef mat<4, 2, int, highp>		highp_imat4x2;
	typedef mat<4, 3, int, highp>		highp_imat4x3;
	typedef mat<4, 4, int, highp>		highp_imat4x4;

	typedef mat<2, 2, int, defaultp>	imat2x2;
	typedef mat<3, 2, int, defaultp>	imat3x2;
	typedef mat<4, 2, int, defaultp>	imat4x2;
	typedef mat<2, 3, int, defaultp>	imat2x3;
	typedef mat<3, 3, int, defaultp>	imat3x3;
	typedef mat<4, 3, int, defaultp>	imat4x3;
	typedef mat<2, 4, int, defaultp>	imat2x4;
	typedef mat<3, 4, int, defaultp>	imat3x4;
	typedef mat<4, 4, int, defaultp>	imat4x4;


	typedef mat<2, 2, int8, lowp>		lowp_i8mat2x2;
	typedef mat<2, 3, int8, lowp>		lowp_i8mat2x3;
	typedef mat<2, 4, int8, lowp>		lowp_i8mat2x4;
	typedef mat<3, 2, int8, lowp>		lowp_i8mat3x2;
	typedef mat<3, 3, int8, lowp>		lowp_i8mat3x3;
	typedef mat<3, 4, int8, lowp>		lowp_i8mat3x4;
	typedef mat<4, 2, int8, lowp>		lowp_i8mat4x2;
	typedef mat<4, 3, int8, lowp>		lowp_i8mat4x3;
	typedef mat<4, 4, int8, lowp>		lowp_i8mat4x4;

	typedef mat<2, 2, int8, mediump>	mediump_i8mat2x2;
	typedef mat<2, 3, int8, mediump>	mediump_i8mat2x3;
	typedef mat<2, 4, int8, mediump>	mediump_i8mat2x4;
	typedef mat<3, 2, int8, mediump>	mediump_i8mat3x2;
	typedef mat<3, 3, int8, mediump>	mediump_i8mat3x3;
	typedef mat<3, 4, int8, mediump>	mediump_i8mat3x4;
	typedef mat<4, 2, int8, mediump>	mediump_i8mat4x2;
	typedef mat<4, 3, int8, mediump>	mediump_i8mat4x3;
	typedef mat<4, 4, int8, mediump>	mediump_i8mat4x4;

	typedef mat<2, 2, int8, highp>		highp_i8mat2x2;
	typedef mat<2, 3, int8, highp>		highp_i8mat2x3;
	typedef mat<2, 4, int8, highp>		highp_i8mat2x4;
	typedef mat<3, 2, int8, highp>		highp_i8mat3x2;
	typedef mat<3, 3, int8, highp>		highp_i8mat3x3;
	typedef mat<3, 4, int8, highp>		highp_i8mat3x4;
	typedef mat<4, 2, int8, highp>		highp_i8mat4x2;
	typedef mat<4, 3, int8, highp>		highp_i8mat4x3;
	typedef mat<4, 4, int8, highp>		highp_i8mat4x4;

	typedef mat<2, 2, int8, defaultp>	i8mat2x2;
	typedef mat<3, 2, int8, defaultp>	i8mat3x2;
	typedef mat<4, 2, int8, defaultp>	i8mat4x2;
	typedef mat<2, 3, int8, defaultp>	i8mat2x3;
	typedef mat<3, 3, int8, defaultp>	i8mat3x3;
	typedef mat<4, 3, int8, defaultp>	i8mat4x3;
	typedef mat<2, 4, int8, defaultp>	i8mat2x4;
	typedef mat<3, 4, int8, defaultp>	i8mat3x4;
	typedef mat<4, 4, int8, defaultp>	i8mat4x4;


	typedef mat<2, 2, int16, lowp>		lowp_i16mat2x2;
	typedef mat<2, 3, int16, lowp>		lowp_i16mat2x3;
	typedef mat<2, 4, int16, lowp>		lowp_i16mat2x4;
	typedef mat<3, 2, int16, lowp>		lowp_i16mat3x2;
	typedef mat<3, 3, int16, lowp>		lowp_i16mat3x3;
	typedef mat<3, 4, int16, lowp>		lowp_i16mat3x4;
	typedef mat<4, 2, int16, lowp>		lowp_i16mat4x2;
	typedef mat<4, 3, int16, lowp>		lowp_i16mat4x3;
	typedef mat<4, 4, int16, lowp>		lowp_i16mat4x4;

	typedef mat<2, 2, int16, mediump>	mediump_i16mat2x2;
	typedef mat<2, 3, int16, mediump>	mediump_i16mat2x3;
	typedef mat<2, 4, int16, mediump>	mediump_i16mat2x4;
	typedef mat<3, 2, int16, mediump>	mediump_i16mat3x2;
	typedef mat<3, 3, int16, mediump>	mediump_i16mat3x3;
	typedef mat<3, 4, int16, mediump>	mediump_i16mat3x4;
	typedef mat<4, 2, int16, mediump>	mediump_i16mat4x2;
	typedef mat<4, 3, int16, mediump>	mediump_i16mat4x3;
	typedef mat<4, 4, int16, mediump>	mediump_i16mat4x4;

	typedef mat<2, 2, int16, highp>		highp_i16mat2x2;
	typedef mat<2, 3, int16, highp>		highp_i16mat2x3;
	typedef mat<2, 4, int16, highp>		highp_i16mat2x4;
	typedef mat<3, 2, int16, highp>		highp_i16mat3x2;
	typedef mat<3, 3, int16, highp>		highp_i16mat3x3;
	typedef mat<3, 4, int16, highp>		highp_i16mat3x4;
	typedef mat<4, 2, int16, highp>		highp_i16mat4x2;
	typedef mat<4, 3, int16, highp>		highp_i16mat4x3;
	typedef mat<4, 4, int16, highp>		highp_i16mat4x4;

	typedef mat<2, 2, int16, defaultp>	i16mat2x2;
	typedef mat<3, 2, int16, defaultp>	i16mat3x2;
	typedef mat<4, 2, int16, defaultp>	i16mat4x2;
	typedef mat<2, 3, int16, defaultp>	i16mat2x3;
	typedef mat<3, 3, int16, defaultp>	i16mat3x3;
	typedef mat<4, 3, int16, defaultp>	i16mat4x3;
	typedef mat<2, 4, int16, defaultp>	i16mat2x4;
	typedef mat<3, 4, int16, defaultp>	i16mat3x4;
	typedef mat<4, 4, int16, defaultp>	i16mat4x4;


	typedef mat<2, 2, int32, lowp>		lowp_i32mat2x2;
	typedef mat<2, 3, int32, lowp>		lowp_i32mat2x3;
	typedef mat<2, 4, int32, lowp>		lowp_i32mat2x4;
	typedef mat<3, 2, int32, lowp>		lowp_i32mat3x2;
	typedef mat<3, 3, int32, lowp>		lowp_i32mat3x3;
	typedef mat<3, 4, int32, lowp>		lowp_i32mat3x4;
	typedef mat<4, 2, int32, lowp>		lowp_i32mat4x2;
	typedef mat<4, 3, int32, lowp>		lowp_i32mat4x3;
	typedef mat<4, 4, int32, lowp>		lowp_i32mat4x4;

	typedef mat<2, 2, int32, mediump>	mediump_i32mat2x2;
	typedef mat<2, 3, int32, mediump>	mediump_i32mat2x3;
	typedef mat<2, 4, int32, mediump>	mediump_i32mat2x4;
	typedef mat<3, 2, int32, mediump>	mediump_i32mat3x2;
	typedef mat<3, 3, int32, mediump>	mediump_i32mat3x3;
	typedef mat<3, 4, int32, mediump>	mediump_i32mat3x4;
	typedef mat<4, 2, int32, mediump>	mediump_i32mat4x2;
	typedef mat<4, 3, int32, mediump>	mediump_i32mat4x3;
	typedef mat<4, 4, int32, mediump>	mediump_i32mat4x4;

	typedef mat<2, 2, int32, highp>		highp_i32mat2x2;
	typedef mat<2, 3, int32, highp>		highp_i32mat2x3;
	typedef mat<2, 4, int32, highp>		highp_i32mat2x4;
	typedef mat<3, 2, int32, highp>		highp_i32mat3x2;
	typedef mat<3, 3, int32, highp>		highp_i32mat3x3;
	typedef mat<3, 4, int32, highp>		highp_i32mat3x4;
	typedef mat<4, 2, int32, highp>		highp_i32mat4x2;
	typedef mat<4, 3, int32, highp>		highp_i32mat4x3;
	typedef mat<4, 4, int32, highp>		highp_i32mat4x4;

	typedef mat<2, 2, int32, defaultp>	i32mat2x2;
	typedef mat<3, 2, int32, defaultp>	i32mat3x2;
	typedef mat<4, 2, int32, defaultp>	i32mat4x2;
	typedef mat<2, 3, int32, defaultp>	i32mat2x3;
	typedef mat<3, 3, int32, defaultp>	i32mat3x3;
	typedef mat<4, 3, int32, defaultp>	i32mat4x3;
	typedef mat<2, 4, int32, defaultp>	i32mat2x4;
	typedef mat<3, 4, int32, defaultp>	i32mat3x4;
	typedef mat<4, 4, int32, defaultp>	i32mat4x4;


	typedef mat<2, 2, int64, lowp>		lowp_i64mat2x2;
	typedef mat<2, 3, int64, lowp>		lowp_i64mat2x3;
	typedef mat<2, 4, int64, lowp>		lowp_i64mat2x4;
	typedef mat<3, 2, int64, lowp>		lowp_i64mat3x2;
	typedef mat<3, 3, int64, lowp>		lowp_i64mat3x3;
	typedef mat<3, 4, int64, lowp>		lowp_i64mat3x4;
	typedef mat<4, 2, int64, lowp>		lowp_i64mat4x2;
	typedef mat<4, 3, int64, lowp>		lowp_i64mat4x3;
	typedef mat<4, 4, int64, lowp>		lowp_i64mat4x4;

	typedef mat<2, 2, int64, mediump>	mediump_i64mat2x2;
	typedef mat<2, 3, int64, mediump>	mediump_i64mat2x3;
	typedef mat<2, 4, int64, mediump>	mediump_i64mat2x4;
	typedef mat<3, 2, int64, mediump>	mediump_i64mat3x2;
	typedef mat<3, 3, int64, mediump>	mediump_i64mat3x3;
	typedef mat<3, 4, int64, mediump>	mediump_i64mat3x4;
	typedef mat<4, 2, int64, mediump>	mediump_i64mat4x2;
	typedef mat<4, 3, int64, mediump>	mediump_i64mat4x3;
	typedef mat<4, 4, int64, mediump>	mediump_i64mat4x4;

	typedef mat<2, 2, int64, highp>		highp_i64mat2x2;
	typedef mat<2, 3, int64, highp>		highp_i64mat2x3;
	typedef mat<2, 4, int64, highp>		highp_i64mat2x4;
	typedef mat<3, 2, int64, highp>		highp_i64mat3x2;
	typedef mat<3, 3, int64, highp>		highp_i64mat3x3;
	typedef mat<3, 4, int64, highp>		highp_i64mat3x4;
	typedef mat<4, 2, int64, highp>		highp_i64mat4x2;
	typedef mat<4, 3, int64, highp>		highp_i64mat4x3;
	typedef mat<4, 4, int64, highp>		highp_i64mat4x4;

	typedef mat<2, 2, int64, defaultp>	i64mat2x2;
	typedef mat<3, 2, int64, defaultp>	i64mat3x2;
	typedef mat<4, 2, int64, defaultp>	i64mat4x2;
	typedef mat<2, 3, int64, defaultp>	i64mat2x3;
	typedef mat<3, 3, int64, defaultp>	i64mat3x3;
	typedef mat<4, 3, int64, defaultp>	i64mat4x3;
	typedef mat<2, 4, int64, defaultp>	i64mat2x4;
	typedef mat<3, 4, int64, defaultp>	i64mat3x4;
	typedef mat<4, 4, int64, defaultp>	i64mat4x4;


	// Unsigned integer matrix MxN

	typedef mat<2, 2, uint, lowp>		lowp_umat2x2;
	typedef mat<2, 3, uint, lowp>		lowp_umat2x3;
	typedef mat<2, 4, uint, lowp>		lowp_umat2x4;
	typedef mat<3, 2, uint, lowp>		lowp_umat3x2;
	typedef mat<3, 3, uint, lowp>		lowp_umat3x3;
	typedef mat<3, 4, uint, lowp>		lowp_umat3x4;
	typedef mat<4, 2, uint, lowp>		lowp_umat4x2;
	typedef mat<4, 3, uint, lowp>		lowp_umat4x3;
	typedef mat<4, 4, uint, lowp>		lowp_umat4x4;

	typedef mat<2, 2, uint, mediump>	mediump_umat2x2;
	typedef mat<2, 3, uint, mediump>	mediump_umat2x3;
	typedef mat<2, 4, uint, mediump>	mediump_umat2x4;
	typedef mat<3, 2, uint, mediump>	mediump_umat3x2;
	typedef mat<3, 3, uint, mediump>	mediump_umat3x3;
	typedef mat<3, 4, uint, mediump>	mediump_umat3x4;
	typedef mat<4, 2, uint, mediump>	mediump_umat4x2;
	typedef mat<4, 3, uint, mediump>	mediump_umat4x3;
	typedef mat<4, 4, uint, mediump>	mediump_umat4x4;

	typedef mat<2, 2, uint, highp>		highp_umat2x2;
	typedef mat<2, 3, uint, highp>		highp_umat2x3;
	typedef mat<2, 4, uint, highp>		highp_umat2x4;
	typedef mat<3, 2, uint, highp>		highp_umat3x2;
	typedef mat<3, 3, uint, highp>		highp_umat3x3;
	typedef mat<3, 4, uint, highp>		highp_umat3x4;
	typedef mat<4, 2, uint, highp>		highp_umat4x2;
	typedef mat<4, 3, uint, highp>		highp_umat4x3;
	typedef mat<4, 4, uint, highp>		highp_umat4x4;

	typedef mat<2, 2, uint, defaultp>	umat2x2;
	typedef mat<3, 2, uint, defaultp>	umat3x2;
	typedef mat<4, 2, uint, defaultp>	umat4x2;
	typedef mat<2, 3, uint, defaultp>	umat2x3;
	typedef mat<3, 3, uint, defaultp>	umat3x3;
	typedef mat<4, 3, uint, defaultp>	umat4x3;
	typedef mat<2, 4, uint, defaultp>	umat2x4;
	typedef mat<3, 4, uint, defaultp>	umat3x4;
	typedef mat<4, 4, uint, defaultp>	umat4x4;


	typedef mat<2, 2, uint8, lowp>		lowp_u8mat2x2;
	typedef mat<2, 3, uint8, lowp>		lowp_u8mat2x3;
	typedef mat<2, 4, uint8, lowp>		lowp_u8mat2x4;
	typedef mat<3, 2, uint8, lowp>		lowp_u8mat3x2;
	typedef mat<3, 3, uint8, lowp>		lowp_u8mat3x3;
	typedef mat<3, 4, uint8, lowp>		lowp_u8mat3x4;
	typedef mat<4, 2, uint8, lowp>		lowp_u8mat4x2;
	typedef mat<4, 3, uint8, lowp>		lowp_u8mat4x3;
	typedef mat<4, 4, uint8, lowp>		lowp_u8mat4x4;

	typedef mat<2, 2, uint8, mediump>	mediump_u8mat2x2;
	typedef mat<2, 3, uint8, mediump>	mediump_u8mat2x3;
	typedef mat<2, 4, uint8, mediump>	mediump_u8mat2x4;
	typedef mat<3, 2, uint8, mediump>	mediump_u8mat3x2;
	typedef mat<3, 3, uint8, mediump>	mediump_u8mat3x3;
	typedef mat<3, 4, uint8, mediump>	mediump_u8mat3x4;
	typedef mat<4, 2, uint8, mediump>	mediump_u8mat4x2;
	typedef mat<4, 3, uint8, mediump>	mediump_u8mat4x3;
	typedef mat<4, 4, uint8, mediump>	mediump_u8mat4x4;

	typedef mat<2, 2, uint8, highp>		highp_u8mat2x2;
	typedef mat<2, 3, uint8, highp>		highp_u8mat2x3;
	typedef mat<2, 4, uint8, highp>		highp_u8mat2x4;
	typedef mat<3, 2, uint8, highp>		highp_u8mat3x2;
	typedef mat<3, 3, uint8, highp>		highp_u8mat3x3;
	typedef mat<3, 4, uint8, highp>		highp_u8mat3x4;
	typedef mat<4, 2, uint8, highp>		highp_u8mat4x2;
	typedef mat<4, 3, uint8, highp>		highp_u8mat4x3;
	typedef mat<4, 4, uint8, highp>		highp_u8mat4x4;

	typedef mat<2, 2, uint8, defaultp>	u8mat2x2;
	typedef mat<3, 2, uint8, defaultp>	u8mat3x2;
	typedef mat<4, 2, uint8, defaultp>	u8mat4x2;
	typedef mat<2, 3, uint8, defaultp>	u8mat2x3;
	typedef mat<3, 3, uint8, defaultp>	u8mat3x3;
	typedef mat<4, 3, uint8, defaultp>	u8mat4x3;
	typedef mat<2, 4, uint8, defaultp>	u8mat2x4;
	typedef mat<3, 4, uint8, defaultp>	u8mat3x4;
	typedef mat<4, 4, uint8, defaultp>	u8mat4x4;


	typedef mat<2, 2, uint16, lowp>		lowp_u16mat2x2;
	typedef mat<2, 3, uint16, lowp>		lowp_u16mat2x3;
	typedef mat<2, 4, uint16, lowp>		lowp_u16mat2x4;
	typedef mat<3, 2, uint16, lowp>		lowp_u16mat3x2;
	typedef mat<3, 3, uint16, lowp>		lowp_u16mat3x3;
	typedef mat<3, 4, uint16, lowp>		lowp_u16mat3x4;
	typedef mat<4, 2, uint16, lowp>		lowp_u16mat4x2;
	typedef mat<4, 3, uint16, lowp>		lowp_u16mat4x3;
	typedef mat<4, 4, uint16, lowp>		lowp_u16mat4x4;

	typedef mat<2, 2, uint16, mediump>	mediump_u16mat2x2;
	typedef mat<2, 3, uint16, mediump>	mediump_u16mat2x3;
	typedef mat<2, 4, uint16, mediump>	mediump_u16mat2x4;
	typedef mat<3, 2, uint16, mediump>	mediump_u16mat3x2;
	typedef mat<3, 3, uint16, mediump>	mediump_u16mat3x3;
	typedef mat<3, 4, uint16, mediump>	mediump_u16mat3x4;
	typedef mat<4, 2, uint16, mediump>	mediump_u16mat4x2;
	typedef mat<4, 3, uint16, mediump>	mediump_u16mat4x3;
	typedef mat<4, 4, uint16, mediump>	mediump_u16mat4x4;

	typedef mat<2, 2, uint16, highp>	highp_u16mat2x2;
	typedef mat<2, 3, uint16, highp>	highp_u16mat2x3;
	typedef mat<2, 4, uint16, highp>	highp_u16mat2x4;
	typedef mat<3, 2, uint16, highp>	highp_u16mat3x2;
	typedef mat<3, 3, uint16, highp>	highp_u16mat3x3;
	typedef mat<3, 4, uint16, highp>	highp_u16mat3x4;
	typedef mat<4, 2, uint16, highp>	highp_u16mat4x2;
	typedef mat<4, 3, uint16, highp>	highp_u16mat4x3;
	typedef mat<4, 4, uint16, highp>	highp_u16mat4x4;

	typedef mat<2, 2, uint16, defaultp>	u16mat2x2;
	typedef mat<3, 2, uint16, defaultp>	u16mat3x2;
	typedef mat<4, 2, uint16, defaultp>	u16mat4x2;
	typedef mat<2, 3, uint16, defaultp>	u16mat2x3;
	typedef mat<3, 3, uint16, defaultp>	u16mat3x3;
	typedef mat<4, 3, uint16, defaultp>	u16mat4x3;
	typedef mat<2, 4, uint16, defaultp>	u16mat2x4;
	typedef mat<3, 4, uint16, defaultp>	u16mat3x4;
	typedef mat<4, 4, uint16, defaultp>	u16mat4x4;


	typedef mat<2, 2, uint32, lowp>		lowp_u32mat2x2;
	typedef mat<2, 3, uint32, lowp>		lowp_u32mat2x3;
	typedef mat<2, 4, uint32, lowp>		lowp_u32mat2x4;
	typedef mat<3, 2, uint32, lowp>		lowp_u32mat3x2;
	typedef mat<3, 3, uint32, lowp>		lowp_u32mat3x3;
	typedef mat<3, 4, uint32, lowp>		lowp_u32mat3x4;
	typedef mat<4, 2, uint32, lowp>		lowp_u32mat4x2;
	typedef mat<4, 3, uint32, lowp>		lowp_u32mat4x3;
	typedef mat<4, 4, uint32, lowp>		lowp_u32mat4x4;

	typedef mat<2, 2, uint32, mediump>	mediump_u32mat2x2;
	typedef mat<2, 3, uint32, mediump>	mediump_u32mat2x3;
	typedef mat<2, 4, uint32, mediump>	mediump_u32mat2x4;
	typedef mat<3, 2, uint32, mediump>	mediump_u32mat3x2;
	typedef mat<3, 3, uint32, mediump>	mediump_u32mat3x3;
	typedef mat<3, 4, uint32, mediump>	mediump_u32mat3x4;
	typedef mat<4, 2, uint32, mediump>	mediump_u32mat4x2;
	typedef mat<4, 3, uint32, mediump>	mediump_u32mat4x3;
	typedef mat<4, 4, uint32, mediump>	mediump_u32mat4x4;

	typedef mat<2, 2, uint32, highp>	highp_u32mat2x2;
	typedef mat<2, 3, uint32, highp>	highp_u32mat2x3;
	typedef mat<2, 4, uint32, highp>	highp_u32mat2x4;
	typedef mat<3, 2, uint32, highp>	highp_u32mat3x2;
	typedef mat<3, 3, uint32, highp>	highp_u32mat3x3;
	typedef mat<3, 4, uint32, highp>	highp_u32mat3x4;
	typedef mat<4, 2, uint32, highp>	highp_u32mat4x2;
	typedef mat<4, 3, uint32, highp>	highp_u32mat4x3;
	typedef mat<4, 4, uint32, highp>	highp_u32mat4x4;

	typedef mat<2, 2, uint32, defaultp>	u32mat2x2;
	typedef mat<3, 2, uint32, defaultp>	u32mat3x2;
	typedef mat<4, 2, uint32, defaultp>	u32mat4x2;
	typedef mat<2, 3, uint32, defaultp>	u32mat2x3;
	typedef mat<3, 3, uint32, defaultp>	u32mat3x3;
	typedef mat<4, 3, uint32, defaultp>	u32mat4x3;
	typedef mat<2, 4, uint32, defaultp>	u32mat2x4;
	typedef mat<3, 4, uint32, defaultp>	u32mat3x4;
	typedef mat<4, 4, uint32, defaultp>	u32mat4x4;


	typedef mat<2, 2, uint64, lowp>		lowp_u64mat2x2;
	typedef mat<2, 3, uint64, lowp>		lowp_u64mat2x3;
	typedef mat<2, 4, uint64, lowp>		lowp_u64mat2x4;
	typedef mat<3, 2, uint64, lowp>		lowp_u64mat3x2;
	typedef mat<3, 3, uint64, lowp>		lowp_u64mat3x3;
	typedef mat<3, 4, uint64, lowp>		lowp_u64mat3x4;
	typedef mat<4, 2, uint64, lowp>		lowp_u64mat4x2;
	typedef mat<4, 3, uint64, lowp>		lowp_u64mat4x3;
	typedef mat<4, 4, uint64, lowp>		lowp_u64mat4x4;

	typedef mat<2, 2, uint64, mediump>	mediump_u64mat2x2;
	typedef mat<2, 3, uint64, mediump>	mediump_u64mat2x3;
	typedef mat<2, 4, uint64, mediump>	mediump_u64mat2x4;
	typedef mat<3, 2, uint64, mediump>	mediump_u64mat3x2;
	typedef mat<3, 3, uint64, mediump>	mediump_u64mat3x3;
	typedef mat<3, 4, uint64, mediump>	mediump_u64mat3x4;
	typedef mat<4, 2, uint64, mediump>	mediump_u64mat4x2;
	typedef mat<4, 3, uint64, mediump>	mediump_u64mat4x3;
	typedef mat<4, 4, uint64, mediump>	mediump_u64mat4x4;

	typedef mat<2, 2, uint64, highp>	highp_u64mat2x2;
	typedef mat<2, 3, uint64, highp>	highp_u64mat2x3;
	typedef mat<2, 4, uint64, highp>	highp_u64mat2x4;
	typedef mat<3, 2, uint64, highp>	highp_u64mat3x2;
	typedef mat<3, 3, uint64, highp>	highp_u64mat3x3;
	typedef mat<3, 4, uint64, highp>	highp_u64mat3x4;
	typedef mat<4, 2, uint64, highp>	highp_u64mat4x2;
	typedef mat<4, 3, uint64, highp>	highp_u64mat4x3;
	typedef mat<4, 4, uint64, highp>	highp_u64mat4x4;

	typedef mat<2, 2, uint64, defaultp>	u64mat2x2;
	typedef mat<3, 2, uint64, defaultp>	u64mat3x2;
	typedef mat<4, 2, uint64, defaultp>	u64mat4x2;
	typedef mat<2, 3, uint64, defaultp>	u64mat2x3;
	typedef mat<3, 3, uint64, defaultp>	u64mat3x3;
	typedef mat<4, 3, uint64, defaultp>	u64mat4x3;
	typedef mat<2, 4, uint64, defaultp>	u64mat2x4;
	typedef mat<3, 4, uint64, defaultp>	u64mat3x4;
	typedef mat<4, 4, uint64, defaultp>	u64mat4x4;

	// Quaternion

	typedef qua<float, lowp>			lowp_quat;
	typedef qua<float, mediump>			mediump_quat;
	typedef qua<float, highp>			highp_quat;
	typedef qua<float, defaultp>		quat;

	typedef qua<float, lowp>			lowp_fquat;
	typedef qua<float, mediump>			mediump_fquat;
	typedef qua<float, highp>			highp_fquat;
	typedef qua<float, defaultp>		fquat;

	typedef qua<f32, lowp>				lowp_f32quat;
	typedef qua<f32, mediump>			mediump_f32quat;
	typedef qua<f32, highp>				highp_f32quat;
	typedef qua<f32, defaultp>			f32quat;

	typedef qua<double, lowp>			lowp_dquat;
	typedef qua<double, mediump>		mediump_dquat;
	typedef qua<double, highp>			highp_dquat;
	typedef qua<double, defaultp>		dquat;

	typedef qua<f64, lowp>				lowp_f64quat;
	typedef qua<f64, mediump>			mediump_f64quat;
	typedef qua<f64, highp>				highp_f64quat;
	typedef qua<f64, defaultp>			f64quat;
}//namespace glm

// ----------------------------------------

// ---------- #include "vec2.hpp" ----------
    // ----------------------------------------------

    #if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
    #	include "_swizzle.hpp"
    #elif GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
    #	include "_swizzle_func.hpp"
    #endif
    #include <cstddef>

    namespace glm
    {
        template<typename T, qualifier Q>
        struct vec<2, T, Q>
        {
            // -- Implementation detail --

            typedef T value_type;
            typedef vec<2, T, Q> type;
            typedef vec<2, bool, Q> bool_type;

            // -- Data --

    #		if GLM_SILENT_WARNINGS == GLM_ENABLE
    #			if GLM_COMPILER & GLM_COMPILER_GCC
    #				pragma GCC diagnostic push
    #				pragma GCC diagnostic ignored "-Wpedantic"
    #			elif GLM_COMPILER & GLM_COMPILER_CLANG
    #				pragma clang diagnostic push
    #				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
    #				pragma clang diagnostic ignored "-Wnested-anon-types"
    #			elif GLM_COMPILER & GLM_COMPILER_VC
    #				pragma warning(push)
    #				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
    #			endif
    #		endif

    #		if GLM_CONFIG_XYZW_ONLY
                T x, y;
    #		elif GLM_CONFIG_ANONYMOUS_STRUCT == GLM_ENABLE
                union
                {
                    struct{ T x, y; };
                    struct{ T r, g; };
                    struct{ T s, t; };

                    typename detail::storage<2, T, detail::is_aligned<Q>::value>::type data;

    #				if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
                        GLM_SWIZZLE2_2_MEMBERS(T, Q, x, y)
                        GLM_SWIZZLE2_2_MEMBERS(T, Q, r, g)
                        GLM_SWIZZLE2_2_MEMBERS(T, Q, s, t)
                        GLM_SWIZZLE2_3_MEMBERS(T, Q, x, y)
                        GLM_SWIZZLE2_3_MEMBERS(T, Q, r, g)
                        GLM_SWIZZLE2_3_MEMBERS(T, Q, s, t)
                        GLM_SWIZZLE2_4_MEMBERS(T, Q, x, y)
                        GLM_SWIZZLE2_4_MEMBERS(T, Q, r, g)
                        GLM_SWIZZLE2_4_MEMBERS(T, Q, s, t)
    #				endif
                };
    #		else
                union {T x, r, s;};
                union {T y, g, t;};

    #			if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
                    GLM_SWIZZLE_GEN_VEC_FROM_VEC2(T, Q)
    #			endif//GLM_CONFIG_SWIZZLE
    #		endif

    #		if GLM_SILENT_WARNINGS == GLM_ENABLE
    #			if GLM_COMPILER & GLM_COMPILER_CLANG
    #				pragma clang diagnostic pop
    #			elif GLM_COMPILER & GLM_COMPILER_GCC
    #				pragma GCC diagnostic pop
    #			elif GLM_COMPILER & GLM_COMPILER_VC
    #				pragma warning(pop)
    #			endif
    #		endif

            // -- Component accesses --

            /// Return the count of components of the vector
            typedef length_t length_type;
            GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 2;}

            GLM_FUNC_DECL GLM_CONSTEXPR T& operator[](length_type i);
            GLM_FUNC_DECL GLM_CONSTEXPR T const& operator[](length_type i) const;

            // -- Implicit basic constructors --

            GLM_FUNC_DECL GLM_CONSTEXPR vec() GLM_DEFAULT;
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec const& v) GLM_DEFAULT;
            template<qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, T, P> const& v);

            // -- Explicit basic constructors --

            GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(T scalar);
            GLM_FUNC_DECL GLM_CONSTEXPR vec(T x, T y);

            // -- Conversion constructors --

            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(vec<1, U, P> const& v);

            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename A, typename B>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(A x, B y);
            template<typename A, typename B>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, Q> const& x, B y);
            template<typename A, typename B>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(A x, vec<1, B, Q> const& y);
            template<typename A, typename B>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, Q> const& x, vec<1, B, Q> const& y);

            // -- Conversion vector constructors --

            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<3, U, P> const& v);
            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<4, U, P> const& v);

            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<2, U, P> const& v);

            // -- Swizzle constructors --
    #		if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
                template<int E0, int E1>
                GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<2, T, Q, E0, E1,-1,-2> const& that)
                {
                    *this = that();
                }
    #		endif//GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR

            // -- Unary arithmetic operators --

            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator=(vec const& v) GLM_DEFAULT;

            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator+=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator+=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator+=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator-=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator-=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator-=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator*=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator*=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator*=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator/=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator/=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator/=(vec<2, U, Q> const& v);

            // -- Increment and decrement operators --

            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator++();
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator--();
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator++(int);
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator--(int);

            // -- Unary bit operators --

            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator%=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator%=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator%=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator&=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator&=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator&=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator|=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator|=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator|=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator^=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator^=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator^=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator<<=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator<<=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator<<=(vec<2, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator>>=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator>>=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> & operator>>=(vec<2, U, Q> const& v);
        };

        // -- Unary operators --

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v);

        // -- Binary operators --

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator+(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator+(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator-(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator-(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator*(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator*(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator*(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator*(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator*(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator/(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator/(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator/(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator/(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator/(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator%(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator%(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator%(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator%(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator%(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator&(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator&(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator&(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator&(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator&(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator|(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator|(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator|(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator|(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator|(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator^(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator^(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator^(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator^(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator^(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator<<(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<2, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator>>(T scalar, vec<2, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, T, Q> operator~(vec<2, T, Q> const& v);

        // -- Boolean operators --

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR bool operator!=(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2);

        template<qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, bool, Q> operator&&(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2);

        template<qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<2, bool, Q> operator||(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2);
    }//namespace glm

    #ifndef GLM_EXTERNAL_TEMPLATE

    namespace glm{
namespace detail
{
	template <typename T, bool isFloat>
	struct compute_equal
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static bool call(T a, T b)
		{
			return a == b;
		}
	};
/*
	template <typename T>
	struct compute_equal<T, true>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static bool call(T a, T b)
		{
			return detail::compute_abs<T, std::numeric_limits<T>::is_signed>::call(b - a) <= static_cast<T>(0);
			//return std::memcmp(&a, &b, sizeof(T)) == 0;
		}
	};
*/
}//namespace detail
}//namespace glm


namespace glm
{
	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0), y(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<2, T, Q> const& v)
			: x(v.x), y(v.y)
		{}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<2, T, P> const& v)
		: x(v.x), y(v.y)
	{}

	// -- Explicit basic constructors --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(T scalar)
		: x(scalar), y(scalar)
	{}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(T _x, T _y)
		: x(_x), y(_y)
	{}

	// -- Conversion scalar constructors --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(A _x, B _y)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<1, A, Q> const& _x, B _y)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(A _x, vec<1, B, Q> const& _y)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<1, A, Q> const& _x, vec<1, B, Q> const& _y)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
	{}

	// -- Conversion vector constructors --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<2, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<3, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{}

	// -- Component accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T & vec<2, T, Q>::operator[](typename vec<2, T, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T const& vec<2, T, Q>::operator[](typename vec<2, T, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator=(vec<2, T, Q> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}
#	endif

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator=(vec<2, U, Q> const& v)
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator+=(vec<1, U, Q> const& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator+=(vec<2, U, Q> const& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator-=(vec<1, U, Q> const& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator-=(vec<2, U, Q> const& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator*=(vec<1, U, Q> const& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator*=(vec<2, U, Q> const& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator/=(vec<1, U, Q> const& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator/=(vec<2, U, Q> const& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> vec<2, T, Q>::operator++(int)
	{
		vec<2, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> vec<2, T, Q>::operator--(int)
	{
		vec<2, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator%=(U scalar)
	{
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator%=(vec<1, U, Q> const& v)
	{
		this->x %= static_cast<T>(v.x);
		this->y %= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator%=(vec<2, U, Q> const& v)
	{
		this->x %= static_cast<T>(v.x);
		this->y %= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator&=(U scalar)
	{
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator&=(vec<1, U, Q> const& v)
	{
		this->x &= static_cast<T>(v.x);
		this->y &= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator&=(vec<2, U, Q> const& v)
	{
		this->x &= static_cast<T>(v.x);
		this->y &= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator|=(U scalar)
	{
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator|=(vec<1, U, Q> const& v)
	{
		this->x |= static_cast<T>(v.x);
		this->y |= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator|=(vec<2, U, Q> const& v)
	{
		this->x |= static_cast<T>(v.x);
		this->y |= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator^=(U scalar)
	{
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator^=(vec<1, U, Q> const& v)
	{
		this->x ^= static_cast<T>(v.x);
		this->y ^= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator^=(vec<2, U, Q> const& v)
	{
		this->x ^= static_cast<T>(v.x);
		this->y ^= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator<<=(U scalar)
	{
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		this->x <<= static_cast<T>(v.x);
		this->y <<= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator<<=(vec<2, U, Q> const& v)
	{
		this->x <<= static_cast<T>(v.x);
		this->y <<= static_cast<T>(v.y);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator>>=(U scalar)
	{
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		this->x >>= static_cast<T>(v.x);
		this->y >>= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator>>=(vec<2, U, Q> const& v)
	{
		this->x >>= static_cast<T>(v.x);
		this->y >>= static_cast<T>(v.y);
		return *this;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v)
	{
		return v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			-v.x,
			-v.y);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x + scalar,
			v.y + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x + v2.x,
			v1.y + v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator+(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar + v.x,
			scalar + v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator+(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x + v2.x,
			v1.x + v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator+(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x + v2.x,
			v1.y + v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x - scalar,
			v.y - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x - v2.x,
			v1.y - v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator-(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar - v.x,
			scalar - v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator-(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x - v2.x,
			v1.x - v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator-(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x - v2.x,
			v1.y - v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator*(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x * scalar,
			v.y * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator*(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x * v2.x,
			v1.y * v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator*(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar * v.x,
			scalar * v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator*(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x * v2.x,
			v1.x * v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator*(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x * v2.x,
			v1.y * v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator/(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x / scalar,
			v.y / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator/(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x / v2.x,
			v1.y / v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator/(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar / v.x,
			scalar / v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator/(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x / v2.x,
			v1.x / v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator/(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x / v2.x,
			v1.y / v2.y);
	}

	// -- Binary bit operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator%(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x % scalar,
			v.y % scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator%(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x % v2.x,
			v1.y % v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator%(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar % v.x,
			scalar % v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator%(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x % v2.x,
			v1.x % v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator%(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x % v2.x,
			v1.y % v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator&(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x & scalar,
			v.y & scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator&(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x & v2.x,
			v1.y & v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator&(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar & v.x,
			scalar & v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator&(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x & v2.x,
			v1.x & v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator&(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x & v2.x,
			v1.y & v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator|(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x | scalar,
			v.y | scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator|(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x | v2.x,
			v1.y | v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator|(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar | v.x,
			scalar | v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator|(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x | v2.x,
			v1.x | v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator|(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x | v2.x,
			v1.y | v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator^(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x ^ scalar,
			v.y ^ scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator^(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x ^ v2.x,
			v1.y ^ v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator^(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar ^ v.x,
			scalar ^ v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator^(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x ^ v2.x,
			v1.x ^ v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator^(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x ^ v2.x,
			v1.y ^ v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x << scalar,
			v.y << scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x << v2.x,
			v1.y << v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator<<(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar << v.x,
			scalar << v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x << v2.x,
			v1.x << v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator<<(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x << v2.x,
			v1.y << v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<2, T, Q> const& v, T scalar)
	{
		return vec<2, T, Q>(
			v.x >> scalar,
			v.y >> scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<2, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x >> v2.x,
			v1.y >> v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator>>(T scalar, vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			scalar >> v.x,
			scalar >> v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<1, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x >> v2.x,
			v1.x >> v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator>>(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return vec<2, T, Q>(
			v1.x >> v2.x,
			v1.y >> v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> operator~(vec<2, T, Q> const& v)
	{
		return vec<2, T, Q>(
			~v.x,
			~v.y);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.y, v2.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<2, T, Q> const& v1, vec<2, T, Q> const& v2)
	{
		return !(v1 == v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, bool, Q> operator&&(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2)
	{
		return vec<2, bool, Q>(v1.x && v2.x, v1.y && v2.y);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, bool, Q> operator||(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2)
	{
		return vec<2, bool, Q>(v1.x || v2.x, v1.y || v2.y);
	}
}//namespace glm

    #endif//GLM_EXTERNAL_TEMPLATE

    // ----------------------------------------------

    namespace glm
    {
        /// @addtogroup core_vector
        /// @{

        /// 2 components vector of boolean.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        typedef vec<2, bool, defaultp>		bvec2;

        /// @}
    }//namespace glm

    // ---------- ./ext/vector_bool2_precision.hpp ----------

    namespace glm
    {
        /// @addtogroup core_vector_precision
        /// @{

        /// 2 components vector of high qualifier bool numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, bool, highp>		highp_bvec2;

        /// 2 components vector of medium qualifier bool numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, bool, mediump>	mediump_bvec2;

        /// 2 components vector of low qualifier bool numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, bool, lowp>		lowp_bvec2;

        /// @}
    }//namespace glm

    // ------------------------------------------------------

    // ---------- "./ext/vector_float2.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector
        /// @{

        /// 2 components vector of single-precision floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        typedef vec<2, float, defaultp>	vec2;

        /// @}
    }//namespace glm

    // -----------------------------------------------

    // ---------- "./ext/vector_float2_precision.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector_precision
        /// @{

        /// 2 components vector of high single-qualifier floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, float, highp>		highp_vec2;

        /// 2 components vector of medium single-qualifier floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, float, mediump>		mediump_vec2;

        /// 2 components vector of low single-qualifier floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, float, lowp>			lowp_vec2;

        /// @}
    }//namespace glm

    // ---------------------------------------------------------

    // ---------- "./ext/vector_double2.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector
        /// @{

        /// 2 components vector of double-precision floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        typedef vec<2, double, defaultp>		dvec2;

        /// @}
    }//namespace glm

    // ------------------------------------------------

    // ---------- "./ext/vector_double2_precision.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector_precision
        /// @{

        /// 2 components vector of high double-qualifier floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, double, highp>		highp_dvec2;

        /// 2 components vector of medium double-qualifier floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, double, mediump>		mediump_dvec2;

        /// 2 components vector of low double-qualifier floating-point numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<2, double, lowp>		lowp_dvec2;

        /// @}
    }//namespace glm

    // ----------------------------------------------------------

    // ---------- "./ext/vector_int2.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector
        /// @{

        /// 2 components vector of signed integer numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        typedef vec<2, int, defaultp>		ivec2;

        /// @}
    }//namespace glm

    // ---------------------------------------------

    // ---------- "./ext/vector_int2_sized.hpp" ----------

    #if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
    #	pragma message("GLM: GLM_EXT_scalar_int_sized extension included")
    #endif

    namespace glm{
    namespace detail
    {
    #	if GLM_HAS_EXTENDED_INTEGER_TYPE
            typedef std::int8_t			int8;
            typedef std::int16_t		int16;
            typedef std::int32_t		int32;
    #	else
            typedef signed char			int8;
            typedef signed short		int16;
            typedef signed int			int32;
    #endif//

        template<>
        struct is_int<int8>
        {
            enum test {value = ~0};
        };

        template<>
        struct is_int<int16>
        {
            enum test {value = ~0};
        };

        template<>
        struct is_int<int64>
        {
            enum test {value = ~0};
        };
    }//namespace detail


        /// @addtogroup ext_scalar_int_sized
        /// @{

        /// 8 bit signed integer type.
        typedef detail::int8		int8;

        /// 16 bit signed integer type.
        typedef detail::int16		int16;

        /// 32 bit signed integer type.
        typedef detail::int32		int32;

        /// 64 bit signed integer type.
        typedef detail::int64		int64;

        /// @}
    }//namespace glm

    #if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
    #	pragma message("GLM: GLM_EXT_vector_int2_sized extension included")
    #endif

    namespace glm
    {
        /// @addtogroup ext_vector_int2_sized
        /// @{

        /// 8 bit signed integer vector of 2 components type.
        ///
        /// @see ext_vector_int2_sized
        typedef vec<2, int8, defaultp>		i8vec2;

        /// 16 bit signed integer vector of 2 components type.
        ///
        /// @see ext_vector_int2_sized
        typedef vec<2, int16, defaultp>		i16vec2;

        /// 32 bit signed integer vector of 2 components type.
        ///
        /// @see ext_vector_int2_sized
        typedef vec<2, int32, defaultp>		i32vec2;

        /// 64 bit signed integer vector of 2 components type.
        ///
        /// @see ext_vector_int2_sized
        typedef vec<2, int64, defaultp>		i64vec2;

        /// @}
    }//namespace glm

    // ---------------------------------------------------

    // ---------- "./ext/vector_uint2.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector
        /// @{

        /// 2 components vector of unsigned integer numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        typedef vec<2, unsigned int, defaultp>		uvec2;

        /// @}
    }//namespace glm

    // ----------------------------------------------

    // ---------- "./ext/vector_uint2_sized.hpp" ----------

    #if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
    #	pragma message("GLM: GLM_EXT_scalar_uint_sized extension included")
    #endif

    namespace glm{
    namespace detail
    {
    #	if GLM_HAS_EXTENDED_INTEGER_TYPE
            typedef std::uint8_t		uint8;
            typedef std::uint16_t		uint16;
            typedef std::uint32_t		uint32;
    #	else
            typedef unsigned char		uint8;
            typedef unsigned short		uint16;
            typedef unsigned int		uint32;
    #endif

        template<>
        struct is_int<uint8>
        {
            enum test {value = ~0};
        };

        template<>
        struct is_int<uint16>
        {
            enum test {value = ~0};
        };

        template<>
        struct is_int<uint64>
        {
            enum test {value = ~0};
        };
    }//namespace detail


        /// @addtogroup ext_scalar_uint_sized
        /// @{

        /// 8 bit unsigned integer type.
        typedef detail::uint8		uint8;

        /// 16 bit unsigned integer type.
        typedef detail::uint16		uint16;

        /// 32 bit unsigned integer type.
        typedef detail::uint32		uint32;

        /// 64 bit unsigned integer type.
        typedef detail::uint64		uint64;

        /// @}
    }//namespace glm

    #if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
    #	pragma message("GLM: GLM_EXT_vector_uint2_sized extension included")
    #endif

    namespace glm
    {
        /// @addtogroup ext_vector_uint2_sized
        /// @{

        /// 8 bit unsigned integer vector of 2 components type.
        ///
        /// @see ext_vector_uint2_sized
        typedef vec<2, uint8, defaultp>		u8vec2;

        /// 16 bit unsigned integer vector of 2 components type.
        ///
        /// @see ext_vector_uint2_sized
        typedef vec<2, uint16, defaultp>	u16vec2;

        /// 32 bit unsigned integer vector of 2 components type.
        ///
        /// @see ext_vector_uint2_sized
        typedef vec<2, uint32, defaultp>	u32vec2;

        /// 64 bit unsigned integer vector of 2 components type.
        ///
        /// @see ext_vector_uint2_sized
        typedef vec<2, uint64, defaultp>	u64vec2;

        /// @}
    }//namespace glm

    // ----------------------------------------------------
// -----------------------------------------

// ---------- #include "vec3.hpp" ----------

    // ---------- "./ext/vector_bool3.hpp" ----------

    #if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
    #	include "_swizzle.hpp"
    #elif GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
    #	include "_swizzle_func.hpp"
    #endif
    #include <cstddef>

    namespace glm
    {
        template<typename T, qualifier Q>
        struct vec<3, T, Q>
        {
            // -- Implementation detail --

            typedef T value_type;
            typedef vec<3, T, Q> type;
            typedef vec<3, bool, Q> bool_type;

            // -- Data --

    #		if GLM_SILENT_WARNINGS == GLM_ENABLE
    #			if GLM_COMPILER & GLM_COMPILER_GCC
    #				pragma GCC diagnostic push
    #				pragma GCC diagnostic ignored "-Wpedantic"
    #			elif GLM_COMPILER & GLM_COMPILER_CLANG
    #				pragma clang diagnostic push
    #				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
    #				pragma clang diagnostic ignored "-Wnested-anon-types"
    #			elif GLM_COMPILER & GLM_COMPILER_VC
    #				pragma warning(push)
    #				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
    #				if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
    #					pragma warning(disable: 4324)  // structure was padded due to alignment specifier
    #				endif
    #			endif
    #		endif

    #		if GLM_CONFIG_XYZW_ONLY
                T x, y, z;
    #		elif GLM_CONFIG_ANONYMOUS_STRUCT == GLM_ENABLE
                union
                {
                    struct{ T x, y, z; };
                    struct{ T r, g, b; };
                    struct{ T s, t, p; };

                    typename detail::storage<3, T, detail::is_aligned<Q>::value>::type data;

    #				if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
                        GLM_SWIZZLE3_2_MEMBERS(T, Q, x, y, z)
                        GLM_SWIZZLE3_2_MEMBERS(T, Q, r, g, b)
                        GLM_SWIZZLE3_2_MEMBERS(T, Q, s, t, p)
                        GLM_SWIZZLE3_3_MEMBERS(T, Q, x, y, z)
                        GLM_SWIZZLE3_3_MEMBERS(T, Q, r, g, b)
                        GLM_SWIZZLE3_3_MEMBERS(T, Q, s, t, p)
                        GLM_SWIZZLE3_4_MEMBERS(T, Q, x, y, z)
                        GLM_SWIZZLE3_4_MEMBERS(T, Q, r, g, b)
                        GLM_SWIZZLE3_4_MEMBERS(T, Q, s, t, p)
    #				endif
                };
    #		else
                union { T x, r, s; };
                union { T y, g, t; };
                union { T z, b, p; };

    #			if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
                    GLM_SWIZZLE_GEN_VEC_FROM_VEC3(T, Q)
    #			endif//GLM_CONFIG_SWIZZLE
    #		endif//GLM_LANG

    #		if GLM_SILENT_WARNINGS == GLM_ENABLE
    #			if GLM_COMPILER & GLM_COMPILER_CLANG
    #				pragma clang diagnostic pop
    #			elif GLM_COMPILER & GLM_COMPILER_GCC
    #				pragma GCC diagnostic pop
    #			elif GLM_COMPILER & GLM_COMPILER_VC
    #				pragma warning(pop)
    #			endif
    #		endif

            // -- Component accesses --

            /// Return the count of components of the vector
            typedef length_t length_type;
            GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 3;}

            GLM_FUNC_DECL GLM_CONSTEXPR T & operator[](length_type i);
            GLM_FUNC_DECL GLM_CONSTEXPR T const& operator[](length_type i) const;

            // -- Implicit basic constructors --

            GLM_FUNC_DECL GLM_CONSTEXPR vec() GLM_DEFAULT;
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec const& v) GLM_DEFAULT;
            template<qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<3, T, P> const& v);

            // -- Explicit basic constructors --

            GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(T scalar);
            GLM_FUNC_DECL GLM_CONSTEXPR vec(T a, T b, T c);

            // -- Conversion scalar constructors --

            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(vec<1, U, P> const& v);

            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(X x, Y y, Z z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, Z _z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, Z _z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, Y _y, vec<1, Z, Q> const& _z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z);
            template<typename X, typename Y, typename Z>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z);

            // -- Conversion vector constructors --

            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename A, typename B, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, B _z);
            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename A, typename B, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z);
            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename A, typename B, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(A _x, vec<2, B, P> const& _yz);
            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename A, typename B, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz);
            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<4, U, P> const& v);

            /// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
            template<typename U, qualifier P>
            GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<3, U, P> const& v);

            // -- Swizzle constructors --
    #		if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
                template<int E0, int E1, int E2>
                GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<3, T, Q, E0, E1, E2, -1> const& that)
                {
                    *this = that();
                }

                template<int E0, int E1>
                GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v, T const& scalar)
                {
                    *this = vec(v(), scalar);
                }

                template<int E0, int E1>
                GLM_FUNC_DECL GLM_CONSTEXPR vec(T const& scalar, detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v)
                {
                    *this = vec(scalar, v());
                }
    #		endif//GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR

            // -- Unary arithmetic operators --

            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q>& operator=(vec<3, T, Q> const& v) GLM_DEFAULT;

            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator+=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator+=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator+=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator-=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator-=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator-=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator*=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator*=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator*=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator/=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator/=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator/=(vec<3, U, Q> const& v);

            // -- Increment and decrement operators --

            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator++();
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator--();
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator++(int);
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator--(int);

            // -- Unary bit operators --

            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator%=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator%=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator%=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator&=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator&=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator&=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator|=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator|=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator|=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator^=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator^=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator^=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator<<=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator<<=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator<<=(vec<3, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator>>=(U scalar);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator>>=(vec<1, U, Q> const& v);
            template<typename U>
            GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> & operator>>=(vec<3, U, Q> const& v);
        };

        // -- Unary operators --

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v);

        // -- Binary operators --

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator+(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator+(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator-(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator-(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator/(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator/(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator%(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator%(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator&(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator&(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator|(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator|(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator^(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator^(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator<<(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v, T scalar);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v1, vec<1, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator>>(T scalar, vec<3, T, Q> const& v);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<1, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator~(vec<3, T, Q> const& v);

        // -- Boolean operators --

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<typename T, qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR bool operator!=(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2);

        template<qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, bool, Q> operator&&(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2);

        template<qualifier Q>
        GLM_FUNC_DECL GLM_CONSTEXPR vec<3, bool, Q> operator||(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2);
    }//namespace glm

    #ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0), y(0), z(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<3, T, Q> const& v)
			: x(v.x), y(v.y), z(v.z)
		{}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<3, T, P> const& v)
		: x(v.x), y(v.y), z(v.z)
	{}

	// -- Explicit basic constructors --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(T scalar)
		: x(scalar), y(scalar), z(scalar)
	{}

	template <typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(T _x, T _y, T _z)
		: x(_x), y(_y), z(_z)
	{}

	// -- Conversion scalar constructors --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.x))
		, z(static_cast<T>(v.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(X _x, Y _y, Z _z)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<1, X, Q> const& _x, Y _y, Z _z)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(X _x, vec<1, Y, Q> const& _y, Z _z)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(X _x, Y _y, vec<1, Z, Q> const& _z)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z.x))
	{}

	// -- Conversion vector constructors --

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<2, A, P> const& _xy, B _z)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_z))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_z.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(A _x, vec<2, B, P> const& _yz)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_yz.x))
		, z(static_cast<T>(_yz.y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_yz.x))
		, z(static_cast<T>(_yz.y))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<3, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
	{}

	// -- Component accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T & vec<3, T, Q>::operator[](typename vec<3, T, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
			case 0:
		return x;
			case 1:
		return y;
			case 2:
		return z;
		}
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T const& vec<3, T, Q>::operator[](typename vec<3, T, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>& vec<3, T, Q>::operator=(vec<3, T, Q> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}
#	endif

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>& vec<3, T, Q>::operator=(vec<3, U, Q> const& v)
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		this->z = static_cast<T>(v.z);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator+=(vec<1, U, Q> const& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.x);
		this->z += static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator+=(vec<3, U, Q> const& v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		this->z += static_cast<T>(v.z);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator-=(vec<1, U, Q> const& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.x);
		this->z -= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator-=(vec<3, U, Q> const& v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		this->z -= static_cast<T>(v.z);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator*=(vec<1, U, Q> const& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.x);
		this->z *= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator*=(vec<3, U, Q> const& v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		this->z *= static_cast<T>(v.z);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator/=(U v)
	{
		this->x /= static_cast<T>(v);
		this->y /= static_cast<T>(v);
		this->z /= static_cast<T>(v);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator/=(vec<1, U, Q> const& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.x);
		this->z /= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator/=(vec<3, U, Q> const& v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		this->z /= static_cast<T>(v.z);
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> vec<3, T, Q>::operator++(int)
	{
		vec<3, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> vec<3, T, Q>::operator--(int)
	{
		vec<3, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator%=(U scalar)
	{
		this->x %= scalar;
		this->y %= scalar;
		this->z %= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator%=(vec<1, U, Q> const& v)
	{
		this->x %= v.x;
		this->y %= v.x;
		this->z %= v.x;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator%=(vec<3, U, Q> const& v)
	{
		this->x %= v.x;
		this->y %= v.y;
		this->z %= v.z;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator&=(U scalar)
	{
		this->x &= scalar;
		this->y &= scalar;
		this->z &= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator&=(vec<1, U, Q> const& v)
	{
		this->x &= v.x;
		this->y &= v.x;
		this->z &= v.x;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator&=(vec<3, U, Q> const& v)
	{
		this->x &= v.x;
		this->y &= v.y;
		this->z &= v.z;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator|=(U scalar)
	{
		this->x |= scalar;
		this->y |= scalar;
		this->z |= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator|=(vec<1, U, Q> const& v)
	{
		this->x |= v.x;
		this->y |= v.x;
		this->z |= v.x;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator|=(vec<3, U, Q> const& v)
	{
		this->x |= v.x;
		this->y |= v.y;
		this->z |= v.z;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator^=(U scalar)
	{
		this->x ^= scalar;
		this->y ^= scalar;
		this->z ^= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator^=(vec<1, U, Q> const& v)
	{
		this->x ^= v.x;
		this->y ^= v.x;
		this->z ^= v.x;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator^=(vec<3, U, Q> const& v)
	{
		this->x ^= v.x;
		this->y ^= v.y;
		this->z ^= v.z;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator<<=(U scalar)
	{
		this->x <<= scalar;
		this->y <<= scalar;
		this->z <<= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		this->x <<= static_cast<T>(v.x);
		this->y <<= static_cast<T>(v.x);
		this->z <<= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator<<=(vec<3, U, Q> const& v)
	{
		this->x <<= static_cast<T>(v.x);
		this->y <<= static_cast<T>(v.y);
		this->z <<= static_cast<T>(v.z);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator>>=(U scalar)
	{
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		this->x >>= static_cast<T>(v.x);
		this->y >>= static_cast<T>(v.x);
		this->z >>= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> & vec<3, T, Q>::operator>>=(vec<3, U, Q> const& v)
	{
		this->x >>= static_cast<T>(v.x);
		this->y >>= static_cast<T>(v.y);
		this->z >>= static_cast<T>(v.z);
		return *this;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v)
	{
		return v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			-v.x,
			-v.y,
			-v.z);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x + scalar,
			v.y + scalar,
			v.z + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x + scalar.x,
			v.y + scalar.x,
			v.z + scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator+(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar + v.x,
			scalar + v.y,
			scalar + v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator+(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x + v.x,
			scalar.x + v.y,
			scalar.x + v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator+(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x - scalar,
			v.y - scalar,
			v.z - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x - scalar.x,
			v.y - scalar.x,
			v.z - scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator-(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar - v.x,
			scalar - v.y,
			scalar - v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator-(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x - v.x,
			scalar.x - v.y,
			scalar.x - v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator-(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x * scalar.x,
			v.y * scalar.x,
			v.z * scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x * v.x,
			scalar.x * v.y,
			scalar.x * v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x * v2.x,
			v1.y * v2.y,
			v1.z * v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x / scalar,
			v.y / scalar,
			v.z / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x / scalar.x,
			v.y / scalar.x,
			v.z / scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator/(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar / v.x,
			scalar / v.y,
			scalar / v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator/(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x / v.x,
			scalar.x / v.y,
			scalar.x / v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator/(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x / v2.x,
			v1.y / v2.y,
			v1.z / v2.z);
	}

	// -- Binary bit operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x % scalar,
			v.y % scalar,
			v.z % scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x % scalar.x,
			v.y % scalar.x,
			v.z % scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator%(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar % v.x,
			scalar % v.y,
			scalar % v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator%(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x % v.x,
			scalar.x % v.y,
			scalar.x % v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator%(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x % v2.x,
			v1.y % v2.y,
			v1.z % v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x & scalar,
			v.y & scalar,
			v.z & scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x & scalar.x,
			v.y & scalar.x,
			v.z & scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator&(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar & v.x,
			scalar & v.y,
			scalar & v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator&(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x & v.x,
			scalar.x & v.y,
			scalar.x & v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator&(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x & v2.x,
			v1.y & v2.y,
			v1.z & v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x | scalar,
			v.y | scalar,
			v.z | scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x | scalar.x,
			v.y | scalar.x,
			v.z | scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator|(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar | v.x,
			scalar | v.y,
			scalar | v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator|(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x | v.x,
			scalar.x | v.y,
			scalar.x | v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator|(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x | v2.x,
			v1.y | v2.y,
			v1.z | v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x ^ scalar,
			v.y ^ scalar,
			v.z ^ scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x ^ scalar.x,
			v.y ^ scalar.x,
			v.z ^ scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator^(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar ^ v.x,
			scalar ^ v.y,
			scalar ^ v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator^(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x ^ v.x,
			scalar.x ^ v.y,
			scalar.x ^ v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator^(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x ^ v2.x,
			v1.y ^ v2.y,
			v1.z ^ v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x << scalar,
			v.y << scalar,
			v.z << scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x << scalar.x,
			v.y << scalar.x,
			v.z << scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator<<(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar << v.x,
			scalar << v.y,
			scalar << v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x << v.x,
			scalar.x << v.y,
			scalar.x << v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator<<(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x << v2.x,
			v1.y << v2.y,
			v1.z << v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v, T scalar)
	{
		return vec<3, T, Q>(
			v.x >> scalar,
			v.y >> scalar,
			v.z >> scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<3, T, Q>(
			v.x >> scalar.x,
			v.y >> scalar.x,
			v.z >> scalar.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator>>(T scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar >> v.x,
			scalar >> v.y,
			scalar >> v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<1, T, Q> const& scalar, vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			scalar.x >> v.x,
			scalar.x >> v.y,
			scalar.x >> v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator>>(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return vec<3, T, Q>(
			v1.x >> v2.x,
			v1.y >> v2.y,
			v1.z >> v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator~(vec<3, T, Q> const& v)
	{
		return vec<3, T, Q>(
			~v.x,
			~v.y,
			~v.z);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.y, v2.y) &&
			detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.z, v2.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<3, T, Q> const& v1, vec<3, T, Q> const& v2)
	{
		return !(v1 == v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, bool, Q> operator&&(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2)
	{
		return vec<3, bool, Q>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, bool, Q> operator||(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2)
	{
		return vec<3, bool, Q>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
	}
}//namespace glm

    #endif//GLM_EXTERNAL_TEMPLATE

    namespace glm
    {
        /// @addtogroup core_vector
        /// @{

        /// 3 components vector of boolean.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        typedef vec<3, bool, defaultp>		bvec3;

        /// @}
    }//namespace glm

    // ------------------------------------------------

    // ---------- "./ext/vector_bool3_precision.hpp" ----------

    namespace glm
    {
        /// @addtogroup core_vector_precision
        /// @{

        /// 3 components vector of high qualifier bool numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<3, bool, highp>		highp_bvec3;

        /// 3 components vector of medium qualifier bool numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<3, bool, mediump>	mediump_bvec3;

        /// 3 components vector of low qualifier bool numbers.
        ///
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
        /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
        typedef vec<3, bool, lowp>		lowp_bvec3;

        /// @}
    }//namespace glm

    // --------------------------------------------------------

    // ---------- "./ext/vector_float3.hpp" ----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 3 components vector of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<3, float, defaultp>		vec3;

	/// @}
}//namespace glm

    // -----------------------------------------------

    // ---------- "./ext/vector_float3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_vector_precision
	/// @{

	/// 3 components vector of high single-qualifier floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<3, float, highp>		highp_vec3;

	/// 3 components vector of medium single-qualifier floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<3, float, mediump>		mediump_vec3;

	/// 3 components vector of low single-qualifier floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<3, float, lowp>			lowp_vec3;

	/// @}
}//namespace glm

    // ---------------------------------------------------------

    // ---------- "./ext/vector_double3.hpp" ----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 3 components vector of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<3, double, defaultp>		dvec3;

	/// @}
}//namespace glm


    // ------------------------------------------------

    // ---------- "./ext/vector_double3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_vector_precision
	/// @{

	/// 3 components vector of high double-qualifier floating-point numbers.
	/// There is no guarantee on the actual qualifier.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<3, double, highp>		highp_dvec3;

	/// 3 components vector of medium double-qualifier floating-point numbers.
	/// There is no guarantee on the actual qualifier.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<3, double, mediump>		mediump_dvec3;

	/// 3 components vector of low double-qualifier floating-point numbers.
	/// There is no guarantee on the actual qualifier.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<3, double, lowp>		lowp_dvec3;

	/// @}
}//namespace glm

    // ----------------------------------------------------------

    // ---------- "./ext/vector_int3.hpp" ----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 3 components vector of signed integer numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<3, int, defaultp>		ivec3;

	/// @}
}//namespace glm

    // ---------------------------------------------

    // ---------- "./ext/vector_int3_sized.hpp" ---------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_int3_sized extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_int3_sized
	/// @{

	/// 8 bit signed integer vector of 3 components type.
	///
	/// @see ext_vector_int3_sized
	typedef vec<3, int8, defaultp>		i8vec3;

	/// 16 bit signed integer vector of 3 components type.
	///
	/// @see ext_vector_int3_sized
	typedef vec<3, int16, defaultp>		i16vec3;

	/// 32 bit signed integer vector of 3 components type.
	///
	/// @see ext_vector_int3_sized
	typedef vec<3, int32, defaultp>		i32vec3;

	/// 64 bit signed integer vector of 3 components type.
	///
	/// @see ext_vector_int3_sized
	typedef vec<3, int64, defaultp>		i64vec3;

	/// @}
}//namespace glm

    // --------------------------------------------------

    // ---------- "./ext/vector_uint3.hpp" ----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 3 components vector of unsigned integer numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<3, unsigned int, defaultp>		uvec3;

	/// @}
}//namespace glm

    // ----------------------------------------------

    // ---------- "./ext/vector_uint3_sized.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_uint3_sized extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_uint3_sized
	/// @{

	/// 8 bit unsigned integer vector of 3 components type.
	///
	/// @see ext_vector_uint3_sized
	typedef vec<3, uint8, defaultp>		u8vec3;

	/// 16 bit unsigned integer vector of 3 components type.
	///
	/// @see ext_vector_uint3_sized
	typedef vec<3, uint16, defaultp>	u16vec3;

	/// 32 bit unsigned integer vector of 3 components type.
	///
	/// @see ext_vector_uint3_sized
	typedef vec<3, uint32, defaultp>	u32vec3;

	/// 64 bit unsigned integer vector of 3 components type.
	///
	/// @see ext_vector_uint3_sized
	typedef vec<3, uint64, defaultp>	u64vec3;

	/// @}
}//namespace glm

    // ----------------------------------------------------

// -----------------------------------------

// ---------- #include "vec4.hpp" ----------

    // ---------- "./ext/vector_bool4.hpp" -----------

    #if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
#	include "_swizzle.hpp"
#elif GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
#	include "_swizzle_func.hpp"
#endif
#include <cstddef>

namespace glm
{
	template<typename T, qualifier Q>
	struct vec<4, T, Q>
	{
		// -- Implementation detail --

		typedef T value_type;
		typedef vec<4, T, Q> type;
		typedef vec<4, bool, Q> bool_type;

		// -- Data --

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic push
#				pragma GCC diagnostic ignored "-Wpedantic"
#			elif GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic push
#				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#				pragma clang diagnostic ignored "-Wnested-anon-types"
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(push)
#				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#			endif
#		endif

#		if GLM_CONFIG_XYZW_ONLY
			T x, y, z, w;
#		elif GLM_CONFIG_ANONYMOUS_STRUCT == GLM_ENABLE
			union
			{
				struct { T x, y, z, w; };
				struct { T r, g, b, a; };
				struct { T s, t, p, q; };

				typename detail::storage<4, T, detail::is_aligned<Q>::value>::type data;

#				if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
					GLM_SWIZZLE4_2_MEMBERS(T, Q, x, y, z, w)
					GLM_SWIZZLE4_2_MEMBERS(T, Q, r, g, b, a)
					GLM_SWIZZLE4_2_MEMBERS(T, Q, s, t, p, q)
					GLM_SWIZZLE4_3_MEMBERS(T, Q, x, y, z, w)
					GLM_SWIZZLE4_3_MEMBERS(T, Q, r, g, b, a)
					GLM_SWIZZLE4_3_MEMBERS(T, Q, s, t, p, q)
					GLM_SWIZZLE4_4_MEMBERS(T, Q, x, y, z, w)
					GLM_SWIZZLE4_4_MEMBERS(T, Q, r, g, b, a)
					GLM_SWIZZLE4_4_MEMBERS(T, Q, s, t, p, q)
#				endif
			};
#		else
			union { T x, r, s; };
			union { T y, g, t; };
			union { T z, b, p; };
			union { T w, a, q; };

#			if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
				GLM_SWIZZLE_GEN_VEC_FROM_VEC4(T, Q)
#			endif
#		endif

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(pop)
#			endif
#		endif

		// -- Component accesses --

		typedef length_t length_type;

		/// Return the count of components of the vector
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 4;}

		GLM_FUNC_DECL GLM_CONSTEXPR T & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR T const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR vec() GLM_DEFAULT;
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<4, T, Q> const& v) GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<4, T, P> const& v);

		// -- Explicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR vec(T x, T y, T z, T w);

		// -- Conversion scalar constructors --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(vec<1, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, Y _y, Z _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, Z _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, Z _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, Y _y, vec<1, Z, Q> const& _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, W _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, Z _z, vec<1, W, Q> const& _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, Z _z, vec<1, W, Q> const& _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z, vec<1, W, Q> const& _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, Y _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w);
		template<typename X, typename Y, typename Z, typename W>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _Y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w);

		// -- Conversion vector constructors --

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, B _z, C _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z, C _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, B _z, vec<1, C, P> const& _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z, vec<1, C, P> const& _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A _x, vec<2, B, P> const& _yz, C _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz, C _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A _x, vec<2, B, P> const& _yz, vec<1, C, P> const& _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz, vec<1, C, P> const& _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A _x, B _y, vec<2, C, P> const& _zw);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, P> const& _x, B _y, vec<2, C, P> const& _zw);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A _x, vec<1, B, P> const& _y, vec<2, C, P> const& _zw);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, typename C, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, P> const& _x, vec<1, B, P> const& _y, vec<2, C, P> const& _zw);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<3, A, P> const& _xyz, B _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<3, A, P> const& _xyz, vec<1, B, P> const& _w);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A _x, vec<3, B, P> const& _yzw);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, P> const& _x, vec<3, B, P> const& _yzw);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, A, P> const& _xy, vec<2, B, P> const& _zw);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<4, U, P> const& v);

		// -- Swizzle constructors --
#		if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
			template<int E0, int E1, int E2, int E3>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<4, T, Q, E0, E1, E2, E3> const& that)
			{
				*this = that();
			}

			template<int E0, int E1, int F0, int F1>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v, detail::_swizzle<2, T, Q, F0, F1, -1, -2> const& u)
			{
				*this = vec<4, T, Q>(v(), u());
			}

			template<int E0, int E1>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(T const& x, T const& y, detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v)
			{
				*this = vec<4, T, Q>(x, y, v());
			}

			template<int E0, int E1>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(T const& x, detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v, T const& w)
			{
				*this = vec<4, T, Q>(x, v(), w);
			}

			template<int E0, int E1>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<2, T, Q, E0, E1, -1, -2> const& v, T const& z, T const& w)
			{
				*this = vec<4, T, Q>(v(), z, w);
			}

			template<int E0, int E1, int E2>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<3, T, Q, E0, E1, E2, -1> const& v, T const& w)
			{
				*this = vec<4, T, Q>(v(), w);
			}

			template<int E0, int E1, int E2>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(T const& x, detail::_swizzle<3, T, Q, E0, E1, E2, -1> const& v)
			{
				*this = vec<4, T, Q>(x, v());
			}
#		endif//GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR

		// -- Unary arithmetic operators --

		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator=(vec<4, T, Q> const& v) GLM_DEFAULT;

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator+=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator+=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator+=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator-=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator-=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator-=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator*=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator*=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator*=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator/=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator/=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q>& operator/=(vec<4, U, Q> const& v);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator++();
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator--();
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator++(int);
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator--(int);

		// -- Unary bit operators --

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator%=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator%=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator%=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator&=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator&=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator&=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator|=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator|=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator|=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator^=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator^=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator^=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator<<=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator<<=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator<<=(vec<4, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator>>=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator>>=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> & operator>>=(vec<4, U, Q> const& v);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v, T const & scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator+(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator+(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v, T const & scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator-(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator-(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v, T const & scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator/(vec<4, T, Q> const& v, T const & scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator/(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator/(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator/(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator/(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator%(vec<4, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator%(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator%(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator%(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator%(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator&(vec<4, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator&(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator&(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator&(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator&(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator|(vec<4, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator|(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator|(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator|(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator|(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator^(vec<4, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator^(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator^(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator^(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator^(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<4, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator<<(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<4, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator>>(T scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator~(vec<4, T, Q> const& v);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator!=(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2);

	template<qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, bool, Q> operator&&(vec<4, bool, Q> const& v1, vec<4, bool, Q> const& v2);

	template<qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, bool, Q> operator||(vec<4, bool, Q> const& v1, vec<4, bool, Q> const& v2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm{
namespace detail
{
	template<typename T, qualifier Q, bool Aligned>
	struct compute_vec4_add
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_vec4_sub
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_vec4_mul
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_vec4_div
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_vec4_mod
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_and
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_or
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_xor
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_shift_left
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_shift_right
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_equal
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static bool call(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
		{
			return
				detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x) &&
				detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.y, v2.y) &&
				detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.z, v2.z) &&
				detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.w, v2.w);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_nequal
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static bool call(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
		{
			return !compute_vec4_equal<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(v1, v2);
		}
	};

	template<typename T, qualifier Q, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_bitwise_not
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(vec<4, T, Q> const& v)
		{
			return vec<4, T, Q>(~v.x, ~v.y, ~v.z, ~v.w);
		}
	};
}//namespace detail

	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0), y(0), z(0), w(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<4, T, Q> const& v)
			: x(v.x), y(v.y), z(v.z), w(v.w)
		{}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<4, T, P> const& v)
		: x(v.x), y(v.y), z(v.z), w(v.w)
	{}

	// -- Explicit basic constructors --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(T scalar)
		: x(scalar), y(scalar), z(scalar), w(scalar)
	{}

	template <typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(T _x, T _y, T _z, T _w)
		: x(_x), y(_y), z(_z), w(_w)
	{}

	// -- Conversion scalar constructors --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.x))
		, z(static_cast<T>(v.x))
		, w(static_cast<T>(v.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, Y _y, Z _z, W _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, Y _y, Z _z, W _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, vec<1, Y, Q> const& _y, Z _z, W _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z, W _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, Y _y, vec<1, Z, Q> const& _z, W _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z, W _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, W _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, W _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, Y _y, Z _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, vec<1, Y, Q> const& _y, Z _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, Y _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename X, typename Y, typename Z, typename W>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z, vec<1, W, Q> const& _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w.x))
	{}

	// -- Conversion vector constructors --

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<2, A, P> const& _xy, B _z, C _w)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z, C _w)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<2, A, P> const& _xy, B _z, vec<1, C, P> const& _w)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_z))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z, vec<1, C, P> const& _w)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_z.x))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(A _x, vec<2, B, P> const& _yz, C _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_yz.x))
		, z(static_cast<T>(_yz.y))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz, C _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_yz.x))
		, z(static_cast<T>(_yz.y))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(A _x, vec<2, B, P> const& _yz, vec<1, C, P> const& _w)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_yz.x))
		, z(static_cast<T>(_yz.y))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz, vec<1, C, P> const& _w)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_yz.x))
		, z(static_cast<T>(_yz.y))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(A _x, B _y, vec<2, C, P> const& _zw)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_zw.x))
		, w(static_cast<T>(_zw.y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, A, P> const& _x, B _y, vec<2, C, P> const& _zw)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y))
		, z(static_cast<T>(_zw.x))
		, w(static_cast<T>(_zw.y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(A _x, vec<1, B, P> const& _y, vec<2, C, P> const& _zw)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_zw.x))
		, w(static_cast<T>(_zw.y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, typename C, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, A, P> const& _x, vec<1, B, P> const& _y, vec<2, C, P> const& _zw)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_y.x))
		, z(static_cast<T>(_zw.x))
		, w(static_cast<T>(_zw.y))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<3, A, P> const& _xyz, B _w)
		: x(static_cast<T>(_xyz.x))
		, y(static_cast<T>(_xyz.y))
		, z(static_cast<T>(_xyz.z))
		, w(static_cast<T>(_w))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<3, A, P> const& _xyz, vec<1, B, P> const& _w)
		: x(static_cast<T>(_xyz.x))
		, y(static_cast<T>(_xyz.y))
		, z(static_cast<T>(_xyz.z))
		, w(static_cast<T>(_w.x))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(A _x, vec<3, B, P> const& _yzw)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_yzw.x))
		, z(static_cast<T>(_yzw.y))
		, w(static_cast<T>(_yzw.z))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<1, A, P> const& _x, vec<3, B, P> const& _yzw)
		: x(static_cast<T>(_x.x))
		, y(static_cast<T>(_yzw.x))
		, z(static_cast<T>(_yzw.y))
		, w(static_cast<T>(_yzw.z))
	{}

	template<typename T, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<2, A, P> const& _xy, vec<2, B, P> const& _zw)
		: x(static_cast<T>(_xy.x))
		, y(static_cast<T>(_xy.y))
		, z(static_cast<T>(_zw.x))
		, w(static_cast<T>(_zw.y))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
		, w(static_cast<T>(v.w))
	{}

	// -- Component accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T& vec<4, T, Q>::operator[](typename vec<4, T, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T const& vec<4, T, Q>::operator[](typename vec<4, T, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		}
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>& vec<4, T, Q>::operator=(vec<4, T, Q> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
			return *this;
		}
#	endif

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q>& vec<4, T, Q>::operator=(vec<4, U, Q> const& v)
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		this->z = static_cast<T>(v.z);
		this->w = static_cast<T>(v.w);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator+=(U scalar)
	{
		return (*this = detail::compute_vec4_add<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator+=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_add<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v.x)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator+=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_add<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator-=(U scalar)
	{
		return (*this = detail::compute_vec4_sub<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator-=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_sub<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v.x)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator-=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_sub<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator*=(U scalar)
	{
		return (*this = detail::compute_vec4_mul<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator*=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_mul<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v.x)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator*=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_mul<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator/=(U scalar)
	{
		return (*this = detail::compute_vec4_div<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator/=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_div<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v.x)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator/=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_div<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> vec<4, T, Q>::operator++(int)
	{
		vec<4, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> vec<4, T, Q>::operator--(int)
	{
		vec<4, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator%=(U scalar)
	{
		return (*this = detail::compute_vec4_mod<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator%=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_mod<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator%=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_mod<T, Q, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator&=(U scalar)
	{
		return (*this = detail::compute_vec4_and<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator&=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_and<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator&=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_and<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator|=(U scalar)
	{
		return (*this = detail::compute_vec4_or<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator|=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_or<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator|=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_or<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator^=(U scalar)
	{
		return (*this = detail::compute_vec4_xor<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator^=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_xor<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator^=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_xor<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator<<=(U scalar)
	{
		return (*this = detail::compute_vec4_shift_left<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_shift_left<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator<<=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_shift_left<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator>>=(U scalar)
	{
		return (*this = detail::compute_vec4_shift_right<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(scalar)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_shift_right<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> & vec<4, T, Q>::operator>>=(vec<4, U, Q> const& v)
	{
		return (*this = detail::compute_vec4_shift_right<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(*this, vec<4, T, Q>(v)));
	}

	// -- Unary constant operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v)
	{
		return v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(0) -= v;
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v, T const & scalar)
	{
		return vec<4, T, Q>(v) += scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) += v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator+(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(v) += scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator+(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v2) += v1;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator+(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) += v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v, T const & scalar)
	{
		return vec<4, T, Q>(v) -= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) -= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator-(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) -= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator-(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) -= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator-(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) -= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v, T const & scalar)
	{
		return vec<4, T, Q>(v) *= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) *= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(v) *= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v2) *= v1;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) *= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator/(vec<4, T, Q> const& v, T const & scalar)
	{
		return vec<4, T, Q>(v) /= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator/(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) /= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator/(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) /= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator/(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) /= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator/(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) /= v2;
	}

	// -- Binary bit operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator%(vec<4, T, Q> const& v, T scalar)
	{
		return vec<4, T, Q>(v) %= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator%(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) %= v2.x;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator%(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) %= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator%(vec<1, T, Q> const& scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar.x) %= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator%(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) %= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator&(vec<4, T, Q> const& v, T scalar)
	{
		return vec<4, T, Q>(v) &= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator&(vec<4, T, Q> const& v, vec<1, T, Q> const& scalar)
	{
		return vec<4, T, Q>(v) &= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator&(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) &= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator&(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) &= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator&(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) &= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator|(vec<4, T, Q> const& v, T scalar)
	{
		return vec<4, T, Q>(v) |= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator|(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) |= v2.x;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator|(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) |= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator|(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) |= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator|(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) |= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator^(vec<4, T, Q> const& v, T scalar)
	{
		return vec<4, T, Q>(v) ^= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator^(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) ^= v2.x;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator^(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) ^= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator^(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) ^= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator^(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) ^= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<4, T, Q> const& v, T scalar)
	{
		return vec<4, T, Q>(v) <<= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) <<= v2.x;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator<<(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) <<= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) <<= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator<<(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) <<= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<4, T, Q> const& v, T scalar)
	{
		return vec<4, T, Q>(v) >>= scalar;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<4, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) >>= v2.x;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator>>(T scalar, vec<4, T, Q> const& v)
	{
		return vec<4, T, Q>(scalar) >>= v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<1, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1.x) >>= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator>>(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return vec<4, T, Q>(v1) >>= v2;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator~(vec<4, T, Q> const& v)
	{
		return detail::compute_vec4_bitwise_not<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(v);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return detail::compute_vec4_equal<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(v1, v2);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<4, T, Q> const& v1, vec<4, T, Q> const& v2)
	{
		return detail::compute_vec4_nequal<T, Q, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<Q>::value>::call(v1, v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, bool, Q> operator&&(vec<4, bool, Q> const& v1, vec<4, bool, Q> const& v2)
	{
		return vec<4, bool, Q>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, bool, Q> operator||(vec<4, bool, Q> const& v1, vec<4, bool, Q> const& v2)
	{
		return vec<4, bool, Q>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/type_vec4_simd.inl"
#endif


#endif//GLM_EXTERNAL_TEMPLATE

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 4 components vector of boolean.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<4, bool, defaultp>		bvec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_bool4_precision.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector_precision
	/// @{

	/// 4 components vector of high qualifier bool numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, bool, highp>		highp_bvec4;

	/// 4 components vector of medium qualifier bool numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, bool, mediump>	mediump_bvec4;

	/// 4 components vector of low qualifier bool numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, bool, lowp>		lowp_bvec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_float4.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 4 components vector of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<4, float, defaultp>		vec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_float4_precision.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector_precision
	/// @{

	/// 4 components vector of high single-qualifier floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, float, highp>		highp_vec4;

	/// 4 components vector of medium single-qualifier floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, float, mediump>		mediump_vec4;

	/// 4 components vector of low single-qualifier floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, float, lowp>			lowp_vec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_double4.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 4 components vector of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<4, double, defaultp>		dvec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_double4_precision.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector_precision
	/// @{

	/// 4 components vector of high double-qualifier floating-point numbers.
	/// There is no guarantee on the actual qualifier.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, double, highp>		highp_dvec4;

	/// 4 components vector of medium double-qualifier floating-point numbers.
	/// There is no guarantee on the actual qualifier.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, double, mediump>		mediump_dvec4;

	/// 4 components vector of low double-qualifier floating-point numbers.
	/// There is no guarantee on the actual qualifier.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef vec<4, double, lowp>		lowp_dvec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_int4.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 4 components vector of signed integer numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<4, int, defaultp>		ivec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_int4_sized.hpp" -----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_int4_sized extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_int4_sized
	/// @{

	/// 8 bit signed integer vector of 4 components type.
	///
	/// @see ext_vector_int4_sized
	typedef vec<4, int8, defaultp>		i8vec4;

	/// 16 bit signed integer vector of 4 components type.
	///
	/// @see ext_vector_int4_sized
	typedef vec<4, int16, defaultp>		i16vec4;

	/// 32 bit signed integer vector of 4 components type.
	///
	/// @see ext_vector_int4_sized
	typedef vec<4, int32, defaultp>		i32vec4;

	/// 64 bit signed integer vector of 4 components type.
	///
	/// @see ext_vector_int4_sized
	typedef vec<4, int64, defaultp>		i64vec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_uint4.hpp" -----------

namespace glm
{
	/// @addtogroup core_vector
	/// @{

	/// 4 components vector of unsigned integer numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef vec<4, unsigned int, defaultp>		uvec4;

	/// @}
}//namespace glm


    // ---------- "./ext/vector_uint4_sized.hpp" -----------


#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_uint4_sized extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_uint4_sized
	/// @{

	/// 8 bit unsigned integer vector of 4 components type.
	///
	/// @see ext_vector_uint4_sized
	typedef vec<4, uint8, defaultp>		u8vec4;

	/// 16 bit unsigned integer vector of 4 components type.
	///
	/// @see ext_vector_uint4_sized
	typedef vec<4, uint16, defaultp>	u16vec4;

	/// 32 bit unsigned integer vector of 4 components type.
	///
	/// @see ext_vector_uint4_sized
	typedef vec<4, uint32, defaultp>	u32vec4;

	/// 64 bit unsigned integer vector of 4 components type.
	///
	/// @see ext_vector_uint4_sized
	typedef vec<4, uint64, defaultp>	u64vec4;

	/// @}
}//namespace glm

// -----------------------------------------

// ---------- #include "mat2x2.hpp" ----------

    // ---------- "./ext/matrix_double2x2.hpp" -----------

#include <limits>
#include <cstddef>

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<2, 2, T, Q>
	{
		typedef vec<2, T, Q> col_type;
		typedef vec<2, T, Q> row_type;
		typedef mat<2, 2, T, Q> type;
		typedef mat<2, 2, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[2];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 2; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<2, 2, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T const& x1, T const& y1,
			T const& x2, T const& y2);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v1,
			col_type const& v2);

		// -- Conversions --

		template<typename U, typename V, typename M, typename N>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			U const& x1, V const& y1,
			M const& x2, N const& y2);

		template<typename U, typename V>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<2, U, Q> const& v1,
			vec<2, V, Q> const& v2);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator=(mat<2, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator+=(mat<2, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator-=(mat<2, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator*=(mat<2, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator/=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator/=(mat<2, 2, U, Q> const& m);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<2, 2, T, Q> & operator++ ();
		GLM_FUNC_DECL mat<2, 2, T, Q> & operator-- ();
		GLM_FUNC_DECL mat<2, 2, T, Q> operator++(int);
		GLM_FUNC_DECL mat<2, 2, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator+(mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator-(mat<2, 2, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator+(mat<2, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator+(T scalar, mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator+(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator-(mat<2, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator-(T scalar, mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator-(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator*(mat<2, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator*(T scalar, mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 2, T, Q>::col_type operator*(mat<2, 2, T, Q> const& m, typename mat<2, 2, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 2, T, Q>::row_type operator*(typename mat<2, 2, T, Q>::col_type const& v, mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator*(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator*(mat<2, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator*(mat<2, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator/(mat<2, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator/(T scalar, mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 2, T, Q>::col_type operator/(mat<2, 2, T, Q> const& m, typename mat<2, 2, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 2, T, Q>::row_type operator/(typename mat<2, 2, T, Q>::col_type const& v, mat<2, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator/(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2);
} //namespace glm

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 2 columns of 2 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 2, double, defaultp>		dmat2x2;

	/// 2 columns of 2 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 2, double, defaultp>		dmat2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double2x2_precision.hpp" -----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 2 columns of 2 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, double, lowp>		lowp_dmat2;

	/// 2 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, double, mediump>	mediump_dmat2;

	/// 2 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, double, highp>	highp_dmat2;

	/// 2 columns of 2 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, double, lowp>		lowp_dmat2x2;

	/// 2 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, double, mediump>	mediump_dmat2x2;

	/// 2 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, double, highp>	highp_dmat2x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float2x2.hpp" -----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 2 columns of 2 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 2, float, defaultp>		mat2x2;

	/// 2 columns of 2 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 2, float, defaultp>		mat2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float2x2_precision.hpp" -----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 2 columns of 2 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, float, lowp>		lowp_mat2;

	/// 2 columns of 2 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, float, mediump>	mediump_mat2;

	/// 2 columns of 2 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, float, highp>		highp_mat2;

	/// 2 columns of 2 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, float, lowp>		lowp_mat2x2;

	/// 2 columns of 2 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, float, mediump>	mediump_mat2x2;

	/// 2 columns of 2 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 2, float, highp>		highp_mat2x2;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat2x3.hpp" ----------

    // ---------- "./ext/matrix_double2x3.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<2, 3, T, Q>
	{
		typedef vec<3, T, Q> col_type;
		typedef vec<2, T, Q> row_type;
		typedef mat<2, 3, T, Q> type;
		typedef mat<3, 2, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[2];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 2; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<2, 3, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T x0, T y0, T z0,
			T x1, T y1, T z1);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1);

		// -- Conversions --

		template<typename X1, typename Y1, typename Z1, typename X2, typename Y2, typename Z2>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 x1, Y1 y1, Z1 z1,
			X2 x2, Y2 y2, Z2 z2);

		template<typename U, typename V>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<3, U, Q> const& v1,
			vec<3, V, Q> const& v2);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator=(mat<2, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator+=(mat<2, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator-=(mat<2, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<2, 3, T, Q> & operator++ ();
		GLM_FUNC_DECL mat<2, 3, T, Q> & operator-- ();
		GLM_FUNC_DECL mat<2, 3, T, Q> operator++(int);
		GLM_FUNC_DECL mat<2, 3, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator+(mat<2, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator-(mat<2, 3, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator+(mat<2, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator+(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator-(mat<2, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator-(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator*(mat<2, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator*(T scalar, mat<2, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 3, T, Q>::col_type operator*(mat<2, 3, T, Q> const& m, typename mat<2, 3, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 3, T, Q>::row_type operator*(typename mat<2, 3, T, Q>::col_type const& v, mat<2, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator*(mat<2, 3, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator*(mat<2, 3, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator*(mat<2, 3, T, Q> const& m1, mat<4, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator/(mat<2, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator/(T scalar, mat<2, 3, T, Q> const& m);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0, 0), col_type(0, 1, 0)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0, 0);
				this->value[1] = col_type(0, 1, 0);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<2, 3, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{m.value[0], m.value[1]}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m.value[0];
			this->value[1] = m.value[1];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(T scalar)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(scalar, 0, 0), col_type(0, scalar, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(scalar, 0, 0);
			this->value[1] = col_type(0, scalar, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat
	(
		T x0, T y0, T z0,
		T x1, T y1, T z1
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0, z0), col_type(x1, y1, z1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0);
			this->value[1] = col_type(x1, y1, z1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(col_type const& v0, col_type const& v1)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v0);
			this->value[1] = col_type(v1);
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X1, typename Y1, typename Z1,
		typename X2, typename Y2, typename Z2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat
	(
		X1 x1, Y1 y1, Z1 z1,
		X2 x2, Y2 y2, Z2 z2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x1, y1, z1), col_type(x2, y2, z2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x1, y1, z1);
			this->value[1] = col_type(x2, y2, z2);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(vec<3, V1, Q> const& v1, vec<3, V2, Q> const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<2, 3, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR  mat<2, 3, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
		: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 3, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 3, T, Q>::col_type & mat<2, 3, T, Q>::operator[](typename mat<2, 3, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<2, 3, T, Q>::col_type const& mat<2, 3, T, Q>::operator[](typename mat<2, 3, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q>& mat<2, 3, T, Q>::operator=(mat<2, 3, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> & mat<2, 3, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q>& mat<2, 3, T, Q>::operator+=(mat<2, 3, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q>& mat<2, 3, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q>& mat<2, 3, T, Q>::operator-=(mat<2, 3, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q>& mat<2, 3, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> & mat<2, 3, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> & mat<2, 3, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> & mat<2, 3, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> mat<2, 3, T, Q>::operator++(int)
	{
		mat<2, 3, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> mat<2, 3, T, Q>::operator--(int)
	{
		mat<2, 3, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator+(mat<2, 3, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator-(mat<2, 3, T, Q> const& m)
	{
		return mat<2, 3, T, Q>(
			-m[0],
			-m[1]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator+(mat<2, 3, T, Q> const& m, T scalar)
	{
		return mat<2, 3, T, Q>(
			m[0] + scalar,
			m[1] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator+(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		return mat<2, 3, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator-(mat<2, 3, T, Q> const& m, T scalar)
	{
		return mat<2, 3, T, Q>(
			m[0] - scalar,
			m[1] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator-(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		return mat<2, 3, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator*(mat<2, 3, T, Q> const& m, T scalar)
	{
		return mat<2, 3, T, Q>(
			m[0] * scalar,
			m[1] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator*(T scalar, mat<2, 3, T, Q> const& m)
	{
		return mat<2, 3, T, Q>(
			m[0] * scalar,
			m[1] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 3, T, Q>::col_type operator*
	(
		mat<2, 3, T, Q> const& m,
		typename mat<2, 3, T, Q>::row_type const& v)
	{
		return typename mat<2, 3, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y,
			m[0][2] * v.x + m[1][2] * v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 3, T, Q>::row_type operator*
	(
		typename mat<2, 3, T, Q>::col_type const& v,
		mat<2, 3, T, Q> const& m)
	{
		return typename mat<2, 3, T, Q>::row_type(
			v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],
			v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator*(mat<2, 3, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return mat<2, 3, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator*(mat<2, 3, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		T SrcA00 = m1[0][0];
		T SrcA01 = m1[0][1];
		T SrcA02 = m1[0][2];
		T SrcA10 = m1[1][0];
		T SrcA11 = m1[1][1];
		T SrcA12 = m1[1][2];

		T SrcB00 = m2[0][0];
		T SrcB01 = m2[0][1];
		T SrcB10 = m2[1][0];
		T SrcB11 = m2[1][1];
		T SrcB20 = m2[2][0];
		T SrcB21 = m2[2][1];

		mat<3, 3, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator*(mat<2, 3, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		return mat<4, 3, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1],
			m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator/(mat<2, 3, T, Q> const& m, T scalar)
	{
		return mat<2, 3, T, Q>(
			m[0] / scalar,
			m[1] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator/(T scalar, mat<2, 3, T, Q> const& m)
	{
		return mat<2, 3, T, Q>(
			scalar / m[0],
			scalar / m[1]);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<2, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}
} //namespace glm


#endif

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 2 columns of 3 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 3, double, defaultp>		dmat2x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double2x3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 2 columns of 3 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 3, double, lowp>		lowp_dmat2x3;

	/// 2 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 3, double, mediump>	mediump_dmat2x3;

	/// 2 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 3, double, highp>	highp_dmat2x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float2x3.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 2 columns of 3 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 3, float, defaultp>		mat2x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float2x3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 2 columns of 3 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 3, float, lowp>		lowp_mat2x3;

	/// 2 columns of 3 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 3, float, mediump>	mediump_mat2x3;

	/// 2 columns of 3 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 3, float, highp>		highp_mat2x3;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat2x4.hpp" ----------

    // ---------- "./ext/matrix_double2x4.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<2, 4, T, Q>
	{
		typedef vec<4, T, Q> col_type;
		typedef vec<2, T, Q> row_type;
		typedef mat<2, 4, T, Q> type;
		typedef mat<4, 2, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[2];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 2; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<2, 4, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T x0, T y0, T z0, T w0,
			T x1, T y1, T z1, T w1);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 x1, Y1 y1, Z1 z1, W1 w1,
			X2 x2, Y2 y2, Z2 z2, W2 w2);

		template<typename U, typename V>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<4, U, Q> const& v1,
			vec<4, V, Q> const& v2);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator=(mat<2, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator+=(mat<2, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator-=(mat<2, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<2, 4, T, Q> & operator++ ();
		GLM_FUNC_DECL mat<2, 4, T, Q> & operator-- ();
		GLM_FUNC_DECL mat<2, 4, T, Q> operator++(int);
		GLM_FUNC_DECL mat<2, 4, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator+(mat<2, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator-(mat<2, 4, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator+(mat<2, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator+(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator-(mat<2, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator-(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator*(mat<2, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator*(T scalar, mat<2, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 4, T, Q>::col_type operator*(mat<2, 4, T, Q> const& m, typename mat<2, 4, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 4, T, Q>::row_type operator*(typename mat<2, 4, T, Q>::col_type const& v, mat<2, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator*(mat<2, 4, T, Q> const& m1, mat<4, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator*(mat<2, 4, T, Q> const& m1, mat<2, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator*(mat<2, 4, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator/(mat<2, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator/(T scalar, mat<2, 4, T, Q> const& m);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0, 0, 0);
				this->value[1] = col_type(0, 1, 0, 0);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<2, 4, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{m[0], m[1]}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(T s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0, 0, 0), col_type(0, s, 0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0, 0, 0);
			this->value[1] = col_type(0, s, 0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat
	(
		T x0, T y0, T z0, T w0,
		T x1, T y1, T z1, T w1
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0, z0, w0), col_type(x1, y1, z1, w1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0, w0);
			this->value[1] = col_type(x1, y1, z1, w1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(col_type const& v0, col_type const& v1)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X1, typename Y1, typename Z1, typename W1,
		typename X2, typename Y2, typename Z2, typename W2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat
	(
		X1 x1, Y1 y1, Z1 z1, W1 w1,
		X2 x2, Y2 y2, Z2 z2, W2 w2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{
				col_type(x1, y1, z1, w1),
				col_type(x2, y2, z2, w2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x1, y1, z1, w1);
			this->value[1] = col_type(x2, y2, z2, w2);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(vec<4, V1, Q> const& v1, vec<4, V2, Q> const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<2, 4, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 4, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 4, T, Q>::col_type & mat<2, 4, T, Q>::operator[](typename mat<2, 4, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<2, 4, T, Q>::col_type const& mat<2, 4, T, Q>::operator[](typename mat<2, 4, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator=(mat<2, 4, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator+=(mat<2, 4, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator-=(mat<2, 4, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> & mat<2, 4, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q>& mat<2, 4, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> mat<2, 4, T, Q>::operator++(int)
	{
		mat<2, 4, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> mat<2, 4, T, Q>::operator--(int)
	{
		mat<2, 4, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator+(mat<2, 4, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator-(mat<2, 4, T, Q> const& m)
	{
		return mat<2, 4, T, Q>(
			-m[0],
			-m[1]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator+(mat<2, 4, T, Q> const& m, T scalar)
	{
		return mat<2, 4, T, Q>(
			m[0] + scalar,
			m[1] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator+(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		return mat<2, 4, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator-(mat<2, 4, T, Q> const& m, T scalar)
	{
		return mat<2, 4, T, Q>(
			m[0] - scalar,
			m[1] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator-(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		return mat<2, 4, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator*(mat<2, 4, T, Q> const& m, T scalar)
	{
		return mat<2, 4, T, Q>(
			m[0] * scalar,
			m[1] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator*(T scalar, mat<2, 4, T, Q> const& m)
	{
		return mat<2, 4, T, Q>(
			m[0] * scalar,
			m[1] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 4, T, Q>::col_type operator*(mat<2, 4, T, Q> const& m, typename mat<2, 4, T, Q>::row_type const& v)
	{
		return typename mat<2, 4, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y,
			m[0][2] * v.x + m[1][2] * v.y,
			m[0][3] * v.x + m[1][3] * v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 4, T, Q>::row_type operator*(typename mat<2, 4, T, Q>::col_type const& v, mat<2, 4, T, Q> const& m)
	{
		return typename mat<2, 4, T, Q>::row_type(
			v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
			v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator*(mat<2, 4, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		T SrcA00 = m1[0][0];
		T SrcA01 = m1[0][1];
		T SrcA02 = m1[0][2];
		T SrcA03 = m1[0][3];
		T SrcA10 = m1[1][0];
		T SrcA11 = m1[1][1];
		T SrcA12 = m1[1][2];
		T SrcA13 = m1[1][3];

		T SrcB00 = m2[0][0];
		T SrcB01 = m2[0][1];
		T SrcB10 = m2[1][0];
		T SrcB11 = m2[1][1];
		T SrcB20 = m2[2][0];
		T SrcB21 = m2[2][1];
		T SrcB30 = m2[3][0];
		T SrcB31 = m2[3][1];

		mat<4, 4, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
		Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
		Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
		Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21;
		Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31;
		Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31;
		Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31;
		Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator*(mat<2, 4, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return mat<2, 4, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator*(mat<2, 4, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		return mat<3, 4, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1],
			m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator/(mat<2, 4, T, Q> const& m, T scalar)
	{
		return mat<2, 4, T, Q>(
			m[0] / scalar,
			m[1] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator/(T scalar, mat<2, 4, T, Q> const& m)
	{
		return mat<2, 4, T, Q>(
			scalar / m[0],
			scalar / m[1]);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<2, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}
} //namespace glm


#endif

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 2 columns of 4 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 4, double, defaultp>		dmat2x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double2x4_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 2 columns of 4 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 4, double, lowp>		lowp_dmat2x4;

	/// 2 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 4, double, mediump>	mediump_dmat2x4;

	/// 2 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 4, double, highp>	highp_dmat2x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float2x4.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 2 columns of 4 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<2, 4, float, defaultp>		mat2x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float2x4_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 2 columns of 4 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 4, float, lowp>		lowp_mat2x4;

	/// 2 columns of 4 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 4, float, mediump>	mediump_mat2x4;

	/// 2 columns of 4 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<2, 4, float, highp>		highp_mat2x4;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat3x2.hpp" ----------

    // ---------- "./ext/matrix_double3x2.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<3, 2, T, Q>
	{
		typedef vec<2, T, Q> col_type;
		typedef vec<3, T, Q> row_type;
		typedef mat<3, 2, T, Q> type;
		typedef mat<2, 3, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[3];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 3; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<3, 2, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T x0, T y0,
			T x1, T y1,
			T x2, T y2);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2);

		// -- Conversions --

		template<
			typename X1, typename Y1,
			typename X2, typename Y2,
			typename X3, typename Y3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 x1, Y1 y1,
			X2 x2, Y2 y2,
			X3 x3, Y3 y3);

		template<typename V1, typename V2, typename V3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<2, V1, Q> const& v1,
			vec<2, V2, Q> const& v2,
			vec<2, V3, Q> const& v3);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator=(mat<3, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator+=(mat<3, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator-=(mat<3, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<3, 2, T, Q> & operator++ ();
		GLM_FUNC_DECL mat<3, 2, T, Q> & operator-- ();
		GLM_FUNC_DECL mat<3, 2, T, Q> operator++(int);
		GLM_FUNC_DECL mat<3, 2, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator+(mat<3, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator-(mat<3, 2, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator+(mat<3, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator+(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator-(mat<3, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator-(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator*(mat<3, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator*(T scalar, mat<3, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 2, T, Q>::col_type operator*(mat<3, 2, T, Q> const& m, typename mat<3, 2, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 2, T, Q>::row_type operator*(typename mat<3, 2, T, Q>::col_type const& v, mat<3, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator*(mat<3, 2, T, Q> const& m1, mat<2, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator*(mat<3, 2, T, Q> const& m1, mat<3, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator*(mat<3, 2, T, Q> const& m1, mat<4, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator/(mat<3, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator/(T scalar, mat<3, 2, T, Q> const& m);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2);

}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0), col_type(0, 1), col_type(0, 0)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0);
				this->value[1] = col_type(0, 1);
				this->value[2] = col_type(0, 0);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<3, 2, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(T s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0), col_type(0, s), col_type(0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0);
			this->value[1] = col_type(0, s);
			this->value[2] = col_type(0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat
	(
		T x0, T y0,
		T x1, T y1,
		T x2, T y2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0);
			this->value[1] = col_type(x1, y1);
			this->value[2] = col_type(x2, y2);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(col_type const& v0, col_type const& v1, col_type const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
			this->value[2] = v2;
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X0, typename Y0,
		typename X1, typename Y1,
		typename X2, typename Y2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat
	(
		X0 x0, Y0 y0,
		X1 x1, Y1 y1,
		X2 x2, Y2 y2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0);
			this->value[1] = col_type(x1, y1);
			this->value[2] = col_type(x2, y2);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V0, typename V1, typename V2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(vec<2, V0, Q> const& v0, vec<2, V1, Q> const& v1, vec<2, V2, Q> const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v0);
			this->value[1] = col_type(v1);
			this->value[2] = col_type(v2);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<3, 2, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 2, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 2, T, Q>::col_type & mat<3, 2, T, Q>::operator[](typename mat<3, 2, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<3, 2, T, Q>::col_type const& mat<3, 2, T, Q>::operator[](typename mat<3, 2, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator=(mat<3, 2, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator+=(mat<3, 2, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator-=(mat<3, 2, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> & mat<3, 2, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q>& mat<3, 2, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> mat<3, 2, T, Q>::operator++(int)
	{
		mat<3, 2, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> mat<3, 2, T, Q>::operator--(int)
	{
		mat<3, 2, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator+(mat<3, 2, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator-(mat<3, 2, T, Q> const& m)
	{
		return mat<3, 2, T, Q>(
			-m[0],
			-m[1],
			-m[2]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator+(mat<3, 2, T, Q> const& m, T scalar)
	{
		return mat<3, 2, T, Q>(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator+(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		return mat<3, 2, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator-(mat<3, 2, T, Q> const& m, T scalar)
	{
		return mat<3, 2, T, Q>(
			m[0] - scalar,
			m[1] - scalar,
			m[2] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator-(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		return mat<3, 2, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator*(mat<3, 2, T, Q> const& m, T scalar)
	{
		return mat<3, 2, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator*(T scalar, mat<3, 2, T, Q> const& m)
	{
		return mat<3, 2, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 2, T, Q>::col_type operator*(mat<3, 2, T, Q> const& m, typename mat<3, 2, T, Q>::row_type const& v)
	{
		return typename mat<3, 2, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 2, T, Q>::row_type operator*(typename mat<3, 2, T, Q>::col_type const& v, mat<3, 2, T, Q> const& m)
	{
		return typename mat<3, 2, T, Q>::row_type(
			v.x * m[0][0] + v.y * m[0][1],
			v.x * m[1][0] + v.y * m[1][1],
			v.x * m[2][0] + v.y * m[2][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator*(mat<3, 2, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		const T SrcA00 = m1[0][0];
		const T SrcA01 = m1[0][1];
		const T SrcA10 = m1[1][0];
		const T SrcA11 = m1[1][1];
		const T SrcA20 = m1[2][0];
		const T SrcA21 = m1[2][1];

		const T SrcB00 = m2[0][0];
		const T SrcB01 = m2[0][1];
		const T SrcB02 = m2[0][2];
		const T SrcB10 = m2[1][0];
		const T SrcB11 = m2[1][1];
		const T SrcB12 = m2[1][2];

		mat<2, 2, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator*(mat<3, 2, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		return mat<3, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator*(mat<3, 2, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		return mat<4, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator/(mat<3, 2, T, Q> const& m, T scalar)
	{
		return mat<3, 2, T, Q>(
			m[0] / scalar,
			m[1] / scalar,
			m[2] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator/(T scalar, mat<3, 2, T, Q> const& m)
	{
		return mat<3, 2, T, Q>(
			scalar / m[0],
			scalar / m[1],
			scalar / m[2]);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<3, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}
} //namespace glm


#endif

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 3 columns of 2 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 2, double, defaultp>		dmat3x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double3x2_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 3 columns of 2 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 2, double, lowp>		lowp_dmat3x2;

	/// 3 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 2, double, mediump>	mediump_dmat3x2;

	/// 3 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 2, double, highp>	highp_dmat3x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float3x2.hpp" ----------

namespace glm
{
	/// @addtogroup core
	/// @{

	/// 3 columns of 2 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 2, float, defaultp>			mat3x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float3x2_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 3 columns of 2 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 2, float, lowp>		lowp_mat3x2;

	/// 3 columns of 2 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 2, float, mediump>	mediump_mat3x2;

	/// 3 columns of 2 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 2, float, highp>		highp_mat3x2;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat3x3.hpp" ----------

    // ---------- "./ext/matrix_double3x3.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<3, 3, T, Q>
	{
		typedef vec<3, T, Q> col_type;
		typedef vec<3, T, Q> row_type;
		typedef mat<3, 3, T, Q> type;
		typedef mat<3, 3, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[3];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 3; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<3, 3, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T x0, T y0, T z0,
			T x1, T y1, T z1,
			T x2, T y2, T z2);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1,
			typename X2, typename Y2, typename Z2,
			typename X3, typename Y3, typename Z3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 x1, Y1 y1, Z1 z1,
			X2 x2, Y2 y2, Z2 z2,
			X3 x3, Y3 y3, Z3 z3);

		template<typename V1, typename V2, typename V3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<3, V1, Q> const& v1,
			vec<3, V2, Q> const& v2,
			vec<3, V3, Q> const& v3);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator=(mat<3, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator+=(mat<3, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator-=(mat<3, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator*=(mat<3, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator/=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator/=(mat<3, 3, U, Q> const& m);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<3, 3, T, Q> & operator++();
		GLM_FUNC_DECL mat<3, 3, T, Q> & operator--();
		GLM_FUNC_DECL mat<3, 3, T, Q> operator++(int);
		GLM_FUNC_DECL mat<3, 3, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator+(mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator-(mat<3, 3, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator+(mat<3, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator+(T scalar, mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator+(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator-(mat<3, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator-(T scalar, mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator-(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator*(mat<3, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator*(T scalar, mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 3, T, Q>::col_type operator*(mat<3, 3, T, Q> const& m, typename mat<3, 3, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 3, T, Q>::row_type operator*(typename mat<3, 3, T, Q>::col_type const& v, mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator*(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator*(mat<3, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator*(mat<3, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator/(mat<3, 3, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator/(T scalar, mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 3, T, Q>::col_type operator/(mat<3, 3, T, Q> const& m, typename mat<3, 3, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 3, T, Q>::row_type operator/(typename mat<3, 3, T, Q>::col_type const& v, mat<3, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator/(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2);
}//namespace glm

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 3 columns of 3 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 3, double, defaultp>		dmat3x3;

	/// 3 columns of 3 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 3, double, defaultp>		dmat3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double3x3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 3 columns of 3 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, double, lowp>		lowp_dmat3;

	/// 3 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, double, mediump>	mediump_dmat3;

	/// 3 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, double, highp>	highp_dmat3;

	/// 3 columns of 3 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, double, lowp>		lowp_dmat3x3;

	/// 3 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, double, mediump>	mediump_dmat3x3;

	/// 3 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, double, highp>	highp_dmat3x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float3x3.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 3 columns of 3 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 3, float, defaultp>			mat3x3;

	/// 3 columns of 3 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 3, float, defaultp>			mat3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float3x3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 3 columns of 3 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, float, lowp>		lowp_mat3;

	/// 3 columns of 3 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, float, mediump>	mediump_mat3;

	/// 3 columns of 3 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, float, highp>		highp_mat3;

	/// 3 columns of 3 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, float, lowp>		lowp_mat3x3;

	/// 3 columns of 3 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, float, mediump>	mediump_mat3x3;

	/// 3 columns of 3 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 3, float, highp>		highp_mat3x3;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat3x4.hpp" ----------

    // ---------- "./ext/matrix_double3x4.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<3, 4, T, Q>
	{
		typedef vec<4, T, Q> col_type;
		typedef vec<3, T, Q> row_type;
		typedef mat<3, 4, T, Q> type;
		typedef mat<4, 3, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[3];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 3; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<3, 4, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T x0, T y0, T z0, T w0,
			T x1, T y1, T z1, T w1,
			T x2, T y2, T z2, T w2);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2,
			typename X3, typename Y3, typename Z3, typename W3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 x1, Y1 y1, Z1 z1, W1 w1,
			X2 x2, Y2 y2, Z2 z2, W2 w2,
			X3 x3, Y3 y3, Z3 z3, W3 w3);

		template<typename V1, typename V2, typename V3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<4, V1, Q> const& v1,
			vec<4, V2, Q> const& v2,
			vec<4, V3, Q> const& v3);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator=(mat<3, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator+=(mat<3, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator-=(mat<3, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<3, 4, T, Q> & operator++();
		GLM_FUNC_DECL mat<3, 4, T, Q> & operator--();
		GLM_FUNC_DECL mat<3, 4, T, Q> operator++(int);
		GLM_FUNC_DECL mat<3, 4, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator+(mat<3, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator-(mat<3, 4, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator+(mat<3, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator+(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator-(mat<3, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator-(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator*(mat<3, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator*(T scalar, mat<3, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 4, T, Q>::col_type operator*(mat<3, 4, T, Q> const& m, typename mat<3, 4, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<3, 4, T, Q>::row_type operator*(typename mat<3, 4, T, Q>::col_type const& v, mat<3, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator*(mat<3, 4, T, Q> const& m1,	mat<4, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator*(mat<3, 4, T, Q> const& m1, mat<2, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator*(mat<3, 4, T, Q> const& m1,	mat<3, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator/(mat<3, 4, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator/(T scalar, mat<3, 4, T, Q> const& m);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0), col_type(0, 0, 1, 0)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0, 0, 0);
				this->value[1] = col_type(0, 1, 0, 0);
				this->value[2] = col_type(0, 0, 1, 0);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<3, 4, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(T s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0, 0, 0), col_type(0, s, 0, 0), col_type(0, 0, s, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0, 0, 0);
			this->value[1] = col_type(0, s, 0, 0);
			this->value[2] = col_type(0, 0, s, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat
	(
		T x0, T y0, T z0, T w0,
		T x1, T y1, T z1, T w1,
		T x2, T y2, T z2, T w2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{
				col_type(x0, y0, z0, w0),
				col_type(x1, y1, z1, w1),
				col_type(x2, y2, z2, w2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0, w0);
			this->value[1] = col_type(x1, y1, z1, w1);
			this->value[2] = col_type(x2, y2, z2, w2);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(col_type const& v0, col_type const& v1, col_type const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
			this->value[2] = v2;
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X0, typename Y0, typename Z0, typename W0,
		typename X1, typename Y1, typename Z1, typename W1,
		typename X2, typename Y2, typename Z2, typename W2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat
	(
		X0 x0, Y0 y0, Z0 z0, W0 w0,
		X1 x1, Y1 y1, Z1 z1, W1 w1,
		X2 x2, Y2 y2, Z2 z2, W2 w2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{
				col_type(x0, y0, z0, w0),
				col_type(x1, y1, z1, w1),
				col_type(x2, y2, z2, w2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0, w0);
			this->value[1] = col_type(x1, y1, z1, w1);
			this->value[2] = col_type(x2, y2, z2, w2);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2, typename V3>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(vec<4, V1, Q> const& v0, vec<4, V2, Q> const& v1, vec<4, V3, Q> const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v0);
			this->value[1] = col_type(v1);
			this->value[2] = col_type(v2);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<3, 4, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
			this->value[2] = col_type(0, 0, 1, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(0, 0, 1, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(0, 0, 1, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(m[2], 1, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
			this->value[2] = col_type(m[2], 1, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0, 0, 1, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(m[2], 1, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
			this->value[2] = col_type(m[2], 1, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 4, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 0);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 4, T, Q>::col_type & mat<3, 4, T, Q>::operator[](typename mat<3, 4, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<3, 4, T, Q>::col_type const& mat<3, 4, T, Q>::operator[](typename mat<3, 4, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator=(mat<3, 4, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator+=(mat<3, 4, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator-=(mat<3, 4, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> & mat<3, 4, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q>& mat<3, 4, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> mat<3, 4, T, Q>::operator++(int)
	{
		mat<3, 4, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> mat<3, 4, T, Q>::operator--(int)
	{
		mat<3, 4, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator+(mat<3, 4, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator-(mat<3, 4, T, Q> const& m)
	{
		return mat<3, 4, T, Q>(
			-m[0],
			-m[1],
			-m[2]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator+(mat<3, 4, T, Q> const& m, T scalar)
	{
		return mat<3, 4, T, Q>(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator+(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		return mat<3, 4, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator-(mat<3, 4, T, Q> const& m,	T scalar)
	{
		return mat<3, 4, T, Q>(
			m[0] - scalar,
			m[1] - scalar,
			m[2] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator-(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		return mat<3, 4, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator*(mat<3, 4, T, Q> const& m, T scalar)
	{
		return mat<3, 4, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator*(T scalar, mat<3, 4, T, Q> const& m)
	{
		return mat<3, 4, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 4, T, Q>::col_type operator*
	(
		mat<3, 4, T, Q> const& m,
		typename mat<3, 4, T, Q>::row_type const& v
	)
	{
		return typename mat<3, 4, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z,
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 4, T, Q>::row_type operator*
	(
		typename mat<3, 4, T, Q>::col_type const& v,
		mat<3, 4, T, Q> const& m
	)
	{
		return typename mat<3, 4, T, Q>::row_type(
			v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
			v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3],
			v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator*(mat<3, 4, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		const T SrcA00 = m1[0][0];
		const T SrcA01 = m1[0][1];
		const T SrcA02 = m1[0][2];
		const T SrcA03 = m1[0][3];
		const T SrcA10 = m1[1][0];
		const T SrcA11 = m1[1][1];
		const T SrcA12 = m1[1][2];
		const T SrcA13 = m1[1][3];
		const T SrcA20 = m1[2][0];
		const T SrcA21 = m1[2][1];
		const T SrcA22 = m1[2][2];
		const T SrcA23 = m1[2][3];

		const T SrcB00 = m2[0][0];
		const T SrcB01 = m2[0][1];
		const T SrcB02 = m2[0][2];
		const T SrcB10 = m2[1][0];
		const T SrcB11 = m2[1][1];
		const T SrcB12 = m2[1][2];
		const T SrcB20 = m2[2][0];
		const T SrcB21 = m2[2][1];
		const T SrcB22 = m2[2][2];
		const T SrcB30 = m2[3][0];
		const T SrcB31 = m2[3][1];
		const T SrcB32 = m2[3][2];

		mat<4, 4, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
		Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01 + SrcA23 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
		Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11 + SrcA23 * SrcB12;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
		Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21 + SrcA23 * SrcB22;
		Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31 + SrcA20 * SrcB32;
		Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31 + SrcA21 * SrcB32;
		Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31 + SrcA22 * SrcB32;
		Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31 + SrcA23 * SrcB32;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator*(mat<3, 4, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		return mat<2, 4, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator*(mat<3, 4, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		return mat<3, 4, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2],
			m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator/(mat<3, 4, T, Q> const& m,	T scalar)
	{
		return mat<3, 4, T, Q>(
			m[0] / scalar,
			m[1] / scalar,
			m[2] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator/(T scalar, mat<3, 4, T, Q> const& m)
	{
		return mat<3, 4, T, Q>(
			scalar / m[0],
			scalar / m[1],
			scalar / m[2]);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<3, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}
} //namespace glm


#endif

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 3 columns of 4 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 4, double, defaultp>		dmat3x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double3x4_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 3 columns of 4 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 4, double, lowp>		lowp_dmat3x4;

	/// 3 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 4, double, mediump>	mediump_dmat3x4;

	/// 3 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 4, double, highp>	highp_dmat3x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float3x4.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 3 columns of 4 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<3, 4, float, defaultp>			mat3x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float3x4_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 3 columns of 4 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 4, float, lowp>		lowp_mat3x4;

	/// 3 columns of 4 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 4, float, mediump>	mediump_mat3x4;

	/// 3 columns of 4 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<3, 4, float, highp>		highp_mat3x4;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat4x2.hpp" ----------

    // ---------- "./ext/matrix_double4x2.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<4, 2, T, Q>
	{
		typedef vec<2, T, Q> col_type;
		typedef vec<4, T, Q> row_type;
		typedef mat<4, 2, T, Q> type;
		typedef mat<2, 4, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[4];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 4; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<4, 2, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T x0, T y0,
			T x1, T y1,
			T x2, T y2,
			T x3, T y3);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2,
			col_type const& v3);

		// -- Conversions --

		template<
			typename X0, typename Y0,
			typename X1, typename Y1,
			typename X2, typename Y2,
			typename X3, typename Y3>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X0 x0, Y0 y0,
			X1 x1, Y1 y1,
			X2 x2, Y2 y2,
			X3 x3, Y3 y3);

		template<typename V1, typename V2, typename V3, typename V4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<2, V1, Q> const& v1,
			vec<2, V2, Q> const& v2,
			vec<2, V3, Q> const& v3,
			vec<2, V4, Q> const& v4);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator=(mat<4, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator+=(mat<4, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator-=(mat<4, 2, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<4, 2, T, Q> & operator++ ();
		GLM_FUNC_DECL mat<4, 2, T, Q> & operator-- ();
		GLM_FUNC_DECL mat<4, 2, T, Q> operator++(int);
		GLM_FUNC_DECL mat<4, 2, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator+(mat<4, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator-(mat<4, 2, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator+(mat<4, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator+(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator-(mat<4, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator-(mat<4, 2, T, Q> const& m1,	mat<4, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator*(mat<4, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator*(T scalar, mat<4, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 2, T, Q>::col_type operator*(mat<4, 2, T, Q> const& m, typename mat<4, 2, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 2, T, Q>::row_type operator*(typename mat<4, 2, T, Q>::col_type const& v, mat<4, 2, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, T, Q> operator*(mat<4, 2, T, Q> const& m1, mat<2, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, T, Q> operator*(mat<4, 2, T, Q> const& m1, mat<3, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator*(mat<4, 2, T, Q> const& m1, mat<4, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator/(mat<4, 2, T, Q> const& m, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, T, Q> operator/(T scalar, mat<4, 2, T, Q> const& m);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0), col_type(0, 1), col_type(0, 0), col_type(0, 0)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0);
				this->value[1] = col_type(0, 1);
				this->value[2] = col_type(0, 0);
				this->value[3] = col_type(0, 0);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<4, 2, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = m[3];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(T s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0), col_type(0, s), col_type(0, 0), col_type(0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0);
			this->value[1] = col_type(0, s);
			this->value[2] = col_type(0, 0);
			this->value[3] = col_type(0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat
	(
		T x0, T y0,
		T x1, T y1,
		T x2, T y2,
		T x3, T y3
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2), col_type(x3, y3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0);
			this->value[1] = col_type(x1, y1);
			this->value[2] = col_type(x2, y2);
			this->value[3] = col_type(x3, y3);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(col_type const& v0, col_type const& v1, col_type const& v2, col_type const& v3)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
			this->value[2] = v2;
			this->value[3] = v3;
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X0, typename Y0,
		typename X1, typename Y1,
		typename X2, typename Y2,
		typename X3, typename Y3>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat
	(
		X0 x0, Y0 y0,
		X1 x1, Y1 y1,
		X2 x2, Y2 y2,
		X3 x3, Y3 y3
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2), col_type(x3, y3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0);
			this->value[1] = col_type(x1, y1);
			this->value[2] = col_type(x2, y2);
			this->value[3] = col_type(x3, y3);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V0, typename V1, typename V2, typename V3>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(vec<2, V0, Q> const& v0, vec<2, V1, Q> const& v1, vec<2, V2, Q> const& v2, vec<2, V3, Q> const& v3)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v0);
			this->value[1] = col_type(v1);
			this->value[2] = col_type(v2);
			this->value[3] = col_type(v3);
#		endif
	}

	// -- Conversion --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<4, 2, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(m[3]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(m[3]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
				this->value[0] = col_type(m[0]);
				this->value[1] = col_type(m[1]);
				this->value[2] = col_type(m[2]);
				this->value[3] = col_type(m[3]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 2, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(0);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 2, T, Q>::col_type & mat<4, 2, T, Q>::operator[](typename mat<4, 2, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<4, 2, T, Q>::col_type const& mat<4, 2, T, Q>::operator[](typename mat<4, 2, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q>& mat<4, 2, T, Q>::operator=(mat<4, 2, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		this->value[3] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator+=(mat<4, 2, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		this->value[3] += m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		this->value[3] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator-=(mat<4, 2, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		this->value[3] -= m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		this->value[3] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		this->value[3] /= s;
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		++this->value[3];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> & mat<4, 2, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		--this->value[3];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> mat<4, 2, T, Q>::operator++(int)
	{
		mat<4, 2, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> mat<4, 2, T, Q>::operator--(int)
	{
		mat<4, 2, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator+(mat<4, 2, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator-(mat<4, 2, T, Q> const& m)
	{
		return mat<4, 2, T, Q>(
			-m[0],
			-m[1],
			-m[2],
			-m[3]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator+(mat<4, 2, T, Q> const& m, T scalar)
	{
		return mat<4, 2, T, Q>(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar,
			m[3] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator+(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		return mat<4, 2, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator-(mat<4, 2, T, Q> const& m, T scalar)
	{
		return mat<4, 2, T, Q>(
			m[0] - scalar,
			m[1] - scalar,
			m[2] - scalar,
			m[3] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator-(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		return mat<4, 2, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator*(mat<4, 2, T, Q> const& m, T scalar)
	{
		return mat<4, 2, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar,
			m[3] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator*(T scalar, mat<4, 2, T, Q> const& m)
	{
		return mat<4, 2, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar,
			m[3] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 2, T, Q>::col_type operator*(mat<4, 2, T, Q> const& m, typename mat<4, 2, T, Q>::row_type const& v)
	{
		return typename mat<4, 2, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 2, T, Q>::row_type operator*(typename mat<4, 2, T, Q>::col_type const& v, mat<4, 2, T, Q> const& m)
	{
		return typename mat<4, 2, T, Q>::row_type(
			v.x * m[0][0] + v.y * m[0][1],
			v.x * m[1][0] + v.y * m[1][1],
			v.x * m[2][0] + v.y * m[2][1],
			v.x * m[3][0] + v.y * m[3][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator*(mat<4, 2, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		T const SrcA00 = m1[0][0];
		T const SrcA01 = m1[0][1];
		T const SrcA10 = m1[1][0];
		T const SrcA11 = m1[1][1];
		T const SrcA20 = m1[2][0];
		T const SrcA21 = m1[2][1];
		T const SrcA30 = m1[3][0];
		T const SrcA31 = m1[3][1];

		T const SrcB00 = m2[0][0];
		T const SrcB01 = m2[0][1];
		T const SrcB02 = m2[0][2];
		T const SrcB03 = m2[0][3];
		T const SrcB10 = m2[1][0];
		T const SrcB11 = m2[1][1];
		T const SrcB12 = m2[1][2];
		T const SrcB13 = m2[1][3];

		mat<2, 2, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02 + SrcA30 * SrcB03;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02 + SrcA31 * SrcB03;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12 + SrcA30 * SrcB13;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12 + SrcA31 * SrcB13;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator*(mat<4, 2, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		return mat<3, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator*(mat<4, 2, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		return mat<4, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator/(mat<4, 2, T, Q> const& m, T scalar)
	{
		return mat<4, 2, T, Q>(
			m[0] / scalar,
			m[1] / scalar,
			m[2] / scalar,
			m[3] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator/(T scalar, mat<4, 2, T, Q> const& m)
	{
		return mat<4, 2, T, Q>(
			scalar / m[0],
			scalar / m[1],
			scalar / m[2],
			scalar / m[3]);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<4, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}
} //namespace glm


#endif

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 4 columns of 2 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 2, double, defaultp>		dmat4x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double4x2_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 2 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 2, double, lowp>		lowp_dmat4x2;

	/// 4 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 2, double, mediump>	mediump_dmat4x2;

	/// 4 columns of 2 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 2, double, highp>	highp_dmat4x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float4x2.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 4 columns of 2 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 2, float, defaultp>			mat4x2;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float4x2_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 2 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 2, float, lowp>		lowp_mat4x2;

	/// 4 columns of 2 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 2, float, mediump>	mediump_mat4x2;

	/// 4 columns of 2 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 2, float, highp>		highp_mat4x2;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat4x3.hpp" ----------

    // ---------- "./ext/matrix_double4x3.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<4, 3, T, Q>
	{
		typedef vec<3, T, Q> col_type;
		typedef vec<4, T, Q> row_type;
		typedef mat<4, 3, T, Q> type;
		typedef mat<3, 4, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[4];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 4; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<4, 3, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T const& x);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T const& x0, T const& y0, T const& z0,
			T const& x1, T const& y1, T const& z1,
			T const& x2, T const& y2, T const& z2,
			T const& x3, T const& y3, T const& z3);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2,
			col_type const& v3);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1,
			typename X2, typename Y2, typename Z2,
			typename X3, typename Y3, typename Z3,
			typename X4, typename Y4, typename Z4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 const& x1, Y1 const& y1, Z1 const& z1,
			X2 const& x2, Y2 const& y2, Z2 const& z2,
			X3 const& x3, Y3 const& y3, Z3 const& z3,
			X4 const& x4, Y4 const& y4, Z4 const& z4);

		template<typename V1, typename V2, typename V3, typename V4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<3, V1, Q> const& v1,
			vec<3, V2, Q> const& v2,
			vec<3, V3, Q> const& v3,
			vec<3, V4, Q> const& v4);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator=(mat<4, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator+=(mat<4, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator-=(mat<4, 3, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 3, T, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<4, 3, T, Q>& operator++();
		GLM_FUNC_DECL mat<4, 3, T, Q>& operator--();
		GLM_FUNC_DECL mat<4, 3, T, Q> operator++(int);
		GLM_FUNC_DECL mat<4, 3, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator+(mat<4, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator-(mat<4, 3, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator+(mat<4, 3, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator+(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator-(mat<4, 3, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator-(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator*(mat<4, 3, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator*(T const& s, mat<4, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 3, T, Q>::col_type operator*(mat<4, 3, T, Q> const& m, typename mat<4, 3, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 3, T, Q>::row_type operator*(typename mat<4, 3, T, Q>::col_type const& v, mat<4, 3, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, T, Q> operator*(mat<4, 3, T, Q> const& m1, mat<2, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> operator*(mat<4, 3, T, Q> const& m1,	mat<3, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator*(mat<4, 3, T, Q> const& m1, mat<4, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator/(mat<4, 3, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, T, Q> operator/(T const& s, mat<4, 3, T, Q> const& m);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0, 0), col_type(0, 1, 0), col_type(0, 0, 1), col_type(0, 0, 0)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0, 0);
				this->value[1] = col_type(0, 1, 0);
				this->value[2] = col_type(0, 0, 1);
				this->value[3] = col_type(0, 0, 0);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<4, 3, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = m[3];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(T const& s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0, 0), col_type(0, s, 0), col_type(0, 0, s), col_type(0, 0, 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0, 0);
			this->value[1] = col_type(0, s, 0);
			this->value[2] = col_type(0, 0, s);
			this->value[3] = col_type(0, 0, 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat
	(
		T const& x0, T const& y0, T const& z0,
		T const& x1, T const& y1, T const& z1,
		T const& x2, T const& y2, T const& z2,
		T const& x3, T const& y3, T const& z3
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0, z0), col_type(x1, y1, z1), col_type(x2, y2, z2), col_type(x3, y3, z3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0);
			this->value[1] = col_type(x1, y1, z1);
			this->value[2] = col_type(x2, y2, z2);
			this->value[3] = col_type(x3, y3, z3);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(col_type const& v0, col_type const& v1, col_type const& v2, col_type const& v3)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
			this->value[2] = v2;
			this->value[3] = v3;
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X0, typename Y0, typename Z0,
		typename X1, typename Y1, typename Z1,
		typename X2, typename Y2, typename Z2,
		typename X3, typename Y3, typename Z3>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat
	(
		X0 const& x0, Y0 const& y0, Z0 const& z0,
		X1 const& x1, Y1 const& y1, Z1 const& z1,
		X2 const& x2, Y2 const& y2, Z2 const& z2,
		X3 const& x3, Y3 const& y3, Z3 const& z3
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0, z0), col_type(x1, y1, z1), col_type(x2, y2, z2), col_type(x3, y3, z3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0);
			this->value[1] = col_type(x1, y1, z1);
			this->value[2] = col_type(x2, y2, z2);
			this->value[3] = col_type(x3, y3, z3);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2, typename V3, typename V4>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(vec<3, V1, Q> const& v1, vec<3, V2, Q> const& v2, vec<3, V3, Q> const& v3, vec<3, V4, Q> const& v4)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v1), col_type(v2), col_type(v3), col_type(v4)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
			this->value[2] = col_type(v3);
			this->value[3] = col_type(v4);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<4, 3, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(m[3]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(0, 0, 1), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(0, 0, 1);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(m[3]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0, 0, 1);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 1), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 1);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0, 0, 1);
			this->value[3] = col_type(0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 1), col_type(m[3], 0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 1);
			this->value[3] = col_type(m[3], 0);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 3, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(0);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 3, T, Q>::col_type & mat<4, 3, T, Q>::operator[](typename mat<4, 3, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<4, 3, T, Q>::col_type const& mat<4, 3, T, Q>::operator[](typename mat<4, 3, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q>& mat<4, 3, T, Q>::operator=(mat<4, 3, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		this->value[3] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator+=(mat<4, 3, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		this->value[3] += m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		this->value[3] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator-=(mat<4, 3, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		this->value[3] -= m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		this->value[3] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		this->value[3] /= s;
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		++this->value[3];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> & mat<4, 3, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		--this->value[3];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> mat<4, 3, T, Q>::operator++(int)
	{
		mat<4, 3, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> mat<4, 3, T, Q>::operator--(int)
	{
		mat<4, 3, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator+(mat<4, 3, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator-(mat<4, 3, T, Q> const& m)
	{
		return mat<4, 3, T, Q>(
			-m[0],
			-m[1],
			-m[2],
			-m[3]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator+(mat<4, 3, T, Q> const& m, T const& s)
	{
		return mat<4, 3, T, Q>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator+(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		return mat<4, 3, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator-(mat<4, 3, T, Q> const& m, T const& s)
	{
		return mat<4, 3, T, Q>(
			m[0] - s,
			m[1] - s,
			m[2] - s,
			m[3] - s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator-(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		return mat<4, 3, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator*(mat<4, 3, T, Q> const& m, T const& s)
	{
		return mat<4, 3, T, Q>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator*(T const& s, mat<4, 3, T, Q> const& m)
	{
		return mat<4, 3, T, Q>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 3, T, Q>::col_type operator*
	(
		mat<4, 3, T, Q> const& m,
		typename mat<4, 3, T, Q>::row_type const& v)
	{
		return typename mat<4, 3, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 3, T, Q>::row_type operator*
	(
		typename mat<4, 3, T, Q>::col_type const& v,
		mat<4, 3, T, Q> const& m)
	{
		return typename mat<4, 3, T, Q>::row_type(
			v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],
			v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2],
			v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2],
			v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator*(mat<4, 3, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		return mat<2, 3, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator*(mat<4, 3, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		T const SrcA00 = m1[0][0];
		T const SrcA01 = m1[0][1];
		T const SrcA02 = m1[0][2];
		T const SrcA10 = m1[1][0];
		T const SrcA11 = m1[1][1];
		T const SrcA12 = m1[1][2];
		T const SrcA20 = m1[2][0];
		T const SrcA21 = m1[2][1];
		T const SrcA22 = m1[2][2];
		T const SrcA30 = m1[3][0];
		T const SrcA31 = m1[3][1];
		T const SrcA32 = m1[3][2];

		T const SrcB00 = m2[0][0];
		T const SrcB01 = m2[0][1];
		T const SrcB02 = m2[0][2];
		T const SrcB03 = m2[0][3];
		T const SrcB10 = m2[1][0];
		T const SrcB11 = m2[1][1];
		T const SrcB12 = m2[1][2];
		T const SrcB13 = m2[1][3];
		T const SrcB20 = m2[2][0];
		T const SrcB21 = m2[2][1];
		T const SrcB22 = m2[2][2];
		T const SrcB23 = m2[2][3];

		mat<3, 3, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02 + SrcA30 * SrcB03;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02 + SrcA31 * SrcB03;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02 + SrcA32 * SrcB03;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12 + SrcA30 * SrcB13;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12 + SrcA31 * SrcB13;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12 + SrcA32 * SrcB13;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22 + SrcA30 * SrcB23;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22 + SrcA31 * SrcB23;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22 + SrcA32 * SrcB23;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator*(mat<4, 3, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		return mat<4, 3, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3],
			m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator/(mat<4, 3, T, Q> const& m, T const& s)
	{
		return mat<4, 3, T, Q>(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator/(T const& s, mat<4, 3, T, Q> const& m)
	{
		return mat<4, 3, T, Q>(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<4, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}
} //namespace glm


#endif //GLM_EXTERNAL_TEMPLATE

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 4 columns of 3 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 3, double, defaultp>		dmat4x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double4x3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 3 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 3, double, lowp>		lowp_dmat4x3;

	/// 4 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 3, double, mediump>	mediump_dmat4x3;

	/// 4 columns of 3 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 3, double, highp>	highp_dmat4x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float4x3.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 4 columns of 3 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 3, float, defaultp>			mat4x3;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float4x3_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 3 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 3, float, lowp>		lowp_mat4x3;

	/// 4 columns of 3 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 3, float, mediump>	mediump_mat4x3;

	/// 4 columns of 3 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 3, float, highp>		highp_mat4x3;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- #include "mat4x4.hpp" ----------

    // ---------- "./ext/matrix_double4x4.hpp" ----------

namespace glm
{
	template<typename T, qualifier Q>
	struct mat<4, 4, T, Q>
	{
		typedef vec<4, T, Q> col_type;
		typedef vec<4, T, Q> row_type;
		typedef mat<4, 4, T, Q> type;
		typedef mat<4, 4, T, Q> transpose_type;
		typedef T value_type;

	private:
		col_type value[4];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 4;}

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<4, 4, T, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(T const& x);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			T const& x0, T const& y0, T const& z0, T const& w0,
			T const& x1, T const& y1, T const& z1, T const& w1,
			T const& x2, T const& y2, T const& z2, T const& w2,
			T const& x3, T const& y3, T const& z3, T const& w3);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2,
			col_type const& v3);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2,
			typename X3, typename Y3, typename Z3, typename W3,
			typename X4, typename Y4, typename Z4, typename W4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,
			X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2,
			X3 const& x3, Y3 const& y3, Z3 const& z3, W3 const& w3,
			X4 const& x4, Y4 const& y4, Z4 const& z4, W4 const& w4);

		template<typename V1, typename V2, typename V3, typename V4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<4, V1, Q> const& v1,
			vec<4, V2, Q> const& v2,
			vec<4, V3, Q> const& v3,
			vec<4, V4, Q> const& v4);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, T, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, T, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator+=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator-=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator*=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator/=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator/=(mat<4, 4, U, Q> const& m);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<4, 4, T, Q> & operator++();
		GLM_FUNC_DECL mat<4, 4, T, Q> & operator--();
		GLM_FUNC_DECL mat<4, 4, T, Q> operator++(int);
		GLM_FUNC_DECL mat<4, 4, T, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator+(mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator-(mat<4, 4, T, Q> const& m);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator+(mat<4, 4, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator+(T const& s, mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator+(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator-(mat<4, 4, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator-(T const& s, mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator-(mat<4, 4, T, Q> const& m1,	mat<4, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator*(mat<4, 4, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator*(T const& s, mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, T, Q>::col_type operator*(mat<4, 4, T, Q> const& m, typename mat<4, 4, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, T, Q>::row_type operator*(typename mat<4, 4, T, Q>::col_type const& v, mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, T, Q> operator*(mat<4, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, T, Q> operator*(mat<4, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator*(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator/(mat<4, 4, T, Q> const& m, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator/(T const& s, mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, T, Q>::col_type operator/(mat<4, 4, T, Q> const& m, typename mat<4, 4, T, Q>::row_type const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, T, Q>::row_type operator/(typename mat<4, 4, T, Q>::col_type const& v, mat<4, 4, T, Q> const& m);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> operator/(mat<4, 4, T, Q> const& m1,	mat<4, 4, T, Q> const& m2);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2);
}//namespace glm

namespace glm
{
	/// @addtogroup core_matrix
	/// @{

	/// 4 columns of 4 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 4, double, defaultp>		dmat4x4;

	/// 4 columns of 4 components matrix of double-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 4, double, defaultp>		dmat4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_double4x4_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 4 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, double, lowp>		lowp_dmat4;

	/// 4 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, double, mediump>	mediump_dmat4;

	/// 4 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, double, highp>	highp_dmat4;

	/// 4 columns of 4 components matrix of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, double, lowp>		lowp_dmat4x4;

	/// 4 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, double, mediump>	mediump_dmat4x4;

	/// 4 columns of 4 components matrix of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, double, highp>	highp_dmat4x4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float4x4.hpp" ----------

namespace glm
{
	/// @ingroup core_matrix
	/// @{

	/// 4 columns of 4 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 4, float, defaultp>			mat4x4;

	/// 4 columns of 4 components matrix of single-precision floating-point numbers.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat<4, 4, float, defaultp>			mat4;

	/// @}
}//namespace glm


    // ---------- "./ext/matrix_float4x4_precision.hpp" ----------

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 4 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, float, lowp>		lowp_mat4;

	/// 4 columns of 4 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, float, mediump>	mediump_mat4;

	/// 4 columns of 4 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, float, highp>		highp_mat4;

	/// 4 columns of 4 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, float, lowp>		lowp_mat4x4;

	/// 4 columns of 4 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, float, mediump>	mediump_mat4x4;

	/// 4 columns of 4 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef mat<4, 4, float, highp>		highp_mat4x4;

	/// @}
}//namespace glm

// -------------------------------------------

// ---------- _vectorize.hpp -----------

namespace glm{
namespace detail
{
	template<template<length_t L, typename T, qualifier Q> class vec, length_t L, typename R, typename T, qualifier Q>
	struct functor1{};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 1, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, R, Q> call(R (*Func) (T x), vec<1, T, Q> const& v)
		{
			return vec<1, R, Q>(Func(v.x));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 2, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, R, Q> call(R (*Func) (T x), vec<2, T, Q> const& v)
		{
			return vec<2, R, Q>(Func(v.x), Func(v.y));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 3, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, R, Q> call(R (*Func) (T x), vec<3, T, Q> const& v)
		{
			return vec<3, R, Q>(Func(v.x), Func(v.y), Func(v.z));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename R, typename T, qualifier Q>
	struct functor1<vec, 4, R, T, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, R, Q> call(R (*Func) (T x), vec<4, T, Q> const& v)
		{
			return vec<4, R, Q>(Func(v.x), Func(v.y), Func(v.z), Func(v.w));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, length_t L, typename T, qualifier Q>
	struct functor2{};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 1, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, T, Q> call(T (*Func) (T x, T y), vec<1, T, Q> const& a, vec<1, T, Q> const& b)
		{
			return vec<1, T, Q>(Func(a.x, b.x));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 2, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, T, Q> call(T (*Func) (T x, T y), vec<2, T, Q> const& a, vec<2, T, Q> const& b)
		{
			return vec<2, T, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 3, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, T, Q> call(T (*Func) (T x, T y), vec<3, T, Q> const& a, vec<3, T, Q> const& b)
		{
			return vec<3, T, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2<vec, 4, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, T, Q> call(T (*Func) (T x, T y), vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			return vec<4, T, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, length_t L, typename T, qualifier Q>
	struct functor2_vec_sca{};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 1, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, T, Q> call(T (*Func) (T x, T y), vec<1, T, Q> const& a, T b)
		{
			return vec<1, T, Q>(Func(a.x, b));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 2, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, T, Q> call(T (*Func) (T x, T y), vec<2, T, Q> const& a, T b)
		{
			return vec<2, T, Q>(Func(a.x, b), Func(a.y, b));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 3, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, T, Q> call(T (*Func) (T x, T y), vec<3, T, Q> const& a, T b)
		{
			return vec<3, T, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b));
		}
	};

	template<template<length_t L, typename T, qualifier Q> class vec, typename T, qualifier Q>
	struct functor2_vec_sca<vec, 4, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, T, Q> call(T (*Func) (T x, T y), vec<4, T, Q> const& a, T b)
		{
			return vec<4, T, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b), Func(a.w, b));
		}
	};

	template<length_t L, typename T, qualifier Q>
	struct functor2_vec_int {};

	template<typename T, qualifier Q>
	struct functor2_vec_int<1, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, int, Q> call(int (*Func) (T x, int y), vec<1, T, Q> const& a, vec<1, int, Q> const& b)
		{
			return vec<1, int, Q>(Func(a.x, b.x));
		}
	};

	template<typename T, qualifier Q>
	struct functor2_vec_int<2, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, int, Q> call(int (*Func) (T x, int y), vec<2, T, Q> const& a, vec<2, int, Q> const& b)
		{
			return vec<2, int, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
	};

	template<typename T, qualifier Q>
	struct functor2_vec_int<3, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, int, Q> call(int (*Func) (T x, int y), vec<3, T, Q> const& a, vec<3, int, Q> const& b)
		{
			return vec<3, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
	};

	template<typename T, qualifier Q>
	struct functor2_vec_int<4, T, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, int, Q> call(int (*Func) (T x, int y), vec<4, T, Q> const& a, vec<4, int, Q> const& b)
		{
			return vec<4, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
	};
}//namespace detail
}//namespace glm


// -------------------------------------

// ---------- #include "trigonometric.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_trigonometric
	/// @{

	/// Converts degrees to radians and returns the result.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/radians.xml">GLSL radians man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> radians(vec<L, T, Q> const& degrees);

	/// Converts radians to degrees and returns the result.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/degrees.xml">GLSL degrees man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> degrees(vec<L, T, Q> const& radians);

	/// The standard trigonometric sine function.
	/// The values returned by this function will range from [-1, 1].
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sin.xml">GLSL sin man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> sin(vec<L, T, Q> const& angle);

	/// The standard trigonometric cosine function.
	/// The values returned by this function will range from [-1, 1].
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/cos.xml">GLSL cos man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> cos(vec<L, T, Q> const& angle);

	/// The standard trigonometric tangent function.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/tan.xml">GLSL tan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> tan(vec<L, T, Q> const& angle);

	/// Arc sine. Returns an angle whose sine is x.
	/// The range of values returned by this function is [-PI/2, PI/2].
	/// Results are undefined if |x| > 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/asin.xml">GLSL asin man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> asin(vec<L, T, Q> const& x);

	/// Arc cosine. Returns an angle whose sine is x.
	/// The range of values returned by this function is [0, PI].
	/// Results are undefined if |x| > 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/acos.xml">GLSL acos man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> acos(vec<L, T, Q> const& x);

	/// Arc tangent. Returns an angle whose tangent is y/x.
	/// The signs of x and y are used to determine what
	/// quadrant the angle is in. The range of values returned
	/// by this function is [-PI, PI]. Results are undefined
	/// if x and y are both 0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/atan.xml">GLSL atan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> atan(vec<L, T, Q> const& y, vec<L, T, Q> const& x);

	/// Arc tangent. Returns an angle whose tangent is y_over_x.
	/// The range of values returned by this function is [-PI/2, PI/2].
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/atan.xml">GLSL atan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> atan(vec<L, T, Q> const& y_over_x);

	/// Returns the hyperbolic sine function, (exp(x) - exp(-x)) / 2
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sinh.xml">GLSL sinh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> sinh(vec<L, T, Q> const& angle);

	/// Returns the hyperbolic cosine function, (exp(x) + exp(-x)) / 2
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/cosh.xml">GLSL cosh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> cosh(vec<L, T, Q> const& angle);

	/// Returns the hyperbolic tangent function, sinh(angle) / cosh(angle)
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/tanh.xml">GLSL tanh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> tanh(vec<L, T, Q> const& angle);

	/// Arc hyperbolic sine; returns the inverse of sinh.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/asinh.xml">GLSL asinh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> asinh(vec<L, T, Q> const& x);

	/// Arc hyperbolic cosine; returns the non-negative inverse
	/// of cosh. Results are undefined if x < 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/acosh.xml">GLSL acosh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> acosh(vec<L, T, Q> const& x);

	/// Arc hyperbolic tangent; returns the inverse of tanh.
	/// Results are undefined if abs(x) >= 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/atanh.xml">GLSL atanh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> atanh(vec<L, T, Q> const& x);

	/// @}
}//namespace glm

namespace glm
{
	// radians
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType radians(genType degrees)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'radians' only accept floating-point input");

		return degrees * static_cast<genType>(0.01745329251994329576923690768489);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> radians(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(radians, v);
	}

	// degrees
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType degrees(genType radians)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'degrees' only accept floating-point input");

		return radians * static_cast<genType>(57.295779513082320876798154814105);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> degrees(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(degrees, v);
	}

	// sin
	using ::std::sin;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> sin(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(sin, v);
	}

	// cos
	using std::cos;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> cos(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(cos, v);
	}

	// tan
	using std::tan;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> tan(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(tan, v);
	}

	// asin
	using std::asin;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> asin(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(asin, v);
	}

	// acos
	using std::acos;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> acos(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(acos, v);
	}

	// atan
	template<typename genType>
	GLM_FUNC_QUALIFIER genType atan(genType y, genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'atan' only accept floating-point input");

		return ::std::atan2(y, x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> atan(vec<L, T, Q> const& a, vec<L, T, Q> const& b)
	{
		return detail::functor2<vec, L, T, Q>::call(::std::atan2, a, b);
	}

	using std::atan;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> atan(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(atan, v);
	}

	// sinh
	using std::sinh;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> sinh(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(sinh, v);
	}

	// cosh
	using std::cosh;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> cosh(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(cosh, v);
	}

	// tanh
	using std::tanh;

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> tanh(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(tanh, v);
	}

	// asinh
#	if GLM_HAS_CXX11_STL
		using std::asinh;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType asinh(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'asinh' only accept floating-point input");

			return (x < static_cast<genType>(0) ? static_cast<genType>(-1) : (x > static_cast<genType>(0) ? static_cast<genType>(1) : static_cast<genType>(0))) * log(std::abs(x) + sqrt(static_cast<genType>(1) + x * x));
		}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> asinh(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(asinh, v);
	}

	// acosh
#	if GLM_HAS_CXX11_STL
		using std::acosh;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType acosh(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'acosh' only accept floating-point input");

			if(x < static_cast<genType>(1))
				return static_cast<genType>(0);
			return log(x + sqrt(x * x - static_cast<genType>(1)));
		}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> acosh(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(acosh, v);
	}

	// atanh
#	if GLM_HAS_CXX11_STL
		using std::atanh;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType atanh(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'atanh' only accept floating-point input");

			if(std::abs(x) >= static_cast<genType>(1))
				return 0;
			return static_cast<genType>(0.5) * log((static_cast<genType>(1) + x) / (static_cast<genType>(1) - x));
		}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> atanh(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(atanh, v);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_trigonometric_simd.inl"
#endif




// ---------- #include "exponential.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_exponential
	/// @{

	/// Returns 'base' raised to the power 'exponent'.
	///
	/// @param base Floating point value. pow function is defined for input values of 'base' defined in the range (inf-, inf+) in the limit of the type qualifier.
	/// @param exponent Floating point value representing the 'exponent'.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/pow.xml">GLSL pow man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> pow(vec<L, T, Q> const& base, vec<L, T, Q> const& exponent);

	/// Returns the natural exponentiation of x, i.e., e^x.
	///
	/// @param v exp function is defined for input values of v defined in the range (inf-, inf+) in the limit of the type qualifier.
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/exp.xml">GLSL exp man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> exp(vec<L, T, Q> const& v);

	/// Returns the natural logarithm of v, i.e.,
	/// returns the value y which satisfies the equation x = e^y.
	/// Results are undefined if v <= 0.
	///
	/// @param v log function is defined for input values of v defined in the range (0, inf+) in the limit of the type qualifier.
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/log.xml">GLSL log man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> log(vec<L, T, Q> const& v);

	/// Returns 2 raised to the v power.
	///
	/// @param v exp2 function is defined for input values of v defined in the range (inf-, inf+) in the limit of the type qualifier.
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/exp2.xml">GLSL exp2 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> exp2(vec<L, T, Q> const& v);

	/// Returns the base 2 log of x, i.e., returns the value y,
	/// which satisfies the equation x = 2 ^ y.
	///
	/// @param v log2 function is defined for input values of v defined in the range (0, inf+) in the limit of the type qualifier.
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/log2.xml">GLSL log2 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> log2(vec<L, T, Q> const& v);

	/// Returns the positive square root of v.
	///
	/// @param v sqrt function is defined for input values of v defined in the range [0, inf+) in the limit of the type qualifier.
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sqrt.xml">GLSL sqrt man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> sqrt(vec<L, T, Q> const& v);

	/// Returns the reciprocal of the positive square root of v.
	///
	/// @param v inversesqrt function is defined for input values of v defined in the range [0, inf+) in the limit of the type qualifier.
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inversesqrt.xml">GLSL inversesqrt man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> inversesqrt(vec<L, T, Q> const& v);

	/// @}
}//namespace glm


// ---------- #include "common.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_common
	/// @{

	/// Returns x if x >= 0; otherwise, it returns -x.
	///
	/// @tparam genType floating-point or signed integer; scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/abs.xml">GLSL abs man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType abs(genType x);

	/// Returns x if x >= 0; otherwise, it returns -x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/abs.xml">GLSL abs man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> abs(vec<L, T, Q> const& x);

	/// Returns 1.0 if x > 0, 0.0 if x == 0, or -1.0 if x < 0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sign.xml">GLSL sign man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> sign(vec<L, T, Q> const& x);

	/// Returns a value equal to the nearest integer that is less then or equal to x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floor.xml">GLSL floor man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> floor(vec<L, T, Q> const& x);

	/// Returns a value equal to the nearest integer to x
	/// whose absolute value is not larger than the absolute value of x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/trunc.xml">GLSL trunc man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> trunc(vec<L, T, Q> const& x);

	/// Returns a value equal to the nearest integer to x.
	/// The fraction 0.5 will round in a direction chosen by the
	/// implementation, presumably the direction that is fastest.
	/// This includes the possibility that round(x) returns the
	/// same value as roundEven(x) for all values of x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/round.xml">GLSL round man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> round(vec<L, T, Q> const& x);

	/// Returns a value equal to the nearest integer to x.
	/// A fractional part of 0.5 will round toward the nearest even
	/// integer. (Both 3.5 and 4.5 for x will return 4.0.)
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/roundEven.xml">GLSL roundEven man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	/// @see <a href="http://developer.amd.com/documentation/articles/pages/New-Round-to-Even-Technique.aspx">New round to even technique</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> roundEven(vec<L, T, Q> const& x);

	/// Returns a value equal to the nearest integer
	/// that is greater than or equal to x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/ceil.xml">GLSL ceil man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> ceil(vec<L, T, Q> const& x);

	/// Return x - floor(x).
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/fract.xml">GLSL fract man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType fract(genType x);

	/// Return x - floor(x).
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/fract.xml">GLSL fract man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> fract(vec<L, T, Q> const& x);

	template<typename genType>
	GLM_FUNC_DECL genType mod(genType x, genType y);

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mod(vec<L, T, Q> const& x, T y);

	/// Modulus. Returns x - y * floor(x / y)
	/// for each component in x using the floating point value y.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types, include glm/gtc/integer for integer scalar types support
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/mod.xml">GLSL mod man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mod(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the fractional part of x and sets i to the integer
	/// part (as a whole number floating point value). Both the
	/// return value and the output parameter will have the same
	/// sign as x.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/modf.xml">GLSL modf man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType modf(genType x, genType& i);

	/// Returns y if y < x; otherwise, it returns x.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/min.xml">GLSL min man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType min(genType x, genType y);

	/// Returns y if y < x; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/min.xml">GLSL min man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> min(vec<L, T, Q> const& x, T y);

	/// Returns y if y < x; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/min.xml">GLSL min man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> min(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns y if x < y; otherwise, it returns x.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/max.xml">GLSL max man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType max(genType x, genType y);

	/// Returns y if x < y; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/max.xml">GLSL max man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> max(vec<L, T, Q> const& x, T y);

	/// Returns y if x < y; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/max.xml">GLSL max man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> max(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns min(max(x, minVal), maxVal) for each component in x
	/// using the floating-point values minVal and maxVal.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml">GLSL clamp man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType clamp(genType x, genType minVal, genType maxVal);

	/// Returns min(max(x, minVal), maxVal) for each component in x
	/// using the floating-point values minVal and maxVal.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml">GLSL clamp man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> clamp(vec<L, T, Q> const& x, T minVal, T maxVal);

	/// Returns min(max(x, minVal), maxVal) for each component in x
	/// using the floating-point values minVal and maxVal.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml">GLSL clamp man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> clamp(vec<L, T, Q> const& x, vec<L, T, Q> const& minVal, vec<L, T, Q> const& maxVal);

	/// If genTypeU is a floating scalar or vector:
	/// Returns x * (1.0 - a) + y * a, i.e., the linear blend of
	/// x and y using the floating-point value a.
	/// The value for a is not restricted to the range [0, 1].
	///
	/// If genTypeU is a boolean scalar or vector:
	/// Selects which vector each returned component comes
	/// from. For a component of 'a' that is false, the
	/// corresponding component of 'x' is returned. For a
	/// component of 'a' that is true, the corresponding
	/// component of 'y' is returned. Components of 'x' and 'y' that
	/// are not selected are allowed to be invalid floating point
	/// values and will have no effect on the results. Thus, this
	/// provides different functionality than
	/// genType mix(genType x, genType y, genType(a))
	/// where a is a Boolean vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/mix.xml">GLSL mix man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	///
	/// @param[in]  x Value to interpolate.
	/// @param[in]  y Value to interpolate.
	/// @param[in]  a Interpolant.
	///
	/// @tparam	genTypeT Floating point scalar or vector.
	/// @tparam genTypeU Floating point or boolean scalar or vector. It can't be a vector if it is the length of genTypeT.
	///
	/// @code
	/// #include <glm/glm.hpp>
	/// ...
	/// float a;
	/// bool b;
	/// glm::dvec3 e;
	/// glm::dvec3 f;
	/// glm::vec4 g;
	/// glm::vec4 h;
	/// ...
	/// glm::vec4 r = glm::mix(g, h, a); // Interpolate with a floating-point scalar two vectors.
	/// glm::vec4 s = glm::mix(g, h, b); // Returns g or h;
	/// glm::dvec3 t = glm::mix(e, f, a); // Types of the third parameter is not required to match with the first and the second.
	/// glm::vec4 u = glm::mix(g, h, r); // Interpolations can be perform per component with a vector for the last parameter.
	/// @endcode
	template<typename genTypeT, typename genTypeU>
	GLM_FUNC_DECL genTypeT mix(genTypeT x, genTypeT y, genTypeU a);

	template<length_t L, typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mix(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, U, Q> const& a);

	template<length_t L, typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mix(vec<L, T, Q> const& x, vec<L, T, Q> const& y, U a);

	/// Returns 0.0 if x < edge, otherwise it returns 1.0 for each component of a genType.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/step.xml">GLSL step man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType step(genType edge, genType x);

	/// Returns 0.0 if x < edge, otherwise it returns 1.0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/step.xml">GLSL step man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> step(T edge, vec<L, T, Q> const& x);

	/// Returns 0.0 if x < edge, otherwise it returns 1.0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/step.xml">GLSL step man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> step(vec<L, T, Q> const& edge, vec<L, T, Q> const& x);

	/// Returns 0.0 if x <= edge0 and 1.0 if x >= edge1 and
	/// performs smooth Hermite interpolation between 0 and 1
	/// when edge0 < x < edge1. This is useful in cases where
	/// you would want a threshold function with a smooth
	/// transition. This is equivalent to:
	/// genType t;
	/// t = clamp ((x - edge0) / (edge1 - edge0), 0, 1);
	/// return t * t * (3 - 2 * t);
	/// Results are undefined if edge0 >= edge1.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/smoothstep.xml">GLSL smoothstep man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType smoothstep(genType edge0, genType edge1, genType x);

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> smoothstep(T edge0, T edge1, vec<L, T, Q> const& x);

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> smoothstep(vec<L, T, Q> const& edge0, vec<L, T, Q> const& edge1, vec<L, T, Q> const& x);

	/// Returns true if x holds a NaN (not a number)
	/// representation in the underlying implementation's set of
	/// floating point representations. Returns false otherwise,
	/// including for implementations with no NaN
	/// representations.
	///
	/// /!\ When using compiler fast math, this function may fail.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/isnan.xml">GLSL isnan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isnan(vec<L, T, Q> const& x);

	/// Returns true if x holds a positive infinity or negative
	/// infinity representation in the underlying implementation's
	/// set of floating point representations. Returns false
	/// otherwise, including for implementations with no infinity
	/// representations.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/isinf.xml">GLSL isinf man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isinf(vec<L, T, Q> const& x);

	/// Returns a signed integer value representing
	/// the encoding of a floating-point value. The floating-point
	/// value's bit-level representation is preserved.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToInt.xml">GLSL floatBitsToInt man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	GLM_FUNC_DECL int floatBitsToInt(float const& v);

	/// Returns a signed integer value representing
	/// the encoding of a floating-point value. The floatingpoint
	/// value's bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToInt.xml">GLSL floatBitsToInt man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, int, Q> floatBitsToInt(vec<L, float, Q> const& v);

	/// Returns a unsigned integer value representing
	/// the encoding of a floating-point value. The floatingpoint
	/// value's bit-level representation is preserved.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToUint.xml">GLSL floatBitsToUint man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	GLM_FUNC_DECL uint floatBitsToUint(float const& v);

	/// Returns a unsigned integer value representing
	/// the encoding of a floating-point value. The floatingpoint
	/// value's bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToUint.xml">GLSL floatBitsToUint man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, uint, Q> floatBitsToUint(vec<L, float, Q> const& v);

	/// Returns a floating-point value corresponding to a signed
	/// integer encoding of a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/intBitsToFloat.xml">GLSL intBitsToFloat man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	GLM_FUNC_DECL float intBitsToFloat(int const& v);

	/// Returns a floating-point value corresponding to a signed
	/// integer encoding of a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/intBitsToFloat.xml">GLSL intBitsToFloat man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, float, Q> intBitsToFloat(vec<L, int, Q> const& v);

	/// Returns a floating-point value corresponding to a
	/// unsigned integer encoding of a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/uintBitsToFloat.xml">GLSL uintBitsToFloat man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	GLM_FUNC_DECL float uintBitsToFloat(uint const& v);

	/// Returns a floating-point value corresponding to a
	/// unsigned integer encoding of a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/uintBitsToFloat.xml">GLSL uintBitsToFloat man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, float, Q> uintBitsToFloat(vec<L, uint, Q> const& v);

	/// Computes and returns a * b + c.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/fma.xml">GLSL fma man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType fma(genType const& a, genType const& b, genType const& c);

	/// Splits x into a floating-point significand in the range
	/// [0.5, 1.0) and an integral exponent of two, such that:
	/// x = significand * exp(2, exponent)
	///
	/// The significand is returned by the function and the
	/// exponent is returned in the parameter exp. For a
	/// floating-point value of zero, the significant and exponent
	/// are both zero. For a floating-point value that is an
	/// infinity or is not a number, the results are undefined.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/frexp.xml">GLSL frexp man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType frexp(genType x, int& exp);
	
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> frexp(vec<L, T, Q> const& v, vec<L, int, Q>& exp);

	/// Builds a floating-point number from x and the
	/// corresponding integral exponent of two in exp, returning:
	/// significand * exp(2, exponent)
	///
	/// If this product is too large to be represented in the
	/// floating-point type, the result is undefined.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/ldexp.xml">GLSL ldexp man page</a>;
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</a>
	template<typename genType>
	GLM_FUNC_DECL genType ldexp(genType const& x, int const& exp);
	
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> ldexp(vec<L, T, Q> const& v, vec<L, int, Q> const& exp);

	/// @}
}//namespace glm


// ---------- #include "packing.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_packing
	/// @{

	/// First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values.
	/// Then, the results are packed into the returned 32-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packUnorm2x16: round(clamp(c, 0, +1) * 65535.0)
	///
	/// The first component of the vector will be written to the least significant bits of the output;
	/// the last component will be written to the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm2x16.xml">GLSL packUnorm2x16 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint packUnorm2x16(vec2 const& v);

	/// First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values.
	/// Then, the results are packed into the returned 32-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packSnorm2x16: round(clamp(v, -1, +1) * 32767.0)
	///
	/// The first component of the vector will be written to the least significant bits of the output;
	/// the last component will be written to the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packSnorm2x16.xml">GLSL packSnorm2x16 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint packSnorm2x16(vec2 const& v);

	/// First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values.
	/// Then, the results are packed into the returned 32-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packUnorm4x8:	round(clamp(c, 0, +1) * 255.0)
	///
	/// The first component of the vector will be written to the least significant bits of the output;
	/// the last component will be written to the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packUnorm4x8.xml">GLSL packUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint packUnorm4x8(vec4 const& v);

	/// First, converts each component of the normalized floating-point value v into 8- or 16-bit integer values.
	/// Then, the results are packed into the returned 32-bit unsigned integer.
	///
	/// The conversion for component c of v to fixed point is done as follows:
	/// packSnorm4x8:	round(clamp(c, -1, +1) * 127.0)
	///
	/// The first component of the vector will be written to the least significant bits of the output;
	/// the last component will be written to the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packSnorm4x8.xml">GLSL packSnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint packSnorm4x8(vec4 const& v);

	/// First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers.
	/// Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackUnorm2x16: f / 65535.0
	///
	/// The first component of the returned vector will be extracted from the least significant bits of the input;
	/// the last component will be extracted from the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackUnorm2x16.xml">GLSL unpackUnorm2x16 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec2 unpackUnorm2x16(uint p);

	/// First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers.
	/// Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackSnorm2x16: clamp(f / 32767.0, -1, +1)
	///
	/// The first component of the returned vector will be extracted from the least significant bits of the input;
	/// the last component will be extracted from the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackSnorm2x16.xml">GLSL unpackSnorm2x16 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec2 unpackSnorm2x16(uint p);

	/// First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers.
	/// Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackUnorm4x8: f / 255.0
	///
	/// The first component of the returned vector will be extracted from the least significant bits of the input;
	/// the last component will be extracted from the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackUnorm4x8.xml">GLSL unpackUnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec4 unpackUnorm4x8(uint p);

	/// First, unpacks a single 32-bit unsigned integer p into a pair of 16-bit unsigned integers, four 8-bit unsigned integers, or four 8-bit signed integers.
	/// Then, each component is converted to a normalized floating-point value to generate the returned two- or four-component vector.
	///
	/// The conversion for unpacked fixed-point value f to floating point is done as follows:
	/// unpackSnorm4x8: clamp(f / 127.0, -1, +1)
	///
	/// The first component of the returned vector will be extracted from the least significant bits of the input;
	/// the last component will be extracted from the most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackSnorm4x8.xml">GLSL unpackSnorm4x8 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec4 unpackSnorm4x8(uint p);

	/// Returns a double-qualifier value obtained by packing the components of v into a 64-bit value.
	/// If an IEEE 754 Inf or NaN is created, it will not signal, and the resulting floating point value is unspecified.
	/// Otherwise, the bit- level representation of v is preserved.
	/// The first vector component specifies the 32 least significant bits;
	/// the second component specifies the 32 most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packDouble2x32.xml">GLSL packDouble2x32 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL double packDouble2x32(uvec2 const& v);

	/// Returns a two-component unsigned integer vector representation of v.
	/// The bit-level representation of v is preserved.
	/// The first component of the vector contains the 32 least significant bits of the double;
	/// the second component consists the 32 most significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackDouble2x32.xml">GLSL unpackDouble2x32 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uvec2 unpackDouble2x32(double v);

	/// Returns an unsigned integer obtained by converting the components of a two-component floating-point vector
	/// to the 16-bit floating-point representation found in the OpenGL Specification,
	/// and then packing these two 16- bit integers into a 32-bit unsigned integer.
	/// The first vector component specifies the 16 least-significant bits of the result;
	/// the second component specifies the 16 most-significant bits.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/packHalf2x16.xml">GLSL packHalf2x16 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL uint packHalf2x16(vec2 const& v);

	/// Returns a two-component floating-point vector with components obtained by unpacking a 32-bit unsigned integer into a pair of 16-bit values,
	/// interpreting those values as 16-bit floating-point numbers according to the OpenGL Specification,
	/// and converting them to 32-bit floating-point values.
	/// The first component of the vector is obtained from the 16 least-significant bits of v;
	/// the second component is obtained from the 16 most-significant bits of v.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/unpackHalf2x16.xml">GLSL unpackHalf2x16 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.4 Floating-Point Pack and Unpack Functions</a>
	GLM_FUNC_DECL vec2 unpackHalf2x16(uint v);

	/// @}
}//namespace glm

namespace glm{
namespace detail
{
	typedef short hdata;

	GLM_FUNC_DECL float toFloat32(hdata value);
	GLM_FUNC_DECL hdata toFloat16(float const& value);

}//namespace detail
}//namespace glm

namespace glm{
namespace detail
{
	GLM_FUNC_QUALIFIER float overflow()
	{
		volatile float f = 1e10;

		for(int i = 0; i < 10; ++i)
			f *= f; // this will overflow before the for loop terminates
		return f;
	}

	union uif32
	{
		GLM_FUNC_QUALIFIER uif32() :
			i(0)
		{}

		GLM_FUNC_QUALIFIER uif32(float f_) :
			f(f_)
		{}

		GLM_FUNC_QUALIFIER uif32(unsigned int i_) :
			i(i_)
		{}

		float f;
		unsigned int i;
	};

	GLM_FUNC_QUALIFIER float toFloat32(hdata value)
	{
		int s = (value >> 15) & 0x00000001;
		int e = (value >> 10) & 0x0000001f;
		int m =  value        & 0x000003ff;

		if(e == 0)
		{
			if(m == 0)
			{
				//
				// Plus or minus zero
				//

				detail::uif32 result;
				result.i = static_cast<unsigned int>(s << 31);
				return result.f;
			}
			else
			{
				//
				// Denormalized number -- renormalize it
				//

				while(!(m & 0x00000400))
				{
					m <<= 1;
					e -=  1;
				}

				e += 1;
				m &= ~0x00000400;
			}
		}
		else if(e == 31)
		{
			if(m == 0)
			{
				//
				// Positive or negative infinity
				//

				uif32 result;
				result.i = static_cast<unsigned int>((s << 31) | 0x7f800000);
				return result.f;
			}
			else
			{
				//
				// Nan -- preserve sign and significand bits
				//

				uif32 result;
				result.i = static_cast<unsigned int>((s << 31) | 0x7f800000 | (m << 13));
				return result.f;
			}
		}

		//
		// Normalized number
		//

		e = e + (127 - 15);
		m = m << 13;

		//
		// Assemble s, e and m.
		//

		uif32 Result;
		Result.i = static_cast<unsigned int>((s << 31) | (e << 23) | m);
		return Result.f;
	}

	GLM_FUNC_QUALIFIER hdata toFloat16(float const& f)
	{
		uif32 Entry;
		Entry.f = f;
		int i = static_cast<int>(Entry.i);

		//
		// Our floating point number, f, is represented by the bit
		// pattern in integer i.  Disassemble that bit pattern into
		// the sign, s, the exponent, e, and the significand, m.
		// Shift s into the position where it will go in the
		// resulting half number.
		// Adjust e, accounting for the different exponent bias
		// of float and half (127 versus 15).
		//

		int s =  (i >> 16) & 0x00008000;
		int e = ((i >> 23) & 0x000000ff) - (127 - 15);
		int m =   i        & 0x007fffff;

		//
		// Now reassemble s, e and m into a half:
		//

		if(e <= 0)
		{
			if(e < -10)
			{
				//
				// E is less than -10.  The absolute value of f is
				// less than half_MIN (f may be a small normalized
				// float, a denormalized float or a zero).
				//
				// We convert f to a half zero.
				//

				return hdata(s);
			}

			//
			// E is between -10 and 0.  F is a normalized float,
			// whose magnitude is less than __half_NRM_MIN.
			//
			// We convert f to a denormalized half.
			//

			m = (m | 0x00800000) >> (1 - e);

			//
			// Round to nearest, round "0.5" up.
			//
			// Rounding may cause the significand to overflow and make
			// our number normalized.  Because of the way a half's bits
			// are laid out, we don't have to treat this case separately;
			// the code below will handle it correctly.
			//

			if(m & 0x00001000)
				m += 0x00002000;

			//
			// Assemble the half from s, e (zero) and m.
			//

			return hdata(s | (m >> 13));
		}
		else if(e == 0xff - (127 - 15))
		{
			if(m == 0)
			{
				//
				// F is an infinity; convert f to a half
				// infinity with the same sign as f.
				//

				return hdata(s | 0x7c00);
			}
			else
			{
				//
				// F is a NAN; we produce a half NAN that preserves
				// the sign bit and the 10 leftmost bits of the
				// significand of f, with one exception: If the 10
				// leftmost bits are all zero, the NAN would turn
				// into an infinity, so we have to set at least one
				// bit in the significand.
				//

				m >>= 13;

				return hdata(s | 0x7c00 | m | (m == 0));
			}
		}
		else
		{
			//
			// E is greater than zero.  F is a normalized float.
			// We try to convert f to a normalized half.
			//

			//
			// Round to nearest, round "0.5" up
			//

			if(m &  0x00001000)
			{
				m += 0x00002000;

				if(m & 0x00800000)
				{
					m =  0;     // overflow in significand,
					e += 1;     // adjust exponent
				}
			}

			//
			// Handle exponent overflow
			//

			if (e > 30)
			{
				overflow();        // Cause a hardware floating point overflow;

				return hdata(s | 0x7c00);
				// if this returns, the half becomes an
			}   // infinity with the same sign as f.

			//
			// Assemble the half from s, e and m.
			//

			return hdata(s | (e << 10) | (m >> 13));
		}
	}

}//namespace detail
}//namespace glm

namespace glm
{
	GLM_FUNC_QUALIFIER uint packUnorm2x16(vec2 const& v)
	{
		union
		{
			unsigned short in[2];
			uint out;
		} u;

		vec<2, unsigned short, defaultp> result(round(clamp(v, 0.0f, 1.0f) * 65535.0f));

		u.in[0] = result[0];
		u.in[1] = result[1];

		return u.out;
	}

	GLM_FUNC_QUALIFIER vec2 unpackUnorm2x16(uint p)
	{
		union
		{
			uint in;
			unsigned short out[2];
		} u;

		u.in = p;

		return vec2(u.out[0], u.out[1]) * 1.5259021896696421759365224689097e-5f;
	}

	GLM_FUNC_QUALIFIER uint packSnorm2x16(vec2 const& v)
	{
		union
		{
			signed short in[2];
			uint out;
		} u;
 
		vec<2, short, defaultp> result(round(clamp(v, -1.0f, 1.0f) * 32767.0f));

		u.in[0] = result[0];
		u.in[1] = result[1];

		return u.out;
	}

	GLM_FUNC_QUALIFIER vec2 unpackSnorm2x16(uint p)
	{
		union
		{
			uint in;
			signed short out[2];
		} u;

		u.in = p;

		return clamp(vec2(u.out[0], u.out[1]) * 3.0518509475997192297128208258309e-5f, -1.0f, 1.0f);
	}

	GLM_FUNC_QUALIFIER uint packUnorm4x8(vec4 const& v)
	{
		union
		{
			unsigned char in[4];
			uint out;
		} u;

		vec<4, unsigned char, defaultp> result(round(clamp(v, 0.0f, 1.0f) * 255.0f));

		u.in[0] = result[0];
		u.in[1] = result[1];
		u.in[2] = result[2];
		u.in[3] = result[3];

		return u.out;
	}

	GLM_FUNC_QUALIFIER vec4 unpackUnorm4x8(uint p)
	{
		union
		{
			uint in;
			unsigned char out[4];
		} u;

		u.in = p;

		return vec4(u.out[0], u.out[1], u.out[2], u.out[3]) * 0.0039215686274509803921568627451f;
	}

	GLM_FUNC_QUALIFIER uint packSnorm4x8(vec4 const& v)
	{
		union
		{
			signed char in[4];
			uint out;
		} u;

		vec<4, signed char, defaultp> result(round(clamp(v, -1.0f, 1.0f) * 127.0f));

		u.in[0] = result[0];
		u.in[1] = result[1];
		u.in[2] = result[2];
		u.in[3] = result[3];

		return u.out;
	}

	GLM_FUNC_QUALIFIER glm::vec4 unpackSnorm4x8(uint p)
	{
		union
		{
			uint in;
			signed char out[4];
		} u;

		u.in = p;

		return clamp(vec4(u.out[0], u.out[1], u.out[2], u.out[3]) * 0.0078740157480315f, -1.0f, 1.0f);
	}

	GLM_FUNC_QUALIFIER double packDouble2x32(uvec2 const& v)
	{
		union
		{
			uint   in[2];
			double out;
		} u;

		u.in[0] = v[0];
		u.in[1] = v[1];

		return u.out;
	}

	GLM_FUNC_QUALIFIER uvec2 unpackDouble2x32(double v)
	{
		union
		{
			double in;
			uint   out[2];
		} u;

		u.in = v;

		return uvec2(u.out[0], u.out[1]);
	}

	GLM_FUNC_QUALIFIER uint packHalf2x16(vec2 const& v)
	{
		union
		{
			signed short in[2];
			uint out;
		} u;

		u.in[0] = detail::toFloat16(v.x);
		u.in[1] = detail::toFloat16(v.y);

		return u.out;
	}

	GLM_FUNC_QUALIFIER vec2 unpackHalf2x16(uint v)
	{
		union
		{
			uint in;
			signed short out[2];
		} u;

		u.in = v;

		return vec2(
			detail::toFloat32(u.out[0]),
			detail::toFloat32(u.out[1]));
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_packing_simd.inl"
#endif




// ---------- #include "geometric.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_geometric
	/// @{

	/// Returns the length of x, i.e., sqrt(x * x).
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/length.xml">GLSL length man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T length(vec<L, T, Q> const& x);

	/// Returns the distance betwwen p0 and p1, i.e., length(p0 - p1).
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/distance.xml">GLSL distance man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T distance(vec<L, T, Q> const& p0, vec<L, T, Q> const& p1);

	/// Returns the dot product of x and y, i.e., result = x * y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/dot.xml">GLSL dot man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T dot(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the cross product of x and y.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/cross.xml">GLSL cross man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> cross(vec<3, T, Q> const& x, vec<3, T, Q> const& y);

	/// Returns a vector in the same direction as x but with length of 1.
	/// According to issue 10 GLSL 1.10 specification, if length(x) == 0 then result is undefined and generate an error.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/normalize.xml">GLSL normalize man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> normalize(vec<L, T, Q> const& x);

	/// If dot(Nref, I) < 0.0, return N, otherwise, return -N.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/faceforward.xml">GLSL faceforward man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> faceforward(
		vec<L, T, Q> const& N,
		vec<L, T, Q> const& I,
		vec<L, T, Q> const& Nref);

	/// For the incident vector I and surface orientation N,
	/// returns the reflection direction : result = I - 2.0 * dot(N, I) * N.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/reflect.xml">GLSL reflect man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> reflect(
		vec<L, T, Q> const& I,
		vec<L, T, Q> const& N);

	/// For the incident vector I and surface normal N,
	/// and the ratio of indices of refraction eta,
	/// return the refraction vector.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/refract.xml">GLSL refract man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.5 Geometric Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> refract(
		vec<L, T, Q> const& I,
		vec<L, T, Q> const& N,
		T eta);

	/// @}
}//namespace glm


// ---------- #include "matrix.hpp" ----------

namespace glm {
namespace detail
{
	template<length_t C, length_t R, typename T, qualifier Q>
	struct outerProduct_trait{};

	template<typename T, qualifier Q>
	struct outerProduct_trait<2, 2, T, Q>
	{
		typedef mat<2, 2, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<2, 3, T, Q>
	{
		typedef mat<3, 2, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<2, 4, T, Q>
	{
		typedef mat<4, 2, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<3, 2, T, Q>
	{
		typedef mat<2, 3, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<3, 3, T, Q>
	{
		typedef mat<3, 3, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<3, 4, T, Q>
	{
		typedef mat<4, 3, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<4, 2, T, Q>
	{
		typedef mat<2, 4, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<4, 3, T, Q>
	{
		typedef mat<3, 4, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<4, 4, T, Q>
	{
		typedef mat<4, 4, T, Q> type;
	};
}//namespace detail

	 /// @addtogroup core_func_matrix
	 /// @{

	 /// Multiply matrix x by matrix y component-wise, i.e.,
	 /// result[i][j] is the scalar product of x[i][j] and y[i][j].
	 ///
	 /// @tparam C Integer between 1 and 4 included that qualify the number a column
	 /// @tparam R Integer between 1 and 4 included that qualify the number a row
	 /// @tparam T Floating-point or signed integer scalar types
	 /// @tparam Q Value from qualifier enum
	 ///
	 /// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/matrixCompMult.xml">GLSL matrixCompMult man page</a>
	 /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL mat<C, R, T, Q> matrixCompMult(mat<C, R, T, Q> const& x, mat<C, R, T, Q> const& y);

	/// Treats the first parameter c as a column vector
	/// and the second parameter r as a row vector
	/// and does a linear algebraic matrix multiply c * r.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam T Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/outerProduct.xml">GLSL outerProduct man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL typename detail::outerProduct_trait<C, R, T, Q>::type outerProduct(vec<C, T, Q> const& c, vec<R, T, Q> const& r);

	/// Returns the transposed matrix of x
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam T Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/transpose.xml">GLSL transpose man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<C, R, T, Q>::transpose_type transpose(mat<C, R, T, Q> const& x);

	/// Return the determinant of a squared matrix.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam T Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/determinant.xml">GLSL determinant man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL T determinant(mat<C, R, T, Q> const& m);

	/// Return the inverse of a squared matrix.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam T Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inverse.xml">GLSL inverse man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL mat<C, R, T, Q> inverse(mat<C, R, T, Q> const& m);

	/// @}
}//namespace glm

namespace glm{
namespace detail
{
	template<length_t C, length_t R, typename T, qualifier Q, bool Aligned>
	struct compute_matrixCompMult
	{
		GLM_FUNC_QUALIFIER static mat<C, R, T, Q> call(mat<C, R, T, Q> const& x, mat<C, R, T, Q> const& y)
		{
			mat<C, R, T, Q> Result;
			for(length_t i = 0; i < Result.length(); ++i)
				Result[i] = x[i] * y[i];
			return Result;
		}
	};

	template<length_t C, length_t R, typename T, qualifier Q, bool Aligned>
	struct compute_transpose{};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<2, 2, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 2, T, Q> call(mat<2, 2, T, Q> const& m)
		{
			mat<2, 2, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<2, 3, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 2, T, Q> call(mat<2, 3, T, Q> const& m)
		{
			mat<3,2, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<2, 4, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 2, T, Q> call(mat<2, 4, T, Q> const& m)
		{
			mat<4, 2, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[3][0] = m[0][3];
			Result[3][1] = m[1][3];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<3, 2, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 3, T, Q> call(mat<3, 2, T, Q> const& m)
		{
			mat<2, 3, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<3, 3, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 3, T, Q> call(mat<3, 3, T, Q> const& m)
		{
			mat<3, 3, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];

			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];

			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<3, 4, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 3, T, Q> call(mat<3, 4, T, Q> const& m)
		{
			mat<4, 3, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			Result[3][0] = m[0][3];
			Result[3][1] = m[1][3];
			Result[3][2] = m[2][3];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<4, 2, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 4, T, Q> call(mat<4, 2, T, Q> const& m)
		{
			mat<2, 4, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[0][3] = m[3][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[1][3] = m[3][1];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<4, 3, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 4, T, Q> call(mat<4, 3, T, Q> const& m)
		{
			mat<3, 4, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[0][3] = m[3][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[1][3] = m[3][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			Result[2][3] = m[3][2];
			return Result;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_transpose<4, 4, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 4, T, Q> call(mat<4, 4, T, Q> const& m)
		{
			mat<4, 4, T, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[0][3] = m[3][0];

			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[1][3] = m[3][1];

			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			Result[2][3] = m[3][2];

			Result[3][0] = m[0][3];
			Result[3][1] = m[1][3];
			Result[3][2] = m[2][3];
			Result[3][3] = m[3][3];
			return Result;
		}
	};

	template<length_t C, length_t R, typename T, qualifier Q, bool Aligned>
	struct compute_determinant{};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_determinant<2, 2, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(mat<2, 2, T, Q> const& m)
		{
			return m[0][0] * m[1][1] - m[1][0] * m[0][1];
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_determinant<3, 3, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(mat<3, 3, T, Q> const& m)
		{
			return
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_determinant<4, 4, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(mat<4, 4, T, Q> const& m)
		{
			T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

			vec<4, T, Q> DetCof(
				+ (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
				- (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
				+ (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
				- (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));

			return
				m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
				m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
		}
	};

	template<length_t C, length_t R, typename T, qualifier Q, bool Aligned>
	struct compute_inverse{};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_inverse<2, 2, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 2, T, Q> call(mat<2, 2, T, Q> const& m)
		{
			T OneOverDeterminant = static_cast<T>(1) / (
				+ m[0][0] * m[1][1]
				- m[1][0] * m[0][1]);

			mat<2, 2, T, Q> Inverse(
				+ m[1][1] * OneOverDeterminant,
				- m[0][1] * OneOverDeterminant,
				- m[1][0] * OneOverDeterminant,
				+ m[0][0] * OneOverDeterminant);

			return Inverse;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_inverse<3, 3, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 3, T, Q> call(mat<3, 3, T, Q> const& m)
		{
			T OneOverDeterminant = static_cast<T>(1) / (
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

			mat<3, 3, T, Q> Inverse;
			Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDeterminant;
			Inverse[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDeterminant;
			Inverse[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDeterminant;
			Inverse[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDeterminant;
			Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDeterminant;
			Inverse[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDeterminant;
			Inverse[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDeterminant;
			Inverse[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDeterminant;
			Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDeterminant;

			return Inverse;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_inverse<4, 4, T, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 4, T, Q> call(mat<4, 4, T, Q> const& m)
		{
			T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			vec<4, T, Q> Fac0(Coef00, Coef00, Coef02, Coef03);
			vec<4, T, Q> Fac1(Coef04, Coef04, Coef06, Coef07);
			vec<4, T, Q> Fac2(Coef08, Coef08, Coef10, Coef11);
			vec<4, T, Q> Fac3(Coef12, Coef12, Coef14, Coef15);
			vec<4, T, Q> Fac4(Coef16, Coef16, Coef18, Coef19);
			vec<4, T, Q> Fac5(Coef20, Coef20, Coef22, Coef23);

			vec<4, T, Q> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			vec<4, T, Q> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			vec<4, T, Q> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			vec<4, T, Q> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			vec<4, T, Q> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			vec<4, T, Q> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			vec<4, T, Q> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			vec<4, T, Q> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			vec<4, T, Q> SignA(+1, -1, +1, -1);
			vec<4, T, Q> SignB(-1, +1, -1, +1);
			mat<4, 4, T, Q> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			vec<4, T, Q> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

			vec<4, T, Q> Dot0(m[0] * Row0);
			T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			T OneOverDeterminant = static_cast<T>(1) / Dot1;

			return Inverse * OneOverDeterminant;
		}
	};
}//namespace detail

	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<C, R, T, Q> matrixCompMult(mat<C, R, T, Q> const& x, mat<C, R, T, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'matrixCompMult' only accept floating-point inputs");
		return detail::compute_matrixCompMult<C, R, T, Q, detail::is_aligned<Q>::value>::call(x, y);
	}

	template<length_t DA, length_t DB, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename detail::outerProduct_trait<DA, DB, T, Q>::type outerProduct(vec<DA, T, Q> const& c, vec<DB, T, Q> const& r)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'outerProduct' only accept floating-point inputs");

		typename detail::outerProduct_trait<DA, DB, T, Q>::type m;
		for(length_t i = 0; i < m.length(); ++i)
			m[i] = c * r[i];
		return m;
	}

	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<C, R, T, Q>::transpose_type transpose(mat<C, R, T, Q> const& m)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'transpose' only accept floating-point inputs");
		return detail::compute_transpose<C, R, T, Q, detail::is_aligned<Q>::value>::call(m);
	}

	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T determinant(mat<C, R, T, Q> const& m)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'determinant' only accept floating-point inputs");
		return detail::compute_determinant<C, R, T, Q, detail::is_aligned<Q>::value>::call(m);
	}

	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<C, R, T, Q> inverse(mat<C, R, T, Q> const& m)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'inverse' only accept floating-point inputs");
		return detail::compute_inverse<C, R, T, Q, detail::is_aligned<Q>::value>::call(m);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_matrix_simd.inl"
#endif




// ---------- #include "vector_relational.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_vector_relational
	/// @{

	/// Returns the component-wise comparison result of x < y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T A floating-point or integer scalar type.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/lessThan.xml">GLSL lessThan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> lessThan(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the component-wise comparison of result x <= y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T A floating-point or integer scalar type.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/lessThanEqual.xml">GLSL lessThanEqual man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> lessThanEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the component-wise comparison of result x > y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T A floating-point or integer scalar type.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/greaterThan.xml">GLSL greaterThan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> greaterThan(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the component-wise comparison of result x >= y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T A floating-point or integer scalar type.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/greaterThanEqual.xml">GLSL greaterThanEqual man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> greaterThanEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the component-wise comparison of result x == y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T A floating-point, integer or bool scalar type.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/equal.xml">GLSL equal man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the component-wise comparison of result x != y.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T A floating-point, integer or bool scalar type.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/notEqual.xml">GLSL notEqual man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns true if any component of x is true.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/any.xml">GLSL any man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool any(vec<L, bool, Q> const& v);

	/// Returns true if all components of x are true.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/all.xml">GLSL all man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool all(vec<L, bool, Q> const& v);

	/// Returns the component-wise logical complement of x.
	/// /!\ Because of language incompatibilities between C++ and GLSL, GLM defines the function not but not_ instead.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/not.xml">GLSL not man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.7 Vector Relational Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> not_(vec<L, bool, Q> const& v);

	/// @}
}//namespace glm

namespace glm
{
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> lessThan(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = x[i] < y[i];
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> lessThanEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = x[i] <= y[i];
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> greaterThan(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = x[i] > y[i];
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> greaterThanEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = x[i] >= y[i];
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = x[i] == y[i];
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = x[i] != y[i];
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool any(vec<L, bool, Q> const& v)
	{
		bool Result = false;
		for(length_t i = 0; i < L; ++i)
			Result = Result || v[i];
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool all(vec<L, bool, Q> const& v)
	{
		bool Result = true;
		for(length_t i = 0; i < L; ++i)
			Result = Result && v[i];
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> not_(vec<L, bool, Q> const& v)
	{
		vec<L, bool, Q> Result(true);
		for(length_t i = 0; i < L; ++i)
			Result[i] = !v[i];
		return Result;
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_vector_relational_simd.inl"
#endif



// ---------- #include "integer.hpp" ----------

namespace glm
{
	/// @addtogroup core_func_integer
	/// @{

	/// Adds 32-bit unsigned integer x and y, returning the sum
	/// modulo pow(2, 32). The value carry is set to 0 if the sum was
	/// less than pow(2, 32), or to 1 otherwise.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/uaddCarry.xml">GLSL uaddCarry man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, uint, Q> uaddCarry(
		vec<L, uint, Q> const& x,
		vec<L, uint, Q> const& y,
		vec<L, uint, Q> & carry);

	/// Subtracts the 32-bit unsigned integer y from x, returning
	/// the difference if non-negative, or pow(2, 32) plus the difference
	/// otherwise. The value borrow is set to 0 if x >= y, or to 1 otherwise.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/usubBorrow.xml">GLSL usubBorrow man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, uint, Q> usubBorrow(
		vec<L, uint, Q> const& x,
		vec<L, uint, Q> const& y,
		vec<L, uint, Q> & borrow);

	/// Multiplies 32-bit integers x and y, producing a 64-bit
	/// result. The 32 least-significant bits are returned in lsb.
	/// The 32 most-significant bits are returned in msb.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/umulExtended.xml">GLSL umulExtended man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL void umulExtended(
		vec<L, uint, Q> const& x,
		vec<L, uint, Q> const& y,
		vec<L, uint, Q> & msb,
		vec<L, uint, Q> & lsb);

	/// Multiplies 32-bit integers x and y, producing a 64-bit
	/// result. The 32 least-significant bits are returned in lsb.
	/// The 32 most-significant bits are returned in msb.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/imulExtended.xml">GLSL imulExtended man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL void imulExtended(
		vec<L, int, Q> const& x,
		vec<L, int, Q> const& y,
		vec<L, int, Q> & msb,
		vec<L, int, Q> & lsb);

	/// Extracts bits [offset, offset + bits - 1] from value,
	/// returning them in the least significant bits of the result.
	/// For unsigned data types, the most significant bits of the
	/// result will be set to zero. For signed data types, the
	/// most significant bits will be set to the value of bit offset + base - 1.
	///
	/// If bits is zero, the result will be zero. The result will be
	/// undefined if offset or bits is negative, or if the sum of
	/// offset and bits is greater than the number of bits used
	/// to store the operand.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Signed or unsigned integer scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/bitfieldExtract.xml">GLSL bitfieldExtract man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> bitfieldExtract(
		vec<L, T, Q> const& Value,
		int Offset,
		int Bits);

	/// Returns the insertion the bits least-significant bits of insert into base.
	///
	/// The result will have bits [offset, offset + bits - 1] taken
	/// from bits [0, bits - 1] of insert, and all other bits taken
	/// directly from the corresponding bits of base. If bits is
	/// zero, the result will simply be base. The result will be
	/// undefined if offset or bits is negative, or if the sum of
	/// offset and bits is greater than the number of bits used to
	/// store the operand.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Signed or unsigned integer scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/bitfieldInsert.xml">GLSL bitfieldInsert man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> bitfieldInsert(
		vec<L, T, Q> const& Base,
		vec<L, T, Q> const& Insert,
		int Offset,
		int Bits);

	/// Returns the reversal of the bits of value.
	/// The bit numbered n of the result will be taken from bit (bits - 1) - n of value,
	/// where bits is the total number of bits used to represent value.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Signed or unsigned integer scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/bitfieldReverse.xml">GLSL bitfieldReverse man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> bitfieldReverse(vec<L, T, Q> const& v);

	/// Returns the number of bits set to 1 in the binary representation of value.
	///
	/// @tparam genType Signed or unsigned integer scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/bitCount.xml">GLSL bitCount man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<typename genType>
	GLM_FUNC_DECL int bitCount(genType v);

	/// Returns the number of bits set to 1 in the binary representation of value.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Signed or unsigned integer scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/bitCount.xml">GLSL bitCount man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, int, Q> bitCount(vec<L, T, Q> const& v);

	/// Returns the bit number of the least significant bit set to
	/// 1 in the binary representation of value.
	/// If value is zero, -1 will be returned.
	///
	/// @tparam genIUType Signed or unsigned integer scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/findLSB.xml">GLSL findLSB man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<typename genIUType>
	GLM_FUNC_DECL int findLSB(genIUType x);

	/// Returns the bit number of the least significant bit set to
	/// 1 in the binary representation of value.
	/// If value is zero, -1 will be returned.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Signed or unsigned integer scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/findLSB.xml">GLSL findLSB man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, int, Q> findLSB(vec<L, T, Q> const& v);

	/// Returns the bit number of the most significant bit in the binary representation of value.
	/// For positive integers, the result will be the bit number of the most significant bit set to 1.
	/// For negative integers, the result will be the bit number of the most significant
	/// bit set to 0. For a value of zero or negative one, -1 will be returned.
	///
	/// @tparam genIUType Signed or unsigned integer scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/findMSB.xml">GLSL findMSB man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<typename genIUType>
	GLM_FUNC_DECL int findMSB(genIUType x);

	/// Returns the bit number of the most significant bit in the binary representation of value.
	/// For positive integers, the result will be the bit number of the most significant bit set to 1.
	/// For negative integers, the result will be the bit number of the most significant
	/// bit set to 0. For a value of zero or negative one, -1 will be returned.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam T Signed or unsigned integer scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/findMSB.xml">GLSL findMSB man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.8 Integer Functions</a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, int, Q> findMSB(vec<L, T, Q> const& v);

	/// @}
}//namespace glm


#if(GLM_ARCH & GLM_ARCH_X86 && GLM_COMPILER & GLM_COMPILER_VC)

	#ifndef _VCRUNTIME_H
#define _VCRUNTIME_H

#ifndef _VCRT_COMPILER_PREPROCESSOR
// Many VCRuntime headers avoid exposing their contents to non-compilers like
// the Windows resource compiler and Qt's meta-object compiler (moc).
#if defined(RC_INVOKED) || defined(Q_MOC_RUN)
#define _VCRT_COMPILER_PREPROCESSOR 0
#else
#define _VCRT_COMPILER_PREPROCESSOR 1
#endif
#endif // _VCRT_COMPILER_PREPROCESSOR

#ifndef _UCRT
    #define _UCRT
#endif

// The _CRTIMP macro is not used in the VCRuntime or the CoreCRT anymore, but
// there is a lot of existing code that declares CRT functions using this macro,
// and if we remove its definition, we break that existing code.  It is thus
// defined here only for compatibility.
#ifndef _CRTIMP
    #define _VCRT_DEFINED_CRTIMP
    #if defined CRTDLL && defined _CRTBLD
        #define _CRTIMP __declspec(dllexport)
    #else
        #ifdef _DLL
            #define _CRTIMP __declspec(dllimport)
        #else
            #define _CRTIMP
        #endif
    #endif
#endif

#include <sal.h>
#include <vadefs.h>

#pragma warning(push)
#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

// All C headers have a common prologue and epilogue, to enclose the header in
// an extern "C" declaration when the header is #included in a C++ translation
// unit and to push/pop the packing.
#if defined __cplusplus

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING)) \
        extern "C" {

    #define _CRT_END_C_HEADER \
        }                     \
        __pragma(pack(pop))

#elif defined __midl

    #define _CRT_BEGIN_C_HEADER                         \
        cpp_quote("__pragma(pack(push, _CRT_PACKING))") \
        cpp_quote("extern \"C\" {")

    #define _CRT_END_C_HEADER            \
        cpp_quote("}")                   \
        cpp_quote("__pragma(pack(pop))")

#else

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING))

    #define _CRT_END_C_HEADER \
        __pragma(pack(pop))

#endif

_CRT_BEGIN_C_HEADER



#ifndef _HAS_EXCEPTIONS // Predefine as 0 to disable exceptions
    #ifdef _KERNEL_MODE
        #define _HAS_EXCEPTIONS 0
    #else
        #define _HAS_EXCEPTIONS 1
    #endif /* _KERNEL_MODE */
#endif /* _HAS_EXCEPTIONS */



#define _CRT_STRINGIZE_(x) #x
#define _CRT_STRINGIZE(x) _CRT_STRINGIZE_(x)

#define _CRT_WIDE_(s) L ## s
#define _CRT_WIDE(s) _CRT_WIDE_(s)

#define _CRT_CONCATENATE_(a, b) a ## b
#define _CRT_CONCATENATE(a, b)  _CRT_CONCATENATE_(a, b)

#define _CRT_UNPARENTHESIZE_(...) __VA_ARGS__
#define _CRT_UNPARENTHESIZE(...)  _CRT_UNPARENTHESIZE_ __VA_ARGS__

#ifndef _VCRTIMP
    #if defined _CRTIMP && !defined _VCRT_DEFINED_CRTIMP
        #define _VCRTIMP _CRTIMP
    #elif defined _VCRT_BUILD && defined CRTDLL && !defined _VCRT_SAT_1
        #define _VCRTIMP __declspec(dllexport)
    #else
        #define _VCRTIMP
    #endif
#endif

#ifndef _MRTIMP
    #if defined MRTDLL && defined _CRTBLD && !defined _M_CEE_PURE
        #define _MRTIMP __declspec(dllexport)
    #else
        #define _MRTIMP
    #endif
#endif

// Definitions of calling conventions used code sometimes compiled as managed
#if defined _M_CEE_PURE || defined MRTDLL
    #define __CLRCALL_OR_CDECL __clrcall
    #define __CLR_OR_THIS_CALL __clrcall
#else
    #define __CLRCALL_OR_CDECL __cdecl
    #define __CLR_OR_THIS_CALL
#endif

#ifdef _M_CEE_PURE
    #define __CLRCALL_PURE_OR_CDECL __clrcall
#else
    #define __CLRCALL_PURE_OR_CDECL __cdecl
#endif

#define __CRTDECL __CLRCALL_PURE_OR_CDECL

// Definitions of common __declspecs
#define _VCRT_NOALIAS __declspec(noalias)
#define _VCRT_RESTRICT __declspec(restrict)

#if !defined _MSC_VER || _MSC_VER >= 1900
    #define _VCRT_ALLOCATOR __declspec(allocator)
#else
    #define _VCRT_ALLOCATOR
#endif

#if defined _M_CEE && defined _M_X64
    #define _VCRT_JIT_INTRINSIC __declspec(jitintrinsic)
#else
    #define _VCRT_JIT_INTRINSIC
#endif

#ifdef __midl
    #define _VCRT_ALIGN(x)
#else
    #define _VCRT_ALIGN(x) __declspec(align(x))
#endif

#ifndef _CONST_RETURN
    #ifdef __cplusplus
        #define _CRT_CONST_CORRECT_OVERLOADS
        #define _CONST_RETURN  const
    #else
      #define _CONST_RETURN
    #endif
#endif

// For backwards compatibility
#define _WConst_return _CONST_RETURN

// Definitions of common types
#ifdef _WIN64
    typedef unsigned __int64 size_t;
    typedef __int64          ptrdiff_t;
    typedef __int64          intptr_t;
#else
    typedef unsigned int     size_t;
    typedef int              ptrdiff_t;
    typedef int              intptr_t;
#endif

#if defined __cplusplus
    typedef bool  __vcrt_bool;
#elif defined __midl
    // MIDL understands neither bool nor _Bool.  Use char as a best-fit
    // replacement (the differences won't matter in practice).
    typedef char __vcrt_bool;
#else
    typedef _Bool __vcrt_bool;
#endif

// Indicate that these common types are defined
#ifndef _SIZE_T_DEFINED
    #define _SIZE_T_DEFINED
#endif

#ifndef _PTRDIFF_T_DEFINED
    #define _PTRDIFF_T_DEFINED
#endif

#ifndef _INTPTR_T_DEFINED
    #define _INTPTR_T_DEFINED
#endif

// Provide a typedef for wchar_t for use under /Zc:wchar_t-
#ifndef _WCHAR_T_DEFINED
    #define _WCHAR_T_DEFINED
    typedef unsigned short wchar_t;
#endif

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

#if defined _M_X64 || defined _M_ARM || defined _M_ARM64
    #define _UNALIGNED __unaligned
#else
    #define _UNALIGNED
#endif

#if defined _M_ARM64EC
    #define __security_check_cookie __security_check_cookie_arm64ec
#endif

#ifdef __cplusplus
    extern "C++"
    {
        template <typename _CountofType, size_t _SizeOfArray>
        char (*__countof_helper(_UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];

        #define __crt_countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
    }
#else
    #define __crt_countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

#if defined(_M_IX86) && defined(_CRT_LEGACY_X86_FLT_EXCEPTIONS) && !defined(_M_CEE_PURE)
    #pragma comment(lib, "legacy_x86_flt_exceptions")
#endif

#if !defined(_HAS_CXX17) && !defined(_HAS_CXX20)
    #if defined(_MSVC_LANG)
        #define _STL_LANG _MSVC_LANG
    #elif defined(__cplusplus) // ^^^ use _MSVC_LANG / use __cplusplus vvv
        #define _STL_LANG __cplusplus
    #else  // ^^^ use __cplusplus / no C++ support vvv
        #define _STL_LANG 0L
    #endif // ^^^ no C++ support ^^^

    #if _STL_LANG > 201703L
        #define _HAS_CXX17 1
        #define _HAS_CXX20 1
    #elif _STL_LANG > 201402L
        #define _HAS_CXX17 1
        #define _HAS_CXX20 0
    #else // _STL_LANG <= 201402L
        #define _HAS_CXX17 0
        #define _HAS_CXX20 0
    #endif // Use the value of _STL_LANG to define _HAS_CXX17 and _HAS_CXX20

    #undef _STL_LANG
#endif // !defined(_HAS_CXX17) && !defined(_HAS_CXX20)

#if !defined(_HAS_CXX17) || !defined(_HAS_CXX20) || _HAS_CXX20 && !_HAS_CXX17
    #error _HAS_CXX17 and _HAS_CXX20 must both be defined, and _HAS_CXX20 must imply _HAS_CXX17
#endif // Verify _HAS_CXX17 and _HAS_CXX20

// [[nodiscard]] attributes on STL functions
#ifndef _HAS_NODISCARD
    #ifndef __has_cpp_attribute
        #define _HAS_NODISCARD 0
    #elif __has_cpp_attribute(nodiscard) >= 201603L // TRANSITION, VSO#939899 (need toolset update)
        #define _HAS_NODISCARD 1
    #else
        #define _HAS_NODISCARD 0
    #endif
#endif // _HAS_NODISCARD

#if _HAS_NODISCARD
    #define _NODISCARD [[nodiscard]]
#else // ^^^ CAN HAZ [[nodiscard]] / NO CAN HAZ [[nodiscard]] vvv
    #define _NODISCARD
#endif // _HAS_NODISCARD

// See note on use of "deprecate" at the top of this file
#define _CRT_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))

#if defined _CRT_SECURE_NO_DEPRECATE && !defined _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_INSECURE_DEPRECATE
    #ifdef _CRT_SECURE_NO_WARNINGS
        #define _CRT_INSECURE_DEPRECATE(_Replacement)
    #else
        #define _CRT_INSECURE_DEPRECATE(_Replacement) _CRT_DEPRECATE_TEXT(    \
            "This function or variable may be unsafe. Consider using "        \
            #_Replacement                                                     \
            " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " \
            "See online help for details.")
    #endif
#endif

#if defined _CRT_SECURE_DEPRECATE_MEMORY && !defined _CRT_SECURE_WARNINGS_MEMORY
    #define _CRT_SECURE_WARNINGS_MEMORY
#endif

#ifndef _CRT_INSECURE_DEPRECATE_MEMORY
    #ifndef _CRT_SECURE_WARNINGS_MEMORY
        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement)
    #else
        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement) \
            _CRT_INSECURE_DEPRECATE(_Replacement)
    #endif
#endif

#if !defined _M_CEE && !defined __midl
    void __cdecl __security_init_cookie(void);

    #if defined(_M_IX86)
        void __fastcall __security_check_cookie(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(void);
    #elif defined(_M_ARM64EC)
        void __cdecl __security_check_cookie_arm64ec(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(_In_ uintptr_t _StackCookie);
    #else
        void __cdecl __security_check_cookie(_In_ uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure(_In_ uintptr_t _StackCookie);
    #endif
#endif

extern uintptr_t __security_cookie;

#ifndef _VCRT_BUILD
    #define __vcrt_malloc_normal(_Size) malloc(_Size)
    #define __vcrt_calloc_normal(_Count, _Size) calloc(_Count, _Size)
    #define __vcrt_free_normal(_Memory) free(_Memory)
#endif

_CRT_END_C_HEADER

#pragma warning(pop) // _VCRUNTIME_DISABLED_WARNINGS

#endif // _VCRUNTIME_H

#if _VCRT_COMPILER_PREPROCESSOR && !defined(__midl)

#pragma warning(push)
#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

#if _VCRT_COMPILER_PREPROCESSOR && !defined(__midl)

#pragma warning(push)
#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

#if defined(__cplusplus)
extern "C" {
#endif

/*
** __MACHINE              : everything
** __MACHINEX86           : x86 only
** __MACHINEX64           : x64 only
** __MACHINEX86_X64       : x86 and x64 only
** __MACHINEARM           : ARM only
** __MACHINEARM64         : ARM64 only
** __MACHINEARM_ARM64     : ARM and ARM64 only
** __MACHINEARM_ARM64_X64 : ARM and 64-bit Arch only
** __MACHINEARM64_X64     : ARM64 and x64 only
** __MACHINECHPEX86ARM64  : CHPE x86 on arm64 only
** __MACHINEWVMPURE       : /clr:pure only
** __MACHINEZ             : nothing
*/

#define __MACHINEX86           __MACHINE
#define __MACHINEX64           __MACHINE
#define __MACHINEX86_X64       __MACHINE
#define __MACHINEARM           __MACHINE
#define __MACHINEARM64         __MACHINE
#define __MACHINEARM_ARM64     __MACHINE
#define __MACHINEARM_ARM64_X64 __MACHINE
#define __MACHINEARM64_X64     __MACHINE
#define __MACHINECHPEX86ARM64  __MACHINE

/* Most intrinsics not available to pure managed code */
#if defined(_M_CEE_PURE)
#define __MACHINE(X)        __MACHINEZ(X)
#define __MACHINEWVMPURE(X) X;
#else
#define __MACHINE(X)        X;
#define __MACHINEWVMPURE(X) __MACHINEZ(X)
#endif

#define __MACHINEZ(X)       /* NOTHING */

#if !defined(_M_IX86) || defined(_CHPE_ONLY_)
#undef __MACHINEX86
#define __MACHINEX86        __MACHINEZ
#endif

#if !defined(_M_X64) || defined(_M_ARM64EC)
#undef __MACHINEX64
#define __MACHINEX64        __MACHINEZ
#endif

#if !(defined(_M_IX86) || defined(_M_X64)) || defined(_CHPE_ONLY_) || defined(_M_ARM64EC)
#undef __MACHINEX86_X64
#define __MACHINEX86_X64    __MACHINEZ
#endif

#if !defined(_M_ARM)
#undef  __MACHINEARM
#define __MACHINEARM        __MACHINEZ
#endif

/* For compatibility with <winnt.h>, some intrinsics are __cdecl except on x64 */
#if defined(_M_X64)
#define __MACHINECALL_CDECL_OR_DEFAULT
#else
#define __MACHINECALL_CDECL_OR_DEFAULT __cdecl
#endif

#if !defined(_M_ARM64) && !defined(_M_HYBRID_X86_ARM64) && !defined(_M_ARM64EC)
#undef  __MACHINEARM64
#define __MACHINEARM64      __MACHINEZ
#endif

#if !(defined(_M_ARM) || defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC))
#undef __MACHINEARM_ARM64
#define __MACHINEARM_ARM64  __MACHINEZ
#endif

#if !(defined(_M_ARM) || defined(_M_X64) || defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC))
#undef __MACHINEARM_ARM64_X64
#define __MACHINEARM_ARM64_X64     __MACHINEZ
#endif

#if !(defined(_M_X64) || defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC))
#undef __MACHINEARM64_X64
#define __MACHINEARM64_X64     __MACHINEZ
#endif

#if !defined(_M_HYBRID_X86_ARM64)
#undef __MACHINECHPEX86ARM64
#define __MACHINECHPEX86ARM64 __MACHINEZ
#endif

/*******************************************************************
* Note: New intrinsics should be added here IF AND ONLY IF they're *
* being used by the C++ Standard Library.                          *
* OTHERWISE, new intrinsics should be added to intrin.h.           *
*******************************************************************/

__MACHINEARM_ARM64(void __dmb(unsigned int _Type))

__MACHINE(unsigned char _BitScanForward(unsigned long * _Index, unsigned long _Mask))
__MACHINEX64(unsigned char _BitScanForward64(unsigned long * _Index, unsigned __int64 _Mask))
__MACHINEARM64(unsigned char _BitScanForward64(unsigned long * _Index, unsigned __int64 _Mask))
__MACHINE(unsigned char _BitScanReverse(unsigned long * _Index, unsigned long _Mask))
__MACHINEX64(unsigned char _BitScanReverse64(unsigned long * _Index, unsigned __int64 _Mask))
__MACHINEARM64(unsigned char _BitScanReverse64(unsigned long * _Index, unsigned __int64 _Mask))
__MACHINE(unsigned char _bittest(long const *, long))
__MACHINEARM_ARM64(unsigned int _CountLeadingZeros(unsigned long))
__MACHINEARM_ARM64(unsigned int _CountLeadingZeros64(unsigned __int64))
__MACHINE(long _InterlockedAnd(long volatile * _Value, long _Mask))
__MACHINE(short _InterlockedAnd16(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedAnd16_acq(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedAnd16_nf(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedAnd16_rel(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64_X64(__int64 _InterlockedAnd64(__int64 volatile * _Value, __int64 _Mask))
__MACHINE(__int64 _interlockedand64(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedAnd64_acq(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedAnd64_nf(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedAnd64_rel(__int64 volatile * _Value, __int64 _Mask))
__MACHINE(char _InterlockedAnd8(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedAnd8_acq(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedAnd8_nf(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedAnd8_rel(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(long _InterlockedAnd_acq(long volatile * _Value, long _Mask))
__MACHINEARM_ARM64(long _InterlockedAnd_nf(long volatile * _Value, long _Mask))
__MACHINEARM_ARM64(long _InterlockedAnd_rel(long volatile * _Value, long _Mask))
__MACHINE(long __MACHINECALL_CDECL_OR_DEFAULT _InterlockedCompareExchange(long volatile * _Destination, long _Exchange, long _Comparand))
__MACHINEWVMPURE(long _InterlockedCompareExchange(long volatile * _Destination, long _Exchange, long _Comparand))
__MACHINE(short _InterlockedCompareExchange16(short volatile * _Destination, short _Exchange, short _Comparand))
__MACHINEARM_ARM64(short _InterlockedCompareExchange16_acq(short volatile * _Destination, short _Exchange, short _Comparand))
__MACHINEARM_ARM64(short _InterlockedCompareExchange16_nf(short volatile * _Destination, short _Exchange, short _Comparand))
__MACHINEARM_ARM64(short _InterlockedCompareExchange16_rel(short volatile * _Destination, short _Exchange, short _Comparand))
__MACHINE(__int64 _InterlockedCompareExchange64(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand))
__MACHINEARM_ARM64(__int64 _InterlockedCompareExchange64_acq(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand))
__MACHINEARM_ARM64(__int64 _InterlockedCompareExchange64_nf(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand))
__MACHINEARM_ARM64(__int64 _InterlockedCompareExchange64_rel(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand))
__MACHINE(char _InterlockedCompareExchange8(char volatile * _Destination, char _Exchange, char _Comparand))
__MACHINEARM_ARM64(char _InterlockedCompareExchange8_acq(char volatile * _Destination, char _Exchange, char _Comparand))
__MACHINEARM_ARM64(char _InterlockedCompareExchange8_nf(char volatile * _Destination, char _Exchange, char _Comparand))
__MACHINEARM_ARM64(char _InterlockedCompareExchange8_rel(char volatile * _Destination, char _Exchange, char _Comparand))
__MACHINEARM_ARM64(long _InterlockedCompareExchange_acq(long volatile * _Destination, long _Exchange, long _Comparand))
__MACHINEARM_ARM64(long _InterlockedCompareExchange_nf(long volatile * _Destination, long _Exchange, long _Comparand))
__MACHINEARM_ARM64(long _InterlockedCompareExchange_rel(long volatile * _Destination, long _Exchange, long _Comparand))
__MACHINEARM64_X64(unsigned char _InterlockedCompareExchange128(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult))
__MACHINEARM64(unsigned char _InterlockedCompareExchange128_acq(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult))
__MACHINEARM64(unsigned char _InterlockedCompareExchange128_nf(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult))
__MACHINEARM64(unsigned char _InterlockedCompareExchange128_rel(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult))
__MACHINE(long __MACHINECALL_CDECL_OR_DEFAULT _InterlockedDecrement(long volatile * _Addend))
__MACHINEWVMPURE(long _InterlockedDecrement(long volatile * _Addend))
__MACHINE(short _InterlockedDecrement16(short volatile * _Addend))
__MACHINEARM_ARM64_X64(__int64 _InterlockedDecrement64(__int64 volatile * _Addend))
__MACHINE(__int64 _interlockeddecrement64(__int64 volatile * _Addend))
__MACHINE(long __MACHINECALL_CDECL_OR_DEFAULT _InterlockedExchange(long volatile * _Target, long _Value))
__MACHINEWVMPURE(long __MACHINECALL_CDECL_OR_DEFAULT _InterlockedExchange(long volatile * _Target, long _Value))
__MACHINE(short _InterlockedExchange16(short volatile * _Target, short _Value))
__MACHINEARM_ARM64(short _InterlockedExchange16_acq(short volatile * _Target, short _Value))
__MACHINEARM_ARM64(short _InterlockedExchange16_nf(short volatile * _Target, short _Value))
__MACHINEARM_ARM64(short _InterlockedExchange16_rel(short volatile * _Target, short _Value))
__MACHINEARM_ARM64_X64(__int64 _InterlockedExchange64(__int64 volatile * _Target, __int64 _Value))
__MACHINE(__int64 _interlockedexchange64(__int64 volatile * _Target, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedExchange64_acq(__int64 volatile * _Target, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedExchange64_nf(__int64 volatile * _Target, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedExchange64_rel(__int64 volatile * _Target, __int64 _Value))
__MACHINE(char _InterlockedExchange8(char volatile * _Target, char _Value))
__MACHINEARM_ARM64(char _InterlockedExchange8_acq(char volatile * _Target, char _Value))
__MACHINEARM_ARM64(char _InterlockedExchange8_nf(char volatile * _Target, char _Value))
__MACHINEARM_ARM64(char _InterlockedExchange8_rel(char volatile * _Target, char _Value))
__MACHINE(long __MACHINECALL_CDECL_OR_DEFAULT _InterlockedExchangeAdd(long volatile * _Addend, long _Value))
__MACHINE(short _InterlockedExchangeAdd16(short volatile * _Addend, short _Value))
__MACHINEARM_ARM64(short _InterlockedExchangeAdd16_acq(short volatile * _Addend, short _Value))
__MACHINEARM_ARM64(short _InterlockedExchangeAdd16_nf(short volatile * _Addend, short _Value))
__MACHINEARM_ARM64(short _InterlockedExchangeAdd16_rel(short volatile * _Addend, short _Value))
__MACHINEARM_ARM64_X64(__int64 _InterlockedExchangeAdd64(__int64 volatile * _Addend, __int64 _Value))
__MACHINE(__int64 _interlockedexchangeadd64(__int64 volatile * _Addend, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedExchangeAdd64_acq(__int64 volatile * _Addend, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedExchangeAdd64_nf(__int64 volatile * _Addend, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedExchangeAdd64_rel(__int64 volatile * _Addend, __int64 _Value))
__MACHINE(char _InterlockedExchangeAdd8(char volatile * _Addend, char _Value))
__MACHINEARM_ARM64(char _InterlockedExchangeAdd8_acq(char volatile * _Addend, char _Value))
__MACHINEARM_ARM64(char _InterlockedExchangeAdd8_nf(char volatile * _Addend, char _Value))
__MACHINEARM_ARM64(char _InterlockedExchangeAdd8_rel(char volatile * _Addend, char _Value))
__MACHINEARM_ARM64(long _InterlockedExchangeAdd_acq(long volatile * _Addend, long _Value))
__MACHINEARM_ARM64(long _InterlockedExchangeAdd_nf(long volatile * _Addend, long _Value))
__MACHINEARM_ARM64(long _InterlockedExchangeAdd_rel(long volatile * _Addend, long _Value))
__MACHINEARM_ARM64(long _InterlockedExchange_acq(long volatile * _Target, long _Value))
__MACHINEARM_ARM64(long _InterlockedExchange_nf(long volatile * _Target, long _Value))
__MACHINEARM_ARM64(long _InterlockedExchange_rel(long volatile * _Target, long _Value))
__MACHINE(long __MACHINECALL_CDECL_OR_DEFAULT _InterlockedIncrement(long volatile * _Addend))
__MACHINEWVMPURE(long _InterlockedIncrement(long volatile * _Addend))
__MACHINE(short _InterlockedIncrement16(short volatile * _Addend))
__MACHINEARM_ARM64_X64(__int64 _InterlockedIncrement64(__int64 volatile * _Addend))
__MACHINE(__int64 _interlockedincrement64(__int64 volatile * _Addend))
__MACHINEARM_ARM64(long _InterlockedIncrement_nf(long volatile * _Addend))
__MACHINE(long _InterlockedOr(long volatile * _Value, long _Mask))
__MACHINE(short _InterlockedOr16(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedOr16_acq(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedOr16_nf(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedOr16_rel(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64_X64(__int64 _InterlockedOr64(__int64 volatile * _Value, __int64 _Mask))
__MACHINE(__int64 _interlockedor64(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedOr64_acq(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedOr64_nf(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedOr64_rel(__int64 volatile * _Value, __int64 _Mask))
__MACHINE(char _InterlockedOr8(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedOr8_acq(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedOr8_nf(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedOr8_rel(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(long _InterlockedOr_acq(long volatile * _Value, long _Mask))
__MACHINEARM_ARM64(long _InterlockedOr_nf(long volatile * _Value, long _Mask))
__MACHINEARM_ARM64(long _InterlockedOr_rel(long volatile * _Value, long _Mask))
__MACHINE(long _InterlockedXor(long volatile * _Value, long _Mask))
__MACHINE(short _InterlockedXor16(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedXor16_acq(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedXor16_nf(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64(short _InterlockedXor16_rel(short volatile * _Value, short _Mask))
__MACHINEARM_ARM64_X64(__int64 _InterlockedXor64(__int64 volatile * _Value, __int64 _Mask))
__MACHINE(__int64 _interlockedxor64(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedXor64_acq(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedXor64_nf(__int64 volatile * _Value, __int64 _Mask))
__MACHINEARM_ARM64(__int64 _InterlockedXor64_rel(__int64 volatile * _Value, __int64 _Mask))
__MACHINE(char _InterlockedXor8(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedXor8_acq(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedXor8_nf(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(char _InterlockedXor8_rel(char volatile * _Value, char _Mask))
__MACHINEARM_ARM64(long _InterlockedXor_acq(long volatile * _Value, long _Mask))
__MACHINEARM_ARM64(long _InterlockedXor_nf(long volatile * _Value, long _Mask))
__MACHINEARM_ARM64(long _InterlockedXor_rel(long volatile * _Value, long _Mask))
__MACHINE(void _ReadWriteBarrier(void))
__MACHINE(__int16 __iso_volatile_load16(const volatile __int16 *))
__MACHINE(__int32 __iso_volatile_load32(const volatile __int32 *))
__MACHINE(__int64 __iso_volatile_load64(const volatile __int64 *))
__MACHINE(__int8 __iso_volatile_load8(const volatile __int8 *))
__MACHINE(void __iso_volatile_store16(volatile __int16 *, __int16))
__MACHINE(void __iso_volatile_store32(volatile __int32 *, __int32))
__MACHINE(void __iso_volatile_store64(volatile __int64 *, __int64))
__MACHINE(void __iso_volatile_store8(volatile __int8 *, __int8))
__MACHINEARM(__int64 __ldrexd(const volatile __int64 *))
__MACHINEARM_ARM64(void __yield(void))
__MACHINE(unsigned char _interlockedbittestandset(long volatile *, long))
__MACHINEARM_ARM64(unsigned char _interlockedbittestandset_acq(long volatile *, long))
__MACHINEARM_ARM64(unsigned char _interlockedbittestandset_nf(long volatile *, long))
__MACHINEARM_ARM64(unsigned char _interlockedbittestandset_rel(long volatile *, long))
__MACHINEX86_X64(void _mm_pause(void))
__MACHINEX86_X64(unsigned int __lzcnt(unsigned int))
__MACHINEX86_X64(unsigned short __lzcnt16(unsigned short))
__MACHINEX64(unsigned __int64 __lzcnt64(unsigned __int64))
__MACHINEX86_X64(unsigned int __popcnt(unsigned int))
__MACHINEX86_X64(unsigned short __popcnt16(unsigned short))
__MACHINEX64(unsigned __int64 __popcnt64(unsigned __int64))
__MACHINEX64(unsigned __int64 __shiftright128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _Shift))
#ifndef __clang__
__MACHINEX86_X64(unsigned int _tzcnt_u32(unsigned int))
__MACHINEX64(unsigned __int64 _tzcnt_u64(unsigned __int64))
#endif // __clang__
__MACHINEX64(unsigned __int64 _umul128(unsigned __int64 _Multiplier, unsigned __int64 _Multiplicand, unsigned __int64 * _HighProduct))
__MACHINE(double __ceil(double))
__MACHINE(float __ceilf(float))
__MACHINE(double __floor(double))
__MACHINE(float __floorf(float))
__MACHINE(double __round(double))
__MACHINE(float __roundf(float))
__MACHINE(double __trunc(double))
__MACHINE(float __truncf(float))
__MACHINE(double __copysign(double, double))
__MACHINE(float __copysignf(float, float))
__MACHINE(unsigned __signbitvalue(double))
__MACHINE(unsigned __signbitvaluef(float))
__MACHINEX86_X64(int _cvt_ftoi_sat (float a))
__MACHINEX86_X64(unsigned _cvt_ftoui_sat (float a))
__MACHINEX86_X64(long long _cvt_ftoll_sat (float a))
__MACHINEX86_X64(unsigned long long _cvt_ftoull_sat (float a))
__MACHINEX86_X64(int _cvt_ftoi_sent (float a))
__MACHINEX86_X64(unsigned _cvt_ftoui_sent (float a))
__MACHINEX86_X64(long long _cvt_ftoll_sent (float a))
__MACHINEX86_X64(unsigned long long _cvt_ftoull_sent (float a))
__MACHINEX86_X64(int _cvt_dtoi_sat (double a))
__MACHINEX86_X64(unsigned _cvt_dtoui_sat (double a))
__MACHINEX86_X64(long long _cvt_dtoll_sat (double a))
__MACHINEX86_X64(unsigned long long _cvt_dtoull_sat (double a))
__MACHINEX86_X64(int _cvt_dtoi_sent (double a))
__MACHINEX86_X64(unsigned _cvt_dtoui_sent (double a))
__MACHINEX86_X64(long long _cvt_dtoll_sent (double a))
__MACHINEX86_X64(unsigned long long _cvt_dtoull_sent (double a))
#if defined(__cplusplus)
#if !defined(__clang__) && !defined(__EDG__) && !defined(__CUDACC__)
__MACHINE(constexpr void * __cdecl __builtin_assume_aligned(const void *, size_t, ...) noexcept)
#else
__MACHINE(void * __cdecl __builtin_assume_aligned(const void *, size_t, ...) noexcept)
#endif // !defined(__clang__) && !defined(__EDG__) && !defined(__CUDACC__)
#endif // defined(__cplusplus)

/*******************************************************************
* Note: New intrinsics should be added here IF AND ONLY IF they're *
* being used by the C++ Standard Library.                          *
* OTHERWISE, new intrinsics should be added to intrin.h.           *
*******************************************************************/

#if defined(__cplusplus)
}
#endif
#pragma warning(pop) // _VCRUNTIME_DISABLED_WARNINGS
#endif /* _VCRT_COMPILER_PREPROCESSOR && !defined(__midl) */

#ifdef _M_CEE
    // The reason why simple setjmp won't work here is that there may
    // be case when CLR stubs are on the stack e.g. function call just
    // after jitting, and not unwinding CLR will result in bad state of
    // CLR which then can AV or do something very bad.
    #include <setjmpex.h>
#endif

#pragma warning(push)
#pragma warning(disable: _VCRUNTIME_DISABLED_WARNINGS)

_CRT_BEGIN_C_HEADER



// Definitions specific to particular setjmp implementations.
#if defined _M_IX86

    #define _JBLEN  16
    #define _JBTYPE int

    typedef struct __JUMP_BUFFER
    {
        unsigned long Ebp;
        unsigned long Ebx;
        unsigned long Edi;
        unsigned long Esi;
        unsigned long Esp;
        unsigned long Eip;
        unsigned long Registration;
        unsigned long TryLevel;
        unsigned long Cookie;
        unsigned long UnwindFunc;
        unsigned long UnwindData[6];
    } _JUMP_BUFFER;

#elif defined _M_X64

    typedef struct _VCRT_ALIGN(16) _SETJMP_FLOAT128
    {
        unsigned __int64 Part[2];
    } SETJMP_FLOAT128;

    #define _JBLEN  16
    typedef SETJMP_FLOAT128 _JBTYPE;

    typedef struct _JUMP_BUFFER
    {
        unsigned __int64 Frame;
        unsigned __int64 Rbx;
        unsigned __int64 Rsp;
        unsigned __int64 Rbp;
        unsigned __int64 Rsi;
        unsigned __int64 Rdi;
        unsigned __int64 R12;
        unsigned __int64 R13;
        unsigned __int64 R14;
        unsigned __int64 R15;
        unsigned __int64 Rip;
        unsigned long MxCsr;
        unsigned short FpCsr;
        unsigned short Spare;

        SETJMP_FLOAT128 Xmm6;
        SETJMP_FLOAT128 Xmm7;
        SETJMP_FLOAT128 Xmm8;
        SETJMP_FLOAT128 Xmm9;
        SETJMP_FLOAT128 Xmm10;
        SETJMP_FLOAT128 Xmm11;
        SETJMP_FLOAT128 Xmm12;
        SETJMP_FLOAT128 Xmm13;
        SETJMP_FLOAT128 Xmm14;
        SETJMP_FLOAT128 Xmm15;
    } _JUMP_BUFFER;

#elif defined _M_ARM

    #define _JBLEN  28
    #define _JBTYPE int

    typedef struct _JUMP_BUFFER
    {
        unsigned long Frame;

        unsigned long R4;
        unsigned long R5;
        unsigned long R6;
        unsigned long R7;
        unsigned long R8;
        unsigned long R9;
        unsigned long R10;
        unsigned long R11;

        unsigned long Sp;
        unsigned long Pc;
        unsigned long Fpscr;
        unsigned long long D[8]; // D8-D15 VFP/NEON regs
    } _JUMP_BUFFER;

#elif defined _M_ARM64

    #define _JBLEN  24
    #define _JBTYPE unsigned __int64

    typedef struct _JUMP_BUFFER {
        unsigned __int64 Frame;
        unsigned __int64 Reserved;
        unsigned __int64 X19;   // x19 -- x28: callee saved registers
        unsigned __int64 X20;
        unsigned __int64 X21;
        unsigned __int64 X22;
        unsigned __int64 X23;
        unsigned __int64 X24;
        unsigned __int64 X25;
        unsigned __int64 X26;
        unsigned __int64 X27;
        unsigned __int64 X28;
        unsigned __int64 Fp;    // x29 frame pointer
        unsigned __int64 Lr;    // x30 link register
        unsigned __int64 Sp;    // x31 stack pointer
        unsigned __int32 Fpcr;  // fp control register
        unsigned __int32 Fpsr;  // fp status register

        double D[8]; // D8-D15 FP regs
    } _JUMP_BUFFER;



#endif



// Define the buffer type for holding the state information
#ifndef _JMP_BUF_DEFINED
    #define _JMP_BUF_DEFINED
    typedef _JBTYPE jmp_buf[_JBLEN];
#endif



#ifndef _INC_SETJMPEX
    #define setjmp _setjmp
#endif



// Function prototypes
int __cdecl setjmp(
    _Out_ jmp_buf _Buf
    );

#ifdef __cplusplus
    __declspec(noreturn) void __cdecl longjmp(
        _In_reads_(_JBLEN) jmp_buf _Buf,
        _In_ int     _Value
        ) noexcept(false);
#else
    __declspec(noreturn) void __cdecl longjmp(
        _In_reads_(_JBLEN) jmp_buf _Buf,
        _In_ int     _Value
        );
#endif


_CRT_END_C_HEADER

#pragma warning(pop) // _VCRUNTIME_DISABLED_WARNINGS

#if defined (_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC)
#include <stdint.h> // uint8_t
#endif

#ifndef _M_CEE_PURE

    #if (defined (_M_IX86) || defined (_M_X64)) && !defined(_CHPE_ONLY_) && (!defined(_M_ARM64EC) || !defined(_DISABLE_SOFTINTRIN_))
        #include <immintrin.h>
        #include <ammintrin.h>
    #endif

    #if defined (_M_IX86) && !defined(_CHPE_ONLY_)
        #include <mm3dnow.h>
    #endif

    #if defined (_M_ARM)
        #include <armintr.h>
        #include <arm_neon.h>
    #endif

    #if defined (_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC)
        #include <arm64intr.h>
        #include <arm64_neon.h>
    #endif
#endif

#if defined (__cplusplus)
extern "C" {
#endif  /* defined (__cplusplus) */

__MACHINEARM(int _AddSatInt(int, int))
__MACHINE(void * _AddressOfReturnAddress(void))
__MACHINEARM_ARM64(double _CopyDoubleFromInt64(__int64))
__MACHINEARM_ARM64(float _CopyFloatFromInt32(__int32))
__MACHINEARM_ARM64(__int32 _CopyInt32FromFloat(float))
__MACHINEARM_ARM64(__int64 _CopyInt64FromDouble(double))
__MACHINEARM_ARM64(unsigned int _CountLeadingOnes(unsigned long))
__MACHINEARM_ARM64(unsigned int _CountLeadingOnes64(unsigned __int64))
__MACHINEARM_ARM64(unsigned int _CountLeadingSigns(long))
__MACHINEARM_ARM64(unsigned int _CountLeadingSigns64(__int64))
__MACHINEARM(unsigned int _CountOneBits(unsigned long))
__MACHINEARM(unsigned int _CountOneBits64(unsigned __int64))
__MACHINEARM(int _DAddSatInt(int, int))
__MACHINEARM(int _DSubSatInt(int, int))
__MACHINECHPEX86ARM64(void _HybridGenerateThunks(void *, unsigned))
__MACHINEARM_ARM64(long _InterlockedAdd(long volatile * _Addend, long _Value))
__MACHINE(long _interlockedadd(long volatile * _Addend, long _Value))
__MACHINEARM_ARM64(__int64 _InterlockedAdd64(__int64 volatile * _Addend, __int64 _Value))
__MACHINE(__int64 _interlockedadd64(__int64 volatile * _Addend, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedAdd64_acq(__int64 volatile * _Addend, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedAdd64_nf(__int64 volatile * _Addend, __int64 _Value))
__MACHINEARM_ARM64(__int64 _InterlockedAdd64_rel(__int64 volatile * _Addend, __int64 _Value))
__MACHINEX86(long _InterlockedAddLargeStatistic(__int64 volatile * _Addend, long _Value))
__MACHINEARM_ARM64(long _InterlockedAdd_acq(long volatile * _Addend, long _Value))
__MACHINEARM_ARM64(long _InterlockedAdd_nf(long volatile * _Addend, long _Value))
__MACHINEARM_ARM64(long _InterlockedAdd_rel(long volatile * _Addend, long _Value))
__MACHINEX64(short _InterlockedAnd16_np(short volatile * _Value, short _Mask))
__MACHINEX64(__int64 _InterlockedAnd64_np(__int64 volatile * _Value, __int64 _Mask))
__MACHINEX64(char _InterlockedAnd8_np(char volatile * _Value, char _Mask))
__MACHINEX64(long _InterlockedAnd_np(long volatile * _Value, long _Mask))
__MACHINEX64(unsigned char _InterlockedCompareExchange128_np(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult))
__MACHINEX64(short _InterlockedCompareExchange16_np(short volatile * _Destination, short _Exchange, short _Comparand))
__MACHINEX64(__int64 _InterlockedCompareExchange64_np(__int64 volatile * _Destination, __int64 _Exchange, __int64 _Comparand))
__MACHINE(void * _InterlockedCompareExchangePointer(void * volatile * _Destination, void * _Exchange, void * _Comparand))
__MACHINEARM_ARM64(void * _InterlockedCompareExchangePointer_acq(void * volatile * _Destination, void * _Exchange, void * _Comparand))
__MACHINEARM_ARM64(void * _InterlockedCompareExchangePointer_nf(void * volatile * _Destination, void * _Exchange, void * _Comparand))
__MACHINEX64(void * _InterlockedCompareExchangePointer_np(void * volatile * _Destination, void * _Exchange, void * _Comparand))
__MACHINEARM_ARM64(void * _InterlockedCompareExchangePointer_rel(void * volatile * _Destination, void * _Exchange, void * _Comparand))
__MACHINEX64(long _InterlockedCompareExchange_np(long volatile * _Destination, long _Exchange, long _Comparand))
__MACHINEARM_ARM64(short _InterlockedDecrement16_acq(short volatile * _Addend))
__MACHINEARM_ARM64(short _InterlockedDecrement16_nf(short volatile * _Addend))
__MACHINEARM_ARM64(short _InterlockedDecrement16_rel(short volatile * _Addend))
__MACHINEARM_ARM64(__int64 _InterlockedDecrement64_acq(__int64 volatile * _Addend))
__MACHINEARM_ARM64(__int64 _InterlockedDecrement64_nf(__int64 volatile * _Addend))
__MACHINEARM_ARM64(__int64 _InterlockedDecrement64_rel(__int64 volatile * _Addend))
__MACHINEARM_ARM64(long _InterlockedDecrement_acq(long volatile * _Addend))
__MACHINEARM_ARM64(long _InterlockedDecrement_nf(long volatile * _Addend))
__MACHINEARM_ARM64(long _InterlockedDecrement_rel(long volatile * _Addend))
__MACHINE(void * _InterlockedExchangePointer(void * volatile * _Target, void * _Value))
__MACHINEARM_ARM64(void * _InterlockedExchangePointer_acq(void * volatile * _Target, void * _Value))
__MACHINEARM_ARM64(void * _InterlockedExchangePointer_nf(void * volatile * _Target, void * _Value))
__MACHINEARM_ARM64(void * _InterlockedExchangePointer_rel(void * volatile * _Target, void * _Value))
__MACHINEARM_ARM64(short _InterlockedIncrement16_acq(short volatile * _Addend))
__MACHINEARM_ARM64(short _InterlockedIncrement16_nf(short volatile * _Addend))
__MACHINEARM_ARM64(short _InterlockedIncrement16_rel(short volatile * _Addend))
__MACHINEARM_ARM64(__int64 _InterlockedIncrement64_acq(__int64 volatile * _Addend))
__MACHINEARM_ARM64(__int64 _InterlockedIncrement64_nf(__int64 volatile * _Addend))
__MACHINEARM_ARM64(__int64 _InterlockedIncrement64_rel(__int64 volatile * _Addend))
__MACHINEARM_ARM64(long _InterlockedIncrement_acq(long volatile * _Addend))
__MACHINEARM_ARM64(long _InterlockedIncrement_rel(long volatile * _Addend))
__MACHINEX64(short _InterlockedOr16_np(short volatile * _Value, short _Mask))
__MACHINEX64(__int64 _InterlockedOr64_np(__int64 volatile * _Value, __int64 _Mask))
__MACHINEX64(char _InterlockedOr8_np(char volatile * _Value, char _Mask))
__MACHINEX64(long _InterlockedOr_np(long volatile * _Value, long _Mask))
__MACHINEX64(short _InterlockedXor16_np(short volatile * _Value, short _Mask))
__MACHINEX64(__int64 _InterlockedXor64_np(__int64 volatile * _Value, __int64 _Mask))
__MACHINEX64(char _InterlockedXor8_np(char volatile * _Value, char _Mask))
__MACHINEX64(long _InterlockedXor_np(long volatile * _Value, long _Mask))
__MACHINEARM(unsigned int _MoveFromCoprocessor(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))
__MACHINEARM(unsigned int _MoveFromCoprocessor2(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))
__MACHINEARM(unsigned __int64 _MoveFromCoprocessor64(unsigned int, unsigned int, unsigned int))
__MACHINEARM(void _MoveToCoprocessor(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))
__MACHINEARM(void _MoveToCoprocessor2(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))
__MACHINEARM(void _MoveToCoprocessor64(unsigned __int64, unsigned int, unsigned int, unsigned int))
__MACHINEARM(long _MulHigh(long, long))
__MACHINEARM(unsigned long _MulUnsignedHigh(unsigned long, unsigned long))
__MACHINE(void _ReadBarrier(void))
__MACHINEARM(int _ReadStatusReg(int))
__MACHINEARM64(__int64 _ReadStatusReg(int))
__MACHINEARM64(unsigned __int64 __getReg(int))
__MACHINEARM64(unsigned __int64 __getCallerReg(int))
__MACHINEARM64(double __getRegFp(int))
__MACHINEARM64(double __getCallerRegFp(int))
__MACHINE(void * _ReturnAddress(void))
__MACHINEARM(int _SubSatInt(int, int))
__MACHINE(void _WriteBarrier(void))
__MACHINEARM(void _WriteStatusReg(int, int, int))
__MACHINEARM64(void _WriteStatusReg(int, __int64))
__MACHINEARM64(void __setReg(int, unsigned __int64))
__MACHINEARM64(void __setCallerReg(int, unsigned __int64))
__MACHINEARM64(void __setRegFp(int, double))
__MACHINEARM64(void __setCallerRegFp(int, double))
__MACHINEX86(void __addfsbyte(unsigned long, unsigned char))
__MACHINEX86(void __addfsdword(unsigned long, unsigned long))
__MACHINEX86(void __addfsword(unsigned long, unsigned short))
__MACHINEX64(void __addgsbyte(unsigned long, unsigned char))
__MACHINEX64(void __addgsdword(unsigned long, unsigned long))
__MACHINEX64(void __addgsqword(unsigned long, unsigned __int64))
__MACHINEX64(void __addgsword(unsigned long, unsigned short))
__MACHINEARM64(void __addx18byte(unsigned long, unsigned char))
__MACHINEARM64(void __addx18dword(unsigned long, unsigned long))
__MACHINEARM64(void __addx18qword(unsigned long, unsigned __int64))
__MACHINEARM64(void __addx18word(unsigned long, unsigned short))
__MACHINEX86_X64(void __clts(void))
__MACHINE(void __code_seg(const char *))
__MACHINEX86_X64(void __cpuid(int[4], int))
__MACHINEX86_X64(void __cpuidex(int[4], int, int))
__MACHINE(void __cdecl __debugbreak(void))
__MACHINEARM_ARM64(void __emit(unsigned __int32))
__MACHINEX86_X64(__int64 __emul(int, int))
__MACHINEX86_X64(unsigned __int64 __emulu(unsigned int, unsigned int))
__MACHINE(__declspec(noreturn) void __fastfail(unsigned int))
__MACHINEX64(void __faststorefence(void))
__MACHINEX86_X64(unsigned int __getcallerseflags(void))
__MACHINEX86_X64(void __halt(void))
__MACHINEARM_ARM64(unsigned int __hvc(unsigned int, ...))
__MACHINEARM64(void __break(int))
__MACHINEX86_X64(unsigned char __inbyte(unsigned short))
__MACHINEX86_X64(void __inbytestring(unsigned short, unsigned char *, unsigned long))
__MACHINEX86(void __incfsbyte(unsigned long))
__MACHINEX86(void __incfsdword(unsigned long))
__MACHINEX86(void __incfsword(unsigned long))
__MACHINEX64(void __incgsbyte(unsigned long))
__MACHINEX64(void __incgsdword(unsigned long))
__MACHINEX64(void __incgsqword(unsigned long))
__MACHINEX64(void __incgsword(unsigned long))
__MACHINEARM64(void __incx18byte(unsigned long))
__MACHINEARM64(void __incx18dword(unsigned long))
__MACHINEARM64(void __incx18qword(unsigned long))
__MACHINEARM64(void __incx18word(unsigned long))
__MACHINEX86_X64(unsigned long __indword(unsigned short))
__MACHINEX86_X64(void __indwordstring(unsigned short, unsigned long *, unsigned long))
__MACHINEX86_X64(void __int2c(void))
__MACHINEX86_X64(void __invlpg(void *))
__MACHINEX86_X64(unsigned short __inword(unsigned short))
__MACHINEX86_X64(void __inwordstring(unsigned short, unsigned short *, unsigned long))
__MACHINEX86_X64(void __lidt(void *))
__MACHINEX86_X64(unsigned __int64 __ll_lshift(unsigned __int64, int))
__MACHINEX86_X64(__int64 __ll_rshift(__int64, int))
__MACHINEX86_X64(void __movsb(unsigned char *, unsigned char const *, size_t))
__MACHINEX86_X64(void __movsd(unsigned long *, unsigned long const *, size_t))
__MACHINEX64(void __movsq(unsigned long long *, unsigned long long const *, size_t))
__MACHINEX86_X64(void __movsw(unsigned short *, unsigned short const *, size_t))
__MACHINEARM64_X64(__int64 __mulh(__int64, __int64))
__MACHINE(void __nop(void))
__MACHINEX86_X64(void __nvreg_restore_fence(void))
__MACHINEX86_X64(void __nvreg_save_fence(void))
__MACHINEX86_X64(void __outbyte(unsigned short, unsigned char))
__MACHINEX86_X64(void __outbytestring(unsigned short, unsigned char *, unsigned long))
__MACHINEX86_X64(void __outdword(unsigned short, unsigned long))
__MACHINEX86_X64(void __outdwordstring(unsigned short, unsigned long *, unsigned long))
__MACHINEX86_X64(void __outword(unsigned short, unsigned short))
__MACHINEX86_X64(void __outwordstring(unsigned short, unsigned short *, unsigned long))
__MACHINEARM_ARM64(void __cdecl __prefetch(const void *))
__MACHINEARM64(void __cdecl __prefetch2(const void *, uint8_t prfop))
__MACHINEARM(void __cdecl __prefetchw(const void *))
__MACHINEARM(unsigned __int64 __rdpmccntr64(void))
__MACHINEX86_X64(unsigned __int64 __rdtsc(void))
__MACHINEX86_X64(unsigned __int64 __rdtscp(unsigned int *))
__MACHINEX64(unsigned __int64 __readcr0(void))
__MACHINEX86(unsigned long __readcr0(void))
__MACHINEX64(unsigned __int64 __readcr2(void))
__MACHINEX86(unsigned long __readcr2(void))
__MACHINEX64(unsigned __int64 __readcr3(void))
__MACHINEX86(unsigned long __readcr3(void))
__MACHINEX64(unsigned __int64 __readcr4(void))
__MACHINEX86(unsigned long __readcr4(void))
__MACHINEX64(unsigned __int64 __readcr8(void))
__MACHINEX86(unsigned long __readcr8(void))
__MACHINEX64(unsigned __int64 __readdr(unsigned int))
__MACHINEX86(unsigned int __readdr(unsigned int))
__MACHINEX64(unsigned __int64 __readeflags(void))
__MACHINEX86(unsigned int __readeflags(void))
__MACHINEX86(unsigned char __readfsbyte(unsigned long))
__MACHINEX86(unsigned long __readfsdword(unsigned long))
__MACHINEX86(unsigned __int64 __readfsqword(unsigned long))
__MACHINEX86(unsigned short __readfsword(unsigned long))
__MACHINEX64(unsigned char __readgsbyte(unsigned long))
__MACHINEX64(unsigned long __readgsdword(unsigned long))
__MACHINEX64(unsigned __int64 __readgsqword(unsigned long))
__MACHINEX64(unsigned short __readgsword(unsigned long))
__MACHINEX86_X64(unsigned __int64 __readmsr(unsigned long))
__MACHINEX86_X64(unsigned __int64 __readpmc(unsigned long))
__MACHINEARM64(unsigned char __readx18byte(unsigned long))
__MACHINEARM64(unsigned long __readx18dword(unsigned long))
__MACHINEARM64(unsigned __int64 __readx18qword(unsigned long))
__MACHINEARM64(unsigned short __readx18word(unsigned long))
__MACHINEX86_X64(unsigned long __segmentlimit(unsigned long))
__MACHINEARM_ARM64(void __sev(void))
__MACHINEX64(unsigned __int64 __shiftleft128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _Shift))
__MACHINEX86_X64(void __sidt(void *))
__MACHINEARM_ARM64(void __static_assert(int, const char *))
__MACHINEX86_X64(void __stosb(unsigned char *, unsigned char, size_t))
__MACHINEX86_X64(void __stosd(unsigned long *, unsigned long, size_t))
__MACHINEX64(void __stosq(unsigned __int64 *, unsigned __int64, size_t))
__MACHINEX86_X64(void __stosw(unsigned short *, unsigned short, size_t))
__MACHINEX86_X64(void __svm_clgi(void))
__MACHINEX86_X64(void __svm_invlpga(void *, int))
__MACHINEX86_X64(void __svm_skinit(int))
__MACHINEX86_X64(void __svm_stgi(void))
__MACHINEX86_X64(void __svm_vmload(size_t))
__MACHINEX86_X64(void __svm_vmrun(size_t))
__MACHINEX86_X64(void __svm_vmsave(size_t))
__MACHINEARM(unsigned int __swi(unsigned int, ...))
__MACHINEARM_ARM64(unsigned int __svc(unsigned int, ...))
__MACHINEARM64(unsigned int __hlt(unsigned int, ...))
__MACHINEARM64(unsigned int __sys(int, __int64))
__MACHINEARM(int __trap(int, ...))
__MACHINEX86_X64(void __ud2(void))
__MACHINEX86_X64(unsigned __int64 __ull_rshift(unsigned __int64, int))
__MACHINEARM64_X64(unsigned __int64 __umulh(unsigned __int64, unsigned __int64))
__MACHINEX86_X64(void __vmx_off(void))
__MACHINEX64(unsigned char __vmx_on(unsigned __int64 *))
__MACHINEX64(unsigned char __vmx_vmclear(unsigned __int64 *))
__MACHINEX64(unsigned char __vmx_vmlaunch(void))
__MACHINEX64(unsigned char __vmx_vmptrld(unsigned __int64 *))
__MACHINEX86_X64(void __vmx_vmptrst(unsigned __int64 *))
__MACHINEX64(unsigned char __vmx_vmread(size_t, size_t *))
__MACHINEX64(unsigned char __vmx_vmresume(void))
__MACHINEX64(unsigned char __vmx_vmwrite(size_t, size_t))
__MACHINEX86_X64(void __wbinvd(void))
__MACHINEARM_ARM64(void __wfe(void))
__MACHINEARM_ARM64(void __wfi(void))
__MACHINEX64(void __writecr0(unsigned __int64))
__MACHINEX86(void __writecr0(unsigned int))
__MACHINEX64(void __writecr2(unsigned __int64))
__MACHINEX86(void __writecr2(unsigned int))
__MACHINEX64(void __writecr3(unsigned __int64))
__MACHINEX86(void __writecr3(unsigned int))
__MACHINEX64(void __writecr4(unsigned __int64))
__MACHINEX86(void __writecr4(unsigned int))
__MACHINEX64(void __writecr8(unsigned __int64))
__MACHINEX86(void __writecr8(unsigned int))
__MACHINEX64(void __writedr(unsigned int, unsigned __int64))
__MACHINEX86(void __writedr(unsigned int, unsigned int))
__MACHINEX64(void __writeeflags(unsigned __int64))
__MACHINEX86(void __writeeflags(unsigned int))
__MACHINEX86(void __writefsbyte(unsigned long, unsigned char))
__MACHINEX86(void __writefsdword(unsigned long, unsigned long))
__MACHINEX86(void __writefsqword(unsigned long, unsigned __int64))
__MACHINEX86(void __writefsword(unsigned long, unsigned short))
__MACHINEX64(void __writegsbyte(unsigned long, unsigned char))
__MACHINEX64(void __writegsdword(unsigned long, unsigned long))
__MACHINEX64(void __writegsqword(unsigned long, unsigned __int64))
__MACHINEX64(void __writegsword(unsigned long, unsigned short))
__MACHINEX86_X64(void __writemsr(unsigned long, unsigned __int64))
__MACHINEARM64(void __writex18byte(unsigned long, unsigned char))
__MACHINEARM64(void __writex18dword(unsigned long, unsigned long))
__MACHINEARM64(void __writex18qword(unsigned long, unsigned __int64))
__MACHINEARM64(void __writex18word(unsigned long, unsigned short))
__MACHINEARM64_X64(unsigned char _bittest64(__int64 const *, __int64))
__MACHINE(unsigned char _bittestandcomplement(long *, long))
__MACHINEARM64_X64(unsigned char _bittestandcomplement64(__int64 *, __int64))
__MACHINE(unsigned char _bittestandreset(long *, long))
__MACHINEARM64_X64(unsigned char _bittestandreset64(__int64 *, __int64))
__MACHINE(unsigned char _bittestandset(long *, long))
__MACHINEARM64_X64(unsigned char _bittestandset64(__int64 *, __int64))
__MACHINE(_NODISCARD _Check_return_ unsigned __int64 __cdecl _byteswap_uint64(_In_ unsigned __int64))
__MACHINE(_NODISCARD _Check_return_ unsigned long __cdecl _byteswap_ulong(_In_ unsigned long))
__MACHINE(_NODISCARD _Check_return_ unsigned short __cdecl _byteswap_ushort(_In_ unsigned short))
__MACHINE(void __cdecl _disable(void))
__MACHINE(void __cdecl _enable(void))
__MACHINE(unsigned char _interlockedbittestandreset(long volatile *, long))
__MACHINEARM64_X64(unsigned char _interlockedbittestandreset64(__int64 volatile *, __int64))
__MACHINEARM_ARM64(unsigned char _interlockedbittestandreset_acq(long volatile *, long))
__MACHINEARM_ARM64(unsigned char _interlockedbittestandreset_nf(long volatile *, long))
__MACHINEARM_ARM64(unsigned char _interlockedbittestandreset_rel(long volatile *, long))
__MACHINEARM64(unsigned char _interlockedbittestandreset64_acq(__int64 volatile *, __int64))
__MACHINEARM64(unsigned char _interlockedbittestandreset64_rel(__int64 volatile *, __int64))
__MACHINEARM64(unsigned char _interlockedbittestandreset64_nf(__int64 volatile *, __int64))
__MACHINEARM64_X64(unsigned char _interlockedbittestandset64(__int64 volatile *, __int64))
__MACHINEARM64(unsigned char _interlockedbittestandset64_acq(__int64 volatile *, __int64))
__MACHINEARM64(unsigned char _interlockedbittestandset64_rel(__int64 volatile *, __int64))
__MACHINEARM64(unsigned char _interlockedbittestandset64_nf(__int64 volatile *, __int64))
__MACHINEARM64(unsigned __int32 __crc32b(unsigned __int32, unsigned __int32))
__MACHINEARM64(unsigned __int32 __crc32h(unsigned __int32, unsigned __int32))
__MACHINEARM64(unsigned __int32 __crc32w(unsigned __int32, unsigned __int32))
__MACHINEARM64(unsigned __int32 __crc32d(unsigned __int32, unsigned __int64))
__MACHINEARM64(unsigned __int32 __crc32cb(unsigned __int32, unsigned __int32))
__MACHINEARM64(unsigned __int32 __crc32ch(unsigned __int32, unsigned __int32))
__MACHINEARM64(unsigned __int32 __crc32cw(unsigned __int32, unsigned __int32))
__MACHINEARM64(unsigned __int32 __crc32cd(unsigned __int32, unsigned __int64))
__MACHINEARM(int _isunordered(double, double))
__MACHINEARM(int _isunorderedf(float, float))
__MACHINE(_NODISCARD _Check_return_ unsigned long __cdecl _lrotl(_In_ unsigned long, _In_ int))
__MACHINE(_NODISCARD _Check_return_ unsigned long __cdecl _lrotr(_In_ unsigned long, _In_ int))
__MACHINEX86(void _m_empty(void))
__MACHINEX86(void _m_femms(void))
__MACHINEX86(__m64 _m_from_float(float))
__MACHINEX86(__m64 _m_from_int(int))
__MACHINEX86(void _m_maskmovq(__m64, __m64, char *))
__MACHINEX86(__m64 _m_packssdw(__m64, __m64))
__MACHINEX86(__m64 _m_packsswb(__m64, __m64))
__MACHINEX86(__m64 _m_packuswb(__m64, __m64))
__MACHINEX86(__m64 _m_paddb(__m64, __m64))
__MACHINEX86(__m64 _m_paddd(__m64, __m64))
__MACHINEX86(__m64 _m_paddsb(__m64, __m64))
__MACHINEX86(__m64 _m_paddsw(__m64, __m64))
__MACHINEX86(__m64 _m_paddusb(__m64, __m64))
__MACHINEX86(__m64 _m_paddusw(__m64, __m64))
__MACHINEX86(__m64 _m_paddw(__m64, __m64))
__MACHINEX86(__m64 _m_pand(__m64, __m64))
__MACHINEX86(__m64 _m_pandn(__m64, __m64))
__MACHINEX86(__m64 _m_pavgb(__m64, __m64))
__MACHINEX86(__m64 _m_pavgusb(__m64, __m64))
__MACHINEX86(__m64 _m_pavgw(__m64, __m64))
__MACHINEX86(__m64 _m_pcmpeqb(__m64, __m64))
__MACHINEX86(__m64 _m_pcmpeqd(__m64, __m64))
__MACHINEX86(__m64 _m_pcmpeqw(__m64, __m64))
__MACHINEX86(__m64 _m_pcmpgtb(__m64, __m64))
__MACHINEX86(__m64 _m_pcmpgtd(__m64, __m64))
__MACHINEX86(__m64 _m_pcmpgtw(__m64, __m64))
__MACHINEX86(int _m_pextrw(__m64, int))
__MACHINEX86(__m64 _m_pf2id(__m64))
__MACHINEX86(__m64 _m_pf2iw(__m64))
__MACHINEX86(__m64 _m_pfacc(__m64, __m64))
__MACHINEX86(__m64 _m_pfadd(__m64, __m64))
__MACHINEX86(__m64 _m_pfcmpeq(__m64, __m64))
__MACHINEX86(__m64 _m_pfcmpge(__m64, __m64))
__MACHINEX86(__m64 _m_pfcmpgt(__m64, __m64))
__MACHINEX86(__m64 _m_pfmax(__m64, __m64))
__MACHINEX86(__m64 _m_pfmin(__m64, __m64))
__MACHINEX86(__m64 _m_pfmul(__m64, __m64))
__MACHINEX86(__m64 _m_pfnacc(__m64, __m64))
__MACHINEX86(__m64 _m_pfpnacc(__m64, __m64))
__MACHINEX86(__m64 _m_pfrcp(__m64))
__MACHINEX86(__m64 _m_pfrcpit1(__m64, __m64))
__MACHINEX86(__m64 _m_pfrcpit2(__m64, __m64))
__MACHINEX86(__m64 _m_pfrsqit1(__m64, __m64))
__MACHINEX86(__m64 _m_pfrsqrt(__m64))
__MACHINEX86(__m64 _m_pfsub(__m64, __m64))
__MACHINEX86(__m64 _m_pfsubr(__m64, __m64))
__MACHINEX86(__m64 _m_pi2fd(__m64))
__MACHINEX86(__m64 _m_pi2fw(__m64))
__MACHINEX86(__m64 _m_pinsrw(__m64, int, int))
__MACHINEX86(__m64 _m_pmaddwd(__m64, __m64))
__MACHINEX86(__m64 _m_pmaxsw(__m64, __m64))
__MACHINEX86(__m64 _m_pmaxub(__m64, __m64))
__MACHINEX86(__m64 _m_pminsw(__m64, __m64))
__MACHINEX86(__m64 _m_pminub(__m64, __m64))
__MACHINEX86(int _m_pmovmskb(__m64))
__MACHINEX86(__m64 _m_pmulhrw(__m64, __m64))
__MACHINEX86(__m64 _m_pmulhuw(__m64, __m64))
__MACHINEX86(__m64 _m_pmulhw(__m64, __m64))
__MACHINEX86(__m64 _m_pmullw(__m64, __m64))
__MACHINEX86(__m64 _m_por(__m64, __m64))
__MACHINEX86_X64(void _m_prefetch(void *))
__MACHINEX86_X64(void _m_prefetchw(volatile const void *))
__MACHINEX86(__m64 _m_psadbw(__m64, __m64))
__MACHINEX86(__m64 _m_pshufw(__m64, int))
__MACHINEX86(__m64 _m_pslld(__m64, __m64))
__MACHINEX86(__m64 _m_pslldi(__m64, int))
__MACHINEX86(__m64 _m_psllq(__m64, __m64))
__MACHINEX86(__m64 _m_psllqi(__m64, int))
__MACHINEX86(__m64 _m_psllw(__m64, __m64))
__MACHINEX86(__m64 _m_psllwi(__m64, int))
__MACHINEX86(__m64 _m_psrad(__m64, __m64))
__MACHINEX86(__m64 _m_psradi(__m64, int))
__MACHINEX86(__m64 _m_psraw(__m64, __m64))
__MACHINEX86(__m64 _m_psrawi(__m64, int))
__MACHINEX86(__m64 _m_psrld(__m64, __m64))
__MACHINEX86(__m64 _m_psrldi(__m64, int))
__MACHINEX86(__m64 _m_psrlq(__m64, __m64))
__MACHINEX86(__m64 _m_psrlqi(__m64, int))
__MACHINEX86(__m64 _m_psrlw(__m64, __m64))
__MACHINEX86(__m64 _m_psrlwi(__m64, int))
__MACHINEX86(__m64 _m_psubb(__m64, __m64))
__MACHINEX86(__m64 _m_psubd(__m64, __m64))
__MACHINEX86(__m64 _m_psubsb(__m64, __m64))
__MACHINEX86(__m64 _m_psubsw(__m64, __m64))
__MACHINEX86(__m64 _m_psubusb(__m64, __m64))
__MACHINEX86(__m64 _m_psubusw(__m64, __m64))
__MACHINEX86(__m64 _m_psubw(__m64, __m64))
__MACHINEX86(__m64 _m_pswapd(__m64))
__MACHINEX86(__m64 _m_punpckhbw(__m64, __m64))
__MACHINEX86(__m64 _m_punpckhdq(__m64, __m64))
__MACHINEX86(__m64 _m_punpckhwd(__m64, __m64))
__MACHINEX86(__m64 _m_punpcklbw(__m64, __m64))
__MACHINEX86(__m64 _m_punpckldq(__m64, __m64))
__MACHINEX86(__m64 _m_punpcklwd(__m64, __m64))
__MACHINEX86(__m64 _m_pxor(__m64, __m64))
__MACHINEX86(float _m_to_float(__m64))
__MACHINEX86(int _m_to_int(__m64))
__MACHINEX86_X64(__m128i _mm_abs_epi16(__m128i))
__MACHINEX86_X64(__m128i _mm_abs_epi32(__m128i))
__MACHINEX86_X64(__m128i _mm_abs_epi8(__m128i))
__MACHINEX86(__m64 _mm_abs_pi16(__m64))
__MACHINEX86(__m64 _mm_abs_pi32(__m64))
__MACHINEX86(__m64 _mm_abs_pi8(__m64))
__MACHINEX86_X64(__m128i _mm_add_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_add_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_add_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_add_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_add_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_add_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_add_sd(__m128d, __m128d))
__MACHINEX86(__m64 _mm_add_si64(__m64, __m64))
__MACHINEX86_X64(__m128 _mm_add_ss(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_adds_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_adds_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_adds_epu16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_adds_epu8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_addsub_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_addsub_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_alignr_epi8(__m128i, __m128i, int))
__MACHINEX86(__m64 _mm_alignr_pi8(__m64, __m64, int))
__MACHINEX86_X64(__m128d _mm_and_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_and_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_and_si128(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_andnot_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_andnot_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_andnot_si128(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_avg_epu16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_avg_epu8(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_blend_epi16(__m128i, __m128i, int))
__MACHINEX86_X64(__m128d _mm_blend_pd(__m128d, __m128d, int))
__MACHINEX86_X64(__m128 _mm_blend_ps(__m128, __m128, int))
__MACHINEX86_X64(__m128i _mm_blendv_epi8(__m128i, __m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_blendv_pd(__m128d, __m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_blendv_ps(__m128, __m128, __m128))
__MACHINEX86_X64(void _mm_clflush(void const *))
__MACHINEX86_X64(void _mm_clflushopt(void const *))
__MACHINEX86_X64(void _mm_clwb(void const *))
__MACHINEX86_X64(void _mm_clzero(void const *))
__MACHINEX86_X64(__m128i _mm_cmpeq_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmpeq_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmpeq_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmpeq_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_cmpeq_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpeq_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpeq_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpeq_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_cmpestra(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(int _mm_cmpestrc(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(int _mm_cmpestri(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(__m128i _mm_cmpestrm(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(int _mm_cmpestro(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(int _mm_cmpestrs(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(int _mm_cmpestrz(__m128i, int, __m128i, int, int))
__MACHINEX86_X64(__m128d _mm_cmpge_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpge_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpge_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpge_ss(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_cmpgt_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmpgt_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmpgt_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmpgt_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_cmpgt_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpgt_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpgt_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpgt_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_cmpistra(__m128i, __m128i, int))
__MACHINEX86_X64(int _mm_cmpistrc(__m128i, __m128i, int))
__MACHINEX86_X64(int _mm_cmpistri(__m128i, __m128i, int))
__MACHINEX86_X64(__m128i _mm_cmpistrm(__m128i, __m128i, int))
__MACHINEX86_X64(int _mm_cmpistro(__m128i, __m128i, int))
__MACHINEX86_X64(int _mm_cmpistrs(__m128i, __m128i, int))
__MACHINEX86_X64(int _mm_cmpistrz(__m128i, __m128i, int))
__MACHINEX86_X64(__m128d _mm_cmple_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmple_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmple_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmple_ss(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_cmplt_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmplt_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_cmplt_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_cmplt_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmplt_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmplt_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmplt_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpneq_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpneq_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpneq_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpneq_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpnge_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpnge_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpnge_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpnge_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpngt_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpngt_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpngt_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpngt_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpnle_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpnle_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpnle_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpnle_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpnlt_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpnlt_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpnlt_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpnlt_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpord_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpord_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpord_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpord_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpunord_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpunord_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_cmpunord_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_cmpunord_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_comieq_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_comieq_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_comige_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_comige_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_comigt_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_comigt_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_comile_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_comile_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_comilt_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_comilt_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_comineq_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_comineq_ss(__m128, __m128))
__MACHINEX86_X64(unsigned int _mm_crc32_u16(unsigned int, unsigned short))
__MACHINEX86_X64(unsigned int _mm_crc32_u32(unsigned int, unsigned int))
__MACHINEX64(unsigned __int64 _mm_crc32_u64(unsigned __int64, unsigned __int64))
__MACHINEX86_X64(unsigned int _mm_crc32_u8(unsigned int, unsigned char))
__MACHINEX86(__m128 _mm_cvt_pi2ps(__m128, __m64))
__MACHINEX86(__m64 _mm_cvt_ps2pi(__m128))
__MACHINEX86_X64(__m128 _mm_cvt_si2ss(__m128, int))
__MACHINEX86_X64(int _mm_cvt_ss2si(__m128))
__MACHINEX86_X64(__m128i _mm_cvtepi16_epi32(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepi16_epi64(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepi32_epi64(__m128i))
__MACHINEX86_X64(__m128d _mm_cvtepi32_pd(__m128i))
__MACHINEX86_X64(__m128 _mm_cvtepi32_ps(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepi8_epi16(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepi8_epi32(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepi8_epi64(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepu16_epi32(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepu16_epi64(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepu32_epi64(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepu8_epi16(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepu8_epi32(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtepu8_epi64(__m128i))
__MACHINEX86_X64(__m128i _mm_cvtpd_epi32(__m128d))
__MACHINEX86(__m64 _mm_cvtpd_pi32(__m128d))
__MACHINEX86_X64(__m128 _mm_cvtpd_ps(__m128d))
__MACHINEX86(__m128d _mm_cvtpi32_pd(__m64))
__MACHINEX86_X64(__m128i _mm_cvtps_epi32(__m128))
__MACHINEX86_X64(__m128d _mm_cvtps_pd(__m128))
__MACHINEX86_X64(int _mm_cvtsd_si32(__m128d))
__MACHINEX64(__int64 _mm_cvtsd_si64(__m128d))
__MACHINEX64(__int64 _mm_cvtsd_si64x(__m128d))
__MACHINEX86_X64(__m128 _mm_cvtsd_ss(__m128, __m128d))
__MACHINEX86_X64(int _mm_cvtsi128_si32(__m128i))
__MACHINEX64(__int64 _mm_cvtsi128_si64(__m128i))
__MACHINEX64(__int64 _mm_cvtsi128_si64x(__m128i))
__MACHINEX86_X64(__m128d _mm_cvtsi32_sd(__m128d, int))
__MACHINEX86_X64(__m128i _mm_cvtsi32_si128(int))
__MACHINEX64(__m128d _mm_cvtsi64_sd(__m128d, __int64))
__MACHINEX64(__m128i _mm_cvtsi64_si128(__int64))
__MACHINEX64(__m128 _mm_cvtsi64_ss(__m128, __int64))
__MACHINEX64(__m128d _mm_cvtsi64x_sd(__m128d, __int64))
__MACHINEX64(__m128i _mm_cvtsi64x_si128(__int64))
__MACHINEX64(__m128 _mm_cvtsi64x_ss(__m128, __int64))
__MACHINEX86_X64(__m128d _mm_cvtss_sd(__m128d, __m128))
__MACHINEX64(__int64 _mm_cvtss_si64(__m128))
__MACHINEX64(__int64 _mm_cvtss_si64x(__m128))
__MACHINEX86(__m64 _mm_cvtt_ps2pi(__m128))
__MACHINEX86_X64(int _mm_cvtt_ss2si(__m128))
__MACHINEX86_X64(__m128i _mm_cvttpd_epi32(__m128d))
__MACHINEX86(__m64 _mm_cvttpd_pi32(__m128d))
__MACHINEX86_X64(__m128i _mm_cvttps_epi32(__m128))
__MACHINEX86_X64(int _mm_cvttsd_si32(__m128d))
__MACHINEX64(__int64 _mm_cvttsd_si64(__m128d))
__MACHINEX64(__int64 _mm_cvttsd_si64x(__m128d))
__MACHINEX64(__int64 _mm_cvttss_si64(__m128))
__MACHINEX64(__int64 _mm_cvttss_si64x(__m128))
__MACHINEX86_X64(__m128d _mm_div_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_div_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_div_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_div_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_dp_pd(__m128d, __m128d, int))
__MACHINEX86_X64(__m128 _mm_dp_ps(__m128, __m128, int))
__MACHINEX86_X64(int _mm_extract_epi16(__m128i, int))
__MACHINEX86_X64(int _mm_extract_epi32(__m128i, int))
__MACHINEX64(__int64 _mm_extract_epi64(__m128i, int))
__MACHINEX86_X64(int _mm_extract_epi8(__m128i, int))
__MACHINEX86_X64(int _mm_extract_ps(__m128, int))
__MACHINEX86_X64(__m128i _mm_extract_si64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_extracti_si64(__m128i, int, int))
__MACHINEX86_X64(unsigned int _mm_getcsr(void))
__MACHINEX86_X64(__m128i _mm_hadd_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_hadd_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_hadd_pd(__m128d, __m128d))
__MACHINEX86(__m64 _mm_hadd_pi16(__m64, __m64))
__MACHINEX86(__m64 _mm_hadd_pi32(__m64, __m64))
__MACHINEX86_X64(__m128 _mm_hadd_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_hadds_epi16(__m128i, __m128i))
__MACHINEX86(__m64 _mm_hadds_pi16(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_hsub_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_hsub_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_hsub_pd(__m128d, __m128d))
__MACHINEX86(__m64 _mm_hsub_pi16(__m64, __m64))
__MACHINEX86(__m64 _mm_hsub_pi32(__m64, __m64))
__MACHINEX86_X64(__m128 _mm_hsub_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_hsubs_epi16(__m128i, __m128i))
__MACHINEX86(__m64 _mm_hsubs_pi16(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_insert_epi16(__m128i, int, int))
__MACHINEX86_X64(__m128i _mm_insert_epi32(__m128i, int, int))
__MACHINEX64(__m128i _mm_insert_epi64(__m128i, __int64, int))
__MACHINEX86_X64(__m128i _mm_insert_epi8(__m128i, int, int))
__MACHINEX86_X64(__m128 _mm_insert_ps(__m128, __m128, int))
__MACHINEX86_X64(__m128i _mm_insert_si64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_inserti_si64(__m128i, __m128i, int, int))
__MACHINEX86_X64(__m128i _mm_lddqu_si128(__m128i const *))
__MACHINEX86_X64(void _mm_lfence(void))
__MACHINEX86_X64(__m128d _mm_load1_pd(double const *))
__MACHINEX86_X64(__m128d _mm_load_pd(double const *))
__MACHINEX86_X64(__m128 _mm_load_ps(float const *))
__MACHINEX86_X64(__m128 _mm_load_ps1(float const *))
__MACHINEX86_X64(__m128d _mm_load_sd(double const *))
__MACHINEX86_X64(__m128i _mm_load_si128(__m128i const *))
__MACHINEX86_X64(__m128 _mm_load_ss(float const *))
__MACHINEX86_X64(__m128d _mm_loaddup_pd(double const *))
__MACHINEX86_X64(__m128d _mm_loadh_pd(__m128d, double const *))
__MACHINEX86_X64(__m128 _mm_loadh_pi(__m128, __m64 const *))
__MACHINEX86_X64(__m128i _mm_loadl_epi64(__m128i const *))
__MACHINEX86_X64(__m128d _mm_loadl_pd(__m128d, double const *))
__MACHINEX86_X64(__m128 _mm_loadl_pi(__m128, __m64 const *))
__MACHINEX86_X64(__m128d _mm_loadr_pd(double const *))
__MACHINEX86_X64(__m128 _mm_loadr_ps(float const *))
__MACHINEX86_X64(__m128d _mm_loadu_pd(double const *))
__MACHINEX86_X64(__m128 _mm_loadu_ps(float const *))
__MACHINEX86_X64(__m128i _mm_loadu_si128(__m128i const *))
__MACHINEX86_X64(__m128i _mm_madd_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_maddubs_epi16(__m128i, __m128i))
__MACHINEX86(__m64 _mm_maddubs_pi16(__m64, __m64))
__MACHINEX86_X64(void _mm_maskmoveu_si128(__m128i, __m128i, char *))
__MACHINEX86_X64(__m128i _mm_max_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_max_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_max_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_max_epu16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_max_epu32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_max_epu8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_max_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_max_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_max_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_max_ss(__m128, __m128))
__MACHINEX86_X64(void _mm_mfence(void))
__MACHINEX86_X64(__m128i _mm_min_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_min_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_min_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_min_epu16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_min_epu32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_min_epu8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_min_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_min_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_min_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_min_ss(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_minpos_epu16(__m128i))
__MACHINEX86_X64(void _mm_monitor(void const *, unsigned int, unsigned int))
__MACHINEX86_X64(__m128i _mm_move_epi64(__m128i))
__MACHINEX86_X64(__m128d _mm_move_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_move_ss(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_movedup_pd(__m128d))
__MACHINEX86_X64(__m128 _mm_movehdup_ps(__m128))
__MACHINEX86_X64(__m128 _mm_movehl_ps(__m128, __m128))
__MACHINEX86_X64(__m128 _mm_moveldup_ps(__m128))
__MACHINEX86_X64(__m128 _mm_movelh_ps(__m128, __m128))
__MACHINEX86_X64(int _mm_movemask_epi8(__m128i))
__MACHINEX86_X64(int _mm_movemask_pd(__m128d))
__MACHINEX86_X64(int _mm_movemask_ps(__m128))
__MACHINEX86(__m64 _mm_movepi64_pi64(__m128i))
__MACHINEX86(__m128i _mm_movpi64_epi64(__m64))
__MACHINEX86_X64(__m128i _mm_mpsadbw_epu8(__m128i, __m128i, int))
__MACHINEX86_X64(__m128i _mm_mul_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_mul_epu32(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_mul_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_mul_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_mul_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_mul_ss(__m128, __m128))
__MACHINEX86(__m64 _mm_mul_su32(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_mulhi_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_mulhi_epu16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_mulhrs_epi16(__m128i, __m128i))
__MACHINEX86(__m64 _mm_mulhrs_pi16(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_mullo_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_mullo_epi32(__m128i, __m128i))
__MACHINEX86_X64(void _mm_mwait(unsigned int, unsigned int))
__MACHINEX86_X64(__m128d _mm_or_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_or_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_or_si128(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_packs_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_packs_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_packus_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_packus_epi32(__m128i, __m128i))
__MACHINEX86_X64(int _mm_popcnt_u32(unsigned int))
__MACHINEX64(__int64 _mm_popcnt_u64(unsigned __int64))
__MACHINEX86_X64(void _mm_prefetch(char const *, int))
__MACHINEX86_X64(__m128 _mm_rcp_ps(__m128))
__MACHINEX86_X64(__m128 _mm_rcp_ss(__m128))
__MACHINEX86_X64(__m128d _mm_round_pd(__m128d, int))
__MACHINEX86_X64(__m128 _mm_round_ps(__m128, int))
__MACHINEX86_X64(__m128d _mm_round_sd(__m128d, __m128d, int))
__MACHINEX86_X64(__m128 _mm_round_ss(__m128, __m128, int))
__MACHINEX86_X64(__m128 _mm_rsqrt_ps(__m128))
__MACHINEX86_X64(__m128 _mm_rsqrt_ss(__m128))
__MACHINEX86_X64(__m128i _mm_sad_epu8(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_set1_epi16(short))
__MACHINEX86_X64(__m128i _mm_set1_epi32(int))
__MACHINEX86(__m128i _mm_set1_epi64(__m64))
__MACHINEX86_X64(__m128i _mm_set1_epi64x(__int64))
__MACHINEX86_X64(__m128i _mm_set1_epi8(char))
__MACHINEX86_X64(__m128d _mm_set1_pd(double))
__MACHINEX86(__m64 _mm_set1_pi16(short))
__MACHINEX86(__m64 _mm_set1_pi32(int))
__MACHINEX86(__m64 _mm_set1_pi8(char))
__MACHINEX86_X64(__m128i _mm_set_epi16(short, short, short, short, short, short, short, short))
__MACHINEX86_X64(__m128i _mm_set_epi32(int, int, int, int))
__MACHINEX86(__m128i _mm_set_epi64(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_set_epi64x(__int64, __int64))
__MACHINEX86_X64(__m128i _mm_set_epi8(char, char, char, char, char, char, char, char, char, char, char, char, char, char, char, char))
__MACHINEX86_X64(__m128d _mm_set_pd(double, double))
__MACHINEX86(__m64 _mm_set_pi16(short, short, short, short))
__MACHINEX86(__m64 _mm_set_pi32(int, int))
__MACHINEX86(__m64 _mm_set_pi8(char, char, char, char, char, char, char, char))
__MACHINEX86_X64(__m128 _mm_set_ps(float, float, float, float))
__MACHINEX86_X64(__m128 _mm_set_ps1(float))
__MACHINEX86_X64(__m128d _mm_set_sd(double))
__MACHINEX86_X64(__m128 _mm_set_ss(float))
__MACHINEX86_X64(void _mm_setcsr(unsigned int))
__MACHINEX86_X64(__m128i _mm_setl_epi64(__m128i))
__MACHINEX86_X64(__m128i _mm_setr_epi16(short, short, short, short, short, short, short, short))
__MACHINEX86_X64(__m128i _mm_setr_epi32(int, int, int, int))
__MACHINEX86(__m128i _mm_setr_epi64(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_setr_epi64x(__int64, __int64))
__MACHINEX86_X64(__m128i _mm_setr_epi8(char, char, char, char, char, char, char, char, char, char, char, char, char, char, char, char))
__MACHINEX86_X64(__m128d _mm_setr_pd(double, double))
__MACHINEX86(__m64 _mm_setr_pi16(short, short, short, short))
__MACHINEX86(__m64 _mm_setr_pi32(int, int))
__MACHINEX86(__m64 _mm_setr_pi8(char, char, char, char, char, char, char, char))
__MACHINEX86_X64(__m128 _mm_setr_ps(float, float, float, float))
__MACHINEX86_X64(__m128d _mm_setzero_pd(void))
__MACHINEX86_X64(__m128 _mm_setzero_ps(void))
__MACHINEX86_X64(__m128i _mm_setzero_si128(void))
__MACHINEX86(__m64 _mm_setzero_si64(void))
__MACHINEX86_X64(void _mm_sfence(void))
__MACHINEX86_X64(__m128i _mm_shuffle_epi32(__m128i, int))
__MACHINEX86_X64(__m128i _mm_shuffle_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_shuffle_pd(__m128d, __m128d, int))
__MACHINEX86(__m64 _mm_shuffle_pi8(__m64, __m64))
__MACHINEX86_X64(__m128 _mm_shuffle_ps(__m128, __m128, unsigned int))
__MACHINEX86_X64(__m128i _mm_shufflehi_epi16(__m128i, int))
__MACHINEX86_X64(__m128i _mm_shufflelo_epi16(__m128i, int))
__MACHINEX86_X64(__m128i _mm_sign_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sign_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sign_epi8(__m128i, __m128i))
__MACHINEX86(__m64 _mm_sign_pi16(__m64, __m64))
__MACHINEX86(__m64 _mm_sign_pi32(__m64, __m64))
__MACHINEX86(__m64 _mm_sign_pi8(__m64, __m64))
__MACHINEX86_X64(__m128i _mm_sll_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sll_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sll_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_slli_epi16(__m128i, int))
__MACHINEX86_X64(__m128i _mm_slli_epi32(__m128i, int))
__MACHINEX86_X64(__m128i _mm_slli_epi64(__m128i, int))
__MACHINEX86_X64(__m128i _mm_slli_si128(__m128i, int))
__MACHINEX86_X64(__m128d _mm_sqrt_pd(__m128d))
__MACHINEX86_X64(__m128 _mm_sqrt_ps(__m128))
__MACHINEX86_X64(__m128d _mm_sqrt_sd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_sqrt_ss(__m128))
__MACHINEX86_X64(__m128i _mm_sra_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sra_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_srai_epi16(__m128i, int))
__MACHINEX86_X64(__m128i _mm_srai_epi32(__m128i, int))
__MACHINEX86_X64(__m128i _mm_srl_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_srl_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_srl_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_srli_epi16(__m128i, int))
__MACHINEX86_X64(__m128i _mm_srli_epi32(__m128i, int))
__MACHINEX86_X64(__m128i _mm_srli_epi64(__m128i, int))
__MACHINEX86_X64(__m128i _mm_srli_si128(__m128i, int))
__MACHINEX86_X64(void _mm_store1_pd(double *, __m128d))
__MACHINEX86_X64(void _mm_store_pd(double *, __m128d))
__MACHINEX86_X64(void _mm_store_ps(float *, __m128))
__MACHINEX86_X64(void _mm_store_ps1(float *, __m128))
__MACHINEX86_X64(void _mm_store_sd(double *, __m128d))
__MACHINEX86_X64(void _mm_store_si128(__m128i *, __m128i))
__MACHINEX86_X64(void _mm_store_ss(float *, __m128))
__MACHINEX86_X64(void _mm_storeh_pd(double *, __m128d))
__MACHINEX86_X64(void _mm_storeh_pi(__m64 *, __m128))
__MACHINEX86_X64(void _mm_storel_epi64(__m128i *, __m128i))
__MACHINEX86_X64(void _mm_storel_pd(double *, __m128d))
__MACHINEX86_X64(void _mm_storel_pi(__m64 *, __m128))
__MACHINEX86_X64(void _mm_storer_pd(double *, __m128d))
__MACHINEX86_X64(void _mm_storer_ps(float *, __m128))
__MACHINEX86_X64(void _mm_storeu_pd(double *, __m128d))
__MACHINEX86_X64(void _mm_storeu_ps(float *, __m128))
__MACHINEX86_X64(void _mm_storeu_si128(__m128i *, __m128i))
#if defined(_CRT_WINDOWS) || defined(UNDOCKED_WINDOWS_UCRT)
__MACHINEX86_X64(__m128i _mm_stream_load_si128(__m128i *))
#else
__MACHINEX86_X64(__m128i _mm_stream_load_si128(const __m128i *))
#endif
__MACHINEX86_X64(void _mm_stream_pd(double *, __m128d))
__MACHINEX86(void _mm_stream_pi(__m64 *, __m64))
__MACHINEX86_X64(void _mm_stream_ps(float *, __m128))
__MACHINEX86_X64(void _mm_stream_sd(double *, __m128d))
__MACHINEX86_X64(void _mm_stream_si128(__m128i *, __m128i))
__MACHINEX86_X64(void _mm_stream_si32(int *, int))
__MACHINEX64(void _mm_stream_si64x(__int64 *, __int64))
__MACHINEX86_X64(void _mm_stream_ss(float *, __m128))
__MACHINEX86_X64(__m128i _mm_sub_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sub_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sub_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_sub_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_sub_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_sub_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_sub_sd(__m128d, __m128d))
__MACHINEX86(__m64 _mm_sub_si64(__m64, __m64))
__MACHINEX86_X64(__m128 _mm_sub_ss(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_subs_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_subs_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_subs_epu16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_subs_epu8(__m128i, __m128i))
__MACHINEX86_X64(int _mm_testc_si128(__m128i, __m128i))
__MACHINEX86_X64(int _mm_testnzc_si128(__m128i, __m128i))
__MACHINEX86_X64(int _mm_testz_si128(__m128i, __m128i))
__MACHINEX86_X64(int _mm_ucomieq_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_ucomieq_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_ucomige_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_ucomige_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_ucomigt_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_ucomigt_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_ucomile_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_ucomile_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_ucomilt_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_ucomilt_ss(__m128, __m128))
__MACHINEX86_X64(int _mm_ucomineq_sd(__m128d, __m128d))
__MACHINEX86_X64(int _mm_ucomineq_ss(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_unpackhi_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_unpackhi_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_unpackhi_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_unpackhi_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_unpackhi_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_unpackhi_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_unpacklo_epi16(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_unpacklo_epi32(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_unpacklo_epi64(__m128i, __m128i))
__MACHINEX86_X64(__m128i _mm_unpacklo_epi8(__m128i, __m128i))
__MACHINEX86_X64(__m128d _mm_unpacklo_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_unpacklo_ps(__m128, __m128))
__MACHINEX86_X64(__m128d _mm_xor_pd(__m128d, __m128d))
__MACHINEX86_X64(__m128 _mm_xor_ps(__m128, __m128))
__MACHINEX86_X64(__m128i _mm_xor_si128(__m128i, __m128i))
__MACHINEX64(__int64 _mul128(__int64 _Multiplier, __int64 _Multiplicand, __int64 * _HighProduct))
__MACHINE(unsigned int __cdecl _rotl(_In_ unsigned int _Value, _In_ int _Shift))
__MACHINE(unsigned short __cdecl _rotl16(unsigned short _Value, unsigned char _Shift))
__MACHINE(unsigned __int64 __cdecl _rotl64(_In_ unsigned __int64 _Value, _In_ int _Shift))
__MACHINE(unsigned char __cdecl _rotl8(unsigned char _Value, unsigned char _Shift))
__MACHINE(unsigned int __cdecl _rotr(_In_ unsigned int _Value, _In_ int _Shift))
__MACHINE(unsigned short __cdecl _rotr16(unsigned short _Value, unsigned char _Shift))
__MACHINE(unsigned __int64 __cdecl _rotr64(_In_ unsigned __int64 _Value, _In_ int _Shift))
__MACHINE(unsigned char __cdecl _rotr8(unsigned char _Value, unsigned char _Shift))
__MACHINE(int __cdecl _setjmp(jmp_buf))
__MACHINEARM_ARM64_X64(int __cdecl _setjmpex(jmp_buf))
__MACHINEX86_X64(void _rsm(void))
__MACHINEX86_X64(void _lgdt(void *))
__MACHINEX86_X64(void _sgdt(void *))
__MACHINEX86_X64(void _clac(void))
__MACHINEX86_X64(void _stac(void))
__MACHINEX86_X64(unsigned char __cdecl _addcarry_u8(unsigned char, unsigned char, unsigned char, unsigned char *))
__MACHINEX86_X64(unsigned char __cdecl _subborrow_u8(unsigned char, unsigned char, unsigned char, unsigned char *))
__MACHINEX86_X64(unsigned char __cdecl _addcarry_u16(unsigned char, unsigned short, unsigned short, unsigned short *))
__MACHINEX86_X64(unsigned char __cdecl _subborrow_u16(unsigned char, unsigned short, unsigned short, unsigned short *))
__MACHINEX86_X64(unsigned char __cdecl _addcarry_u32(unsigned char, unsigned int, unsigned int, unsigned int *))
__MACHINEX86_X64(unsigned char __cdecl _subborrow_u32(unsigned char, unsigned int, unsigned int, unsigned int *))
__MACHINEX64(unsigned char __cdecl _addcarry_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *))
__MACHINEX64(unsigned char __cdecl _subborrow_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *))
__MACHINEX86_X64(void _mm_monitorx(void const *, unsigned int, unsigned int))
__MACHINEX86_X64(void _mm_mwaitx(unsigned int, unsigned int, unsigned int))
__MACHINEX64(unsigned int __rmpupdate(unsigned __int64, rmp_seg *, int))
__MACHINEX64(unsigned int __psmash(unsigned __int64))
__MACHINEX64(unsigned int __rmpadjust(unsigned __int64, int, int))
__MACHINEX64(unsigned int __pvalidate(unsigned __int64, int, int, int*))
__MACHINEX86_X64(void __svm_invlpgb(void*, int))
__MACHINEX86_X64(void __svm_tlbsync(void))

#ifndef _M_CEE_PURE

    #if defined(_M_ARM64EC) && !defined(_DISABLE_SOFTINTRIN_)
    /***
     * softintrin.h includes widemath.h, which uses _rotr64, so
     * softintrin.h must be included after declaration of _rotr64.
     ****/
        #include <softintrin.h>
    #endif

#endif

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
#pragma warning(pop) // _VCRUNTIME_DISABLED_WARNINGS
#endif /* _VCRT_COMPILER_PREPROCESSOR && !defined(__midl) */


#	include <intrin.h>
#	pragma intrinsic(_BitScanReverse)
#endif//(GLM_ARCH & GLM_ARCH_X86 && GLM_COMPILER & GLM_COMPILER_VC)
#include <limits>

#if !GLM_HAS_EXTENDED_INTEGER_TYPE
#	if GLM_COMPILER & GLM_COMPILER_GCC
#		pragma GCC diagnostic ignored "-Wlong-long"
#	endif
#	if (GLM_COMPILER & GLM_COMPILER_CLANG)
#		pragma clang diagnostic ignored "-Wc++11-long-long"
#	endif
#endif

namespace glm{
namespace detail
{
	template<typename T>
	GLM_FUNC_QUALIFIER T mask(T Bits)
	{
		return Bits >= static_cast<T>(sizeof(T) * 8) ? ~static_cast<T>(0) : (static_cast<T>(1) << Bits) - static_cast<T>(1);
	}

	template<length_t L, typename T, qualifier Q, bool Aligned, bool EXEC>
	struct compute_bitfieldReverseStep
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v, T, T)
		{
			return v;
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_bitfieldReverseStep<L, T, Q, Aligned, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v, T Mask, T Shift)
		{
			return (v & Mask) << Shift | (v & (~Mask)) >> Shift;
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned, bool EXEC>
	struct compute_bitfieldBitCountStep
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v, T, T)
		{
			return v;
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_bitfieldBitCountStep<L, T, Q, Aligned, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v, T Mask, T Shift)
		{
			return (v & Mask) + ((v >> Shift) & Mask);
		}
	};

	template<typename genIUType, size_t Bits>
	struct compute_findLSB
	{
		GLM_FUNC_QUALIFIER static int call(genIUType Value)
		{
			if(Value == 0)
				return -1;

			return glm::bitCount(~Value & (Value - static_cast<genIUType>(1)));
		}
	};

#	if GLM_HAS_BITSCAN_WINDOWS
		template<typename genIUType>
		struct compute_findLSB<genIUType, 32>
		{
			GLM_FUNC_QUALIFIER static int call(genIUType Value)
			{
				unsigned long Result(0);
				unsigned char IsNotNull = _BitScanForward(&Result, *reinterpret_cast<unsigned long*>(&Value));
				return IsNotNull ? int(Result) : -1;
			}
		};

#		if !((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_MODEL == GLM_MODEL_32))
		template<typename genIUType>
		struct compute_findLSB<genIUType, 64>
		{
			GLM_FUNC_QUALIFIER static int call(genIUType Value)
			{
				unsigned long Result(0);
				unsigned char IsNotNull = _BitScanForward64(&Result, *reinterpret_cast<unsigned __int64*>(&Value));
				return IsNotNull ? int(Result) : -1;
			}
		};
#		endif
#	endif//GLM_HAS_BITSCAN_WINDOWS

	template<length_t L, typename T, qualifier Q, bool EXEC = true>
	struct compute_findMSB_step_vec
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, T Shift)
		{
			return x | (x >> Shift);
		}
	};

	template<length_t L, typename T, qualifier Q>
	struct compute_findMSB_step_vec<L, T, Q, false>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, T)
		{
			return x;
		}
	};

	template<length_t L, typename T, qualifier Q, int>
	struct compute_findMSB_vec
	{
		GLM_FUNC_QUALIFIER static vec<L, int, Q> call(vec<L, T, Q> const& v)
		{
			vec<L, T, Q> x(v);
			x = compute_findMSB_step_vec<L, T, Q, sizeof(T) * 8 >=  8>::call(x, static_cast<T>( 1));
			x = compute_findMSB_step_vec<L, T, Q, sizeof(T) * 8 >=  8>::call(x, static_cast<T>( 2));
			x = compute_findMSB_step_vec<L, T, Q, sizeof(T) * 8 >=  8>::call(x, static_cast<T>( 4));
			x = compute_findMSB_step_vec<L, T, Q, sizeof(T) * 8 >= 16>::call(x, static_cast<T>( 8));
			x = compute_findMSB_step_vec<L, T, Q, sizeof(T) * 8 >= 32>::call(x, static_cast<T>(16));
			x = compute_findMSB_step_vec<L, T, Q, sizeof(T) * 8 >= 64>::call(x, static_cast<T>(32));
			return vec<L, int, Q>(sizeof(T) * 8 - 1) - glm::bitCount(~x);
		}
	};

#	if GLM_HAS_BITSCAN_WINDOWS
		template<typename genIUType>
		GLM_FUNC_QUALIFIER int compute_findMSB_32(genIUType Value)
		{
			unsigned long Result(0);
			unsigned char IsNotNull = _BitScanReverse(&Result, *reinterpret_cast<unsigned long*>(&Value));
			return IsNotNull ? int(Result) : -1;
		}

		template<length_t L, typename T, qualifier Q>
		struct compute_findMSB_vec<L, T, Q, 32>
		{
			GLM_FUNC_QUALIFIER static vec<L, int, Q> call(vec<L, T, Q> const& x)
			{
				return detail::functor1<vec, L, int, T, Q>::call(compute_findMSB_32, x);
			}
		};

#		if !((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_MODEL == GLM_MODEL_32))
		template<typename genIUType>
		GLM_FUNC_QUALIFIER int compute_findMSB_64(genIUType Value)
		{
			unsigned long Result(0);
			unsigned char IsNotNull = _BitScanReverse64(&Result, *reinterpret_cast<unsigned __int64*>(&Value));
			return IsNotNull ? int(Result) : -1;
		}

		template<length_t L, typename T, qualifier Q>
		struct compute_findMSB_vec<L, T, Q, 64>
		{
			GLM_FUNC_QUALIFIER static vec<L, int, Q> call(vec<L, T, Q> const& x)
			{
				return detail::functor1<vec, L, int, T, Q>::call(compute_findMSB_64, x);
			}
		};
#		endif
#	endif//GLM_HAS_BITSCAN_WINDOWS
}//namespace detail

	// uaddCarry
	GLM_FUNC_QUALIFIER uint uaddCarry(uint const& x, uint const& y, uint & Carry)
	{
		detail::uint64 const Value64(static_cast<detail::uint64>(x) + static_cast<detail::uint64>(y));
		detail::uint64 const Max32((static_cast<detail::uint64>(1) << static_cast<detail::uint64>(32)) - static_cast<detail::uint64>(1));
		Carry = Value64 > Max32 ? 1u : 0u;
		return static_cast<uint>(Value64 % (Max32 + static_cast<detail::uint64>(1)));
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, uint, Q> uaddCarry(vec<L, uint, Q> const& x, vec<L, uint, Q> const& y, vec<L, uint, Q>& Carry)
	{
		vec<L, detail::uint64, Q> Value64(vec<L, detail::uint64, Q>(x) + vec<L, detail::uint64, Q>(y));
		vec<L, detail::uint64, Q> Max32((static_cast<detail::uint64>(1) << static_cast<detail::uint64>(32)) - static_cast<detail::uint64>(1));
		Carry = mix(vec<L, uint, Q>(0), vec<L, uint, Q>(1), greaterThan(Value64, Max32));
		return vec<L, uint, Q>(Value64 % (Max32 + static_cast<detail::uint64>(1)));
	}

	// usubBorrow
	GLM_FUNC_QUALIFIER uint usubBorrow(uint const& x, uint const& y, uint & Borrow)
	{
		Borrow = x >= y ? static_cast<uint>(0) : static_cast<uint>(1);
		if(y >= x)
			return y - x;
		else
			return static_cast<uint>((static_cast<detail::int64>(1) << static_cast<detail::int64>(32)) + (static_cast<detail::int64>(y) - static_cast<detail::int64>(x)));
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, uint, Q> usubBorrow(vec<L, uint, Q> const& x, vec<L, uint, Q> const& y, vec<L, uint, Q>& Borrow)
	{
		Borrow = mix(vec<L, uint, Q>(1), vec<L, uint, Q>(0), greaterThanEqual(x, y));
		vec<L, uint, Q> const YgeX(y - x);
		vec<L, uint, Q> const XgeY(vec<L, uint, Q>((static_cast<detail::int64>(1) << static_cast<detail::int64>(32)) + (vec<L, detail::int64, Q>(y) - vec<L, detail::int64, Q>(x))));
		return mix(XgeY, YgeX, greaterThanEqual(y, x));
	}

	// umulExtended
	GLM_FUNC_QUALIFIER void umulExtended(uint const& x, uint const& y, uint & msb, uint & lsb)
	{
		detail::uint64 Value64 = static_cast<detail::uint64>(x) * static_cast<detail::uint64>(y);
		msb = static_cast<uint>(Value64 >> static_cast<detail::uint64>(32));
		lsb = static_cast<uint>(Value64);
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER void umulExtended(vec<L, uint, Q> const& x, vec<L, uint, Q> const& y, vec<L, uint, Q>& msb, vec<L, uint, Q>& lsb)
	{
		vec<L, detail::uint64, Q> Value64(vec<L, detail::uint64, Q>(x) * vec<L, detail::uint64, Q>(y));
		msb = vec<L, uint, Q>(Value64 >> static_cast<detail::uint64>(32));
		lsb = vec<L, uint, Q>(Value64);
	}

	// imulExtended
	GLM_FUNC_QUALIFIER void imulExtended(int x, int y, int& msb, int& lsb)
	{
		detail::int64 Value64 = static_cast<detail::int64>(x) * static_cast<detail::int64>(y);
		msb = static_cast<int>(Value64 >> static_cast<detail::int64>(32));
		lsb = static_cast<int>(Value64);
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER void imulExtended(vec<L, int, Q> const& x, vec<L, int, Q> const& y, vec<L, int, Q>& msb, vec<L, int, Q>& lsb)
	{
		vec<L, detail::int64, Q> Value64(vec<L, detail::int64, Q>(x) * vec<L, detail::int64, Q>(y));
		lsb = vec<L, int, Q>(Value64 & static_cast<detail::int64>(0xFFFFFFFF));
		msb = vec<L, int, Q>((Value64 >> static_cast<detail::int64>(32)) & static_cast<detail::int64>(0xFFFFFFFF));
	}

	// bitfieldExtract
	template<typename genIUType>
	GLM_FUNC_QUALIFIER genIUType bitfieldExtract(genIUType Value, int Offset, int Bits)
	{
		return bitfieldExtract(vec<1, genIUType>(Value), Offset, Bits).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> bitfieldExtract(vec<L, T, Q> const& Value, int Offset, int Bits)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_integer, "'bitfieldExtract' only accept integer inputs");

		return (Value >> static_cast<T>(Offset)) & static_cast<T>(detail::mask(Bits));
	}

	// bitfieldInsert
	template<typename genIUType>
	GLM_FUNC_QUALIFIER genIUType bitfieldInsert(genIUType const& Base, genIUType const& Insert, int Offset, int Bits)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldInsert' only accept integer values");

		return bitfieldInsert(vec<1, genIUType>(Base), vec<1, genIUType>(Insert), Offset, Bits).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> bitfieldInsert(vec<L, T, Q> const& Base, vec<L, T, Q> const& Insert, int Offset, int Bits)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_integer, "'bitfieldInsert' only accept integer values");

		T const Mask = static_cast<T>(detail::mask(Bits) << Offset);
		return (Base & ~Mask) | ((Insert << static_cast<T>(Offset)) & Mask);
	}

	// bitfieldReverse
	template<typename genIUType>
	GLM_FUNC_QUALIFIER genIUType bitfieldReverse(genIUType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldReverse' only accept integer values");

		return bitfieldReverse(glm::vec<1, genIUType, glm::defaultp>(x)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> bitfieldReverse(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_integer, "'bitfieldReverse' only accept integer values");

		vec<L, T, Q> x(v);
		x = detail::compute_bitfieldReverseStep<L, T, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>=  2>::call(x, static_cast<T>(0x5555555555555555ull), static_cast<T>( 1));
		x = detail::compute_bitfieldReverseStep<L, T, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>=  4>::call(x, static_cast<T>(0x3333333333333333ull), static_cast<T>( 2));
		x = detail::compute_bitfieldReverseStep<L, T, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>=  8>::call(x, static_cast<T>(0x0F0F0F0F0F0F0F0Full), static_cast<T>( 4));
		x = detail::compute_bitfieldReverseStep<L, T, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>= 16>::call(x, static_cast<T>(0x00FF00FF00FF00FFull), static_cast<T>( 8));
		x = detail::compute_bitfieldReverseStep<L, T, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>= 32>::call(x, static_cast<T>(0x0000FFFF0000FFFFull), static_cast<T>(16));
		x = detail::compute_bitfieldReverseStep<L, T, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>= 64>::call(x, static_cast<T>(0x00000000FFFFFFFFull), static_cast<T>(32));
		return x;
	}

	// bitCount
	template<typename genIUType>
	GLM_FUNC_QUALIFIER int bitCount(genIUType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitCount' only accept integer values");

		return bitCount(glm::vec<1, genIUType, glm::defaultp>(x)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> bitCount(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_integer, "'bitCount' only accept integer values");

#		if GLM_COMPILER & GLM_COMPILER_VC
#			pragma warning(push)
#			pragma warning(disable : 4310) //cast truncates constant value
#		endif

		vec<L, typename detail::make_unsigned<T>::type, Q> x(*reinterpret_cast<vec<L, typename detail::make_unsigned<T>::type, Q> const *>(&v));
		x = detail::compute_bitfieldBitCountStep<L, typename detail::make_unsigned<T>::type, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>=  2>::call(x, typename detail::make_unsigned<T>::type(0x5555555555555555ull), typename detail::make_unsigned<T>::type( 1));
		x = detail::compute_bitfieldBitCountStep<L, typename detail::make_unsigned<T>::type, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>=  4>::call(x, typename detail::make_unsigned<T>::type(0x3333333333333333ull), typename detail::make_unsigned<T>::type( 2));
		x = detail::compute_bitfieldBitCountStep<L, typename detail::make_unsigned<T>::type, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>=  8>::call(x, typename detail::make_unsigned<T>::type(0x0F0F0F0F0F0F0F0Full), typename detail::make_unsigned<T>::type( 4));
		x = detail::compute_bitfieldBitCountStep<L, typename detail::make_unsigned<T>::type, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>= 16>::call(x, typename detail::make_unsigned<T>::type(0x00FF00FF00FF00FFull), typename detail::make_unsigned<T>::type( 8));
		x = detail::compute_bitfieldBitCountStep<L, typename detail::make_unsigned<T>::type, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>= 32>::call(x, typename detail::make_unsigned<T>::type(0x0000FFFF0000FFFFull), typename detail::make_unsigned<T>::type(16));
		x = detail::compute_bitfieldBitCountStep<L, typename detail::make_unsigned<T>::type, Q, detail::is_aligned<Q>::value, sizeof(T) * 8>= 64>::call(x, typename detail::make_unsigned<T>::type(0x00000000FFFFFFFFull), typename detail::make_unsigned<T>::type(32));
		return vec<L, int, Q>(x);

#		if GLM_COMPILER & GLM_COMPILER_VC
#			pragma warning(pop)
#		endif
	}

	// findLSB
	template<typename genIUType>
	GLM_FUNC_QUALIFIER int findLSB(genIUType Value)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findLSB' only accept integer values");

		return detail::compute_findLSB<genIUType, sizeof(genIUType) * 8>::call(Value);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> findLSB(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_integer, "'findLSB' only accept integer values");

		return detail::functor1<vec, L, int, T, Q>::call(findLSB, x);
	}

	// findMSB
	template<typename genIUType>
	GLM_FUNC_QUALIFIER int findMSB(genIUType v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findMSB' only accept integer values");

		return findMSB(vec<1, genIUType>(v)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> findMSB(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_integer, "'findMSB' only accept integer values");

		return detail::compute_findMSB_vec<L, T, Q, sizeof(T) * 8>::call(v);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_integer_simd.inl"
#endif

// mat2x2 .inl file

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0), col_type(0, 1)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0);
				this->value[1] = col_type(0, 1);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<2, 2, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{m[0], m[1]}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(T scalar)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(scalar, 0), col_type(0, scalar)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(scalar, 0);
			this->value[1] = col_type(0, scalar);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat
	(
		T const& x0, T const& y0,
		T const& x1, T const& y1
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0), col_type(x1, y1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0);
			this->value[1] = col_type(x1, y1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(col_type const& v0, col_type const& v1)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{v0, v1}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<typename X1, typename Y1, typename X2, typename Y2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat
	(
		X1 const& x1, Y1 const& y1,
		X2 const& x2, Y2 const& y2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(static_cast<T>(x1), value_type(y1)), col_type(static_cast<T>(x2), value_type(y2)) }
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(static_cast<T>(x1), value_type(y1));
			this->value[1] = col_type(static_cast<T>(x2), value_type(y2));
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(vec<2, V1, Q> const& v1, vec<2, V2, Q> const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
#		endif
	}

	// -- mat2x2 matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<2, 2, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<2, 2, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 2, T, Q>::col_type& mat<2, 2, T, Q>::operator[](typename mat<2, 2, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<2, 2, T, Q>::col_type const& mat<2, 2, T, Q>::operator[](typename mat<2, 2, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator=(mat<2, 2, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator+=(U scalar)
	{
		this->value[0] += scalar;
		this->value[1] += scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator+=(mat<2, 2, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator-=(U scalar)
	{
		this->value[0] -= scalar;
		this->value[1] -= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator-=(mat<2, 2, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator*=(U scalar)
	{
		this->value[0] *= scalar;
		this->value[1] *= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator*=(mat<2, 2, U, Q> const& m)
	{
		return (*this = *this * m);
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator/=(U scalar)
	{
		this->value[0] /= scalar;
		this->value[1] /= scalar;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator/=(mat<2, 2, U, Q> const& m)
	{
		return *this *= inverse(m);
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q>& mat<2, 2, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> mat<2, 2, T, Q>::operator++(int)
	{
		mat<2, 2, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> mat<2, 2, T, Q>::operator--(int)
	{
		mat<2, 2, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator+(mat<2, 2, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator-(mat<2, 2, T, Q> const& m)
	{
		return mat<2, 2, T, Q>(
			-m[0],
			-m[1]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator+(mat<2, 2, T, Q> const& m, T scalar)
	{
		return mat<2, 2, T, Q>(
			m[0] + scalar,
			m[1] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator+(T scalar, mat<2, 2, T, Q> const& m)
	{
		return mat<2, 2, T, Q>(
			m[0] + scalar,
			m[1] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator+(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return mat<2, 2, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator-(mat<2, 2, T, Q> const& m, T scalar)
	{
		return mat<2, 2, T, Q>(
			m[0] - scalar,
			m[1] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator-(T scalar, mat<2, 2, T, Q> const& m)
	{
		return mat<2, 2, T, Q>(
			scalar - m[0],
			scalar - m[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator-(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return mat<2, 2, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator*(mat<2, 2, T, Q> const& m, T scalar)
	{
		return mat<2, 2, T, Q>(
			m[0] * scalar,
			m[1] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator*(T scalar, mat<2, 2, T, Q> const& m)
	{
		return mat<2, 2, T, Q>(
			m[0] * scalar,
			m[1] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 2, T, Q>::col_type operator*
	(
		mat<2, 2, T, Q> const& m,
		typename mat<2, 2, T, Q>::row_type const& v
	)
	{
		return vec<2, T, Q>(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 2, T, Q>::row_type operator*
	(
		typename mat<2, 2, T, Q>::col_type const& v,
		mat<2, 2, T, Q> const& m
	)
	{
		return vec<2, T, Q>(
			v.x * m[0][0] + v.y * m[0][1],
			v.x * m[1][0] + v.y * m[1][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator*(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return mat<2, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 2, T, Q> operator*(mat<2, 2, T, Q> const& m1, mat<3, 2, T, Q> const& m2)
	{
		return mat<3, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 2, T, Q> operator*(mat<2, 2, T, Q> const& m1, mat<4, 2, T, Q> const& m2)
	{
		return mat<4, 2, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator/(mat<2, 2, T, Q> const& m, T scalar)
	{
		return mat<2, 2, T, Q>(
			m[0] / scalar,
			m[1] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator/(T scalar, mat<2, 2, T, Q> const& m)
	{
		return mat<2, 2, T, Q>(
			scalar / m[0],
			scalar / m[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 2, T, Q>::col_type operator/(mat<2, 2, T, Q> const& m, typename mat<2, 2, T, Q>::row_type const& v)
	{
		return inverse(m) * v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<2, 2, T, Q>::row_type operator/(typename mat<2, 2, T, Q>::col_type const& v, mat<2, 2, T, Q> const& m)
	{
		return v *  inverse(m);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, T, Q> operator/(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		mat<2, 2, T, Q> m1_copy(m1);
		return m1_copy /= m2;
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<2, 2, T, Q> const& m1, mat<2, 2, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}
} //namespace glm

#endif

// mat3x3 .inl file

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0, 0), col_type(0, 1, 0), col_type(0, 0, 1)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
			this->value[0] = col_type(1, 0, 0);
				this->value[1] = col_type(0, 1, 0);
				this->value[2] = col_type(0, 0, 1);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<3, 3, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(T s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0, 0), col_type(0, s, 0), col_type(0, 0, s)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0, 0);
			this->value[1] = col_type(0, s, 0);
			this->value[2] = col_type(0, 0, s);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat
	(
		T x0, T y0, T z0,
		T x1, T y1, T z1,
		T x2, T y2, T z2
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x0, y0, z0), col_type(x1, y1, z1), col_type(x2, y2, z2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0);
			this->value[1] = col_type(x1, y1, z1);
			this->value[2] = col_type(x2, y2, z2);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(col_type const& v0, col_type const& v1, col_type const& v2)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v0);
			this->value[1] = col_type(v1);
			this->value[2] = col_type(v2);
#		endif
	}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<
		typename X1, typename Y1, typename Z1,
		typename X2, typename Y2, typename Z2,
		typename X3, typename Y3, typename Z3>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat
	(
		X1 x1, Y1 y1, Z1 z1,
		X2 x2, Y2 y2, Z2 z2,
		X3 x3, Y3 y3, Z3 z3
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x1, y1, z1), col_type(x2, y2, z2), col_type(x3, y3, z3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x1, y1, z1);
			this->value[1] = col_type(x2, y2, z2);
			this->value[2] = col_type(x3, y3, z3);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2, typename V3>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(vec<3, V1, Q> const& v1, vec<3, V2, Q> const& v2, vec<3, V3, Q> const& v3)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v1), col_type(v2), col_type(v3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
			this->value[2] = col_type(v3);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<3, 3, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<4, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 3, T, Q>::col_type & mat<3, 3, T, Q>::operator[](typename mat<3, 3, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<3, 3, T, Q>::col_type const& mat<3, 3, T, Q>::operator[](typename mat<3, 3, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary updatable operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator=(mat<3, 3, U, Q> const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator+=(mat<3, 3, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator-=(mat<3, 3, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator*=(mat<3, 3, U, Q> const& m)
	{
		return (*this = *this * m);
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator/=(mat<3, 3, U, Q> const& m)
	{
		return *this *= inverse(m);
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> & mat<3, 3, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> mat<3, 3, T, Q>::operator++(int)
	{
		mat<3, 3, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> mat<3, 3, T, Q>::operator--(int)
	{
		mat<3, 3, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator+(mat<3, 3, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator-(mat<3, 3, T, Q> const& m)
	{
		return mat<3, 3, T, Q>(
			-m[0],
			-m[1],
			-m[2]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator+(mat<3, 3, T, Q> const& m, T scalar)
	{
		return mat<3, 3, T, Q>(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator+(T scalar, mat<3, 3, T, Q> const& m)
	{
		return mat<3, 3, T, Q>(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator+(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		return mat<3, 3, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator-(mat<3, 3, T, Q> const& m, T scalar)
	{
		return mat<3, 3, T, Q>(
			m[0] - scalar,
			m[1] - scalar,
			m[2] - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator-(T scalar, mat<3, 3, T, Q> const& m)
	{
		return mat<3, 3, T, Q>(
			scalar - m[0],
			scalar - m[1],
			scalar - m[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator-(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		return mat<3, 3, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator*(mat<3, 3, T, Q> const& m, T scalar)
	{
		return mat<3, 3, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator*(T scalar, mat<3, 3, T, Q> const& m)
	{
		return mat<3, 3, T, Q>(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 3, T, Q>::col_type operator*(mat<3, 3, T, Q> const& m, typename mat<3, 3, T, Q>::row_type const& v)
	{
		return typename mat<3, 3, T, Q>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 3, T, Q>::row_type operator*(typename mat<3, 3, T, Q>::col_type const& v, mat<3, 3, T, Q> const& m)
	{
		return typename mat<3, 3, T, Q>::row_type(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator*(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		T const SrcA00 = m1[0][0];
		T const SrcA01 = m1[0][1];
		T const SrcA02 = m1[0][2];
		T const SrcA10 = m1[1][0];
		T const SrcA11 = m1[1][1];
		T const SrcA12 = m1[1][2];
		T const SrcA20 = m1[2][0];
		T const SrcA21 = m1[2][1];
		T const SrcA22 = m1[2][2];

		T const SrcB00 = m2[0][0];
		T const SrcB01 = m2[0][1];
		T const SrcB02 = m2[0][2];
		T const SrcB10 = m2[1][0];
		T const SrcB11 = m2[1][1];
		T const SrcB12 = m2[1][2];
		T const SrcB20 = m2[2][0];
		T const SrcB21 = m2[2][1];
		T const SrcB22 = m2[2][2];

		mat<3, 3, T, Q> Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 3, T, Q> operator*(mat<3, 3, T, Q> const& m1, mat<2, 3, T, Q> const& m2)
	{
		return mat<2, 3, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 3, T, Q> operator*(mat<3, 3, T, Q> const& m1, mat<4, 3, T, Q> const& m2)
	{
		return mat<4, 3, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2],
			m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator/(mat<3, 3, T, Q> const& m,	T scalar)
	{
		return mat<3, 3, T, Q>(
			m[0] / scalar,
			m[1] / scalar,
			m[2] / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator/(T scalar, mat<3, 3, T, Q> const& m)
	{
		return mat<3, 3, T, Q>(
			scalar / m[0],
			scalar / m[1],
			scalar / m[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 3, T, Q>::col_type operator/(mat<3, 3, T, Q> const& m, typename mat<3, 3, T, Q>::row_type const& v)
	{
		return  inverse(m) * v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<3, 3, T, Q>::row_type operator/(typename mat<3, 3, T, Q>::col_type const& v, mat<3, 3, T, Q> const& m)
	{
		return v * inverse(m);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> operator/(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		mat<3, 3, T, Q> m1_copy(m1);
		return m1_copy /= m2;
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<3, 3, T, Q> const& m1, mat<3, 3, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}
} //namespace glm

#endif

// mat4x4 .inl file

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat()
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALIZER_LIST
				: value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
#			endif
		{
#			if GLM_CONFIG_CTOR_INIT == GLM_CTOR_INITIALISATION
				this->value[0] = col_type(1, 0, 0, 0);
				this->value[1] = col_type(0, 1, 0, 0);
				this->value[2] = col_type(0, 0, 1, 0);
				this->value[3] = col_type(0, 0, 0, 1);
#			endif
		}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<4, 4, T, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = m[3];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(T const& s)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(s, 0, 0, 0), col_type(0, s, 0, 0), col_type(0, 0, s, 0), col_type(0, 0, 0, s)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(s, 0, 0, 0);
			this->value[1] = col_type(0, s, 0, 0);
			this->value[2] = col_type(0, 0, s, 0);
			this->value[3] = col_type(0, 0, 0, s);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat
	(
		T const& x0, T const& y0, T const& z0, T const& w0,
		T const& x1, T const& y1, T const& z1, T const& w1,
		T const& x2, T const& y2, T const& z2, T const& w2,
		T const& x3, T const& y3, T const& z3, T const& w3
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{
				col_type(x0, y0, z0, w0),
				col_type(x1, y1, z1, w1),
				col_type(x2, y2, z2, w2),
				col_type(x3, y3, z3, w3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x0, y0, z0, w0);
			this->value[1] = col_type(x1, y1, z1, w1);
			this->value[2] = col_type(x2, y2, z2, w2);
			this->value[3] = col_type(x3, y3, z3, w3);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(col_type const& v0, col_type const& v1, col_type const& v2, col_type const& v3)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = v0;
			this->value[1] = v1;
			this->value[2] = v2;
			this->value[3] = v3;
#		endif
	}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<4, 4, U, P> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
			this->value[2] = col_type(m[2]);
			this->value[3] = col_type(m[3]);
#		endif
	}

	// -- Conversions --

	template<typename T, qualifier Q>
	template<
		typename X1, typename Y1, typename Z1, typename W1,
		typename X2, typename Y2, typename Z2, typename W2,
		typename X3, typename Y3, typename Z3, typename W3,
		typename X4, typename Y4, typename Z4, typename W4>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat
	(
		X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,
		X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2,
		X3 const& x3, Y3 const& y3, Z3 const& z3, W3 const& w3,
		X4 const& x4, Y4 const& y4, Z4 const& z4, W4 const& w4
	)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(x1, y1, z1, w1), col_type(x2, y2, z2, w2), col_type(x3, y3, z3, w3), col_type(x4, y4, z4, w4)}
#		endif
	{
		GLM_STATIC_ASSERT(std::numeric_limits<X1>::is_iec559 || std::numeric_limits<X1>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 1st parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Y1>::is_iec559 || std::numeric_limits<Y1>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 2nd parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Z1>::is_iec559 || std::numeric_limits<Z1>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 3rd parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<W1>::is_iec559 || std::numeric_limits<W1>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 4th parameter type invalid.");

		GLM_STATIC_ASSERT(std::numeric_limits<X2>::is_iec559 || std::numeric_limits<X2>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 5th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Y2>::is_iec559 || std::numeric_limits<Y2>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 6th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Z2>::is_iec559 || std::numeric_limits<Z2>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 7th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<W2>::is_iec559 || std::numeric_limits<W2>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 8th parameter type invalid.");

		GLM_STATIC_ASSERT(std::numeric_limits<X3>::is_iec559 || std::numeric_limits<X3>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 9th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Y3>::is_iec559 || std::numeric_limits<Y3>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 10th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Z3>::is_iec559 || std::numeric_limits<Z3>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 11th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<W3>::is_iec559 || std::numeric_limits<W3>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 12th parameter type invalid.");

		GLM_STATIC_ASSERT(std::numeric_limits<X4>::is_iec559 || std::numeric_limits<X4>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 13th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Y4>::is_iec559 || std::numeric_limits<Y4>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 14th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<Z4>::is_iec559 || std::numeric_limits<Z4>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 15th parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<W4>::is_iec559 || std::numeric_limits<W4>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 16th parameter type invalid.");

#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(x1, y1, z1, w1);
			this->value[1] = col_type(x2, y2, z2, w2);
			this->value[2] = col_type(x3, y3, z3, w3);
			this->value[3] = col_type(x4, y4, z4, w4);
#		endif
	}

	template<typename T, qualifier Q>
	template<typename V1, typename V2, typename V3, typename V4>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(vec<4, V1, Q> const& v1, vec<4, V2, Q> const& v2, vec<4, V3, Q> const& v3, vec<4, V4, Q> const& v4)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(v1), col_type(v2), col_type(v3), col_type(v4)}
#		endif
	{
		GLM_STATIC_ASSERT(std::numeric_limits<V1>::is_iec559 || std::numeric_limits<V1>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 1st parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<V2>::is_iec559 || std::numeric_limits<V2>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 2nd parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<V3>::is_iec559 || std::numeric_limits<V3>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 3rd parameter type invalid.");
		GLM_STATIC_ASSERT(std::numeric_limits<V4>::is_iec559 || std::numeric_limits<V4>::is_integer || GLM_CONFIG_UNRESTRICTED_GENTYPE, "*mat4x4 constructor only takes float and integer types, 4th parameter type invalid.");

#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
			this->value[2] = col_type(v3);
			this->value[3] = col_type(v4);
#		endif
	}

	// -- Matrix conversions --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<2, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
			this->value[2] = col_type(0, 0, 1, 0);
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<3, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 0);
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<2, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(0, 0, 1, 0);
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<3, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(m[2], 1, 0), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
			this->value[2] = col_type(m[2], 1, 0);
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<2, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = col_type(0, 0, 1, 0);
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<4, 2, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0, 0);
			this->value[1] = col_type(m[1], 0, 0);
			this->value[2] = col_type(0, 0, 1, 0);
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<3, 4, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0, 0, 0, 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = col_type(0, 0, 0, 1);
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<4, 4, T, Q>::mat(mat<4, 3, T, Q> const& m)
#		if GLM_HAS_INITIALIZER_LISTS
			: value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0), col_type(m[3], 1)}
#		endif
	{
#		if !GLM_HAS_INITIALIZER_LISTS
			this->value[0] = col_type(m[0], 0);
			this->value[1] = col_type(m[1], 0);
			this->value[2] = col_type(m[2], 0);
			this->value[3] = col_type(m[3], 1);
#		endif
	}

	// -- Accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 4, T, Q>::col_type & mat<4, 4, T, Q>::operator[](typename mat<4, 4, T, Q>::length_type i)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<4, 4, T, Q>::col_type const& mat<4, 4, T, Q>::operator[](typename mat<4, 4, T, Q>::length_type i) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	// -- Unary arithmetic operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q>& mat<4, 4, T, Q>::operator=(mat<4, 4, U, Q> const& m)
	{
		//memcpy could be faster
		//memcpy(&this->value, &m.value, 16 * sizeof(valType));
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q>& mat<4, 4, T, Q>::operator+=(U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		this->value[3] += s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q>& mat<4, 4, T, Q>::operator+=(mat<4, 4, U, Q> const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		this->value[3] += m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator-=(U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		this->value[3] -= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator-=(mat<4, 4, U, Q> const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		this->value[3] -= m[3];
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator*=(U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		this->value[3] *= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator*=(mat<4, 4, U, Q> const& m)
	{
		return (*this = *this * m);
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator/=(U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		this->value[3] /= s;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator/=(mat<4, 4, U, Q> const& m)
	{
		return *this *= inverse(m);
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		++this->value[3];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> & mat<4, 4, T, Q>::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		--this->value[3];
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> mat<4, 4, T, Q>::operator++(int)
	{
		mat<4, 4, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> mat<4, 4, T, Q>::operator--(int)
	{
		mat<4, 4, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary constant operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator+(mat<4, 4, T, Q> const& m)
	{
		return m;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator-(mat<4, 4, T, Q> const& m)
	{
		return mat<4, 4, T, Q>(
			-m[0],
			-m[1],
			-m[2],
			-m[3]);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator+(mat<4, 4, T, Q> const& m, T const& s)
	{
		return mat<4, 4, T, Q>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator+(T const& s, mat<4, 4, T, Q> const& m)
	{
		return mat<4, 4, T, Q>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator+(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		return mat<4, 4, T, Q>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator-(mat<4, 4, T, Q> const& m, T const& s)
	{
		return mat<4, 4, T, Q>(
			m[0] - s,
			m[1] - s,
			m[2] - s,
			m[3] - s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator-(T const& s, mat<4, 4, T, Q> const& m)
	{
		return mat<4, 4, T, Q>(
			s - m[0],
			s - m[1],
			s - m[2],
			s - m[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator-(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		return mat<4, 4, T, Q>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator*(mat<4, 4, T, Q> const& m, T const  & s)
	{
		return mat<4, 4, T, Q>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator*(T const& s, mat<4, 4, T, Q> const& m)
	{
		return mat<4, 4, T, Q>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 4, T, Q>::col_type operator*
	(
		mat<4, 4, T, Q> const& m,
		typename mat<4, 4, T, Q>::row_type const& v
	)
	{
/*
		__m128 v0 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 v1 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 v2 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 v3 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(m[0].data, v0);
		__m128 m1 = _mm_mul_ps(m[1].data, v1);
		__m128 a0 = _mm_add_ps(m0, m1);

		__m128 m2 = _mm_mul_ps(m[2].data, v2);
		__m128 m3 = _mm_mul_ps(m[3].data, v3);
		__m128 a1 = _mm_add_ps(m2, m3);

		__m128 a2 = _mm_add_ps(a0, a1);

		return typename mat<4, 4, T, Q>::col_type(a2);
*/

		typename mat<4, 4, T, Q>::col_type const Mov0(v[0]);
		typename mat<4, 4, T, Q>::col_type const Mov1(v[1]);
		typename mat<4, 4, T, Q>::col_type const Mul0 = m[0] * Mov0;
		typename mat<4, 4, T, Q>::col_type const Mul1 = m[1] * Mov1;
		typename mat<4, 4, T, Q>::col_type const Add0 = Mul0 + Mul1;
		typename mat<4, 4, T, Q>::col_type const Mov2(v[2]);
		typename mat<4, 4, T, Q>::col_type const Mov3(v[3]);
		typename mat<4, 4, T, Q>::col_type const Mul2 = m[2] * Mov2;
		typename mat<4, 4, T, Q>::col_type const Mul3 = m[3] * Mov3;
		typename mat<4, 4, T, Q>::col_type const Add1 = Mul2 + Mul3;
		typename mat<4, 4, T, Q>::col_type const Add2 = Add0 + Add1;
		return Add2;

/*
		return typename mat<4, 4, T, Q>::col_type(
			m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
			m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
			m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
			m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]);
*/
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 4, T, Q>::row_type operator*
	(
		typename mat<4, 4, T, Q>::col_type const& v,
		mat<4, 4, T, Q> const& m
	)
	{
		return typename mat<4, 4, T, Q>::row_type(
			m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
			m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
			m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
			m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, T, Q> operator*(mat<4, 4, T, Q> const& m1, mat<2, 4, T, Q> const& m2)
	{
		return mat<2, 4, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, T, Q> operator*(mat<4, 4, T, Q> const& m1, mat<3, 4, T, Q> const& m2)
	{
		return mat<3, 4, T, Q>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
			m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator*(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		typename mat<4, 4, T, Q>::col_type const SrcA0 = m1[0];
		typename mat<4, 4, T, Q>::col_type const SrcA1 = m1[1];
		typename mat<4, 4, T, Q>::col_type const SrcA2 = m1[2];
		typename mat<4, 4, T, Q>::col_type const SrcA3 = m1[3];

		typename mat<4, 4, T, Q>::col_type const SrcB0 = m2[0];
		typename mat<4, 4, T, Q>::col_type const SrcB1 = m2[1];
		typename mat<4, 4, T, Q>::col_type const SrcB2 = m2[2];
		typename mat<4, 4, T, Q>::col_type const SrcB3 = m2[3];

		mat<4, 4, T, Q> Result;
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator/(mat<4, 4, T, Q> const& m, T const& s)
	{
		return mat<4, 4, T, Q>(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator/(T const& s,	mat<4, 4, T, Q> const& m)
	{
		return mat<4, 4, T, Q>(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 4, T, Q>::col_type operator/(mat<4, 4, T, Q> const& m, typename mat<4, 4, T, Q>::row_type const& v)
	{
		return inverse(m) * v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<4, 4, T, Q>::row_type operator/(typename mat<4, 4, T, Q>::col_type const& v, mat<4, 4, T, Q> const& m)
	{
		return v * inverse(m);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> operator/(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		mat<4, 4, T, Q> m1_copy(m1);
		return m1_copy /= m2;
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(mat<4, 4, T, Q> const& m1, mat<4, 4, T, Q> const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/type_mat4x4_simd.inl"
#endif

#endif//GLM_EXTERNAL_TEMPLATE

// exponential .inl file

namespace glm{
namespace detail
{
#	if GLM_HAS_CXX11_STL
		using std::log2;
#	else
		template<typename genType>
		genType log2(genType Value)
		{
			return std::log(Value) * static_cast<genType>(1.4426950408889634073599246810019);
		}
#	endif

	template<length_t L, typename T, qualifier Q, bool isFloat, bool Aligned>
	struct compute_log2
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'log2' only accept floating-point inputs. Include <glm/gtc/integer.hpp> for integer inputs.");

			return detail::functor1<vec, L, T, T, Q>::call(log2, v);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_sqrt
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return detail::functor1<vec, L, T, T, Q>::call(std::sqrt, x);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_inversesqrt
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return static_cast<T>(1) / sqrt(x);
		}
	};

	template<length_t L, bool Aligned>
	struct compute_inversesqrt<L, float, lowp, Aligned>
	{
		GLM_FUNC_QUALIFIER static vec<L, float, lowp> call(vec<L, float, lowp> const& x)
		{
			vec<L, float, lowp> tmp(x);
			vec<L, float, lowp> xhalf(tmp * 0.5f);
			vec<L, uint, lowp>* p = reinterpret_cast<vec<L, uint, lowp>*>(const_cast<vec<L, float, lowp>*>(&x));
			vec<L, uint, lowp> i = vec<L, uint, lowp>(0x5f375a86) - (*p >> vec<L, uint, lowp>(1));
			vec<L, float, lowp>* ptmp = reinterpret_cast<vec<L, float, lowp>*>(&i);
			tmp = *ptmp;
			tmp = tmp * (1.5f - xhalf * tmp * tmp);
			return tmp;
		}
	};
}//namespace detail

	// pow
	using std::pow;
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> pow(vec<L, T, Q> const& base, vec<L, T, Q> const& exponent)
	{
		return detail::functor2<vec, L, T, Q>::call(pow, base, exponent);
	}

	// exp
	using std::exp;
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> exp(vec<L, T, Q> const& x)
	{
		return detail::functor1<vec, L, T, T, Q>::call(exp, x);
	}

	// log
	using std::log;
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> log(vec<L, T, Q> const& x)
	{
		return detail::functor1<vec, L, T, T, Q>::call(log, x);
	}

#   if GLM_HAS_CXX11_STL
    using std::exp2;
#   else
	//exp2, ln2 = 0.69314718055994530941723212145818f
	template<typename genType>
	GLM_FUNC_QUALIFIER genType exp2(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'exp2' only accept floating-point inputs");

		return std::exp(static_cast<genType>(0.69314718055994530941723212145818) * x);
	}
#   endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> exp2(vec<L, T, Q> const& x)
	{
		return detail::functor1<vec, L, T, T, Q>::call(exp2, x);
	}

	// log2, ln2 = 0.69314718055994530941723212145818f
	template<typename genType>
	GLM_FUNC_QUALIFIER genType log2(genType x)
	{
		return log2(vec<1, genType>(x)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> log2(vec<L, T, Q> const& x)
	{
		return detail::compute_log2<L, T, Q, std::numeric_limits<T>::is_iec559, detail::is_aligned<Q>::value>::call(x);
	}

	// sqrt
	using std::sqrt;
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> sqrt(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'sqrt' only accept floating-point inputs");
		return detail::compute_sqrt<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	// inversesqrt
	template<typename genType>
	GLM_FUNC_QUALIFIER genType inversesqrt(genType x)
	{
		return static_cast<genType>(1) / sqrt(x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> inversesqrt(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'inversesqrt' only accept floating-point inputs");
		return detail::compute_inversesqrt<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_exponential_simd.inl"
#endif


namespace glm{
namespace detail
{
	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_length
	{
		GLM_FUNC_QUALIFIER static T call(vec<L, T, Q> const& v)
		{
			return sqrt(dot(v, v));
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_distance
	{
		GLM_FUNC_QUALIFIER static T call(vec<L, T, Q> const& p0, vec<L, T, Q> const& p1)
		{
			return length(p1 - p0);
		}
	};

	template<typename V, typename T, bool Aligned>
	struct compute_dot{};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_dot<vec<1, T, Q>, T, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(vec<1, T, Q> const& a, vec<1, T, Q> const& b)
		{
			return a.x * b.x;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_dot<vec<2, T, Q>, T, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(vec<2, T, Q> const& a, vec<2, T, Q> const& b)
		{
			vec<2, T, Q> tmp(a * b);
			return tmp.x + tmp.y;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_dot<vec<3, T, Q>, T, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(vec<3, T, Q> const& a, vec<3, T, Q> const& b)
		{
			vec<3, T, Q> tmp(a * b);
			return tmp.x + tmp.y + tmp.z;
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_dot<vec<4, T, Q>, T, Aligned>
	{
		GLM_FUNC_QUALIFIER static T call(vec<4, T, Q> const& a, vec<4, T, Q> const& b)
		{
			vec<4, T, Q> tmp(a * b);
			return (tmp.x + tmp.y) + (tmp.z + tmp.w);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_cross
	{
		GLM_FUNC_QUALIFIER static vec<3, T, Q> call(vec<3, T, Q> const& x, vec<3, T, Q> const& y)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'cross' accepts only floating-point inputs");

			return vec<3, T, Q>(
				x.y * y.z - y.y * x.z,
				x.z * y.x - y.z * x.x,
				x.x * y.y - y.x * x.y);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_normalize
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

			return v * inversesqrt(dot(v, v));
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_faceforward
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& N, vec<L, T, Q> const& I, vec<L, T, Q> const& Nref)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

			return dot(Nref, I) < static_cast<T>(0) ? N : -N;
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_reflect
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& I, vec<L, T, Q> const& N)
		{
			return I - N * dot(N, I) * static_cast<T>(2);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_refract
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& I, vec<L, T, Q> const& N, T eta)
		{
			T const dotValue(dot(N, I));
			T const k(static_cast<T>(1) - eta * eta * (static_cast<T>(1) - dotValue * dotValue));
			vec<L, T, Q> const Result =
                (k >= static_cast<T>(0)) ? (eta * I - (eta * dotValue + std::sqrt(k)) * N) : vec<L, T, Q>(0);
			return Result;
		}
	};
}//namespace detail

	// length
	template<typename genType>
	GLM_FUNC_QUALIFIER genType length(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'length' accepts only floating-point inputs");

		return abs(x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T length(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");

		return detail::compute_length<L, T, Q, detail::is_aligned<Q>::value>::call(v);
	}

	// distance
	template<typename genType>
	GLM_FUNC_QUALIFIER genType distance(genType const& p0, genType const& p1)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'distance' accepts only floating-point inputs");

		return length(p1 - p0);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T distance(vec<L, T, Q> const& p0, vec<L, T, Q> const& p1)
	{
		return detail::compute_distance<L, T, Q, detail::is_aligned<Q>::value>::call(p0, p1);
	}

	// dot
	template<typename T>
	GLM_FUNC_QUALIFIER T dot(T x, T y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
		return x * y;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T dot(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
		return detail::compute_dot<vec<L, T, Q>, T, detail::is_aligned<Q>::value>::call(x, y);
	}

	// cross
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> cross(vec<3, T, Q> const& x, vec<3, T, Q> const& y)
	{
		return detail::compute_cross<T, Q, detail::is_aligned<Q>::value>::call(x, y);
	}
/*
	// normalize
	template<typename genType>
	GLM_FUNC_QUALIFIER genType normalize(genType const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'normalize' accepts only floating-point inputs");

		return x < genType(0) ? genType(-1) : genType(1);
	}
*/
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> normalize(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

		return detail::compute_normalize<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	// faceforward
	template<typename genType>
	GLM_FUNC_QUALIFIER genType faceforward(genType const& N, genType const& I, genType const& Nref)
	{
		return dot(Nref, I) < static_cast<genType>(0) ? N : -N;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> faceforward(vec<L, T, Q> const& N, vec<L, T, Q> const& I, vec<L, T, Q> const& Nref)
	{
		return detail::compute_faceforward<L, T, Q, detail::is_aligned<Q>::value>::call(N, I, Nref);
	}

	// reflect
	template<typename genType>
	GLM_FUNC_QUALIFIER genType reflect(genType const& I, genType const& N)
	{
		return I - N * dot(N, I) * genType(2);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> reflect(vec<L, T, Q> const& I, vec<L, T, Q> const& N)
	{
		return detail::compute_reflect<L, T, Q, detail::is_aligned<Q>::value>::call(I, N);
	}

	// refract
	template<typename genType>
	GLM_FUNC_QUALIFIER genType refract(genType const& I, genType const& N, genType eta)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'refract' accepts only floating-point inputs");
		genType const dotValue(dot(N, I));
		genType const k(static_cast<genType>(1) - eta * eta * (static_cast<genType>(1) - dotValue * dotValue));
		return (eta * I - (eta * dotValue + sqrt(k)) * N) * static_cast<genType>(k >= static_cast<genType>(0));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> refract(vec<L, T, Q> const& I, vec<L, T, Q> const& N, T eta)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'refract' accepts only floating-point inputs");
		return detail::compute_refract<L, T, Q, detail::is_aligned<Q>::value>::call(I, N, eta);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_geometric_simd.inl"
#endif


#if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
#	include "_swizzle.hpp"
#elif GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
#	include "_swizzle_func.hpp"
#endif
#include <cstddef>

namespace glm
{
	template<typename T, qualifier Q>
	struct vec<1, T, Q>
	{
		// -- Implementation detail --

		typedef T value_type;
		typedef vec<1, T, Q> type;
		typedef vec<1, bool, Q> bool_type;

		// -- Data --

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic push
#				pragma GCC diagnostic ignored "-Wpedantic"
#			elif GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic push
#				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#				pragma clang diagnostic ignored "-Wnested-anon-types"
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(push)
#				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#			endif
#		endif

#		if GLM_CONFIG_XYZW_ONLY
			T x;
#		elif GLM_CONFIG_ANONYMOUS_STRUCT == GLM_ENABLE
			union
			{
				T x;
				T r;
				T s;

				typename detail::storage<1, T, detail::is_aligned<Q>::value>::type data;
/*
#				if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
					_GLM_SWIZZLE1_2_MEMBERS(T, Q, x)
					_GLM_SWIZZLE1_2_MEMBERS(T, Q, r)
					_GLM_SWIZZLE1_2_MEMBERS(T, Q, s)
					_GLM_SWIZZLE1_3_MEMBERS(T, Q, x)
					_GLM_SWIZZLE1_3_MEMBERS(T, Q, r)
					_GLM_SWIZZLE1_3_MEMBERS(T, Q, s)
					_GLM_SWIZZLE1_4_MEMBERS(T, Q, x)
					_GLM_SWIZZLE1_4_MEMBERS(T, Q, r)
					_GLM_SWIZZLE1_4_MEMBERS(T, Q, s)
#				endif
*/
			};
#		else
			union {T x, r, s;};
/*
#			if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
				GLM_SWIZZLE_GEN_VEC_FROM_VEC1(T, Q)
#			endif
*/
#		endif

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(pop)
#			endif
#		endif

		// -- Component accesses --

		/// Return the count of components of the vector
		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 1;}

		GLM_FUNC_DECL GLM_CONSTEXPR T & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR T const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR vec() GLM_DEFAULT;
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec const& v) GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, T, P> const& v);

		// -- Explicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(T scalar);

		// -- Conversion vector constructors --

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<2, U, P> const& v);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<3, U, P> const& v);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<4, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<1, U, P> const& v);

		// -- Swizzle constructors --
/*
#		if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
			template<int E0>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<1, T, Q, E0, -1,-2,-3> const& that)
			{
				*this = that();
			}
#		endif//GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
*/
		// -- Unary arithmetic operators --

		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator=(vec const& v) GLM_DEFAULT;

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator+=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator+=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator-=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator-=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator*=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator*=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator/=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator/=(vec<1, U, Q> const& v);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator++();
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator--();
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator++(int);
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator--(int);

		// -- Unary bit operators --

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator%=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator%=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator&=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator&=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator|=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator|=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator^=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator^=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator<<=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator<<=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator>>=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> & operator>>=(vec<1, U, Q> const& v);
	};

	// -- Unary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator+(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator-(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator*(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator*(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator*(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator/(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator/(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator/(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator%(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator%(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator%(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator&(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator&(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator&(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator|(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator|(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator|(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator^(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator^(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator^(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator<<(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator<<(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator<<(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator>>(vec<1, T, Q> const& v, T scalar);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator>>(T scalar, vec<1, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator>>(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, T, Q> operator~(vec<1, T, Q> const& v);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator!=(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2);

	template<qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, bool, Q> operator&&(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2);

	template<qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<1, bool, Q> operator||(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm
{
	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<1, T, Q> const& v)
			: x(v.x)
		{}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<1, T, P> const& v)
		: x(v.x)
	{}

	// -- Explicit basic constructors --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(T scalar)
		: x(scalar)
	{}

	// -- Conversion vector constructors --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<T>(v.x))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<2, U, P> const& v)
		: x(static_cast<T>(v.x))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<3, U, P> const& v)
		: x(static_cast<T>(v.x))
	{}

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<T>(v.x))
	{}

	// -- Component accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T & vec<1, T, Q>::operator[](typename vec<1, T, Q>::length_type)
	{
		return x;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T const& vec<1, T, Q>::operator[](typename vec<1, T, Q>::length_type) const
	{
		return x;
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator=(vec<1, T, Q> const& v)
		{
			this->x = v.x;
			return *this;
		}
#	endif

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator=(vec<1, U, Q> const& v)
	{
		this->x = static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator+=(vec<1, U, Q> const& v)
	{
		this->x += static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator-=(vec<1, U, Q> const& v)
	{
		this->x -= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator*=(vec<1, U, Q> const& v)
	{
		this->x *= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator/=(vec<1, U, Q> const& v)
	{
		this->x /= static_cast<T>(v.x);
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator++()
	{
		++this->x;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator--()
	{
		--this->x;
		return *this;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> vec<1, T, Q>::operator++(int)
	{
		vec<1, T, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> vec<1, T, Q>::operator--(int)
	{
		vec<1, T, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator%=(U scalar)
	{
		this->x %= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator%=(vec<1, U, Q> const& v)
	{
		this->x %= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator&=(U scalar)
	{
		this->x &= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator&=(vec<1, U, Q> const& v)
	{
		this->x &= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator|=(U scalar)
	{
		this->x |= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator|=(vec<1, U, Q> const& v)
	{
		this->x |= U(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator^=(U scalar)
	{
		this->x ^= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator^=(vec<1, U, Q> const& v)
	{
		this->x ^= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator<<=(U scalar)
	{
		this->x <<= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		this->x <<= static_cast<T>(v.x);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator>>=(U scalar)
	{
		this->x >>= static_cast<T>(scalar);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		this->x >>= static_cast<T>(v.x);
		return *this;
	}

	// -- Unary constant operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v)
	{
		return v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			-v.x);
	}

	// -- Binary arithmetic operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x + scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator+(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar + v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator+(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x + v2.x);
	}

	//operator-
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x - scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator-(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar - v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator-(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x - v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator*(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x * scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator*(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar * v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator*(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x * v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator/(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x / scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator/(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar / v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator/(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x / v2.x);
	}

	// -- Binary bit operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator%(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x % scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator%(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar % v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator%(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x % v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator&(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x & scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator&(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar & v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator&(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x & v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator|(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x | scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator|(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar | v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator|(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x | v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator^(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			v.x ^ scalar);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator^(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			scalar ^ v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator^(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			v1.x ^ v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator<<(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			static_cast<T>(v.x << scalar));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator<<(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			static_cast<T>(scalar << v.x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator<<(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			static_cast<T>(v1.x << v2.x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator>>(vec<1, T, Q> const& v, T scalar)
	{
		return vec<1, T, Q>(
			static_cast<T>(v.x >> scalar));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator>>(T scalar, vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			static_cast<T>(scalar >> v.x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator>>(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return vec<1, T, Q>(
			static_cast<T>(v1.x >> v2.x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> operator~(vec<1, T, Q> const& v)
	{
		return vec<1, T, Q>(
			~v.x);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return detail::compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<1, T, Q> const& v1, vec<1, T, Q> const& v2)
	{
		return !(v1 == v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, bool, Q> operator&&(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2)
	{
		return vec<1, bool, Q>(v1.x && v2.x);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, bool, Q> operator||(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2)
	{
		return vec<1, bool, Q>(v1.x || v2.x);
	}
}//namespace glm


#endif//GLM_EXTERNAL_TEMPLATE



// common .inl file


namespace glm{
namespace detail
{
	template<typename genFIType, bool /*signed*/>
	struct compute_abs
	{};

	template<typename genFIType>
	struct compute_abs<genFIType, true>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static genFIType call(genFIType x)
		{
			GLM_STATIC_ASSERT(
				std::numeric_limits<genFIType>::is_iec559 || std::numeric_limits<genFIType>::is_signed,
				"'abs' only accept floating-point and integer scalar or vector inputs");

			return x >= genFIType(0) ? x : -x;
			// TODO, perf comp with: *(((int *) &x) + 1) &= 0x7fffffff;
		}
	};

#if GLM_COMPILER & GLM_COMPILER_CUDA
	template<>
	struct compute_abs<float, true>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static float call(float x)
		{
			return fabsf(x);
		}
	};
#endif

	template<typename genFIType>
	struct compute_abs<genFIType, false>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static genFIType call(genFIType x)
		{
			GLM_STATIC_ASSERT(
				(!std::numeric_limits<genFIType>::is_signed && std::numeric_limits<genFIType>::is_integer),
				"'abs' only accept floating-point and integer scalar or vector inputs");
			return x;
		}
	};
}//namespace detail
}//namespace glm


namespace glm
{
	// min
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType min(genType x, genType y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559 || std::numeric_limits<genType>::is_integer, "'min' only accept floating-point or integer inputs");
		return (y < x) ? y : x;
	}

	// max
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType max(genType x, genType y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559 || std::numeric_limits<genType>::is_integer, "'max' only accept floating-point or integer inputs");

		return (x < y) ? y : x;
	}

	// abs
	template<>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR int abs(int x)
	{
		int const y = x >> (sizeof(int) * 8 - 1);
		return (x ^ y) - y;
	}

	// round
#	if GLM_HAS_CXX11_STL
		using ::std::round;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType round(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'round' only accept floating-point inputs");

			return x < static_cast<genType>(0) ? static_cast<genType>(int(x - static_cast<genType>(0.5))) : static_cast<genType>(int(x + static_cast<genType>(0.5)));
		}
#	endif

	// trunc
#	if GLM_HAS_CXX11_STL
		using ::std::trunc;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType trunc(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'trunc' only accept floating-point inputs");

			return x < static_cast<genType>(0) ? -std::floor(-x) : std::floor(x);
		}
#	endif

}//namespace glm

namespace glm{
namespace detail
{
	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_abs_vector
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return detail::functor1<vec, L, T, T, Q>::call(abs, x);
		}
	};

	template<length_t L, typename T, typename U, qualifier Q, bool Aligned>
	struct compute_mix_vector
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, U, Q> const& a)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<U>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'mix' only accept floating-point inputs for the interpolator a");

			return vec<L, T, Q>(vec<L, U, Q>(x) * (static_cast<U>(1) - a) + vec<L, U, Q>(y) * a);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_mix_vector<L, T, bool, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, bool, Q> const& a)
		{
			vec<L, T, Q> Result;
			for(length_t i = 0; i < x.length(); ++i)
				Result[i] = a[i] ? y[i] : x[i];
			return Result;
		}
	};

	template<length_t L, typename T, typename U, qualifier Q, bool Aligned>
	struct compute_mix_scalar
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& y, U const& a)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<U>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'mix' only accept floating-point inputs for the interpolator a");

			return vec<L, T, Q>(vec<L, U, Q>(x) * (static_cast<U>(1) - a) + vec<L, U, Q>(y) * a);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_mix_scalar<L, T, bool, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& y, bool const& a)
		{
			return a ? y : x;
		}
	};

	template<typename T, typename U>
	struct compute_mix
	{
		GLM_FUNC_QUALIFIER static T call(T const& x, T const& y, U const& a)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<U>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'mix' only accept floating-point inputs for the interpolator a");

			return static_cast<T>(static_cast<U>(x) * (static_cast<U>(1) - a) + static_cast<U>(y) * a);
		}
	};

	template<typename T>
	struct compute_mix<T, bool>
	{
		GLM_FUNC_QUALIFIER static T call(T const& x, T const& y, bool const& a)
		{
			return a ? y : x;
		}
	};

	template<length_t L, typename T, qualifier Q, bool isFloat, bool Aligned>
	struct compute_sign
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return vec<L, T, Q>(glm::lessThan(vec<L, T, Q>(0), x)) - vec<L, T, Q>(glm::lessThan(x, vec<L, T, Q>(0)));
		}
	};

#	if GLM_ARCH == GLM_ARCH_X86
	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_sign<L, T, Q, false, Aligned>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			T const Shift(static_cast<T>(sizeof(T) * 8 - 1));
			vec<L, T, Q> const y(vec<L, typename detail::make_unsigned<T>::type, Q>(-x) >> typename detail::make_unsigned<T>::type(Shift));

			return (x >> Shift) | y;
		}
	};
#	endif

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_floor
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return detail::functor1<vec, L, T, T, Q>::call(std::floor, x);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_ceil
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return detail::functor1<vec, L, T, T, Q>::call(std::ceil, x);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_fract
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return x - floor(x);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_trunc
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return detail::functor1<vec, L, T, T, Q>::call(trunc, x);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_round
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			return detail::functor1<vec, L, T, T, Q>::call(round, x);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_mod
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& a, vec<L, T, Q> const& b)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'mod' only accept floating-point inputs. Include <glm/gtc/integer.hpp> for integer inputs.");
			return a - b * floor(a / b);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_min_vector
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
		{
			return detail::functor2<vec, L, T, Q>::call(min, x, y);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_max_vector
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
		{
			return detail::functor2<vec, L, T, Q>::call(max, x, y);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_clamp_vector
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x, vec<L, T, Q> const& minVal, vec<L, T, Q> const& maxVal)
		{
			return min(max(x, minVal), maxVal);
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_step_vector
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& edge, vec<L, T, Q> const& x)
		{
			return mix(vec<L, T, Q>(1), vec<L, T, Q>(0), glm::lessThan(x, edge));
		}
	};

	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_smoothstep_vector
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& edge0, vec<L, T, Q> const& edge1, vec<L, T, Q> const& x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'smoothstep' only accept floating-point inputs");
			vec<L, T, Q> const tmp(clamp((x - edge0) / (edge1 - edge0), static_cast<T>(0), static_cast<T>(1)));
			return tmp * tmp * (static_cast<T>(3) - static_cast<T>(2) * tmp);
		}
	};
}//namespace detail

	template<typename genFIType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genFIType abs(genFIType x)
	{
		return detail::compute_abs<genFIType, std::numeric_limits<genFIType>::is_signed>::call(x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> abs(vec<L, T, Q> const& x)
	{
		return detail::compute_abs_vector<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	// sign
	// fast and works for any type
	template<typename genFIType>
	GLM_FUNC_QUALIFIER genFIType sign(genFIType x)
	{
		GLM_STATIC_ASSERT(
			std::numeric_limits<genFIType>::is_iec559 || (std::numeric_limits<genFIType>::is_signed && std::numeric_limits<genFIType>::is_integer),
			"'sign' only accept signed inputs");

		return detail::compute_sign<1, genFIType, defaultp,
                                    std::numeric_limits<genFIType>::is_iec559, detail::is_aligned<highp>::value>::call(vec<1, genFIType>(x)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> sign(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(
			std::numeric_limits<T>::is_iec559 || (std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer),
			"'sign' only accept signed inputs");

		return detail::compute_sign<L, T, Q, std::numeric_limits<T>::is_iec559, detail::is_aligned<Q>::value>::call(x);
	}

	// floor
	using ::std::floor;
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> floor(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'floor' only accept floating-point inputs.");
		return detail::compute_floor<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> trunc(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'trunc' only accept floating-point inputs");
		return detail::compute_trunc<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> round(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'round' only accept floating-point inputs");
		return detail::compute_round<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

/*
	// roundEven
	template<typename genType>
	GLM_FUNC_QUALIFIER genType roundEven(genType const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'roundEven' only accept floating-point inputs");

		return genType(int(x + genType(int(x) % 2)));
	}
*/

	// roundEven
	template<typename genType>
	GLM_FUNC_QUALIFIER genType roundEven(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'roundEven' only accept floating-point inputs");

		int Integer = static_cast<int>(x);
		genType IntegerPart = static_cast<genType>(Integer);
		genType FractionalPart = fract(x);

		if(FractionalPart > static_cast<genType>(0.5) || FractionalPart < static_cast<genType>(0.5))
		{
			return round(x);
		}
		else if((Integer % 2) == 0)
		{
			return IntegerPart;
		}
		else if(x <= static_cast<genType>(0)) // Work around...
		{
			return IntegerPart - static_cast<genType>(1);
		}
		else
		{
			return IntegerPart + static_cast<genType>(1);
		}
		//else // Bug on MinGW 4.5.2
		//{
		//	return mix(IntegerPart + genType(-1), IntegerPart + genType(1), x <= genType(0));
		//}
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> roundEven(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'roundEven' only accept floating-point inputs");
		return detail::functor1<vec, L, T, T, Q>::call(roundEven, x);
	}

	// ceil
	using ::std::ceil;
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> ceil(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'ceil' only accept floating-point inputs");
		return detail::compute_ceil<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	// fract
	template<typename genType>
	GLM_FUNC_QUALIFIER genType fract(genType x)
	{
		return fract(vec<1, genType>(x)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fract(vec<L, T, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fract' only accept floating-point inputs");
		return detail::compute_fract<L, T, Q, detail::is_aligned<Q>::value>::call(x);
	}

	// mod
	template<typename genType>
	GLM_FUNC_QUALIFIER genType mod(genType x, genType y)
	{
#		if GLM_COMPILER & GLM_COMPILER_CUDA
			// Another Cuda compiler bug https://github.com/g-truc/glm/issues/530
			vec<1, genType, defaultp> Result(mod(vec<1, genType, defaultp>(x), y));
			return Result.x;
#		else
			return mod(vec<1, genType, defaultp>(x), y).x;
#		endif
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> mod(vec<L, T, Q> const& x, T y)
	{
		return detail::compute_mod<L, T, Q, detail::is_aligned<Q>::value>::call(x, vec<L, T, Q>(y));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> mod(vec<L, T, Q> const& x, vec<L, T, Q> const& y)
	{
		return detail::compute_mod<L, T, Q, detail::is_aligned<Q>::value>::call(x, y);
	}

	// modf
	template<typename genType>
	GLM_FUNC_QUALIFIER genType modf(genType x, genType & i)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'modf' only accept floating-point inputs");
		return std::modf(x, &i);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<1, T, Q> modf(vec<1, T, Q> const& x, vec<1, T, Q> & i)
	{
		return vec<1, T, Q>(
			modf(x.x, i.x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, T, Q> modf(vec<2, T, Q> const& x, vec<2, T, Q> & i)
	{
		return vec<2, T, Q>(
			modf(x.x, i.x),
			modf(x.y, i.y));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> modf(vec<3, T, Q> const& x, vec<3, T, Q> & i)
	{
		return vec<3, T, Q>(
			modf(x.x, i.x),
			modf(x.y, i.y),
			modf(x.z, i.z));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, T, Q> modf(vec<4, T, Q> const& x, vec<4, T, Q> & i)
	{
		return vec<4, T, Q>(
			modf(x.x, i.x),
			modf(x.y, i.y),
			modf(x.z, i.z),
			modf(x.w, i.w));
	}

	//// Only valid if (INT_MIN <= x-y <= INT_MAX)
	//// min(x,y)
	//r = y + ((x - y) & ((x - y) >> (sizeof(int) *
	//CHAR_BIT - 1)));
	//// max(x,y)
	//r = x - ((x - y) & ((x - y) >> (sizeof(int) *
	//CHAR_BIT - 1)));

	// min
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> min(vec<L, T, Q> const& a, T b)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'min' only accept floating-point or integer inputs");
		return detail::compute_min_vector<L, T, Q, detail::is_aligned<Q>::value>::call(a, vec<L, T, Q>(b));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> min(vec<L, T, Q> const& a, vec<L, T, Q> const& b)
	{
		return detail::compute_min_vector<L, T, Q, detail::is_aligned<Q>::value>::call(a, b);
	}

	// max
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> max(vec<L, T, Q> const& a, T b)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'max' only accept floating-point or integer inputs");
		return detail::compute_max_vector<L, T, Q, detail::is_aligned<Q>::value>::call(a, vec<L, T, Q>(b));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> max(vec<L, T, Q> const& a, vec<L, T, Q> const& b)
	{
		return detail::compute_max_vector<L, T, Q, detail::is_aligned<Q>::value>::call(a, b);
	}

	// clamp
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType clamp(genType x, genType minVal, genType maxVal)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559 || std::numeric_limits<genType>::is_integer, "'clamp' only accept floating-point or integer inputs");
		return min(max(x, minVal), maxVal);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> clamp(vec<L, T, Q> const& x, T minVal, T maxVal)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'clamp' only accept floating-point or integer inputs");
		return detail::compute_clamp_vector<L, T, Q, detail::is_aligned<Q>::value>::call(x, vec<L, T, Q>(minVal), vec<L, T, Q>(maxVal));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, T, Q> clamp(vec<L, T, Q> const& x, vec<L, T, Q> const& minVal, vec<L, T, Q> const& maxVal)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'clamp' only accept floating-point or integer inputs");
		return detail::compute_clamp_vector<L, T, Q, detail::is_aligned<Q>::value>::call(x, minVal, maxVal);
	}

	template<typename genTypeT, typename genTypeU>
	GLM_FUNC_QUALIFIER genTypeT mix(genTypeT x, genTypeT y, genTypeU a)
	{
		return detail::compute_mix<genTypeT, genTypeU>::call(x, y, a);
	}

	template<length_t L, typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> mix(vec<L, T, Q> const& x, vec<L, T, Q> const& y, U a)
	{
		return detail::compute_mix_scalar<L, T, U, Q, detail::is_aligned<Q>::value>::call(x, y, a);
	}

	template<length_t L, typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> mix(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, U, Q> const& a)
	{
		return detail::compute_mix_vector<L, T, U, Q, detail::is_aligned<Q>::value>::call(x, y, a);
	}

	// step
	template<typename genType>
	GLM_FUNC_QUALIFIER genType step(genType edge, genType x)
	{
		return mix(static_cast<genType>(1), static_cast<genType>(0), x < edge);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> step(T edge, vec<L, T, Q> const& x)
	{
		return detail::compute_step_vector<L, T, Q, detail::is_aligned<Q>::value>::call(vec<L, T, Q>(edge), x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> step(vec<L, T, Q> const& edge, vec<L, T, Q> const& x)
	{
		return detail::compute_step_vector<L, T, Q, detail::is_aligned<Q>::value>::call(edge, x);
	}

	// smoothstep
	template<typename genType>
	GLM_FUNC_QUALIFIER genType smoothstep(genType edge0, genType edge1, genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'smoothstep' only accept floating-point inputs");

		genType const tmp(clamp((x - edge0) / (edge1 - edge0), genType(0), genType(1)));
		return tmp * tmp * (genType(3) - genType(2) * tmp);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> smoothstep(T edge0, T edge1, vec<L, T, Q> const& x)
	{
		return detail::compute_smoothstep_vector<L, T, Q, detail::is_aligned<Q>::value>::call(vec<L, T, Q>(edge0), vec<L, T, Q>(edge1), x);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> smoothstep(vec<L, T, Q> const& edge0, vec<L, T, Q> const& edge1, vec<L, T, Q> const& x)
	{
		return detail::compute_smoothstep_vector<L, T, Q, detail::is_aligned<Q>::value>::call(edge0, edge1, x);
	}

#	if GLM_HAS_CXX11_STL
		using std::isnan;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER bool isnan(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'isnan' only accept floating-point inputs");

#			if GLM_HAS_CXX11_STL
				return std::isnan(x);
#			elif GLM_COMPILER & GLM_COMPILER_VC
				return _isnan(x) != 0;
#			elif GLM_COMPILER & GLM_COMPILER_INTEL
#				if GLM_PLATFORM & GLM_PLATFORM_WINDOWS
					return _isnan(x) != 0;
#				else
					return ::isnan(x) != 0;
#				endif
#			elif (GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_CLANG)) && (GLM_PLATFORM & GLM_PLATFORM_ANDROID) && __cplusplus < 201103L
				return _isnan(x) != 0;
#			elif GLM_COMPILER & GLM_COMPILER_CUDA
				return ::isnan(x) != 0;
#			else
				return std::isnan(x);
#			endif
		}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isnan(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isnan' only accept floating-point inputs");

		vec<L, bool, Q> Result;
		for (length_t l = 0; l < v.length(); ++l)
			Result[l] = glm::isnan(v[l]);
		return Result;
	}

#	if GLM_HAS_CXX11_STL
		using std::isinf;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER bool isinf(genType x)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'isinf' only accept floating-point inputs");

#			if GLM_HAS_CXX11_STL
				return std::isinf(x);
#			elif GLM_COMPILER & (GLM_COMPILER_INTEL | GLM_COMPILER_VC)
#				if(GLM_PLATFORM & GLM_PLATFORM_WINDOWS)
					return _fpclass(x) == _FPCLASS_NINF || _fpclass(x) == _FPCLASS_PINF;
#				else
					return ::isinf(x);
#				endif
#			elif GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_CLANG)
#				if(GLM_PLATFORM & GLM_PLATFORM_ANDROID && __cplusplus < 201103L)
					return _isinf(x) != 0;
#				else
					return std::isinf(x);
#				endif
#			elif GLM_COMPILER & GLM_COMPILER_CUDA
				// http://developer.download.nvidia.com/compute/cuda/4_2/rel/toolkit/docs/online/group__CUDA__MATH__DOUBLE_g13431dd2b40b51f9139cbb7f50c18fab.html#g13431dd2b40b51f9139cbb7f50c18fab
				return ::isinf(double(x)) != 0;
#			else
				return std::isinf(x);
#			endif
	}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isinf(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isinf' only accept floating-point inputs");

		vec<L, bool, Q> Result;
		for (length_t l = 0; l < v.length(); ++l)
			Result[l] = glm::isinf(v[l]);
		return Result;
	}

	GLM_FUNC_QUALIFIER int floatBitsToInt(float const& v)
	{
		union
		{
			float in;
			int out;
		} u;

		u.in = v;

		return u.out;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> floatBitsToInt(vec<L, float, Q> const& v)
	{
		return reinterpret_cast<vec<L, int, Q>&>(const_cast<vec<L, float, Q>&>(v));
	}

	GLM_FUNC_QUALIFIER uint floatBitsToUint(float const& v)
	{
		union
		{
			float in;
			uint out;
		} u;

		u.in = v;

		return u.out;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, uint, Q> floatBitsToUint(vec<L, float, Q> const& v)
	{
		return reinterpret_cast<vec<L, uint, Q>&>(const_cast<vec<L, float, Q>&>(v));
	}

	GLM_FUNC_QUALIFIER float intBitsToFloat(int const& v)
	{
		union
		{
			int in;
			float out;
		} u;

		u.in = v;

		return u.out;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, float, Q> intBitsToFloat(vec<L, int, Q> const& v)
	{
		return reinterpret_cast<vec<L, float, Q>&>(const_cast<vec<L, int, Q>&>(v));
	}

	GLM_FUNC_QUALIFIER float uintBitsToFloat(uint const& v)
	{
		union
		{
			uint in;
			float out;
		} u;

		u.in = v;

		return u.out;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, float, Q> uintBitsToFloat(vec<L, uint, Q> const& v)
	{
		return reinterpret_cast<vec<L, float, Q>&>(const_cast<vec<L, uint, Q>&>(v));
	}

#	if GLM_HAS_CXX11_STL
		using std::fma;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType fma(genType const& a, genType const& b, genType const& c)
		{
			return a * b + c;
		}
#	endif

	template<typename genType>
	GLM_FUNC_QUALIFIER genType frexp(genType x, int& exp)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'frexp' only accept floating-point inputs");

		return std::frexp(x, &exp);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> frexp(vec<L, T, Q> const& v, vec<L, int, Q>& exp)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'frexp' only accept floating-point inputs");

		vec<L, T, Q> Result;
		for (length_t l = 0; l < v.length(); ++l)
			Result[l] = std::frexp(v[l], &exp[l]);
		return Result;
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType ldexp(genType const& x, int const& exp)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'ldexp' only accept floating-point inputs");

		return std::ldexp(x, exp);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> ldexp(vec<L, T, Q> const& v, vec<L, int, Q> const& exp)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'ldexp' only accept floating-point inputs");

		vec<L, T, Q> Result;
		for (length_t l = 0; l < v.length(); ++l)
			Result[l] = std::ldexp(v[l], exp[l]);
		return Result;
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/func_common_simd.inl"
#endif


// ! Extensions used for this engine

// ---------- type_ptr.hpp ----------

// ---------- "../gtc/quaternion.hpp" -----------

	// ---------- "../gtc/constants.hpp" ----------

	#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_scalar_constants extension included")
#endif

namespace glm
{
	/// @addtogroup ext_scalar_constants
	/// @{

	/// Return the epsilon constant for floating point types.
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType epsilon();

	/// Return the pi constant for floating point types.
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType pi();

	/// Return the value of cos(1 / 2) for floating point types.
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType cos_one_over_two();

	/// @}
} //namespace glm

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType epsilon()
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'epsilon' only accepts floating-point inputs");
		return std::numeric_limits<genType>::epsilon();
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType pi()
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'pi' only accepts floating-point inputs");
		return static_cast<genType>(3.14159265358979323846264338327950288);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType cos_one_over_two()
	{
		return genType(0.877582561890372716130286068203503191);
	}
} //namespace glm


#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTC_constants extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_constants
	/// @{

	/// Return 0.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType zero();

	/// Return 1.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType one();

	/// Return pi * 2.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType two_pi();

	/// Return square root of pi.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_pi();

	/// Return pi / 2.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType half_pi();

	/// Return pi / 2 * 3.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType three_over_two_pi();

	/// Return pi / 4.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType quarter_pi();

	/// Return 1 / pi.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType one_over_pi();

	/// Return 1 / (pi * 2).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType one_over_two_pi();

	/// Return 2 / pi.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType two_over_pi();

	/// Return 4 / pi.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType four_over_pi();

	/// Return 2 / sqrt(pi).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType two_over_root_pi();

	/// Return 1 / sqrt(2).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType one_over_root_two();

	/// Return sqrt(pi / 2).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_half_pi();

	/// Return sqrt(2 * pi).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_two_pi();

	/// Return sqrt(ln(4)).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_ln_four();

	/// Return e constant.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType e();

	/// Return Euler's constant.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType euler();

	/// Return sqrt(2).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_two();

	/// Return sqrt(3).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_three();

	/// Return sqrt(5).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType root_five();

	/// Return ln(2).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType ln_two();

	/// Return ln(10).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType ln_ten();

	/// Return ln(ln(2)).
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType ln_ln_two();

	/// Return 1 / 3.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType third();

	/// Return 2 / 3.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType two_thirds();

	/// Return the golden ratio constant.
	/// @see gtc_constants
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType golden_ratio();

	/// @}
} //namespace glm

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType zero()
	{
		return genType(0);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType one()
	{
		return genType(1);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType two_pi()
	{
		return genType(6.28318530717958647692528676655900576);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_pi()
	{
		return genType(1.772453850905516027);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType half_pi()
	{
		return genType(1.57079632679489661923132169163975144);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType three_over_two_pi()
	{
		return genType(4.71238898038468985769396507491925432);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType quarter_pi()
	{
		return genType(0.785398163397448309615660845819875721);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType one_over_pi()
	{
		return genType(0.318309886183790671537767526745028724);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType one_over_two_pi()
	{
		return genType(0.159154943091895335768883763372514362);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType two_over_pi()
	{
		return genType(0.636619772367581343075535053490057448);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType four_over_pi()
	{
		return genType(1.273239544735162686151070106980114898);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType two_over_root_pi()
	{
		return genType(1.12837916709551257389615890312154517);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType one_over_root_two()
	{
		return genType(0.707106781186547524400844362104849039);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_half_pi()
	{
		return genType(1.253314137315500251);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_two_pi()
	{
		return genType(2.506628274631000502);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_ln_four()
	{
		return genType(1.17741002251547469);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType e()
	{
		return genType(2.71828182845904523536);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType euler()
	{
		return genType(0.577215664901532860606);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_two()
	{
		return genType(1.41421356237309504880168872420969808);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_three()
	{
		return genType(1.73205080756887729352744634150587236);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType root_five()
	{
		return genType(2.23606797749978969640917366873127623);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType ln_two()
	{
		return genType(0.693147180559945309417232121458176568);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType ln_ten()
	{
		return genType(2.30258509299404568401799145468436421);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType ln_ln_two()
	{
		return genType(-0.3665129205816643);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType third()
	{
		return genType(0.3333333333333333333333333333333333333333);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType two_thirds()
	{
		return genType(0.666666666666666666666666666666666666667);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType golden_ratio()
	{
		return genType(1.61803398874989484820458683436563811);
	}

} //namespace glm




	// ---------- "../gtc/matrix_transform.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_matrix_projection extension included")
#endif

namespace glm
{
	/// @addtogroup ext_matrix_projection
	/// @{

	/// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param obj Specify the object coordinates.
	/// @param model Specifies the current modelview matrix
	/// @param proj Specifies the current projection matrix
	/// @param viewport Specifies the current viewport
	/// @return Return the computed window coordinates.
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluProject.xml">gluProject man page</a>
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> projectZO(
		vec<3, T, Q> const& obj, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport);

	/// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param obj Specify the object coordinates.
	/// @param model Specifies the current modelview matrix
	/// @param proj Specifies the current projection matrix
	/// @param viewport Specifies the current viewport
	/// @return Return the computed window coordinates.
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluProject.xml">gluProject man page</a>
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> projectNO(
		vec<3, T, Q> const& obj, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport);

	/// Map the specified object coordinates (obj.x, obj.y, obj.z) into window coordinates using default near and far clip planes definition.
	/// To change default near and far clip planes definition use GLM_FORCE_DEPTH_ZERO_TO_ONE.
	///
	/// @param obj Specify the object coordinates.
	/// @param model Specifies the current modelview matrix
	/// @param proj Specifies the current projection matrix
	/// @param viewport Specifies the current viewport
	/// @return Return the computed window coordinates.
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluProject.xml">gluProject man page</a>
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> project(
		vec<3, T, Q> const& obj, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport);

	/// Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param win Specify the window coordinates to be mapped.
	/// @param model Specifies the modelview matrix
	/// @param proj Specifies the projection matrix
	/// @param viewport Specifies the viewport
	/// @return Returns the computed object coordinates.
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluUnProject.xml">gluUnProject man page</a>
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> unProjectZO(
		vec<3, T, Q> const& win, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport);

	/// Map the specified window coordinates (win.x, win.y, win.z) into object coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param win Specify the window coordinates to be mapped.
	/// @param model Specifies the modelview matrix
	/// @param proj Specifies the projection matrix
	/// @param viewport Specifies the viewport
	/// @return Returns the computed object coordinates.
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluUnProject.xml">gluUnProject man page</a>
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> unProjectNO(
		vec<3, T, Q> const& win, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport);

	/// Map the specified window coordinates (win.x, win.y, win.z) into object coordinates using default near and far clip planes definition.
	/// To change default near and far clip planes definition use GLM_FORCE_DEPTH_ZERO_TO_ONE.
	///
	/// @param win Specify the window coordinates to be mapped.
	/// @param model Specifies the modelview matrix
	/// @param proj Specifies the projection matrix
	/// @param viewport Specifies the viewport
	/// @return Returns the computed object coordinates.
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluUnProject.xml">gluUnProject man page</a>
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> unProject(
		vec<3, T, Q> const& win, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport);

	/// Define a picking region
	///
	/// @param center Specify the center of a picking region in window coordinates.
	/// @param delta Specify the width and height, respectively, of the picking region in window coordinates.
	/// @param viewport Rendering viewport
	/// @tparam T Native type used for the computation. Currently supported: half (not recommended), float or double.
	/// @tparam U Currently supported: Floating-point types and integer types.
	///
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPickMatrix.xml">gluPickMatrix man page</a>
	template<typename T, qualifier Q, typename U>
	GLM_FUNC_DECL mat<4, 4, T, Q> pickMatrix(
		vec<2, T, Q> const& center, vec<2, T, Q> const& delta, vec<4, U, Q> const& viewport);

	/// @}
}//namespace glm

namespace glm
{
	template<typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> projectZO(vec<3, T, Q> const& obj, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		vec<4, T, Q> tmp = vec<4, T, Q>(obj, static_cast<T>(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp.x = tmp.x * static_cast<T>(0.5) + static_cast<T>(0.5);
		tmp.y = tmp.y * static_cast<T>(0.5) + static_cast<T>(0.5);

		tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
		tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

		return vec<3, T, Q>(tmp);
	}

	template<typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> projectNO(vec<3, T, Q> const& obj, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		vec<4, T, Q> tmp = vec<4, T, Q>(obj, static_cast<T>(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp = tmp * static_cast<T>(0.5) + static_cast<T>(0.5);
		tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
		tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

		return vec<3, T, Q>(tmp);
	}

	template<typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> project(vec<3, T, Q> const& obj, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return projectZO(obj, model, proj, viewport);
#		else
			return projectNO(obj, model, proj, viewport);
#		endif
	}

	template<typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> unProjectZO(vec<3, T, Q> const& win, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		mat<4, 4, T, Q> Inverse = inverse(proj * model);

		vec<4, T, Q> tmp = vec<4, T, Q>(win, T(1));
		tmp.x = (tmp.x - T(viewport[0])) / T(viewport[2]);
		tmp.y = (tmp.y - T(viewport[1])) / T(viewport[3]);
		tmp.x = tmp.x * static_cast<T>(2) - static_cast<T>(1);
		tmp.y = tmp.y * static_cast<T>(2) - static_cast<T>(1);

		vec<4, T, Q> obj = Inverse * tmp;
		obj /= obj.w;

		return vec<3, T, Q>(obj);
	}

	template<typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> unProjectNO(vec<3, T, Q> const& win, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		mat<4, 4, T, Q> Inverse = inverse(proj * model);

		vec<4, T, Q> tmp = vec<4, T, Q>(win, T(1));
		tmp.x = (tmp.x - T(viewport[0])) / T(viewport[2]);
		tmp.y = (tmp.y - T(viewport[1])) / T(viewport[3]);
		tmp = tmp * static_cast<T>(2) - static_cast<T>(1);

		vec<4, T, Q> obj = Inverse * tmp;
		obj /= obj.w;

		return vec<3, T, Q>(obj);
	}

	template<typename T, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> unProject(vec<3, T, Q> const& win, mat<4, 4, T, Q> const& model, mat<4, 4, T, Q> const& proj, vec<4, U, Q> const& viewport)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return unProjectZO(win, model, proj, viewport);
#		else
			return unProjectNO(win, model, proj, viewport);
#		endif
	}

	template<typename T, qualifier Q, typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> pickMatrix(vec<2, T, Q> const& center, vec<2, T, Q> const& delta, vec<4, U, Q> const& viewport)
	{
		assert(delta.x > static_cast<T>(0) && delta.y > static_cast<T>(0));
		mat<4, 4, T, Q> Result(static_cast<T>(1));

		if(!(delta.x > static_cast<T>(0) && delta.y > static_cast<T>(0)))
			return Result; // Error

		vec<3, T, Q> Temp(
			(static_cast<T>(viewport[2]) - static_cast<T>(2) * (center.x - static_cast<T>(viewport[0]))) / delta.x,
			(static_cast<T>(viewport[3]) - static_cast<T>(2) * (center.y - static_cast<T>(viewport[1]))) / delta.y,
			static_cast<T>(0));

		// Translate and scale the picked region to the entire window
		Result = translate(Result, Temp);
		return scale(Result, vec<3, T, Q>(static_cast<T>(viewport[2]) / delta.x, static_cast<T>(viewport[3]) / delta.y, static_cast<T>(1)));
	}
}//namespace glm


#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_matrix_clip_space extension included")
#endif

namespace glm
{
	/// @addtogroup ext_matrix_clip_space
	/// @{

	/// Creates a matrix for projecting two-dimensional coordinates onto the screen.
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top, T const& zNear, T const& zFar)
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluOrtho2D.xml">gluOrtho2D man page</a>
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> ortho(
		T left, T right, T bottom, T top);

	/// Creates a matrix for an orthographic parallel viewing volume, using left-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoLH_ZO(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume using right-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoLH_NO(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using left-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoRH_ZO(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using right-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoRH_NO(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using left-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoZO(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoNO(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using left-handed coordinates.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoLH(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using right-handed coordinates.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> orthoRH(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a matrix for an orthographic parallel viewing volume, using the default handedness and default near and far clip planes definition.
	/// To change default handedness use GLM_FORCE_LEFT_HANDED. To change default near and far clip planes definition use GLM_FORCE_DEPTH_ZERO_TO_ONE.
	///
	/// @tparam T A floating-point scalar type
	///
	/// @see - glm::ortho(T const& left, T const& right, T const& bottom, T const& top)
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml">glOrtho man page</a>
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> ortho(
		T left, T right, T bottom, T top, T zNear, T zFar);

	/// Creates a left handed frustum matrix.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumLH_ZO(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a left handed frustum matrix.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumLH_NO(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a right handed frustum matrix.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumRH_ZO(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a right handed frustum matrix.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumRH_NO(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a frustum matrix using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumZO(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a frustum matrix using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumNO(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a left handed frustum matrix.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumLH(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a right handed frustum matrix.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustumRH(
		T left, T right, T bottom, T top, T near, T far);

	/// Creates a frustum matrix with default handedness, using the default handedness and default near and far clip planes definition.
	/// To change default handedness use GLM_FORCE_LEFT_HANDED. To change default near and far clip planes definition use GLM_FORCE_DEPTH_ZERO_TO_ONE.
	///
	/// @tparam T A floating-point scalar type
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glFrustum.xml">glFrustum man page</a>
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> frustum(
		T left, T right, T bottom, T top, T near, T far);


	/// Creates a matrix for a right handed, symetric perspective-view frustum.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveRH_ZO(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a right handed, symetric perspective-view frustum.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveRH_NO(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a left handed, symetric perspective-view frustum.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveLH_ZO(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a left handed, symetric perspective-view frustum.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveLH_NO(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a symetric perspective-view frustum using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveZO(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a symetric perspective-view frustum using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveNO(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a right handed, symetric perspective-view frustum.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveRH(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a left handed, symetric perspective-view frustum.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveLH(
		T fovy, T aspect, T near, T far);

	/// Creates a matrix for a symetric perspective-view frustum based on the default handedness and default near and far clip planes definition.
	/// To change default handedness use GLM_FORCE_LEFT_HANDED. To change default near and far clip planes definition use GLM_FORCE_DEPTH_ZERO_TO_ONE.
	///
	/// @param fovy Specifies the field of view angle in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml">gluPerspective man page</a>
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspective(
		T fovy, T aspect, T near, T far);

	/// Builds a perspective projection matrix based on a field of view using right-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovRH_ZO(
		T fov, T width, T height, T near, T far);

	/// Builds a perspective projection matrix based on a field of view using right-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovRH_NO(
		T fov, T width, T height, T near, T far);

	/// Builds a perspective projection matrix based on a field of view using left-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovLH_ZO(
		T fov, T width, T height, T near, T far);

	/// Builds a perspective projection matrix based on a field of view using left-handed coordinates.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovLH_NO(
		T fov, T width, T height, T near, T far);

	/// Builds a perspective projection matrix based on a field of view using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovZO(
		T fov, T width, T height, T near, T far);

	/// Builds a perspective projection matrix based on a field of view using left-handed coordinates if GLM_FORCE_LEFT_HANDED if defined or right-handed coordinates otherwise.
	/// The near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovNO(
		T fov, T width, T height, T near, T far);

	/// Builds a right handed perspective projection matrix based on a field of view.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovRH(
		T fov, T width, T height, T near, T far);

	/// Builds a left handed perspective projection matrix based on a field of view.
	/// If GLM_FORCE_DEPTH_ZERO_TO_ONE is defined, the near and far clip planes correspond to z normalized device coordinates of 0 and +1 respectively. (Direct3D clip volume definition)
	/// Otherwise, the near and far clip planes correspond to z normalized device coordinates of -1 and +1 respectively. (OpenGL clip volume definition)
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFovLH(
		T fov, T width, T height, T near, T far);

	/// Builds a perspective projection matrix based on a field of view and the default handedness and default near and far clip planes definition.
	/// To change default handedness use GLM_FORCE_LEFT_HANDED. To change default near and far clip planes definition use GLM_FORCE_DEPTH_ZERO_TO_ONE.
	///
	/// @param fov Expressed in radians.
	/// @param width Width of the viewport
	/// @param height Height of the viewport
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param far Specifies the distance from the viewer to the far clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> perspectiveFov(
		T fov, T width, T height, T near, T far);

	/// Creates a matrix for a left handed, symmetric perspective-view frustum with far plane at infinite.
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> infinitePerspectiveLH(
		T fovy, T aspect, T near);

	/// Creates a matrix for a right handed, symmetric perspective-view frustum with far plane at infinite.
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> infinitePerspectiveRH(
		T fovy, T aspect, T near);

	/// Creates a matrix for a symmetric perspective-view frustum with far plane at infinite with default handedness.
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> infinitePerspective(
		T fovy, T aspect, T near);

	/// Creates a matrix for a symmetric perspective-view frustum with far plane at infinite for graphics hardware that doesn't support depth clamping.
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> tweakedInfinitePerspective(
		T fovy, T aspect, T near);

	/// Creates a matrix for a symmetric perspective-view frustum with far plane at infinite for graphics hardware that doesn't support depth clamping.
	///
	/// @param fovy Specifies the field of view angle, in degrees, in the y direction. Expressed in radians.
	/// @param aspect Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	/// @param near Specifies the distance from the viewer to the near clipping plane (always positive).
	/// @param ep Epsilon
	///
	/// @tparam T A floating-point scalar type
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> tweakedInfinitePerspective(
		T fovy, T aspect, T near, T ep);

	/// @}
}//namespace glm

namespace glm
{
	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> ortho(T left, T right, T bottom, T top)
	{
		mat<4, 4, T, defaultp> Result(static_cast<T>(1));
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = - static_cast<T>(1);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoLH_ZO(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		mat<4, 4, T, defaultp> Result(1);
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = static_cast<T>(1) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - zNear / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoLH_NO(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		mat<4, 4, T, defaultp> Result(1);
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = static_cast<T>(2) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - (zFar + zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoRH_ZO(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		mat<4, 4, T, defaultp> Result(1);
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = - static_cast<T>(1) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - zNear / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoRH_NO(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		mat<4, 4, T, defaultp> Result(1);
		Result[0][0] = static_cast<T>(2) / (right - left);
		Result[1][1] = static_cast<T>(2) / (top - bottom);
		Result[2][2] = - static_cast<T>(2) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - (zFar + zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoZO(T left, T right, T bottom, T top, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return orthoLH_ZO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoNO(T left, T right, T bottom, T top, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return orthoLH_NO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoRH_NO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoLH(T left, T right, T bottom, T top, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return orthoLH_ZO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoLH_NO(left, right, bottom, top, zNear, zFar);
#		endif

	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> orthoRH(T left, T right, T bottom, T top, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoRH_NO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> ortho(T left, T right, T bottom, T top, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return orthoLH_ZO(left, right, bottom, top, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return orthoLH_NO(left, right, bottom, top, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return orthoRH_NO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumLH_ZO(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
		mat<4, 4, T, defaultp> Result(0);
		Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = farVal / (farVal - nearVal);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumLH_NO(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
		mat<4, 4, T, defaultp> Result(0);
		Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = (farVal + nearVal) / (farVal - nearVal);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = - (static_cast<T>(2) * farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumRH_ZO(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
		mat<4, 4, T, defaultp> Result(0);
		Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = farVal / (nearVal - farVal);
		Result[2][3] = static_cast<T>(-1);
		Result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumRH_NO(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
		mat<4, 4, T, defaultp> Result(0);
		Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = - (farVal + nearVal) / (farVal - nearVal);
		Result[2][3] = static_cast<T>(-1);
		Result[3][2] = - (static_cast<T>(2) * farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumZO(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return frustumLH_ZO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumNO(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return frustumLH_NO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumLH(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return frustumLH_ZO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumLH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustumRH(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return frustumLH_ZO(left, right, bottom, top, nearVal, farVal);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return frustumLH_NO(left, right, bottom, top, nearVal, farVal);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveRH_ZO(T fovy, T aspect, T zNear, T zFar)
	{
		assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		T const tanHalfFovy = tan(fovy / static_cast<T>(2));

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
		Result[2][2] = zFar / (zNear - zFar);
		Result[2][3] = - static_cast<T>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveRH_NO(T fovy, T aspect, T zNear, T zFar)
	{
		assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		T const tanHalfFovy = tan(fovy / static_cast<T>(2));

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
		Result[2][2] = - (zFar + zNear) / (zFar - zNear);
		Result[2][3] = - static_cast<T>(1);
		Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveLH_ZO(T fovy, T aspect, T zNear, T zFar)
	{
		assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		T const tanHalfFovy = tan(fovy / static_cast<T>(2));

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
		Result[2][2] = zFar / (zFar - zNear);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveLH_NO(T fovy, T aspect, T zNear, T zFar)
	{
		assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		T const tanHalfFovy = tan(fovy / static_cast<T>(2));

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
		Result[2][2] = (zFar + zNear) / (zFar - zNear);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveZO(T fovy, T aspect, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveNO(T fovy, T aspect, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveLH(T fovy, T aspect, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		endif

	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveRH(T fovy, T aspect, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspective(T fovy, T aspect, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovRH_ZO(T fov, T width, T height, T zNear, T zFar)
	{
		assert(width > static_cast<T>(0));
		assert(height > static_cast<T>(0));
		assert(fov > static_cast<T>(0));

		T const rad = fov;
		T const h = glm::cos(static_cast<T>(0.5) * rad) / glm::sin(static_cast<T>(0.5) * rad);
		T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = zFar / (zNear - zFar);
		Result[2][3] = - static_cast<T>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovRH_NO(T fov, T width, T height, T zNear, T zFar)
	{
		assert(width > static_cast<T>(0));
		assert(height > static_cast<T>(0));
		assert(fov > static_cast<T>(0));

		T const rad = fov;
		T const h = glm::cos(static_cast<T>(0.5) * rad) / glm::sin(static_cast<T>(0.5) * rad);
		T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = - (zFar + zNear) / (zFar - zNear);
		Result[2][3] = - static_cast<T>(1);
		Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovLH_ZO(T fov, T width, T height, T zNear, T zFar)
	{
		assert(width > static_cast<T>(0));
		assert(height > static_cast<T>(0));
		assert(fov > static_cast<T>(0));

		T const rad = fov;
		T const h = glm::cos(static_cast<T>(0.5) * rad) / glm::sin(static_cast<T>(0.5) * rad);
		T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = zFar / (zFar - zNear);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovLH_NO(T fov, T width, T height, T zNear, T zFar)
	{
		assert(width > static_cast<T>(0));
		assert(height > static_cast<T>(0));
		assert(fov > static_cast<T>(0));

		T const rad = fov;
		T const h = glm::cos(static_cast<T>(0.5) * rad) / glm::sin(static_cast<T>(0.5) * rad);
		T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = (zFar + zNear) / (zFar - zNear);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovZO(T fov, T width, T height, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveFovLH_ZO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovNO(T fov, T width, T height, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveFovLH_NO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovRH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovLH(T fov, T width, T height, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveFovLH_ZO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovLH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFovRH(T fov, T width, T height, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovRH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveFov(T fov, T width, T height, T zNear, T zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return perspectiveFovLH_ZO(fov, width, height, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return perspectiveFovLH_NO(fov, width, height, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return perspectiveFovRH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> infinitePerspectiveRH(T fovy, T aspect, T zNear)
	{
		T const range = tan(fovy / static_cast<T>(2)) * zNear;
		T const left = -range * aspect;
		T const right = range * aspect;
		T const bottom = -range;
		T const top = range;

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = (static_cast<T>(2) * zNear) / (right - left);
		Result[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
		Result[2][2] = - static_cast<T>(1);
		Result[2][3] = - static_cast<T>(1);
		Result[3][2] = - static_cast<T>(2) * zNear;
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> infinitePerspectiveLH(T fovy, T aspect, T zNear)
	{
		T const range = tan(fovy / static_cast<T>(2)) * zNear;
		T const left = -range * aspect;
		T const right = range * aspect;
		T const bottom = -range;
		T const top = range;

		mat<4, 4, T, defaultp> Result(T(0));
		Result[0][0] = (static_cast<T>(2) * zNear) / (right - left);
		Result[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
		Result[2][2] = static_cast<T>(1);
		Result[2][3] = static_cast<T>(1);
		Result[3][2] = - static_cast<T>(2) * zNear;
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> infinitePerspective(T fovy, T aspect, T zNear)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return infinitePerspectiveLH(fovy, aspect, zNear);
#		else
			return infinitePerspectiveRH(fovy, aspect, zNear);
#		endif
	}

	// Infinite projection matrix: http://www.terathon.com/gdc07_lengyel.pdf
	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> tweakedInfinitePerspective(T fovy, T aspect, T zNear, T ep)
	{
		T const range = tan(fovy / static_cast<T>(2)) * zNear;
		T const left = -range * aspect;
		T const right = range * aspect;
		T const bottom = -range;
		T const top = range;

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = (static_cast<T>(2) * zNear) / (right - left);
		Result[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
		Result[2][2] = ep - static_cast<T>(1);
		Result[2][3] = static_cast<T>(-1);
		Result[3][2] = (ep - static_cast<T>(2)) * zNear;
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> tweakedInfinitePerspective(T fovy, T aspect, T zNear)
	{
		return tweakedInfinitePerspective(fovy, aspect, zNear, epsilon<T>());
	}
}//namespace glm


#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_matrix_transform extension included")
#endif

namespace glm
{
	/// @addtogroup ext_matrix_transform
	/// @{

	/// Builds an identity matrix.
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType identity();

	/// Builds a translation 4 * 4 matrix created from a vector of 3 components.
	///
	/// @param m Input matrix multiplied by this translation matrix.
	/// @param v Coordinates of a translation vector.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @code
	/// #include <glm/glm.hpp>
	/// #include <glm/gtc/matrix_transform.hpp>
	/// ...
	/// glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
	/// // m[0][0] == 1.0f, m[0][1] == 0.0f, m[0][2] == 0.0f, m[0][3] == 0.0f
	/// // m[1][0] == 0.0f, m[1][1] == 1.0f, m[1][2] == 0.0f, m[1][3] == 0.0f
	/// // m[2][0] == 0.0f, m[2][1] == 0.0f, m[2][2] == 1.0f, m[2][3] == 0.0f
	/// // m[3][0] == 1.0f, m[3][1] == 1.0f, m[3][2] == 1.0f, m[3][3] == 1.0f
	/// @endcode
	///
	/// @see - translate(mat<4, 4, T, Q> const& m, T x, T y, T z)
	/// @see - translate(vec<3, T, Q> const& v)
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml">glTranslate man page</a>
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> translate(
		mat<4, 4, T, Q> const& m, vec<3, T, Q> const& v);

	/// Builds a rotation 4 * 4 matrix created from an axis vector and an angle.
	///
	/// @param m Input matrix multiplied by this rotation matrix.
	/// @param angle Rotation angle expressed in radians.
	/// @param axis Rotation axis, recommended to be normalized.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - rotate(mat<4, 4, T, Q> const& m, T angle, T x, T y, T z)
	/// @see - rotate(T angle, vec<3, T, Q> const& v)
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml">glRotate man page</a>
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> rotate(
		mat<4, 4, T, Q> const& m, T angle, vec<3, T, Q> const& axis);

	/// Builds a scale 4 * 4 matrix created from 3 scalars.
	///
	/// @param m Input matrix multiplied by this scale matrix.
	/// @param v Ratio of scaling for each axis.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - scale(mat<4, 4, T, Q> const& m, T x, T y, T z)
	/// @see - scale(vec<3, T, Q> const& v)
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glScale.xml">glScale man page</a>
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> scale(
		mat<4, 4, T, Q> const& m, vec<3, T, Q> const& v);

	/// Build a right handed look at view matrix.
	///
	/// @param eye Position of the camera
	/// @param center Position where the camera is looking at
	/// @param up Normalized up vector, how the camera is oriented. Typically (0, 0, 1)
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - frustum(T const& left, T const& right, T const& bottom, T const& top, T const& nearVal, T const& farVal) frustum(T const& left, T const& right, T const& bottom, T const& top, T const& nearVal, T const& farVal)
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> lookAtRH(
		vec<3, T, Q> const& eye, vec<3, T, Q> const& center, vec<3, T, Q> const& up);

	/// Build a left handed look at view matrix.
	///
	/// @param eye Position of the camera
	/// @param center Position where the camera is looking at
	/// @param up Normalized up vector, how the camera is oriented. Typically (0, 0, 1)
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - frustum(T const& left, T const& right, T const& bottom, T const& top, T const& nearVal, T const& farVal) frustum(T const& left, T const& right, T const& bottom, T const& top, T const& nearVal, T const& farVal)
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> lookAtLH(
		vec<3, T, Q> const& eye, vec<3, T, Q> const& center, vec<3, T, Q> const& up);

	/// Build a look at view matrix based on the default handedness.
	///
	/// @param eye Position of the camera
	/// @param center Position where the camera is looking at
	/// @param up Normalized up vector, how the camera is oriented. Typically (0, 0, 1)
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - frustum(T const& left, T const& right, T const& bottom, T const& top, T const& nearVal, T const& farVal) frustum(T const& left, T const& right, T const& bottom, T const& top, T const& nearVal, T const& farVal)
	/// @see <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml">gluLookAt man page</a>
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> lookAt(
		vec<3, T, Q> const& eye, vec<3, T, Q> const& center, vec<3, T, Q> const& up);

	/// @}
}//namespace glm

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR genType identity()
	{
		return detail::init_gentype<genType, detail::genTypeTrait<genType>::GENTYPE>::identity();
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> translate(mat<4, 4, T, Q> const& m, vec<3, T, Q> const& v)
	{
		mat<4, 4, T, Q> Result(m);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> rotate(mat<4, 4, T, Q> const& m, T angle, vec<3, T, Q> const& v)
	{
		T const a = angle;
		T const c = cos(a);
		T const s = sin(a);

		vec<3, T, Q> axis(normalize(v));
		vec<3, T, Q> temp((T(1) - c) * axis);

		mat<4, 4, T, Q> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		mat<4, 4, T, Q> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> rotate_slow(mat<4, 4, T, Q> const& m, T angle, vec<3, T, Q> const& v)
	{
		T const a = angle;
		T const c = cos(a);
		T const s = sin(a);
		mat<4, 4, T, Q> Result;

		vec<3, T, Q> axis = normalize(v);

		Result[0][0] = c + (static_cast<T>(1) - c)      * axis.x     * axis.x;
		Result[0][1] = (static_cast<T>(1) - c) * axis.x * axis.y + s * axis.z;
		Result[0][2] = (static_cast<T>(1) - c) * axis.x * axis.z - s * axis.y;
		Result[0][3] = static_cast<T>(0);

		Result[1][0] = (static_cast<T>(1) - c) * axis.y * axis.x - s * axis.z;
		Result[1][1] = c + (static_cast<T>(1) - c) * axis.y * axis.y;
		Result[1][2] = (static_cast<T>(1) - c) * axis.y * axis.z + s * axis.x;
		Result[1][3] = static_cast<T>(0);

		Result[2][0] = (static_cast<T>(1) - c) * axis.z * axis.x + s * axis.y;
		Result[2][1] = (static_cast<T>(1) - c) * axis.z * axis.y - s * axis.x;
		Result[2][2] = c + (static_cast<T>(1) - c) * axis.z * axis.z;
		Result[2][3] = static_cast<T>(0);

		Result[3] = vec<4, T, Q>(0, 0, 0, 1);
		return m * Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> scale(mat<4, 4, T, Q> const& m, vec<3, T, Q> const& v)
	{
		mat<4, 4, T, Q> Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> scale_slow(mat<4, 4, T, Q> const& m, vec<3, T, Q> const& v)
	{
		mat<4, 4, T, Q> Result(T(1));
		Result[0][0] = v.x;
		Result[1][1] = v.y;
		Result[2][2] = v.z;
		return m * Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> lookAtRH(vec<3, T, Q> const& eye, vec<3, T, Q> const& center, vec<3, T, Q> const& up)
	{
		vec<3, T, Q> const f(normalize(center - eye));
		vec<3, T, Q> const s(normalize(cross(f, up)));
		vec<3, T, Q> const u(cross(s, f));

		mat<4, 4, T, Q> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] =-f.x;
		Result[1][2] =-f.y;
		Result[2][2] =-f.z;
		Result[3][0] =-dot(s, eye);
		Result[3][1] =-dot(u, eye);
		Result[3][2] = dot(f, eye);
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> lookAtLH(vec<3, T, Q> const& eye, vec<3, T, Q> const& center, vec<3, T, Q> const& up)
	{
		vec<3, T, Q> const f(normalize(center - eye));
		vec<3, T, Q> const s(normalize(cross(up, f)));
		vec<3, T, Q> const u(cross(f, s));

		mat<4, 4, T, Q> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] = f.x;
		Result[1][2] = f.y;
		Result[2][2] = f.z;
		Result[3][0] = -dot(s, eye);
		Result[3][1] = -dot(u, eye);
		Result[3][2] = -dot(f, eye);
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> lookAt(vec<3, T, Q> const& eye, vec<3, T, Q> const& center, vec<3, T, Q> const& up)
	{
		GLM_IF_CONSTEXPR(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT)
			return lookAtLH(eye, center, up);
		else
			return lookAtRH(eye, center, up);
	}
}//namespace glm

	// ---------- "../ext/vector_relational.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_relational extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_relational
	/// @{

	/// Returns the component-wise comparison of |x - y| < epsilon.
	/// True if this expression is satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T epsilon);

	/// Returns the component-wise comparison of |x - y| < epsilon.
	/// True if this expression is satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, T, Q> const& epsilon);

	/// Returns the component-wise comparison of |x - y| >= epsilon.
	/// True if this expression is not satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T epsilon);

	/// Returns the component-wise comparison of |x - y| >= epsilon.
	/// True if this expression is not satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, T, Q> const& epsilon);

	/// Returns the component-wise comparison between two vectors in term of ULPs.
	/// True if this expression is satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, int ULPs);

	/// Returns the component-wise comparison between two vectors in term of ULPs.
	/// True if this expression is satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, int, Q> const& ULPs);

	/// Returns the component-wise comparison between two vectors in term of ULPs.
	/// True if this expression is not satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, int ULPs);

	/// Returns the component-wise comparison between two vectors in term of ULPs.
	/// True if this expression is not satisfied.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point
	/// @tparam Q Value from qualifier enum
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, int, Q> const& ULPs);

	/// @}
}//namespace glm

#if GLM_COMPILER == GLM_COMPILER_VC12
#	pragma warning(push)
#	pragma warning(disable: 4512) // assignment operator could not be generated
#endif

namespace glm{
namespace detail
{
	template <typename T>
	union float_t
	{};

	// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
	template <>
	union float_t<float>
	{
		typedef int int_type;
		typedef float float_type;

		GLM_CONSTEXPR float_t(float_type Num = 0.0f) : f(Num) {}

		GLM_CONSTEXPR float_t& operator=(float_t const& x)
		{
			f = x.f;
			return *this;
		}

		// Portable extraction of components.
		GLM_CONSTEXPR bool negative() const { return i < 0; }
		GLM_CONSTEXPR int_type mantissa() const { return i & ((1 << 23) - 1); }
		GLM_CONSTEXPR int_type exponent() const { return (i >> 23) & ((1 << 8) - 1); }

		int_type i;
		float_type f;
	};

	template <>
	union float_t<double>
	{
		typedef detail::int64 int_type;
		typedef double float_type;

		GLM_CONSTEXPR float_t(float_type Num = static_cast<float_type>(0)) : f(Num) {}

		GLM_CONSTEXPR float_t& operator=(float_t const& x)
		{
			f = x.f;
			return *this;
		}

		// Portable extraction of components.
		GLM_CONSTEXPR bool negative() const { return i < 0; }
		GLM_CONSTEXPR int_type mantissa() const { return i & ((int_type(1) << 52) - 1); }
		GLM_CONSTEXPR int_type exponent() const { return (i >> 52) & ((int_type(1) << 11) - 1); }

		int_type i;
		float_type f;
	};
}//namespace detail
}//namespace glm

#if GLM_COMPILER == GLM_COMPILER_VC12
#	pragma warning(pop)
#endif



namespace glm
{
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T Epsilon)
	{
		return equal(x, y, vec<L, T, Q>(Epsilon));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, T, Q> const& Epsilon)
	{
		return lessThanEqual(abs(x - y), Epsilon);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T Epsilon)
	{
		return notEqual(x, y, vec<L, T, Q>(Epsilon));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, T, Q> const& Epsilon)
	{
		return greaterThan(abs(x - y), Epsilon);
	}


	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, int MaxULPs)
	{
		return equal(x, y, vec<L, int, Q>(MaxULPs));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> equal(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, int, Q> const& MaxULPs)
	{
		vec<L, bool, Q> Result(false);
		for(length_t i = 0; i < L; ++i)
		{
			detail::float_t<T> const a(x[i]);
			detail::float_t<T> const b(y[i]);

			// Different signs means they do not match.
			if(a.negative() != b.negative())
			{
				// Check for equality to make sure +0==-0
				Result[i] = a.mantissa() == b.mantissa() && a.exponent() == b.exponent();
			}
			else
			{
				// Find the difference in ULPs.
				typename detail::float_t<T>::int_type const DiffULPs = abs(a.i - b.i);
				Result[i] = DiffULPs <= MaxULPs[i];
			}
		}
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, int MaxULPs)
	{
		return notEqual(x, y, vec<L, int, Q>(MaxULPs));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, bool, Q> notEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, int, Q> const& MaxULPs)
	{
		return not_(equal(x, y, MaxULPs));
	}
}//namespace glm



	// ---------- "../ext/quaternion_common.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_geometric extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_geometric
	/// @{

	/// Returns the norm of a quaternions
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_geometric
	template<typename T, qualifier Q>
	GLM_FUNC_DECL T length(qua<T, Q> const& q);

	/// Returns the normalized quaternion.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_geometric
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> normalize(qua<T, Q> const& q);

	/// Returns dot product of q1 and q2, i.e., q1[0] * q2[0] + q1[1] * q2[1] + ...
	///
	/// @tparam T Floating-point scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_geometric
	template<typename T, qualifier Q>
	GLM_FUNC_DECL T dot(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Compute a cross product.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_geometric
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> cross(qua<T, Q> const& q1, qua<T, Q> const& q2);

	/// @}
} //namespace glm

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T dot(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
		return detail::compute_dot<qua<T, Q>, T, detail::is_aligned<Q>::value>::call(x, y);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T length(qua<T, Q> const& q)
	{
		return glm::sqrt(dot(q, q));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> normalize(qua<T, Q> const& q)
	{
		T len = length(q);
		if(len <= static_cast<T>(0)) // Problem
			return qua<T, Q>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
		T oneOverLen = static_cast<T>(1) / len;
		return qua<T, Q>(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> cross(qua<T, Q> const& q1, qua<T, Q> const& q2)
	{
		return qua<T, Q>(
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
	}
}//namespace glm



#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_common extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_common
	/// @{

	/// Spherical linear interpolation of two quaternions.
	/// The interpolation is oriented and the rotation is performed at constant speed.
	/// For short path spherical linear interpolation, use the slerp function.
	///
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - slerp(qua<T, Q> const& x, qua<T, Q> const& y, T const& a)
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> mix(qua<T, Q> const& x, qua<T, Q> const& y, T a);

	/// Linear interpolation of two quaternions.
	/// The interpolation is oriented.
	///
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined in the range [0, 1].
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> lerp(qua<T, Q> const& x, qua<T, Q> const& y, T a);

	/// Spherical linear interpolation of two quaternions.
	/// The interpolation always take the short path and the rotation is performed at constant speed.
	///
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> slerp(qua<T, Q> const& x, qua<T, Q> const& y, T a);

    /// Spherical linear interpolation of two quaternions with multiple spins over rotation axis.
    /// The interpolation always take the short path when the spin count is positive and long path
    /// when count is negative. Rotation is performed at constant speed.
    ///
    /// @param x A quaternion
    /// @param y A quaternion
    /// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
    /// @param k Additional spin count. If Value is negative interpolation will be on "long" path.
    ///
    /// @tparam T A floating-point scalar type
    /// @tparam S An integer scalar type
    /// @tparam Q A value from qualifier enum
    template<typename T, typename S, qualifier Q>
    GLM_FUNC_DECL qua<T, Q> slerp(qua<T, Q> const& x, qua<T, Q> const& y, T a, S k);

	/// Returns the q conjugate.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> conjugate(qua<T, Q> const& q);

	/// Returns the q inverse.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> inverse(qua<T, Q> const& q);

	/// Returns true if x holds a NaN (not a number)
	/// representation in the underlying implementation's set of
	/// floating point representations. Returns false otherwise,
	/// including for implementations with no NaN
	/// representations.
	///
	/// /!\ When using compiler fast math, this function may fail.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> isnan(qua<T, Q> const& x);

	/// Returns true if x holds a positive infinity or negative
	/// infinity representation in the underlying implementation's
	/// set of floating point representations. Returns false
	/// otherwise, including for implementations with no infinity
	/// representations.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> isinf(qua<T, Q> const& x);

	/// @}
} //namespace glm

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> mix(qua<T, Q> const& x, qua<T, Q> const& y, T a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'mix' only accept floating-point inputs");

		T const cosTheta = dot(x, y);

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > static_cast<T>(1) - epsilon<T>())
		{
			// Linear interpolation
			return qua<T, Q>(
				mix(x.w, y.w, a),
				mix(x.x, y.x, a),
				mix(x.y, y.y, a),
				mix(x.z, y.z, a));
		}
		else
		{
			// Essential Mathematics, page 467
			T angle = acos(cosTheta);
			return (sin((static_cast<T>(1) - a) * angle) * x + sin(a * angle) * y) / sin(angle);
		}
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> lerp(qua<T, Q> const& x, qua<T, Q> const& y, T a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lerp' only accept floating-point inputs");

		// Lerp is only defined in [0, 1]
		assert(a >= static_cast<T>(0));
		assert(a <= static_cast<T>(1));

		return x * (static_cast<T>(1) - a) + (y * a);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> slerp(qua<T, Q> const& x, qua<T, Q> const& y, T a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'slerp' only accept floating-point inputs");

		qua<T, Q> z = y;

		T cosTheta = dot(x, y);

		// If cosTheta < 0, the interpolation will take the long way around the sphere.
		// To fix this, one quat must be negated.
		if(cosTheta < static_cast<T>(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > static_cast<T>(1) - epsilon<T>())
		{
			// Linear interpolation
			return qua<T, Q>(
				mix(x.w, z.w, a),
				mix(x.x, z.x, a),
				mix(x.y, z.y, a),
				mix(x.z, z.z, a));
		}
		else
		{
			// Essential Mathematics, page 467
			T angle = acos(cosTheta);
			return (sin((static_cast<T>(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
		}
	}

    template<typename T, typename S, qualifier Q>
    GLM_FUNC_QUALIFIER qua<T, Q> slerp(qua<T, Q> const& x, qua<T, Q> const& y, T a, S k)
    {
        GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'slerp' only accept floating-point inputs");
        GLM_STATIC_ASSERT(std::numeric_limits<S>::is_integer, "'slerp' only accept integer for spin count");

        qua<T, Q> z = y;

        T cosTheta = dot(x, y);

        // If cosTheta < 0, the interpolation will take the long way around the sphere.
        // To fix this, one quat must be negated.
        if (cosTheta < static_cast<T>(0))
        {
            z = -y;
            cosTheta = -cosTheta;
        }

        // Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
        if (cosTheta > static_cast<T>(1) - epsilon<T>())
        {
            // Linear interpolation
            return qua<T, Q>(
                mix(x.w, z.w, a),
                mix(x.x, z.x, a),
                mix(x.y, z.y, a),
                mix(x.z, z.z, a));
        }
        else
        {
            // Graphics Gems III, page 96
            T angle = acos(cosTheta);
            T phi = angle + k * glm::pi<T>();
            return (sin(angle - a * phi)* x + sin(a * phi) * z) / sin(angle);
        }
    }

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> conjugate(qua<T, Q> const& q)
	{
		return qua<T, Q>(q.w, -q.x, -q.y, -q.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> inverse(qua<T, Q> const& q)
	{
		return conjugate(q) / dot(q, q);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isnan(qua<T, Q> const& q)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isnan' only accept floating-point inputs");

		return vec<4, bool, Q>(isnan(q.x), isnan(q.y), isnan(q.z), isnan(q.w));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isinf(qua<T, Q> const& q)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isinf' only accept floating-point inputs");

		return vec<4, bool, Q>(isinf(q.x), isinf(q.y), isinf(q.z), isinf(q.w));
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "ext/quaternion_common_simd.inl"
#endif




	// ---------- "../ext/quaternion_float.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_relational extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_relational
	/// @{

	/// Returns the component-wise comparison of result x == y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> equal(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of |x - y| < epsilon.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> equal(qua<T, Q> const& x, qua<T, Q> const& y, T epsilon);

	/// Returns the component-wise comparison of result x != y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> notEqual(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of |x - y| >= epsilon.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> notEqual(qua<T, Q> const& x, qua<T, Q> const& y, T epsilon);

	/// @}
} //namespace glm

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> equal(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] == y[i];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> equal(qua<T, Q> const& x, qua<T, Q> const& y, T epsilon)
	{
		vec<4, T, Q> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
		return lessThan(abs(v), vec<4, T, Q>(epsilon));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> notEqual(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] != y[i];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> notEqual(qua<T, Q> const& x, qua<T, Q> const& y, T epsilon)
	{
		vec<4, T, Q> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
		return greaterThanEqual(abs(v), vec<4, T, Q>(epsilon));
	}
}//namespace glm



namespace glm
{
	template<typename T, qualifier Q>
	struct qua
	{
		// -- Implementation detail --

		typedef qua<T, Q> type;
		typedef T value_type;

		// -- Data --

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic push
#				pragma GCC diagnostic ignored "-Wpedantic"
#			elif GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic push
#				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#				pragma clang diagnostic ignored "-Wnested-anon-types"
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(push)
#				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#			endif
#		endif

#		if GLM_LANG & GLM_LANG_CXXMS_FLAG
			union
			{
#				ifdef GLM_FORCE_QUAT_DATA_WXYZ
					struct { T w, x, y, z; };
#				else
					struct { T x, y, z, w; };
#				endif

				typename detail::storage<4, T, detail::is_aligned<Q>::value>::type data;
			};
#		else
#			ifdef GLM_FORCE_QUAT_DATA_WXYZ
				T w, x, y, z;
#			else
				T x, y, z, w;
#			endif
#		endif

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(pop)
#			endif
#		endif

		// -- Component accesses --

		typedef length_t length_type;

		/// Return the count of components of a quaternion
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 4;}

		GLM_FUNC_DECL GLM_CONSTEXPR T & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR T const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR qua() GLM_DEFAULT;
		GLM_FUNC_DECL GLM_CONSTEXPR qua(qua<T, Q> const& q) GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR qua(qua<T, P> const& q);

		// -- Explicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR qua(T s, vec<3, T, Q> const& v);
		GLM_FUNC_DECL GLM_CONSTEXPR qua(T w, T x, T y, T z);

		// -- Conversion constructors --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT qua(qua<U, P> const& q);

		/// Explicit conversion operators
#		if GLM_HAS_EXPLICIT_CONVERSION_OPERATORS
			GLM_FUNC_DECL explicit operator mat<3, 3, T, Q>() const;
			GLM_FUNC_DECL explicit operator mat<4, 4, T, Q>() const;
#		endif

		/// Create a quaternion from two normalized axis
		///
		/// @param u A first normalized axis
		/// @param v A second normalized axis
		/// @see gtc_quaternion
		/// @see http://lolengine.net/blog/2013/09/18/beautiful-maths-quaternion-from-vectors
		GLM_FUNC_DECL qua(vec<3, T, Q> const& u, vec<3, T, Q> const& v);

		/// Build a quaternion from euler angles (pitch, yaw, roll), in radians.
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT qua(vec<3, T, Q> const& eulerAngles);
		GLM_FUNC_DECL GLM_EXPLICIT qua(mat<3, 3, T, Q> const& q);
		GLM_FUNC_DECL GLM_EXPLICIT qua(mat<4, 4, T, Q> const& q);

		// -- Unary arithmetic operators --

		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator=(qua<T, Q> const& q) GLM_DEFAULT;

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator=(qua<U, Q> const& q);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator+=(qua<U, Q> const& q);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator-=(qua<U, Q> const& q);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator*=(qua<U, Q> const& q);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q>& operator/=(U s);
	};

	// -- Unary bit operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator+(qua<T, Q> const& q);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator-(qua<T, Q> const& q);

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator+(qua<T, Q> const& q, qua<T, Q> const& p);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator-(qua<T, Q> const& q, qua<T, Q> const& p);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator*(qua<T, Q> const& q, qua<T, Q> const& p);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(qua<T, Q> const& q, vec<3, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v, qua<T, Q> const& q);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(qua<T, Q> const& q, vec<4, T, Q> const& v);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v, qua<T, Q> const& q);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator*(qua<T, Q> const& q, T const& s);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator*(T const& s, qua<T, Q> const& q);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<T, Q> operator/(qua<T, Q> const& q, T const& s);

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(qua<T, Q> const& q1, qua<T, Q> const& q2);

	template<typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator!=(qua<T, Q> const& q1, qua<T, Q> const& q2);
} //namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE

namespace glm{
namespace detail
{
	template <typename T>
	struct genTypeTrait<qua<T> >
	{
		static const genTypeEnum GENTYPE = GENTYPE_QUAT;
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_dot<qua<T, Q>, T, Aligned>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static T call(qua<T, Q> const& a, qua<T, Q> const& b)
		{
			vec<4, T, Q> tmp(a.w * b.w, a.x * b.x, a.y * b.y, a.z * b.z);
			return (tmp.x + tmp.y) + (tmp.z + tmp.w);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_quat_add
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<T, Q> call(qua<T, Q> const& q, qua<T, Q> const& p)
		{
			return qua<T, Q>(q.w + p.w, q.x + p.x, q.y + p.y, q.z + p.z);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_quat_sub
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<T, Q> call(qua<T, Q> const& q, qua<T, Q> const& p)
		{
			return qua<T, Q>(q.w - p.w, q.x - p.x, q.y - p.y, q.z - p.z);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_quat_mul_scalar
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<T, Q> call(qua<T, Q> const& q, T s)
		{
			return qua<T, Q>(q.w * s, q.x * s, q.y * s, q.z * s);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_quat_div_scalar
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<T, Q> call(qua<T, Q> const& q, T s)
		{
			return qua<T, Q>(q.w / s, q.x / s, q.y / s, q.z / s);
		}
	};

	template<typename T, qualifier Q, bool Aligned>
	struct compute_quat_mul_vec4
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, T, Q> call(qua<T, Q> const& q, vec<4, T, Q> const& v)
		{
			return vec<4, T, Q>(q * vec<3, T, Q>(v), v.w);
		}
	};
}//namespace detail

	// -- Component accesses --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T & qua<T, Q>::operator[](typename qua<T, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			return (&w)[i];
#		else
			return (&x)[i];
#		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR T const& qua<T, Q>::operator[](typename qua<T, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			return (&w)[i];
#		else
			return (&x)[i];
#		endif
	}

	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
#				ifdef GLM_FORCE_QUAT_DATA_WXYZ
					: w(1), x(0), y(0), z(0)
#				else
					: x(0), y(0), z(0), w(1)
#				endif
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(qua<T, Q> const& q)
#			ifdef GLM_FORCE_QUAT_DATA_WXYZ
				: w(q.w), x(q.x), y(q.y), z(q.z)
#			else
				: x(q.x), y(q.y), z(q.z), w(q.w)
#			endif
		{}
#	endif

	template<typename T, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(qua<T, P> const& q)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(q.w), x(q.x), y(q.y), z(q.z)
#		else
			: x(q.x), y(q.y), z(q.z), w(q.w)
#		endif
	{}

	// -- Explicit basic constructors --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(T s, vec<3, T, Q> const& v)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(s), x(v.x), y(v.y), z(v.z)
#		else
			: x(v.x), y(v.y), z(v.z), w(s)
#		endif
	{}

	template <typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(T _w, T _x, T _y, T _z)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(_w), x(_x), y(_y), z(_z)
#		else
			: x(_x), y(_y), z(_z), w(_w)
#		endif
	{}

	// -- Conversion constructors --

	template<typename T, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(qua<U, P> const& q)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(static_cast<T>(q.w)), x(static_cast<T>(q.x)), y(static_cast<T>(q.y)), z(static_cast<T>(q.z))
#		else
			: x(static_cast<T>(q.x)), y(static_cast<T>(q.y)), z(static_cast<T>(q.z)), w(static_cast<T>(q.w))
#		endif
	{}

	//template<typename valType>
	//GLM_FUNC_QUALIFIER qua<valType>::qua
	//(
	//	valType const& pitch,
	//	valType const& yaw,
	//	valType const& roll
	//)
	//{
	//	vec<3, valType> eulerAngle(pitch * valType(0.5), yaw * valType(0.5), roll * valType(0.5));
	//	vec<3, valType> c = glm::cos(eulerAngle * valType(0.5));
	//	vec<3, valType> s = glm::sin(eulerAngle * valType(0.5));
	//
	//	this->w = c.x * c.y * c.z + s.x * s.y * s.z;
	//	this->x = s.x * c.y * c.z - c.x * s.y * s.z;
	//	this->y = c.x * s.y * c.z + s.x * c.y * s.z;
	//	this->z = c.x * c.y * s.z - s.x * s.y * c.z;
	//}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q>::qua(vec<3, T, Q> const& u, vec<3, T, Q> const& v)
	{
		T norm_u_norm_v = sqrt(dot(u, u) * dot(v, v));
		T real_part = norm_u_norm_v + dot(u, v);
		vec<3, T, Q> t;

		if(real_part < static_cast<T>(1.e-6f) * norm_u_norm_v)
		{
			// If u and v are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			real_part = static_cast<T>(0);
			t = abs(u.x) > abs(u.z) ? vec<3, T, Q>(-u.y, u.x, static_cast<T>(0)) : vec<3, T, Q>(static_cast<T>(0), -u.z, u.y);
		}
		else
		{
			// Otherwise, build quaternion the standard way.
			t = cross(u, v);
		}

		*this = normalize(qua<T, Q>(real_part, t.x, t.y, t.z));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(vec<3, T, Q> const& eulerAngle)
	{
		vec<3, T, Q> c = glm::cos(eulerAngle * T(0.5));
		vec<3, T, Q> s = glm::sin(eulerAngle * T(0.5));

		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q>::qua(mat<3, 3, T, Q> const& m)
	{
		*this = quat_cast(m);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q>::qua(mat<4, 4, T, Q> const& m)
	{
		*this = quat_cast(m);
	}

#	if GLM_HAS_EXPLICIT_CONVERSION_OPERATORS
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q>::operator mat<3, 3, T, Q>() const
	{
		return mat3_cast(*this);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q>::operator mat<4, 4, T, Q>() const
	{
		return mat4_cast(*this);
	}
#	endif//GLM_HAS_EXPLICIT_CONVERSION_OPERATORS

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator=(qua<T, Q> const& q)
		{
			this->w = q.w;
			this->x = q.x;
			this->y = q.y;
			this->z = q.z;
			return *this;
		}
#	endif

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator=(qua<U, Q> const& q)
	{
		this->w = static_cast<T>(q.w);
		this->x = static_cast<T>(q.x);
		this->y = static_cast<T>(q.y);
		this->z = static_cast<T>(q.z);
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator+=(qua<U, Q> const& q)
	{
		return (*this = detail::compute_quat_add<T, Q, detail::is_aligned<Q>::value>::call(*this, qua<T, Q>(q)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator-=(qua<U, Q> const& q)
	{
		return (*this = detail::compute_quat_sub<T, Q, detail::is_aligned<Q>::value>::call(*this, qua<T, Q>(q)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator*=(qua<U, Q> const& r)
	{
		qua<T, Q> const p(*this);
		qua<T, Q> const q(r);

		this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
		return *this;
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator*=(U s)
	{
		return (*this = detail::compute_quat_mul_scalar<T, Q, detail::is_aligned<Q>::value>::call(*this, static_cast<U>(s)));
	}

	template<typename T, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator/=(U s)
	{
		return (*this = detail::compute_quat_div_scalar<T, Q, detail::is_aligned<Q>::value>::call(*this, static_cast<U>(s)));
	}

	// -- Unary bit operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator+(qua<T, Q> const& q)
	{
		return q;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator-(qua<T, Q> const& q)
	{
		return qua<T, Q>(-q.w, -q.x, -q.y, -q.z);
	}

	// -- Binary operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator+(qua<T, Q> const& q, qua<T, Q> const& p)
	{
		return qua<T, Q>(q) += p;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator-(qua<T, Q> const& q, qua<T, Q> const& p)
	{
		return qua<T, Q>(q) -= p;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator*(qua<T, Q> const& q, qua<T, Q> const& p)
	{
		return qua<T, Q>(q) *= p;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(qua<T, Q> const& q, vec<3, T, Q> const& v)
	{
		vec<3, T, Q> const QuatVector(q.x, q.y, q.z);
		vec<3, T, Q> const uv(glm::cross(QuatVector, v));
		vec<3, T, Q> const uuv(glm::cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<T>(2);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q> operator*(vec<3, T, Q> const& v, qua<T, Q> const& q)
	{
		return glm::inverse(q) * v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(qua<T, Q> const& q, vec<4, T, Q> const& v)
	{
		return detail::compute_quat_mul_vec4<T, Q, detail::is_aligned<Q>::value>::call(q, v);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, T, Q> operator*(vec<4, T, Q> const& v, qua<T, Q> const& q)
	{
		return glm::inverse(q) * v;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator*(qua<T, Q> const& q, T const& s)
	{
		return qua<T, Q>(
			q.w * s, q.x * s, q.y * s, q.z * s);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator*(T const& s, qua<T, Q> const& q)
	{
		return q * s;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> operator/(qua<T, Q> const& q, T const& s)
	{
		return qua<T, Q>(
			q.w / s, q.x / s, q.y / s, q.z / s);
	}

	// -- Boolean operators --

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(qua<T, Q> const& q1, qua<T, Q> const& q2)
	{
		return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(qua<T, Q> const& q1, qua<T, Q> const& q2)
	{
		return q1.x != q2.x || q1.y != q2.y || q1.z != q2.z || q1.w != q2.w;
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "detail/type_quat_simd.inl"
#endif



#endif//GLM_EXTERNAL_TEMPLATE


#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_float extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_float
	/// @{

	/// Quaternion of single-precision floating-point numbers.
	typedef qua<float, defaultp>		quat;

	/// @}
} //namespace glm



	// ---------- "../ext/quaternion_float_precision.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_float_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_float_precision
	/// @{

	/// Quaternion of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	typedef qua<float, lowp>		lowp_quat;

	/// Quaternion of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	typedef qua<float, mediump>		mediump_quat;

	/// Quaternion of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	typedef qua<float, highp>		highp_quat;

	/// @}
} //namespace glm



	// ---------- "../ext/quaternion_double.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_double extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_double
	/// @{

	/// Quaternion of double-precision floating-point numbers.
	typedef qua<double, defaultp>		dquat;

	/// @}
} //namespace glm



	// ---------- "../ext/quaternion_double_precision.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_double_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_double_precision
	/// @{

	/// Quaternion of double-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see ext_quaternion_double_precision
	typedef qua<double, lowp>		lowp_dquat;

	/// Quaternion of medium double-qualifier floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see ext_quaternion_double_precision
	typedef qua<double, mediump>	mediump_dquat;

	/// Quaternion of high double-qualifier floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see ext_quaternion_double_precision
	typedef qua<double, highp>		highp_dquat;

	/// @}
} //namespace glm


	// ---------- "../ext/quaternion_relational.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_relational extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_relational
	/// @{

	/// Returns the component-wise comparison of result x == y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> equal(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of |x - y| < epsilon.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> equal(qua<T, Q> const& x, qua<T, Q> const& y, T epsilon);

	/// Returns the component-wise comparison of result x != y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> notEqual(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of |x - y| >= epsilon.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> notEqual(qua<T, Q> const& x, qua<T, Q> const& y, T epsilon);

	/// @}
} //namespace glm

	// ---------- "../ext/quaternion_trigonometric.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_trigonometric extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_trigonometric
	/// @{

	/// Returns the quaternion rotation angle.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL T angle(qua<T, Q> const& x);

	/// Returns the q rotation axis.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> axis(qua<T, Q> const& x);

	/// Build a quaternion from an angle and a normalized axis.
	///
	/// @param angle Angle expressed in radians.
	/// @param axis Axis of the quaternion, must be normalized.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> angleAxis(T const& angle, vec<3, T, Q> const& axis);

	/// @}
} //namespace glm

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T angle(qua<T, Q> const& x)
	{
		if (abs(x.w) > cos_one_over_two<T>())
		{
			return asin(sqrt(x.x * x.x + x.y * x.y + x.z * x.z)) * static_cast<T>(2);
		}

		return acos(x.w) * static_cast<T>(2);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> axis(qua<T, Q> const& x)
	{
		T const tmp1 = static_cast<T>(1) - x.w * x.w;
		if(tmp1 <= static_cast<T>(0))
			return vec<3, T, Q>(0, 0, 1);
		T const tmp2 = static_cast<T>(1) / sqrt(tmp1);
		return vec<3, T, Q>(x.x * tmp2, x.y * tmp2, x.z * tmp2);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> angleAxis(T const& angle, vec<3, T, Q> const& v)
	{
		T const a(angle);
		T const s = glm::sin(a * static_cast<T>(0.5));

		return qua<T, Q>(glm::cos(a * static_cast<T>(0.5)), v * s);
	}
}//namespace glm



	// ---------- "../ext/quaternion_transform.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_transform extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_transform
	/// @{

	/// Rotates a quaternion from a vector of 3 components axis and an angle.
	///
	/// @param q Source orientation
	/// @param angle Angle expressed in radians.
	/// @param axis Axis of the rotation
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> rotate(qua<T, Q> const& q, T const& angle, vec<3, T, Q> const& axis);
	/// @}
} //namespace glm

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> rotate(qua<T, Q> const& q, T const& angle, vec<3, T, Q> const& v)
	{
		vec<3, T, Q> Tmp = v;

		// Axis of rotation must be normalised
		T len = glm::length(Tmp);
		if(abs(len - static_cast<T>(1)) > static_cast<T>(0.001))
		{
			T oneOverLen = static_cast<T>(1) / len;
			Tmp.x *= oneOverLen;
			Tmp.y *= oneOverLen;
			Tmp.z *= oneOverLen;
		}

		T const AngleRad(angle);
		T const Sin = sin(AngleRad * static_cast<T>(0.5));

		return q * qua<T, Q>(cos(AngleRad * static_cast<T>(0.5)), Tmp.x * Sin, Tmp.y * Sin, Tmp.z * Sin);
	}
}//namespace glm



// ----------------------------------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTC_quaternion extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_quaternion
	/// @{

	/// Returns euler angles, pitch as x, yaw as y, roll as z.
	/// The result is expressed in radians.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> eulerAngles(qua<T, Q> const& x);

	/// Returns roll value of euler angles expressed in radians.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL T roll(qua<T, Q> const& x);

	/// Returns pitch value of euler angles expressed in radians.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL T pitch(qua<T, Q> const& x);

	/// Returns yaw value of euler angles expressed in radians.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL T yaw(qua<T, Q> const& x);

	/// Converts a quaternion to a 3 * 3 matrix.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, T, Q> mat3_cast(qua<T, Q> const& x);

	/// Converts a quaternion to a 4 * 4 matrix.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> mat4_cast(qua<T, Q> const& x);

	/// Converts a pure rotation 3 * 3 matrix to a quaternion.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> quat_cast(mat<3, 3, T, Q> const& x);

	/// Converts a pure rotation 4 * 4 matrix to a quaternion.
	///
	/// @tparam T Floating-point scalar types.
	///
	/// @see gtc_quaternion
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> quat_cast(mat<4, 4, T, Q> const& x);

	/// Returns the component-wise comparison result of x < y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_relational
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> lessThan(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of result x <= y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_relational
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> lessThanEqual(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of result x > y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_relational
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> greaterThan(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Returns the component-wise comparison of result x >= y.
	///
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_quaternion_relational
	template<typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> greaterThanEqual(qua<T, Q> const& x, qua<T, Q> const& y);

	/// Build a look at quaternion based on the default handedness.
	///
	/// @param direction Desired forward direction. Needs to be normalized.
	/// @param up Up vector, how the camera is oriented. Typically (0, 1, 0).
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> quatLookAt(
		vec<3, T, Q> const& direction,
		vec<3, T, Q> const& up);

	/// Build a right-handed look at quaternion.
	///
	/// @param direction Desired forward direction onto which the -z-axis gets mapped. Needs to be normalized.
	/// @param up Up vector, how the camera is oriented. Typically (0, 1, 0).
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> quatLookAtRH(
		vec<3, T, Q> const& direction,
		vec<3, T, Q> const& up);

	/// Build a left-handed look at quaternion.
	///
	/// @param direction Desired forward direction onto which the +z-axis gets mapped. Needs to be normalized.
	/// @param up Up vector, how the camera is oriented. Typically (0, 1, 0).
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> quatLookAtLH(
		vec<3, T, Q> const& direction,
		vec<3, T, Q> const& up);
	/// @}
} //namespace glm

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTC_epsilon extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_epsilon
	/// @{

	/// Returns the component-wise comparison of |x - y| < epsilon.
	/// True if this expression is satisfied.
	///
	/// @see gtc_epsilon
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> epsilonEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T const& epsilon);

	/// Returns the component-wise comparison of |x - y| < epsilon.
	/// True if this expression is satisfied.
	///
	/// @see gtc_epsilon
	template<typename genType>
	GLM_FUNC_DECL bool epsilonEqual(genType const& x, genType const& y, genType const& epsilon);

	/// Returns the component-wise comparison of |x - y| < epsilon.
	/// True if this expression is not satisfied.
	///
	/// @see gtc_epsilon
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> epsilonNotEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T const& epsilon);

	/// Returns the component-wise comparison of |x - y| >= epsilon.
	/// True if this expression is not satisfied.
	///
	/// @see gtc_epsilon
	template<typename genType>
	GLM_FUNC_DECL bool epsilonNotEqual(genType const& x, genType const& y, genType const& epsilon);

	/// @}
}//namespace glm

namespace glm
{
	template<>
	GLM_FUNC_QUALIFIER bool epsilonEqual
	(
		float const& x,
		float const& y,
		float const& epsilon
	)
	{
		return abs(x - y) < epsilon;
	}

	template<>
	GLM_FUNC_QUALIFIER bool epsilonEqual
	(
		double const& x,
		double const& y,
		double const& epsilon
	)
	{
		return abs(x - y) < epsilon;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> epsilonEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T const& epsilon)
	{
		return lessThan(abs(x - y), vec<L, T, Q>(epsilon));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> epsilonEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, T, Q> const& epsilon)
	{
		return lessThan(abs(x - y), vec<L, T, Q>(epsilon));
	}

	template<>
	GLM_FUNC_QUALIFIER bool epsilonNotEqual(float const& x, float const& y, float const& epsilon)
	{
		return abs(x - y) >= epsilon;
	}

	template<>
	GLM_FUNC_QUALIFIER bool epsilonNotEqual(double const& x, double const& y, double const& epsilon)
	{
		return abs(x - y) >= epsilon;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> epsilonNotEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, T const& epsilon)
	{
		return greaterThanEqual(abs(x - y), vec<L, T, Q>(epsilon));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> epsilonNotEqual(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, T, Q> const& epsilon)
	{
		return greaterThanEqual(abs(x - y), vec<L, T, Q>(epsilon));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> epsilonEqual(qua<T, Q> const& x, qua<T, Q> const& y, T const& epsilon)
	{
		vec<4, T, Q> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
		return lessThan(abs(v), vec<4, T, Q>(epsilon));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> epsilonNotEqual(qua<T, Q> const& x, qua<T, Q> const& y, T const& epsilon)
	{
		vec<4, T, Q> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
		return greaterThanEqual(abs(v), vec<4, T, Q>(epsilon));
	}
}//namespace glm

namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, T, Q> eulerAngles(qua<T, Q> const& x)
	{
		return vec<3, T, Q>(pitch(x), yaw(x), roll(x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T roll(qua<T, Q> const& q)
	{
		return static_cast<T>(atan(static_cast<T>(2) * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T pitch(qua<T, Q> const& q)
	{
		//return T(atan(T(2) * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
		T const y = static_cast<T>(2) * (q.y * q.z + q.w * q.x);
		T const x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;

		if(all(equal(vec<2, T, Q>(x, y), vec<2, T, Q>(0), epsilon<T>()))) //avoid atan2(0,0) - handle singularity - Matiis
			return static_cast<T>(static_cast<T>(2) * atan(q.x, q.w));

		return static_cast<T>(atan(y, x));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T yaw(qua<T, Q> const& q)
	{
		return asin(clamp(static_cast<T>(-2) * (q.x * q.z - q.w * q.y), static_cast<T>(-1), static_cast<T>(1)));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> mat3_cast(qua<T, Q> const& q)
	{
		mat<3, 3, T, Q> Result(T(1));
		T qxx(q.x * q.x);
		T qyy(q.y * q.y);
		T qzz(q.z * q.z);
		T qxz(q.x * q.z);
		T qxy(q.x * q.y);
		T qyz(q.y * q.z);
		T qwx(q.w * q.x);
		T qwy(q.w * q.y);
		T qwz(q.w * q.z);

		Result[0][0] = T(1) - T(2) * (qyy +  qzz);
		Result[0][1] = T(2) * (qxy + qwz);
		Result[0][2] = T(2) * (qxz - qwy);

		Result[1][0] = T(2) * (qxy - qwz);
		Result[1][1] = T(1) - T(2) * (qxx +  qzz);
		Result[1][2] = T(2) * (qyz + qwx);

		Result[2][0] = T(2) * (qxz + qwy);
		Result[2][1] = T(2) * (qyz - qwx);
		Result[2][2] = T(1) - T(2) * (qxx +  qyy);
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> mat4_cast(qua<T, Q> const& q)
	{
		return mat<4, 4, T, Q>(mat3_cast(q));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> quat_cast(mat<3, 3, T, Q> const& m)
	{
		T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex = 0;
		T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		T biggestVal = sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1)) * static_cast<T>(0.5);
		T mult = static_cast<T>(0.25) / biggestVal;

		switch(biggestIndex)
		{
		case 0:
			return qua<T, Q>(biggestVal, (m[1][2] - m[2][1]) * mult, (m[2][0] - m[0][2]) * mult, (m[0][1] - m[1][0]) * mult);
		case 1:
			return qua<T, Q>((m[1][2] - m[2][1]) * mult, biggestVal, (m[0][1] + m[1][0]) * mult, (m[2][0] + m[0][2]) * mult);
		case 2:
			return qua<T, Q>((m[2][0] - m[0][2]) * mult, (m[0][1] + m[1][0]) * mult, biggestVal, (m[1][2] + m[2][1]) * mult);
		case 3:
			return qua<T, Q>((m[0][1] - m[1][0]) * mult, (m[2][0] + m[0][2]) * mult, (m[1][2] + m[2][1]) * mult, biggestVal);
		default: // Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
			assert(false);
			return qua<T, Q>(1, 0, 0, 0);
		}
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> quat_cast(mat<4, 4, T, Q> const& m4)
	{
		return quat_cast(mat<3, 3, T, Q>(m4));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> lessThan(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] < y[i];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> lessThanEqual(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] <= y[i];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> greaterThan(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] > y[i];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> greaterThanEqual(qua<T, Q> const& x, qua<T, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] >= y[i];
		return Result;
	}


	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> quatLookAt(vec<3, T, Q> const& direction, vec<3, T, Q> const& up)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return quatLookAtLH(direction, up);
#		else
			return quatLookAtRH(direction, up);
# 		endif
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> quatLookAtRH(vec<3, T, Q> const& direction, vec<3, T, Q> const& up)
	{
		mat<3, 3, T, Q> Result;

		Result[2] = -direction;
		vec<3, T, Q> const& Right = cross(up, Result[2]);
		Result[0] = Right * inversesqrt(max(static_cast<T>(0.00001), dot(Right, Right)));
		Result[1] = cross(Result[2], Result[0]);

		return quat_cast(Result);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> quatLookAtLH(vec<3, T, Q> const& direction, vec<3, T, Q> const& up)
	{
		mat<3, 3, T, Q> Result;

		Result[2] = direction;
		vec<3, T, Q> const& Right = cross(up, Result[2]);
		Result[0] = Right * inversesqrt(max(static_cast<T>(0.00001), dot(Right, Right)));
		Result[1] = cross(Result[2], Result[0]);

		return quat_cast(Result);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "gtc/quaternion_simd.inl"
#endif



// ---------- "../gtc/vec1.hpp" ----------

	// ---------- "../ext/vector_bool1.hpp" ----------

namespace glm
{
	/// @addtogroup ext_vector_bool1
	/// @{

	/// 1 components vector of boolean.
	typedef vec<1, bool, defaultp>		bvec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_bool1_precision.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_bool1_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_bool1_precision
	/// @{

	/// 1 component vector of bool values.
	typedef vec<1, bool, highp>			highp_bvec1;

	/// 1 component vector of bool values.
	typedef vec<1, bool, mediump>		mediump_bvec1;

	/// 1 component vector of bool values.
	typedef vec<1, bool, lowp>			lowp_bvec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_float1.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_float1 extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_float1
	/// @{

	/// 1 components vector of single-precision floating-point numbers.
	typedef vec<1, float, defaultp>		vec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_float1_precision.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_float1_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_float1_precision
	/// @{

	/// 1 component vector of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	typedef vec<1, float, highp>		highp_vec1;

	/// 1 component vector of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	typedef vec<1, float, mediump>		mediump_vec1;

	/// 1 component vector of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	typedef vec<1, float, lowp>			lowp_vec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_double1.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_double1 extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_double1
	/// @{

	/// 1 components vector of double-precision floating-point numbers.
	typedef vec<1, double, defaultp>		dvec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_double1_precision.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_double1_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_double1_precision
	/// @{

	/// 1 component vector of double-precision floating-point numbers using high precision arithmetic in term of ULPs.
	typedef vec<1, double, highp>		highp_dvec1;

	/// 1 component vector of double-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	typedef vec<1, double, mediump>		mediump_dvec1;

	/// 1 component vector of double-precision floating-point numbers using low precision arithmetic in term of ULPs.
	typedef vec<1, double, lowp>		lowp_dvec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_int1.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_int1 extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_int1
	/// @{

	/// 1 component vector of signed integer numbers.
	typedef vec<1, int, defaultp>			ivec1;

	/// @}
}//namespace glm



	// ---------- "../ext/vector_int1_sized.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_int1_sized extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_int1_sized
	/// @{

	/// 8 bit signed integer vector of 1 component type.
	///
	/// @see ext_vector_int1_sized
	typedef vec<1, int8, defaultp>	i8vec1;

	/// 16 bit signed integer vector of 1 component type.
	///
	/// @see ext_vector_int1_sized
	typedef vec<1, int16, defaultp>	i16vec1;

	/// 32 bit signed integer vector of 1 component type.
	///
	/// @see ext_vector_int1_sized
	typedef vec<1, int32, defaultp>	i32vec1;

	/// 64 bit signed integer vector of 1 component type.
	///
	/// @see ext_vector_int1_sized
	typedef vec<1, int64, defaultp>	i64vec1;

	/// @}
}//namespace glm


	// ---------- "../ext/vector_uint1.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_uint1 extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_uint1
	/// @{

	/// 1 component vector of unsigned integer numbers.
	typedef vec<1, unsigned int, defaultp>			uvec1;

	/// @}
}//namespace glm



	// ---------- "../ext/vector_uint1_sized.hpp" ----------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_uint1_sized extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_uint1_sized
	/// @{

	/// 8 bit unsigned integer vector of 1 component type.
	///
	/// @see ext_vector_uint1_sized
	typedef vec<1, uint8, defaultp>		u8vec1;

	/// 16 bit unsigned integer vector of 1 component type.
	///
	/// @see ext_vector_uint1_sized
	typedef vec<1, uint16, defaultp>	u16vec1;

	/// 32 bit unsigned integer vector of 1 component type.
	///
	/// @see ext_vector_uint1_sized
	typedef vec<1, uint32, defaultp>	u32vec1;

	/// 64 bit unsigned integer vector of 1 component type.
	///
	/// @see ext_vector_uint1_sized
	typedef vec<1, uint64, defaultp>	u64vec1;

	/// @}
}//namespace glm

	// -----------------------------------------------------

// ---------------------------------------

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTC_type_ptr extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_type_ptr
	/// @{

	/// Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename genType>
	GLM_FUNC_DECL typename genType::value_type const * value_ptr(genType const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<1, T, Q> make_vec1(vec<1, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<1, T, Q> make_vec1(vec<2, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<1, T, Q> make_vec1(vec<3, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<1, T, Q> make_vec1(vec<4, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<2, T, Q> make_vec2(vec<1, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<2, T, Q> make_vec2(vec<2, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<2, T, Q> make_vec2(vec<3, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<2, T, Q> make_vec2(vec<4, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> make_vec3(vec<1, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> make_vec3(vec<2, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> make_vec3(vec<3, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<3, T, Q> make_vec3(vec<4, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, T, Q> make_vec4(vec<1, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, T, Q> make_vec4(vec<2, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, T, Q> make_vec4(vec<3, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template <typename T, qualifier Q>
	GLM_FUNC_DECL vec<4, T, Q> make_vec4(vec<4, T, Q> const& v);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL vec<2, T, defaultp> make_vec2(T const * const ptr);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL vec<3, T, defaultp> make_vec3(T const * const ptr);

	/// Build a vector from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL vec<4, T, defaultp> make_vec4(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<2, 2, T, defaultp> make_mat2x2(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<2, 3, T, defaultp> make_mat2x3(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<2, 4, T, defaultp> make_mat2x4(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<3, 2, T, defaultp> make_mat3x2(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<3, 3, T, defaultp> make_mat3x3(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<3, 4, T, defaultp> make_mat3x4(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<4, 2, T, defaultp> make_mat4x2(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<4, 3, T, defaultp> make_mat4x3(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> make_mat4x4(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<2, 2, T, defaultp> make_mat2(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<3, 3, T, defaultp> make_mat3(T const * const ptr);

	/// Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL mat<4, 4, T, defaultp> make_mat4(T const * const ptr);

	/// Build a quaternion from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_DECL qua<T, defaultp> make_quat(T const * const ptr);

	/// @}
}//namespace glm

namespace glm
{
	/// @addtogroup gtc_type_ptr
	/// @{

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(vec<2, T, Q> const& v)
	{
		return &(v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(vec<2, T, Q>& v)
	{
		return &(v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const * value_ptr(vec<3, T, Q> const& v)
	{
		return &(v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(vec<3, T, Q>& v)
	{
		return &(v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(vec<4, T, Q> const& v)
	{
		return &(v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(vec<4, T, Q>& v)
	{
		return &(v.x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<2, 2, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<2, 2, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<3, 3, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<3, 3, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<4, 4, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<4, 4, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<2, 3, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<2, 3, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<3, 2, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<3, 2, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<2, 4, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<2, 4, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<4, 2, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<4, 2, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<3, 4, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(mat<3, 4, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const* value_ptr(mat<4, 3, T, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T * value_ptr(mat<4, 3, T, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T const * value_ptr(qua<T, Q> const& q)
	{
		return &(q[0]);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T* value_ptr(qua<T, Q>& q)
	{
		return &(q[0]);
	}

	template <typename T, qualifier Q>
	inline vec<1, T, Q> make_vec1(vec<1, T, Q> const& v)
	{
		return v;
	}

	template <typename T, qualifier Q>
	inline vec<1, T, Q> make_vec1(vec<2, T, Q> const& v)
	{
		return vec<1, T, Q>(v);
	}

	template <typename T, qualifier Q>
	inline vec<1, T, Q> make_vec1(vec<3, T, Q> const& v)
	{
		return vec<1, T, Q>(v);
	}

	template <typename T, qualifier Q>
	inline vec<1, T, Q> make_vec1(vec<4, T, Q> const& v)
	{
		return vec<1, T, Q>(v);
	}

	template <typename T, qualifier Q>
	inline vec<2, T, Q> make_vec2(vec<1, T, Q> const& v)
	{
		return vec<2, T, Q>(v.x, static_cast<T>(0));
	}

	template <typename T, qualifier Q>
	inline vec<2, T, Q> make_vec2(vec<2, T, Q> const& v)
	{
		return v;
	}

	template <typename T, qualifier Q>
	inline vec<2, T, Q> make_vec2(vec<3, T, Q> const& v)
	{
		return vec<2, T, Q>(v);
	}

	template <typename T, qualifier Q>
	inline vec<2, T, Q> make_vec2(vec<4, T, Q> const& v)
	{
		return vec<2, T, Q>(v);
	}

	template <typename T, qualifier Q>
	inline vec<3, T, Q> make_vec3(vec<1, T, Q> const& v)
	{
		return vec<3, T, Q>(v.x, static_cast<T>(0), static_cast<T>(0));
	}

	template <typename T, qualifier Q>
	inline vec<3, T, Q> make_vec3(vec<2, T, Q> const& v)
	{
		return vec<3, T, Q>(v.x, v.y, static_cast<T>(0));
	}

	template <typename T, qualifier Q>
	inline vec<3, T, Q> make_vec3(vec<3, T, Q> const& v)
	{
		return v;
	}

	template <typename T, qualifier Q>
	inline vec<3, T, Q> make_vec3(vec<4, T, Q> const& v)
	{
		return vec<3, T, Q>(v);
	}

	template <typename T, qualifier Q>
	inline vec<4, T, Q> make_vec4(vec<1, T, Q> const& v)
	{
		return vec<4, T, Q>(v.x, static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	template <typename T, qualifier Q>
	inline vec<4, T, Q> make_vec4(vec<2, T, Q> const& v)
	{
		return vec<4, T, Q>(v.x, v.y, static_cast<T>(0), static_cast<T>(1));
	}

	template <typename T, qualifier Q>
	inline vec<4, T, Q> make_vec4(vec<3, T, Q> const& v)
	{
		return vec<4, T, Q>(v.x, v.y, v.z, static_cast<T>(1));
	}

	template <typename T, qualifier Q>
	inline vec<4, T, Q> make_vec4(vec<4, T, Q> const& v)
	{
		return v;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER vec<2, T, defaultp> make_vec2(T const *const ptr)
	{
		vec<2, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(vec<2, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER vec<3, T, defaultp> make_vec3(T const *const ptr)
	{
		vec<3, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(vec<3, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER vec<4, T, defaultp> make_vec4(T const *const ptr)
	{
		vec<4, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(vec<4, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<2, 2, T, defaultp> make_mat2x2(T const *const ptr)
	{
		mat<2, 2, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<2, 2, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<2, 3, T, defaultp> make_mat2x3(T const *const ptr)
	{
		mat<2, 3, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<2, 3, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<2, 4, T, defaultp> make_mat2x4(T const *const ptr)
	{
		mat<2, 4, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<2, 4, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<3, 2, T, defaultp> make_mat3x2(T const *const ptr)
	{
		mat<3, 2, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<3, 2, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<3, 3, T, defaultp> make_mat3x3(T const *const ptr)
	{
		mat<3, 3, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<3, 3, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<3, 4, T, defaultp> make_mat3x4(T const *const ptr)
	{
		mat<3, 4, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<3, 4, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 2, T, defaultp> make_mat4x2(T const *const ptr)
	{
		mat<4, 2, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<4, 2, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 3, T, defaultp> make_mat4x3(T const *const ptr)
	{
		mat<4, 3, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<4, 3, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> make_mat4x4(T const *const ptr)
	{
		mat<4, 4, T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<4, 4, T, defaultp>));
		return Result;
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<2, 2, T, defaultp> make_mat2(T const *const ptr)
	{
		return make_mat2x2(ptr);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<3, 3, T, defaultp> make_mat3(T const *const ptr)
	{
		return make_mat3x3(ptr);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> make_mat4(T const *const ptr)
	{
		return make_mat4x4(ptr);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER qua<T, defaultp> make_quat(T const *const ptr)
	{
		qua<T, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(qua<T, defaultp>));
		return Result;
	}

	/// @}
}//namespace glm



// ----------------------------------


// ----------  ----------
// -----------------------


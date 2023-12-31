#pragma once

#include <float.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

/* byte */
typedef uint8_t byte;

/* floating point */
typedef float f32;
typedef double f64;

/* integer */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef ssize_t isize;

/* unsigned integer */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;

/* floating point limits */
#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX
#define F64_MIN DBL_MIN
#define F64_MAX DBL_MAX

/* signed integer limits */
#define I8_MIN INT8_MIN
#define I8_MAX INT8_MAX
#define I16_MIN INT16_MIN
#define I16_MAX INT16_MAX
#define I32_MIN INT32_MIN
#define I32_MAX INT32_MAX
#define I64_MIN INT64_MIN
#define I64_MAX INT64_MAX

/* unsigned integer limits */
#define U8_MIN UINT8_MIN
#define U8_MAX UINT8_MAX
#define U16_MIN UINT16_MIN
#define U16_MAX UINT16_MAX
#define U32_MIN UINT32_MIN
#define U32_MAX UINT32_MAX
#define U64_MIN UINT64_MIN
#define U64_MAX UINT64_MAX

// -*-C++-*-

#ifndef FLOATTYPES_H
#define FLOATTYPES_H



#include <cmath>
#include <cstdlib>

// We expect either 199711L or 201103L
#if __cplusplus >= 201103L
// C++11 is supported, use it

#include <cstdint>

#else
// C++11 is not supported, work around the missing pieces

#include <stdint.h>



#define static_assert(x,y)
#define __builtin_unreachable() (assert(0))



// Make some type definitions from stdint.h available in std
namespace std {
  typedef unsigned char uint8_t;
  typedef signed char int8_t;
  typedef unsigned short uint16_t;
  typedef short int16_t;
  typedef unsigned int uint32_t;
  typedef int int32_t;
  typedef unsigned long long uint64_t;
  typedef long long int64_t;
}



// Make some math functions from math.h available in std
namespace std {
  // Capture macros into functions, then undefine the macros
  namespace {
    template<typename T> int libc_isfinite(T x) { return isfinite(x); }
    template<typename T> int libc_isinf(T x) { return isinf(x); }
    template<typename T> int libc_isnan(T x) { return isnan(x); }
    template<typename T> int libc_isnormal(T x) { return isnormal(x); }
    template<typename T> int libc_signbit(T x) { return signbit(x); }
  }
#undef isfinite
#undef isinf
#undef isnan
#undef isnormal
#undef signbit
  
  inline float asinh(float x) { return ::asinhf(x); }
  inline float acosh(float x) { return ::acoshf(x); }
  inline float atanh(float x) { return ::atanh(x); }
  inline float cbrt(float x) { return ::cbrtf(x); }
  // inline float ceil(float x) { return ::ceilf(x); }
  inline float copysign(float x, float y) { return ::copysignf(x, y); }
  inline float exp2(float x) { return ::exp2f(x); }
  inline float expm1(float x) { return ::expm1f(x); }
  inline float fdim(float x, float y) { return ::fdimf(x, y); }
  // inline float floor(float x) { return ::floorf(x); }
  inline float fma(float x, float y, float z) { return ::fmaf(x, y, z); }
  inline float fmax(float x, float y) { return ::fmaxf(x, y); }
  inline float fmin(float x, float y) { return ::fminf(x, y); }
  // inline float frexp(float x, int* r) { return ::frexpf(x, r); }
  inline float hypot(float x, float y) { return ::hypotf(x, y); }
  inline int ilogb(float x) { return ::ilogbf(x); }
  inline bool isfinite(float x) { return libc_isfinite(x); }
  inline bool isinf(float x) { return libc_isinf(x); }
  inline bool isnan(float x) { return libc_isnan(x); }
  inline bool isnormal(float x) { return libc_isnormal(x); }
  inline float log1p(float x) { return ::log1pf(x); }
  inline float log2(float x) { return ::log2f(x); }
  inline float nextafter(float x, float y) { return ::nextafterf(x, y); }
  inline float remainder(float x, float y) { return ::remainderf(x, y); }
  inline float rint(float x) { return ::rintf(x); }
  inline float round(float x) { return ::roundf(x); }
  inline bool signbit(float x) { return libc_signbit(x); }
  inline float trunc(float x) { return ::truncf(x); }
  
  inline double asinh(double x) { return ::asinh(x); }
  inline double acosh(double x) { return ::acosh(x); }
  inline double atanh(double x) { return ::atanh(x); }
  inline double cbrt(double x) { return ::cbrt(x); }
  // inline double ceil(double x) { return ::ceil(x); }
  inline double copysign(double x, double y) { return ::copysign(x, y); }
  inline double exp2(double x) { return ::exp2(x); }
  inline double expm1(double x) { return ::expm1(x); }
  inline double fdim(double x, double y) { return ::fdim(x, y); }
  // inline double floor(double x) { return ::floor(x); }
  inline double fma(double x, double y, double z) { return ::fma(x, y, z); }
  inline double fmax(double x, double y) { return ::fmax(x, y); }
  inline double fmin(double x, double y) { return ::fmin(x, y); }
  // inline double frexp(double x, int* r) { return ::frexp(x, r); }
  inline double hypot(double x, double y) { return ::hypot(x, y); }
  inline int ilogb(double x) { return ::ilogb(x); }
  inline bool isfinite(double x) { return libc_isfinite(x); }
  inline bool isinf(double x) { return libc_isinf(x); }
  inline bool isnan(double x) { return libc_isnan(x); }
  inline bool isnormal(double x) { return libc_isnormal(x); }
  inline double log1p(double x) { return ::log1p(x); }
  inline double log2(double x) { return ::log2(x); }
  inline double nextafter(double x, double y) { return ::nextafter(x, y); }
  inline double remainder(double x, double y) { return ::remainder(x, y); }
  inline double rint(double x) { return ::rint(x); }
  inline double round(double x) { return ::round(x); }
  inline bool signbit(double x) { return libc_signbit(x); }
  inline double trunc(double x) { return ::trunc(x); }
}

#endif



namespace vecmathlib {
  
  struct fp8 {
    // 1 bit sign, 4 bits exponent, 3 bits mantissa
    std::uint8_t val;
  };
  
  struct fp16 {
    // 1 bit sign, 5 bits exponent, 10 bits mantissa
    std::uint16_t val;
  };
  
} // namespace vecmathlib

#endif  // #ifndef FLOATTYPES_H

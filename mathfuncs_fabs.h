// -*-C++-*-

#ifndef MATHFUNCS_FABS_H
#define MATHFUNCS_FABS_H

#include "mathfuncs_base.h"

#include <cmath>



namespace vecmathlib {
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_copysign(realvec_t x, realvec_t y)
  {
    intvec_t value = as_int(x) & IV(U(~FP::signbit_mask));
    intvec_t sign = as_int(y) & IV(FP::signbit_mask);
    return as_float(sign | value);
  }
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_fabs(realvec_t x)
  {
    return as_float(as_int(x) & IV(U(~FP::signbit_mask)));
  }
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_fdim(realvec_t x, realvec_t y)
  {
    // return ifthen(x > y, x - y, RV(0.0));
    return fmax(x - y, RV(0.0));
  }
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_fma(realvec_t x, realvec_t y, realvec_t z)
  {
    return x * y + z;
  }
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_fmax(realvec_t x, realvec_t y)
  {
    return ifthen(x < y, y, x);
  }
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_fmin(realvec_t x, realvec_t y)
  {
    return ifthen(y < x, y, x);
  }
  
  template<typename realvec_t>
  auto mathfuncs<realvec_t>::vml_ilogb(realvec_t x) -> intvec_t
  {
    intvec_t e = lsr(as_int(x) & IV(FP::exponent_mask), FP::mantissa_bits);
    intvec_t r = e - IV(FP::exponent_offset);
    r = ifthen(convert_bool(e), r, IV(numeric_limits<int_t>::min()));
    return r;
  }
  
  template<typename realvec_t>
  auto mathfuncs<realvec_t>::vml_isfinite(realvec_t x) -> boolvec_t
  {
#if defined VML_HAVE_INF || defined VML_HAVE_NAN
    return (as_int(x) & IV(FP::exponent_mask)) != IV(FP::exponent_mask);
#else
    return BV(true);
#endif
  }
  
  template<typename realvec_t>
  auto mathfuncs<realvec_t>::vml_isinf(realvec_t x) -> boolvec_t
  {
#if defined VML_HAVE_INF
    return (as_int(x) & IV(~FP::signbit_mask)) == IV(FP::exponent_mask);
#else
    return BV(false);
#endif
  }
  
  template<typename realvec_t>
  auto mathfuncs<realvec_t>::vml_isnan(realvec_t x) -> boolvec_t
  {
#if defined VML_HAVE_NAN
    return
      (as_int(x) & IV(FP::exponent_mask)) == IV(FP::exponent_mask) &&
      (as_int(x) & IV(FP::mantissa_mask)) != IV(I(0));
#else
    return BV(false);
#endif
  }
  
  template<typename realvec_t>
  auto mathfuncs<realvec_t>::vml_isnormal(realvec_t x) -> boolvec_t
  {
#if defined VML_HAVE_DENORMALS || defined VML_HAVE_INF || defined VML_HAVE_NAN
    return
      (as_int(x) & IV(FP::exponent_mask)) != IV(FP::exponent_mask) &&
      (as_int(x) & IV(FP::exponent_mask)) != IV(I(0));
#else
    return BV(true);
#endif
  }
  
  template<typename realvec_t>
  realvec_t mathfuncs<realvec_t>::vml_ldexp(realvec_t x, intvec_t n)
  {
    realvec_t r = as_float(as_int(x) + (n << I(FP::mantissa_bits)));
    r = ifthen((as_int(x) & IV(FP::exponent_mask)) == IV(I(0)), x, r);
    return r;
  }
  
  template<typename realvec_t>
  auto mathfuncs<realvec_t>::vml_signbit(realvec_t x) -> boolvec_t
  {
    return convert_bool(as_int(x) & IV(FP::signbit_mask));
  }
  
}; // namespace vecmathlib

#endif  // #ifndef MATHFUNCS_FABS_H

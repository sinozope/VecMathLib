// -*-C++-*-

#ifndef VEC_PSEUDO_H
#define VEC_PSEUDO_H

#include "floatprops.h"
#include "mathfuncs.h"
#include "vec_base.h"

#include <cmath>
#include <string>
#include <typeinfo>



namespace vecmathlib {
  
  template<typename T, int N> struct boolpseudovec;
  template<typename T, int N> struct intpseudovec;
  template<typename T, int N> struct realpseudovec;
  
  
  
  template<typename T, int N>
  struct boolpseudovec: floatprops<T>
  {
    typedef typename floatprops<T>::int_t int_t;
    typedef typename floatprops<T>::uint_t uint_t;
    typedef typename floatprops<T>::real_t real_t;
    
    static int const size = N;
    typedef bool scalar_t;
    typedef bool bvector_t[size];
    
    typedef boolpseudovec boolvec_t;
    typedef intpseudovec<real_t, size> intvec_t;
    typedef realpseudovec<real_t, size> realvec_t;
    
    // Short names for type casts
    typedef real_t R;
    typedef int_t I;
    typedef uint_t U;
    typedef realvec_t RV;
    typedef intvec_t IV;
    typedef boolvec_t BV;
    typedef floatprops<real_t> FP;
    typedef mathfuncs<realvec_t> MF;
    
    
    
    bvector_t v;
    
    boolpseudovec() {}
    // Can't have a non-trivial copy constructor; if so, objects won't
    // be passed in registers
    // boolpseudovec(boolpseudovec const& x): v(x.v) {}
    // boolpseudovec& operator=(boolpseudovec const& x) { return v=x.v, *this; }
    boolpseudovec(bool a) { for (int d=0; d<size; ++d) v[d]=a; }
    boolpseudovec(bool const* as) { for (int d=0; d<size; ++d) v[d]=as[d]; }
    
    bool operator[](int n) const { return v[n]; }
    boolpseudovec& set_elt(int n, bool a) { return v[n]=a, *this; }
    
    
    
    intvec_t as_int() const;      // defined after intpseudovec
    intvec_t convert_int() const; // defined after intpseudovec
    
    
    
    boolpseudovec operator!() const
    {
      boolpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = !v[d];
      return res;
    }
    
    boolpseudovec operator&&(boolpseudovec x) const
    {
      boolpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] && x.v[d];
      return res;
    }
    boolpseudovec operator||(boolpseudovec x) const
    {
      boolpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] || x.v[d];
      return res;
    }
    boolpseudovec operator==(boolpseudovec x) const
    {
      boolpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] == x.v[d];
      return res;
    }
    boolpseudovec operator!=(boolpseudovec x) const
    {
      boolpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] != x.v[d];
      return res;
    }
    
    bool all() const;
    bool any() const;
    
    
    
    // ifthen(condition, then-value, else-value)
    intvec_t ifthen(intvec_t x, intvec_t y) const; // defined after intpseudovec
    realvec_t ifthen(realvec_t x, realvec_t y) const; // defined after realpseudovec
  };
  
  
  
  template<typename T, int N>
  struct intpseudovec: floatprops<T>
  {
    typedef typename floatprops<T>::int_t int_t;
    typedef typename floatprops<T>::uint_t uint_t;
    typedef typename floatprops<T>::real_t real_t;
    
    static int const size = N;
    typedef int_t scalar_t;
    typedef int_t ivector_t[size];
    
    typedef boolpseudovec<real_t, size> boolvec_t;
    typedef intpseudovec intvec_t;
    typedef realpseudovec<real_t, size> realvec_t;
    
    // Short names for type casts
    typedef real_t R;
    typedef int_t I;
    typedef uint_t U;
    typedef realvec_t RV;
    typedef intvec_t IV;
    typedef boolvec_t BV;
    typedef floatprops<real_t> FP;
    typedef mathfuncs<realvec_t> MF;
    
    
    
    ivector_t v;
    
    intpseudovec() {}
    // Can't have a non-trivial copy constructor; if so, objects won't
    // be passed in registers
    // intpseudovec(intpseudovec const& x): v(x.v) {}
    // intpseudovec& operator=(intpseudovec const& x) { return v=x.v, *this; }
    intpseudovec(int_t a) { for (int d=0; d<size; ++d) v[d]=a; }
    intpseudovec(int_t const* as) { for (int d=0; d<size; ++d) v[d]=as[d]; }
    
    int_t operator[](int n) const { return v[n]; }
    intpseudovec& set_elt(int n, int_t a) { return v[n]=a, *this; }
    
    
    
    boolvec_t as_bool() const { return convert_bool(); }
    boolvec_t convert_bool() const
    {
      // Result: convert_bool(0)=false, convert_bool(else)=true
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d]=v[d];
      return res;
    }
    realvec_t as_float() const;      // defined after realpseudovec
    realvec_t convert_float() const; // defined after realpseudovec
    
    
    
    intpseudovec operator+() const
    {
      intpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = + v[d];
      return res;
    }
    intpseudovec operator-() const
    {
      intpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = - v[d];
      return res;
    }
    
    intpseudovec& operator+=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] += x.v[d];
      return *this;
    }
    intpseudovec& operator-=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] -= x.v[d];
      return *this;
    }
    intpseudovec& operator*=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] *= x.v[d];
      return *this;
    }
    intpseudovec& operator/=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] /= x.v[d];
      return *this;
    }
    intpseudovec& operator%=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] %= x.v[d];
      return *this;
    }
    
    intpseudovec operator+(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res += x;
    }
    intpseudovec operator-(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res -= x;
    }
    intpseudovec operator*(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res *= x;
    }
    intpseudovec operator/(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res /= x;
    }
    intpseudovec operator%(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res %= x;
    }
    
    
    
    intpseudovec operator~() const
    {
      intpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = ! v[d];
      return res;
    }
    
    intpseudovec& operator&=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] &= x.v[d];
      return *this;
    }
    intpseudovec& operator|=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] |= x.v[d];
      return *this;
    }
    intpseudovec& operator^=(intpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] ^= x.v[d];
      return *this;
    }
    
    intpseudovec operator&(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res &= x;
    }
    intpseudovec operator|(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res |= x;
    }
    intpseudovec operator^(intpseudovec x) const
    {
      intpseudovec res = *this;
      return res ^= x;
    }
    
    
    
    intpseudovec lsr(int_t n) const
    {
      intpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = I(U(v[d]) >> U(n));
      return res;
    }
    intpseudovec& operator>>=(int_t n)
    {
      for (int d=0; d<size; ++d) v[d] >>= n;
      return *this;
    }
    intpseudovec& operator<<=(int_t n)
    {
      for (int d=0; d<size; ++d) v[d] <<= n;
      return *this;
    }
    
    intpseudovec operator>>(int_t n) const
    {
      intpseudovec res = *this;
      return res >>= n;
    }
    intpseudovec operator<<(int_t n) const
    {
      intpseudovec res = *this;
      return res <<= n;
    }
    
    
    
    boolvec_t operator==(intpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] == x.v[d];
      return res;
    }
    boolvec_t operator!=(intpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] != x.v[d];
      return res;
    }
  };
  
  
  
  template<typename T, int N>
  struct realpseudovec: floatprops<T>
  {
    typedef typename floatprops<T>::int_t int_t;
    typedef typename floatprops<T>::uint_t uint_t;
    typedef typename floatprops<T>::real_t real_t;
    
    static int const size = N;
    typedef real_t scalar_t;
    typedef real_t vector_t[size];
    
    static char const* name()
    {
      static std::string name_;
      if (name_.length()==0) {
        std::string base;
        if (typeid(T) == typeid(float)) base = "float";
        else if (typeid(T) == typeid(double)) base = "double";
        else base = typeid(T).name();
        name_ = std::string("<") + std::to_string(N) + "*" + base + ">";
      }
      return name_.c_str();
    }
    
    typedef boolpseudovec<real_t, size> boolvec_t;
    typedef intpseudovec<real_t, size> intvec_t;
    typedef realpseudovec realvec_t;
    
  private:
    boolvec_t map(bool f(real_t)) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = f(v[d]);
      return res;
    }
    intvec_t map(int_t f(real_t)) const
    {
      intvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = f(v[d]);
      return res;
    }
    realvec_t map(real_t f(real_t)) const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = f(v[d]);
      return res;
    }
    realvec_t map(real_t f(real_t, int_t), intvec_t x) const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = f(v[d], x.v[d]);
      return res;
    }
    realvec_t map(real_t f(real_t, real_t), realvec_t x) const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = f(v[d], x.v[d]);
      return res;
    }
    realvec_t map(real_t f(real_t, real_t, real_t),
                  realvec_t x, realvec_t y) const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = f(v[d], x.v[d], y.v[d]);
      return res;
    }
  public:
    
    // Short names for type casts
    typedef real_t R;
    typedef int_t I;
    typedef uint_t U;
    typedef realvec_t RV;
    typedef intvec_t IV;
    typedef boolvec_t BV;
    typedef floatprops<real_t> FP;
    typedef mathfuncs<realvec_t> MF;
    
    
    
    vector_t v;
    
    realpseudovec() {}
    // Can't have a non-trivial copy constructor; if so, objects won't
    // be passed in registers
    // realpseudovec(realpseudovec const& x): v(x.v) {}
    // realpseudovec& operator=(realpseudovec const& x) { return v=x.v, *this; }
    realpseudovec(real_t a) { for (int d=0; d<size; ++d) v[d]=a; }
    realpseudovec(real_t const* as) { for (int d=0; d<size; ++d) v[d]=as[d]; }
    
    real_t operator[](int n) const { return v[n]; }
    realpseudovec& set_elt(int n, real_t a) { return v[n]=a, *this; }
    
    
    
    intvec_t as_int() const
    {
      intvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = as_int(v[d]);
      return res;
    }
    intvec_t convert_int() const
    {
      intvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = floatprops<T>::convert_int(v[d]);
      return res;
    }
    
    
    
    realpseudovec operator+() const
    {
      realpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = + v[d];
      return res;
    }
    realpseudovec operator-() const
    {
      realpseudovec res;
      for (int d=0; d<size; ++d) res.v[d] = - v[d];
      return res;
    }
    
    realpseudovec& operator+=(realpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] += x.v[d];
      return *this;
    }
    realpseudovec& operator-=(realpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] -= x.v[d];
      return *this;
    }
    realpseudovec& operator*=(realpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] *= x.v[d];
      return *this;
    }
    realpseudovec& operator/=(realpseudovec const& x)
    {
      for (int d=0; d<size; ++d) v[d] /= x.v[d];
      return *this;
    }
    
    realpseudovec operator+(realpseudovec x) const
    {
      realpseudovec res = *this;
      return res += x;
    }
    realpseudovec operator-(realpseudovec x) const
    {
      realpseudovec res = *this;
      return res -= x;
    }
    realpseudovec operator*(realpseudovec x) const
    {
      realpseudovec res = *this;
      return res *= x;
    }
    realpseudovec operator/(realpseudovec x) const
    {
      realpseudovec res = *this;
      return res /= x;
    }
    
    real_t prod() const
    {
      real_t res = R(1.0);
      for (int d=0; d<size; ++d) res *= v[d];
      return res;
    }
    real_t sum() const
    {
      real_t res = R(1.0);
      for (int d=0; d<size; ++d) res += v[d];
      return res;
    }
    
    
    
    boolvec_t operator==(realpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] == x.v[d];
      return res;
    }
    boolvec_t operator!=(realpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] != x.v[d];
      return res;
    }
    boolvec_t operator<(realpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] < x.v[d];
      return res;
    }
    boolvec_t operator<=(realpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] <= x.v[d];
      return res;
    }
    boolvec_t operator>(realpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] > x.v[d];
      return res;
    }
    boolvec_t operator>=(realpseudovec const& x) const
    {
      boolvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = v[d] >= x.v[d];
      return res;
    }
    
    
    
    realpseudovec acos() const { return map(std::acos); }
    realpseudovec acosh() const { return map(std::acosh); }
    realpseudovec asin() const { return map(std::asin); }
    realpseudovec asinh() const { return map(std::asinh); }
    realpseudovec atan() const { return map(std::atan); }
    realpseudovec atanh() const { return map(std::atanh); }
    realpseudovec ceil() const { return map(std::ceil); }
    realpseudovec copysign(realpseudovec y) const
    {
      return map(std::copysign, y);
    }
    realpseudovec cos() const { return map(std::cos); }
    realpseudovec cosh() const { return map(std::cosh); }
    realpseudovec exp() const { return map(std::exp); }
    realpseudovec exp10() const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = std::exp(R(M_LN10) * v[d]);
      return res;
    }
    realpseudovec exp2() const { return map(std::exp2); }
    realpseudovec expm1() const { return map(std::expm1); }
    realpseudovec fabs() const { return map(std::fabs); }
    realpseudovec fdim(realpseudovec y) const { return map(std::fdim, y); }
    realpseudovec floor() const { return map(std::floor); }
    realpseudovec fma(realpseudovec y, realpseudovec z) const
    {
      return map(std::fma, y, z);
    }
    realpseudovec fmax(realpseudovec y) const { return map(std::fmax, y); }
    realpseudovec fmin(realpseudovec y) const { return map(std::fmin, y); }
    realpseudovec fmod(realpseudovec y) const { return map(std::fmod, y); }
    intvec_t ilogb() const
    {
      intvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = std::ilogb(v[d]);
      return res;
    }
    boolvec_t isfinite() const { return map(std::isfinite); }
    boolvec_t isinf() const { return map(std::isinf); }
    boolvec_t isnan() const { return map(std::isnan); }
    boolvec_t isnormal() const { return map(std::isnormal); }
    realpseudovec log() const { return map(std::log); }
    realpseudovec log10() const { return map(std::log10); }
    realpseudovec log1p() const { return map(std::log1p); }
    realpseudovec log2() const { return map(std::log2); }
    realpseudovec pow(realpseudovec y) const { return map(std::pow, y); }
    realpseudovec rcp() const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = R(1.0) / v[d];
      return res;
    }
    realpseudovec remainder(realpseudovec y) const
    {
      return map(std::remainder, y);
    }
    realpseudovec round() const { return map(std::round); }
    realpseudovec rsqrt() const { return sqrt().rcp(); }
    realpseudovec scalbn(intvec_t n) const
    {
      realvec_t res;
      for (int d=0; d<size; ++d) res.v[d] = std::scalbn(v[d], n.v[d]);
      return res;
    }
    boolvec_t signbit() const { return map(std::signbit); }
    realpseudovec sin() const { return map(std::sin); }
    realpseudovec sinh() const { return map(std::sinh); }
    realpseudovec sqrt() const { return map(std::sqrt); }
    realpseudovec tan() const { return map(std::tan); }
    realpseudovec tanh() const { return map(std::tanh); }
  };
  
  
  
  // boolpseudovec definitions
  
  template<typename T, int N>
  inline
  auto boolpseudovec<T,N>::as_int() const -> intvec_t
  {
    return convert_int();
  }
  
  template<typename T, int N>
  inline
  auto boolpseudovec<T,N>::convert_int() const -> intvec_t
  {
    intvec_t res;
    for (int d=0; d<size; ++d) res.v[d] = v[d];
    return res;
  }
  
  template<typename T, int N>
  inline
  bool boolpseudovec<T,N>::all() const
  {
    bool res = true;
    for (int d=0; d<size; ++d) res = res && v[d];
    return res;
  }
  
  template<typename T, int N>
  inline
  bool boolpseudovec<T,N>::any() const
  {
    bool res = false;
    for (int d=0; d<size; ++d) res = res || v[d];
    return res;
  }
  
  template<typename T, int N>
  inline
  auto boolpseudovec<T,N>::ifthen(intvec_t x, intvec_t y) const -> intvec_t
  {
    intvec_t res;
    for (int d=0; d<size; ++d) res.v[d] = v[d] ? x.v[d] : y.v[d];
    return res;
  }
  
  template<typename T, int N>
  inline
  auto boolpseudovec<T,N>::ifthen(realvec_t x, realvec_t y) const -> realvec_t
  {
    realvec_t res;
    for (int d=0; d<size; ++d) res.v[d] = v[d] ? x.v[d] : y.v[d];
    return res;
  }
  
  
  
  // intpseudovec definitions
  
  template<typename T, int N>
  inline auto intpseudovec<T,N>::as_float() const -> realvec_t
  {
    realvec_t res;
    for (int d=0; d<size; ++d) res.v[d] = as_float(v[d]);
    return res;
  }
  
  template<typename T, int N>
  inline auto intpseudovec<T,N>::convert_float() const -> realvec_t
  {
    realvec_t res;
    for (int d=0; d<size; ++d) res.v[d] = floatprops<T>::convert_float(v[d]);
    return res;
  }
  


  // Wrappers
  
  // boolpseudovec wrappers
  
  template<typename real_t, int size>
  inline intpseudovec<real_t, size> as_int(boolpseudovec<real_t, size> x)
  {
    return x.as_int();
  }
  
  template<typename real_t, int size>
  inline intpseudovec<real_t, size> convert_int(boolpseudovec<real_t, size> x)
  {
    return x.convert_int();
  }
  
  template<typename real_t, int size>
  inline bool all(boolpseudovec<real_t, size> x) { return x.all(); }
  
  template<typename real_t, int size>
  inline bool any(boolpseudovec<real_t, size> x) { return x.any(); }
  
  template<typename real_t, int size>
  inline
  intpseudovec<real_t, size> ifthen(boolpseudovec<real_t, size> c,
                                    intpseudovec<real_t, size> x,
                                    intpseudovec<real_t, size> y)
  {
    return c.ifthen(x, y);
  }
  
  template<typename real_t, int size>
  inline
  realpseudovec<real_t, size> ifthen(boolpseudovec<real_t, size> c,
                                     realpseudovec<real_t, size> x,
                                     realpseudovec<real_t, size> y)
  {
    return c.ifthen(x, y);
  }
  
  
  
  // intpseudovec wrappers
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> as_bool(intpseudovec<real_t, size> x)
  {
    return x.as_bool();
  }
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> convert_bool(intpseudovec<real_t, size> x)
  {
    return x.convert_bool();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> as_float(intpseudovec<real_t, size> x)
  {
    return x.as_float();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> convert_float(intpseudovec<real_t, size> x)
  {
    return x.convert_float();
  }
  
  template<typename real_t, int size>
  inline
  intpseudovec<real_t, size> lsr(intpseudovec<real_t, size> x,
                                 typename intpseudovec<real_t, size>::int_t n)
  {
    return x.lsr(n);
  }
  
  template<typename real_t, int size>
  inline intpseudovec<real_t, size> lsr(intpseudovec<real_t, size> x,
                                        intpseudovec<real_t, size> n)
  {
    return x.lsr(n);
  }
  
  
  
  // realpseudovec wrappers
  
  template<typename real_t, int size>
  inline intpseudovec<real_t, size> as_int(realpseudovec<real_t, size> x)
  {
    return x.as_int();
  }
  
  template<typename real_t, int size>
  inline intpseudovec<real_t, size> convert_int(realpseudovec<real_t, size> x)
  {
    return x.convert_int();
  }
  
  template<typename real_t, int size>
  inline auto prod(realpseudovec<real_t, size> x) -> real_t
  {
    return x.prod();
  }
  
  template<typename real_t, int size>
  inline auto sum(realpseudovec<real_t, size> x) -> real_t
  {
    return x.sum();
  }
  
  
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> acos(realpseudovec<real_t, size> x)
  {
    return x.acos();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> acosh(realpseudovec<real_t, size> x)
  {
    return x.acosh();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> asin(realpseudovec<real_t, size> x)
  {
    return x.asin();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> asinh(realpseudovec<real_t, size> x)
  {
    return x.asinh();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> atan(realpseudovec<real_t, size> x)
  {
    return x.atan();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> atanh(realpseudovec<real_t, size> x)
  {
    return x.atanh();
  }
    
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> ceil(realpseudovec<real_t, size> x)
  {
    return x.ceil();
  }

  template<typename real_t, int size>
  inline realpseudovec<real_t, size> copysign(realpseudovec<real_t, size> x,
                                              realpseudovec<real_t, size> y)
  {
    return x.copysign(y);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> cos(realpseudovec<real_t, size> x)
  {
    return x.cos();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> cosh(realpseudovec<real_t, size> x)
  {
    return x.cosh();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> exp(realpseudovec<real_t, size> x)
  {
    return x.exp();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> exp10(realpseudovec<real_t, size> x)
  {
    return x.exp10();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> exp2(realpseudovec<real_t, size> x)
  {
    return x.exp2();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> expm1(realpseudovec<real_t, size> x)
  {
    return x.expm1();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> fabs(realpseudovec<real_t, size> x)
  {
    return x.fabs();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> floor(realpseudovec<real_t, size> x)
  {
    return x.floor();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> fdim(realpseudovec<real_t, size> x,
                                          realpseudovec<real_t, size> y)
  {
    return x.fdim(y);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> fma(realpseudovec<real_t, size> x,
                                         realpseudovec<real_t, size> y,
                                         realpseudovec<real_t, size> z)
  {
    return x.fma(y, z);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> fmax(realpseudovec<real_t, size> x,
                                          realpseudovec<real_t, size> y)
  {
    return x.fmax(y);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> fmin(realpseudovec<real_t, size> x,
                                          realpseudovec<real_t, size> y)
  {
    return x.fmin(y);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> fmod(realpseudovec<real_t, size> x,
                                          realpseudovec<real_t, size> y)
  {
    return x.fmod(y);
  }
  
  template<typename real_t, int size>
  inline intpseudovec<real_t, size> ilogb(realpseudovec<real_t, size> x)
  {
    return x.ilogb();
  }
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> isfinite(realpseudovec<real_t, size> x)
  {
    return x.isfinite();
  }
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> isinf(realpseudovec<real_t, size> x)
  {
    return x.isinf();
  }
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> isnan(realpseudovec<real_t, size> x)
  {
    return x.isnan();
  }
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> isnormal(realpseudovec<real_t, size> x)
  {
    return x.isnormal();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> log(realpseudovec<real_t, size> x)
  {
    return x.log();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> log10(realpseudovec<real_t, size> x)
  {
    return x.log10();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> log1p(realpseudovec<real_t, size> x)
  {
    return x.log1p();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> log2(realpseudovec<real_t, size> x)
  {
    return x.log2();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> pow(realpseudovec<real_t, size> x,
                                         realpseudovec<real_t, size> y)
  {
    return x.pow(y);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> rcp(realpseudovec<real_t, size> x)
  {
    return x.rcp();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> remainder(realpseudovec<real_t, size> x,
                                               realpseudovec<real_t, size> y)
  {
    return x.remainder(y);
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> round(realpseudovec<real_t, size> x)
  {
    return x.round();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> rsqrt(realpseudovec<real_t, size> x)
  {
    return x.rsqrt();
  }
  
  template<typename real_t, int size>
  inline
  realpseudovec<real_t, size> scalbn(realpseudovec<real_t, size> x,
                                     intpseudovec<real_t, size> n)
  {
    return x.scalbn(n);
  }
  
  template<typename real_t, int size>
  inline boolpseudovec<real_t, size> signbit(realpseudovec<real_t, size> x)
  {
    return x.signbit();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> sin(realpseudovec<real_t, size> x)
  {
    return x.sin();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> sinh(realpseudovec<real_t, size> x)
  {
    return x.sinh();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> sqrt(realpseudovec<real_t, size> x)
  {
    return x.sqrt();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> tan(realpseudovec<real_t, size> x)
  {
    return x.tan();
  }
  
  template<typename real_t, int size>
  inline realpseudovec<real_t, size> tanh(realpseudovec<real_t, size> x)
  {
    return x.tanh();
  }
  
  
  
  template<typename real_t, int size>
  std::ostream& operator<<(std::ostream& os,
                           boolpseudovec<real_t, size> const& x)
  {
    os << "[";
    for (int i=0; i<size; ++i) {
      if (i!=0) os << ",";
      os << x[i];
    }
    os << "]";
    return os;
  }
  
  template<typename real_t, int size>
  std::ostream& operator<<(std::ostream& os,
                           intpseudovec<real_t, size> const& x)
  {
    os << "[";
    for (int i=0; i<size; ++i) {
      if (i!=0) os << ",";
      os << x[i];
    }
    os << "]";
    return os;
  }
  
  template<typename real_t, int size>
  std::ostream& operator<<(std::ostream& os,
                           realpseudovec<real_t, size> const& x)
  {
    os << "[";
    for (int i=0; i<size; ++i) {
      if (i!=0) os << ",";
      os << x[i];
    }
    os << "]";
    return os;
  }
  
} // namespace vecmathlib

#endif  // #ifndef VEC_PSEUDO_H
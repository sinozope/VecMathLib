// Instantiante some functions to be able to inspect the generated
// machine code

#define NDEBUG
#define VML_NODEBUG

#include "vecmathlib.h"

using namespace std;

namespace vecmathlib {
  
#ifdef VECMATHLIB_HAVE_VEC_DOUBLE_1
  template realvec<double,1> sin(realvec<double,1> x);
  template realvec<double,1> sqrt(realvec<double,1> x);
#endif
  
#ifdef VECMATHLIB_HAVE_VEC_DOUBLE_2
  template realvec<double,2> sin(realvec<double,2> x);
  template realvec<double,2> sqrt(realvec<double,2> x);
#endif
  
#ifdef VECMATHLIB_HAVE_VEC_DOUBLE_4
  template realvec<double,4> sin(realvec<double,4> x);
  template realvec<double,4> sqrt(realvec<double,4> x);
#endif
  
}

int main()
{
  return 0;
}

#include <cstdint>
#include <iostream>
#include <limits>
#include <cmath>

#include <pmmintrin.h>

#include <sleef.h>

union FloatInt {
  int32_t i;
  float f;
};
int main() {
  FloatInt fi;
  fi.i = 1;

  std::cout << fi.f << std::endl;
  int count = 0;
  while (fi.f < std::numeric_limits<float>::max()) {
    fi.i += 1;

    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    float result_denormal = xlogf(fi.f);

    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_OFF);
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_OFF);
    float result_normal = xlogf(fi.f);

    if (result_denormal != result_normal) {
      std::cout << "Result differs : " << fi.f << std::endl;
    }

    if (++count == 10000000) {
      count = 0;
      std::cout << "Computed " << fi.f << std::endl;
    }
  }
  std::cout << fi.f << std::endl;
}
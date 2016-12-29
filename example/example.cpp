#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <bitset>

#include <pmmintrin.h>

#include "purec/sleef.h"
#include "simd/sleefsimd.h"

enum FloatCategory
{
  NEGATIVE_INFINITY,
  NEGATIVE_NORMAL,
  NEGATIVE_SUBNORMAL,
  NEGATIVE_ZERO,
  POSITIVE_ZERO,
  POSITIVE_SUBNORMAL,
  POSITIVE_NORMAL,
  POSITIVE_INFINITY,
  SIZE,
};

using FloatRangeConfig = std::bitset<FloatCategory::SIZE>;

union UIntFloat {
  uint32_t u;
  float f;
};

template <typename F>
void float_loop(FloatRangeConfig config, F function)
{
  if (config[NEGATIVE_INFINITY])
  {
    function(-std::numeric_limits<float>::infinity());
  }
  if (config[NEGATIVE_NORMAL])
  {
    UIntFloat x;
    for (x.f = -std::numeric_limits<float>::max(); x.f <= -std::numeric_limits<float>::min(); --x.u)
    {
      function(x.f);
    };
  }
  if (config[NEGATIVE_SUBNORMAL])
  {
    UIntFloat x;
    x.f = -std::numeric_limits<float>::min();
    for (--x.u; x.f < -0.0f; --x.u)
    {
      function(x.f);
    };
  }
  if (config[NEGATIVE_ZERO])
  {
    function(-0.0f);
  }
  if (config[POSITIVE_ZERO])
  {
    function(0.0f);
  }
  if (config[POSITIVE_SUBNORMAL])
  {
    UIntFloat x;
    x.f = 0.0f;
    for (++x.u; x.f < std::numeric_limits<float>::min(); ++x.u)
    {
      function(x.f);
    };
  }
  if (config[POSITIVE_NORMAL])
  {
    UIntFloat x;
    for (x.f = std::numeric_limits<float>::min(); x.f <= std::numeric_limits<float>::max(); ++x.u)
    {
      function(x.f);
    };
  }
  if (config[POSITIVE_INFINITY])
  {
    function(std::numeric_limits<float>::infinity());
  }
}

int main()
{
  FloatRangeConfig config;
  config[POSITIVE_NORMAL] = 1;

  int count = 0;
  float_loop(config, [&](float x) {
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    float result_denormal = xsinf(x);

    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_OFF);
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_OFF);
    float result_normal = xsinf(x);

    if (result_denormal != result_normal)
    {
      std::cout << "Result differs : " << x << std::endl;
    }

    if (++count == 10'000'000)
    {
      count = 0;
      std::cout << "Computed " << x << std::endl;
    }
  });
}
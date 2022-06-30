#ifndef OVERCOMMITMENT_HPP
#define OVERCOMMITMENT_HPP

#include <safe_call.hpp>
#include <getDeviceProperties.hpp>

TEST(hip, Overcommitment) {
  auto devProp = getDeviceProperties(0);
  int* ptr;
  HIP_SAFE_CALL(hipHostMalloc(&ptr, 1.2 * devProp.totalGlobalMem));
  HIP_SAFE_CALL(hipFree(ptr));
  HIP_SAFE_CALL(hipMallocManaged(&ptr, 1.2 * devProp.totalGlobalMem));
  HIP_SAFE_CALL(hipFree(ptr));
}

#endif

#ifndef OVERCOMMITMENT_HPP
#define OVERCOMMITMENT_HPP

#include <cstdlib>

#include <safe_call.hpp>
#include <getDeviceProperties.hpp>

TEST(hip, Overcommitment) {
  auto devProp = getDeviceProperties(0);
  int* ptr     = nullptr;  // as we might call free on it without
                           // allocating anything
  ASSERT_NO_THROW(
      ptr = static_cast<int*>(std::malloc(10 * devProp.totalGlobalMem)));
  std::free(static_cast<void*>(ptr));
  ptr = nullptr;

  ASSERT_NO_THROW(
      HIP_SAFE_CALL(hipHostMalloc(&ptr, 1.2 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(ptr));
  ASSERT_NO_THROW(
      HIP_SAFE_CALL(hipMallocManaged(&ptr, 1.2 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(ptr));
}

TEST(hip, overcommitment_after_inital_alloc) {
  auto devProp      = getDeviceProperties(0);
  int* pre_load_ptr = nullptr;
  ASSERT_NO_THROW(
      HIP_SAFE_CALL(hipMalloc(&pre_load_ptr, 0.8 * devProp.totalGlobalMem)));

  int* host_pinned_ptr = nullptr;
  ASSERT_NO_THROW(HIP_SAFE_CALL(
      hipHostMalloc(&host_pinned_ptr, 0.5 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(host_pinned_ptr));

  int* managed_ptr = nullptr;
  ASSERT_NO_THROW(
      HIP_SAFE_CALL(hipHostMalloc(&managed_ptr, 0.5 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(managed_ptr));

  HIP_SAFE_CALL(hipFree(pre_load_ptr));
}

#endif

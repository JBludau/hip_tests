#ifndef OVERCOMMITMENT_HPP
#define OVERCOMMITMENT_HPP

#include <cstdlib>

#include <safe_call.hpp>
#include <getDeviceProperties.hpp>

TEST(hip, Overcommitment_hostMalloc) {
  auto devProp = getDeviceProperties(0);
  void* ptr    = nullptr;  // as we might call free on it without
                           // allocating anything
  ASSERT_NO_THROW(ptr = std::malloc(10 * devProp.totalGlobalMem));
  std::free(ptr);
  ptr = nullptr;

  ASSERT_NO_THROW(
      HIP_SAFE_CALL(hipHostMalloc(&ptr, 1.2 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(ptr));
}

TEST(hip, Overcommitment_managed) {
  auto devProp = getDeviceProperties(0);
  void* ptr    = nullptr;  // as we might call free on it without
                           // allocating anything
  ASSERT_NO_THROW(ptr = std::malloc(10 * devProp.totalGlobalMem));
  std::free(ptr);
  ptr = nullptr;

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
      hipHostMalloc(&host_pinned_ptr, 0.8 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(host_pinned_ptr));

  int* managed_ptr = nullptr;
  ASSERT_NO_THROW(HIP_SAFE_CALL(
      hipMallocManaged(&managed_ptr, 0.8 * devProp.totalGlobalMem)));
  HIP_SAFE_CALL(hipFree(managed_ptr));

  HIP_SAFE_CALL(hipFree(pre_load_ptr));
}

TEST(hip, repeated_alloc_managed) {
  auto devProp = getDeviceProperties(0);
  int* managed_ptr[10];
  for (unsigned i = 0; i < 10; ++i)
    ASSERT_NO_THROW(HIP_SAFE_CALL(
        hipMallocManaged(&managed_ptr[i], 0.8 * devProp.totalGlobalMem)));

  for (unsigned i = 0; i < 10; ++i) HIP_SAFE_CALL(hipFree(managed_ptr[i]));
}

TEST(hip, repeated_alloc_device) {
  auto devProp = getDeviceProperties(0);
  int* device_ptr[10];
  for (unsigned i = 0; i < 10; ++i)
    ASSERT_NO_THROW(
        HIP_SAFE_CALL(hipMalloc(&device_ptr[i], 0.8 * devProp.totalGlobalMem)));

  for (unsigned i = 0; i < 10; ++i) HIP_SAFE_CALL(hipFree(device_ptr[i]));
}
#endif

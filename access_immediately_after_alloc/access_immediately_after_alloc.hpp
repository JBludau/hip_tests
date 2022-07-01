#ifndef ACCESS_IMMEDIATELY_AFTER_ALLOC_HPP
#define ACCESS_IMMEDIATELY_AFTER_ALLOC_HPP

#include <safe_call.hpp>

TEST(hip, Access_immediately_after_alloc) {
  auto devProp = getDeviceProperties(0);
  int* ptr;
  int value;
  // make the allocation big, so we have some time to access it immediately
  // after
  HIP_SAFE_CALL(hipMallocManaged(&ptr, 0.5 * devProp.totalGlobalMem));
  ASSERT_NO_THROW(value = ptr[0]);
  ASSERT_NO_THROW(ptr[0] = value + 1);
  HIP_SAFE_CALL(hipFree(ptr));
}

#endif

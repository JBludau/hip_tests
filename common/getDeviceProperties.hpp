#ifndef GET_DEVICE_PROPERTIES_HPP
#define GET_DEVICE_PROPERTIES_HPP

#include <hip/hip_runtime.h>
#include <safe_call.hpp>

hipDeviceProp_t getDeviceProperties(int deviceId) {
  hipDeviceProp_t devProp;
  HIP_SAFE_CALL(hipGetDeviceProperties(&devProp, deviceId));
  return devProp;
}

#endif

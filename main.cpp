#include <gtest/gtest.h>
#include <iostream>
#include <hip/hip_runtime.h>
#include <safe_call.hpp>
#include <printDeviceInfo.hpp>
#include <getDeviceProperties.hpp>

#include "overcommitment/overcommitment.hpp"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  std::cout << getDeviceProperties(0) << std::endl;
  return RUN_ALL_TESTS();
}

#ifndef SAFE_CALL_HPP
#define SAFE_CALL_HPP

#include <stdexcept>

inline void hip_safe_call(hipError_t e, const char* name,
                          const char* file = nullptr, const int line = 0) {
  if (hipSuccess != e) {
    std::ostringstream out;
    out << name << " error( " << hipGetErrorName(e)
        << "): " << hipGetErrorString(e);
    if (file) {
      out << " " << file << ":" << line;
    }
    throw std::runtime_error(out.str());
  }
}

#define HIP_SAFE_CALL(call) hip_safe_call(call, #call, __FILE__, __LINE__)

#endif  // guard

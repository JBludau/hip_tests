#ifndef PRINT_DEVICE_INFO_HPP
#define PRINT_DEVICE_INFO_HPP
#include <iostream>

std::ostream& operator<<(std::ostream& out, hipDeviceProp_t const& devProp) {
  out << "Device supports allocating managed memory on this system: "
      << devProp.managedMemory << "\n";
  out << "Host can directly access managed memory on the device without "
         "migration: "
      << devProp.directManagedMemAccessFromHost << "\n";

  out << "Device can coherently access managed memory concurrently with the "
         "CPU: "
      << devProp.concurrentManagedAccess << "\n";

  out << "Device has pagable memory access: " << devProp.pageableMemoryAccess
      << "\n";

  out << "Device accesses pageable memory via the host's page tables: "
      << devProp.pageableMemoryAccessUsesHostPageTables << "\n";

  return out;
}
#endif

#include "info_storage.h"

#include <iostream>

InfoStorage& InfoStorage::GetInstance() {
  static InfoStorage storage;
  return storage;
}

InfoStorage::~InfoStorage() {
  CheckMap();
}

void InfoStorage::Register(void* ptr, const PtrInfo& info) {
  // if (already in map - add error)
  ptr_map[ptr] = info;
}

void InfoStorage::Unregister(void* ptr) {
  auto iter = ptr_map.find(ptr);
  if (iter == ptr_map.end())
    std::cout << "Try to erase unregistered pointer " << std::hex << ptr << std::dec << "!" << std::endl;
  ptr_map.erase(ptr);
}

// PRIVATE FUNCS

void InfoStorage::CheckMap() const {
  if(ptr_map.empty()) return;
  std::cout << "Memory leak summary:" << std::endl;
  std::map<void*, PtrInfo>::const_iterator iter = ptr_map.begin();
  unsigned int leaked_bytes = 0;
  for ( ; iter != ptr_map.end(); ++iter) {
    std::cout << "\t" << iter->second.func_name << " (" << std::hex
	      << iter->first << std::dec << ") missed " << iter->second.size
	      << " bytes in " << iter->second.file << ":" << iter->second.line <<  std::endl;
    leaked_bytes += iter->second.size;
    free(iter->first);
  }
    std::cout << "Total leaked " << leaked_bytes << " bytes" << std::endl;
}

InfoStorage::InfoStorage() {
}

InfoStorage& GetInfoStorage() {
  return InfoStorage::GetInstance();
}

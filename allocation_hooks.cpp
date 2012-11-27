#include <stdlib.h>
#include <iostream>
#include <map>

struct PtrInfo{
  const char* file;
  int line;
};

std::map<void*, PtrInfo> ptr_map;

void* operator new(size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  //std::cout << std::hex << ptr << std::dec << " " << file << " " << line << std::endl;
  ptr_map[ptr] = {file, line};
  return ptr;
}

void* operator new[](size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  //std::cout << std::hex << ptr << std::dec << " " << file << " " << line << std::endl;
  ptr_map[ptr] = {file, line};
  return ptr;
}

void operator delete(void* ptr) {
  //std::cout << std::hex << ptr << std::endl;
  ptr_map.erase(ptr);
  free(ptr);
}

void operator delete[](void* ptr) {
  //std::cout << std::hex << ptr << std::endl;
  ptr_map.erase(ptr);
  free(ptr);
}


void check_map() {
  if(ptr_map.empty()) return;
  std::map<void*, PtrInfo>::const_iterator iter = ptr_map.begin();
  for ( ; iter != ptr_map.end(); ++iter) {
    std::cout << "MEMORY LEAK! " << std::hex << iter->first << std::dec << " "
	      << iter->second.file << " " << iter->second.line << std::endl;
  }
}

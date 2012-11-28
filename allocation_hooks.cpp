#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <map>

struct PtrInfo{
  const char* file;
  int line;
};

std::map<void*, PtrInfo> ptr_map;

void add_ptr(void* ptr, const PtrInfo& info) {
  ptr_map[ptr] = info;  
}

void erase_ptr(void* ptr) {
  ptr_map.erase(ptr);
}

void* operator new(size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  //std::cout << std::hex << ptr << std::dec << " " << file << " " << line << std::endl;
  add_ptr(ptr, {file, line});
  return ptr;
}

void* operator new[](size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  //std::cout << std::hex << ptr << std::dec << " " << file << " " << line << std::endl;
  add_ptr(ptr, {file, line});
  ptr;
}

void operator delete(void* ptr) {
  //std::cout << std::hex << ptr << std::endl;
  erase_ptr(ptr);
  free(ptr);
}

void operator delete[](void* ptr) {
  //std::cout << std::hex << ptr << std::endl;
  erase_ptr(ptr);
  free(ptr);
}

void* malloc(size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  ptr_map[ptr] = {file, line};
  return ptr;
}
void* calloc(size_t num, size_t size, const char* file, int line) {
  void* ptr = calloc(num, size);  
  add_ptr(ptr, {file, line});
  return ptr;
}
void* realloc(void* source, size_t size, const char* file, int line) {
  void* ptr = realloc(source, size);
  erase_ptr(source);
  add_ptr(ptr, {file, line});
  return ptr;
}
void free(void* ptr, const char* file, int line) {
  erase_ptr(ptr);
  free(ptr);
}


void check_map() {
  if(ptr_map.empty()) return;
  std::map<void*, PtrInfo>::const_iterator iter = ptr_map.begin();
  for ( ; iter != ptr_map.end(); ++iter) {
    std::cout << "MEMORY LEAK! " << std::hex << iter->first << std::dec << " "
	      << iter->second.file << " " << iter->second.line << std::endl;
    free(iter->first);
  }
}

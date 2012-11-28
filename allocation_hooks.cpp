#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <map>
#include <typeinfo>

const char* ALLOC_STRINGS[] = {
  "operator new",
  "operator new[]",
  "malloc",
  "calloc",
  "realloc"
};
enum AllocType { NEW, NEW_WITH_BRACKETS, MALLOC, CALLOC, REALLOC };

struct PtrInfo{
  const char* file;
  int line;
  int size;
  AllocType type;
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
  add_ptr(ptr, {file, line, size, NEW});
  return ptr;
}

void* operator new[](size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  add_ptr(ptr, {file, line, size, NEW_WITH_BRACKETS});
  ptr;
}

void operator delete(void* ptr) {
  erase_ptr(ptr);
  free(ptr);
}

void operator delete[](void* ptr) {
  erase_ptr(ptr);
  free(ptr);
}

void* malloc(size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  ptr_map[ptr] = {file, line, size, MALLOC};
  return ptr;
}
void* calloc(size_t num, size_t size, const char* file, int line) {
  void* ptr = calloc(num, size);  
  add_ptr(ptr, {file, line, size, CALLOC});
  return ptr;
}
void* realloc(void* source, size_t size, const char* file, int line) {
  void* ptr = realloc(source, size);
  erase_ptr(source);
  add_ptr(ptr, {file, line, size, REALLOC});
  return ptr;
}
void free(void* ptr, const char* file, int line) {
  erase_ptr(ptr);
  free(ptr);
}


void check_map() {
  if(ptr_map.empty()) return;
  std::cout << "Memory leak summary:" << std::endl;
  std::map<void*, PtrInfo>::const_iterator iter = ptr_map.begin();
  unsigned int leaked_bytes = 0;
  for ( ; iter != ptr_map.end(); ++iter) {
    std::cout << "\t" << ALLOC_STRINGS[iter->second.type] << " (" << std::hex
	      << iter->first << std::dec << ") missed " << iter->second.size
	      << " bytes in " << iter->second.file << ":" << iter->second.line <<  std::endl;
    leaked_bytes += iter->second.size;
    free(iter->first);
  }
  std::cout << "Total leaked " << leaked_bytes << " bytes" << std::endl;
}

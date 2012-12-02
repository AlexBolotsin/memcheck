#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <map>
#include <list>

struct PtrInfo{
  const char* file;
  int line;
  int size;
  const char* func_name;
};

class InfoStorage {
  std::list<const char*> error_list;
  std::map<void*, PtrInfo> ptr_map;

  void check_map() const {
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

  InfoStorage() {}
  InfoStorage(const InfoStorage& rhs);
  InfoStorage& operator=(const InfoStorage& rhs);
public:

  static InfoStorage& GetInstance() {
    static InfoStorage storage;
    return storage;
  }

  ~InfoStorage() {
    check_map();
  }

  void add_ptr(void* ptr, const PtrInfo& info) {
    ptr_map[ptr] = info;
  }

  void error(const char* msg) {
    error_list.push_back(msg);
    std::cout << msg << std::endl;
  }

  void erase_ptr(void* ptr) {
    auto iter = ptr_map.find(ptr);
    if (iter == ptr_map.end())
      std::cout << "Try to erase unregistered pointer " << std::hex << ptr << std::dec << "!" << std::endl;
    ptr_map.erase(ptr);
  }
};

InfoStorage& GetInfoStorage() {
  return InfoStorage::GetInstance();
}

void* operator new(size_t size, const char* file, int line) throw (std::bad_alloc) {
  void* ptr = malloc(size);
  if (!ptr) throw std::bad_alloc();
  GetInfoStorage().add_ptr(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void* operator new[](size_t size, const char* file, int line) throw (std::bad_alloc) {
  void* ptr = malloc(size);
  if (!ptr) throw std::bad_alloc();
  GetInfoStorage().add_ptr(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void operator delete(void* ptr) {
  GetInfoStorage().erase_ptr(ptr);
  free(ptr);
}

void operator delete[](void* ptr) {
  GetInfoStorage().erase_ptr(ptr);
  free(ptr);
}

void* malloc(size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  GetInfoStorage().add_ptr(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void* calloc(size_t num, size_t size, const char* file, int line) {
  void* ptr = calloc(num, size);  
  GetInfoStorage().add_ptr(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void* realloc(void* source, size_t size, const char* file, int line) {
  void* ptr = realloc(source, size);
  if (source)
    GetInfoStorage().erase_ptr(source);
  if (ptr) {
    GetInfoStorage().add_ptr(ptr, {file, line, size, __FUNCTION__});
  } else {
    ptr = source;
  }
  return ptr;
}

void free(void* ptr, const char* file, int line) {
  GetInfoStorage().erase_ptr(ptr);
  free(ptr);
}

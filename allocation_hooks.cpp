#include <stdlib.h>
#include <cstring>

#include "info_storage.h"

/*! Define function which does exist in memcheck lib
  @return Reference to InfoStorage
 */
InfoStorage& GetInfoStorage();

void* operator new(size_t size, const char* file, int line) throw (std::bad_alloc) {
  void* ptr = malloc(size);
  if (!ptr) throw std::bad_alloc();
  GetInfoStorage().Register(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void* operator new[](size_t size, const char* file, int line) throw (std::bad_alloc) {
  void* ptr = malloc(size);
  if (!ptr) throw std::bad_alloc();
  GetInfoStorage().Register(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void operator delete(void* ptr) {
  GetInfoStorage().Unregister(ptr);
  free(ptr);
}

void operator delete[](void* ptr) {
  GetInfoStorage().Unregister(ptr);
  free(ptr);
}

void* malloc(size_t size, const char* file, int line) {
  void* ptr = malloc(size);
  GetInfoStorage().Register(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

void* calloc(size_t num, size_t size, const char* file, int line) {
  void* ptr = calloc(num, size);  
  GetInfoStorage().Register(ptr, {file, line, size, __FUNCTION__});
  return ptr;
}

/*! It has pretty tricky logic.
  @param[in] source regularly it gets pointer to existing memory. If equals 0 so realloc works as malloc.
  @param[in] size regularly it gets size of new memory. If equals 0 so realloc works as free.
  /TODO Fix it and test in cppunit
  @return Pointer to new memory. Null if it fails of size equals 0.
 */
void* realloc(void* source, size_t size, const char* file, int line) {
  void* ptr = realloc(source, size);
  if (source)
    GetInfoStorage().Unregister(source);
  if (ptr) {
    GetInfoStorage().Register(ptr, {file, line, size, __FUNCTION__});
  } else {
    ptr = source;
  }
  return ptr;
}

void free(void* ptr, const char* file, int line) {
  GetInfoStorage().Unregister(ptr);
  free(ptr);
}

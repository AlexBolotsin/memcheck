#ifndef __TRACKER_H__
#define __TRACKER_H__

#include <iostream>
#include <typeinfo>

class MemoryTracker {
  const char* file_;
  int line_;
 public:
  MemoryTracker(const char* file, int line) : file_(file), line_(line) {
  }
  const char* GetFile() const { return file_; }
  int GetLine() const { return line_; }
};

template <class T> inline T *operator*(const MemoryTracker& track, T *p) {
  std::cout << track.GetFile() << ":" << track.GetLine() << " " << typeid(p).name() << std::endl;
  return p;
}

#define MEMCHECK MemoryTracker(__FILE__, __LINE__) *
#define new      MEMCHECK new
#define malloc   MEMCHECK malloc
#define calloc   MEMCHECK calloc
#define realloc  MEMCHECK realloc
#define free     MEMCHECK free

#endif

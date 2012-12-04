#ifndef __PTR_INFO_H__
#define __PTR_INFO_H__

struct PtrInfo{
  const char* file;
  int line;
  int size;
  const char* func_name;
};

#endif

#ifndef __INFO_STORAGE_H__
#define __INFO_STORAGE_H__

#include <map>
#include <list>

#include "ptr_info.h"

class InfoStorage {
  InfoStorage();
  InfoStorage(const InfoStorage& rhs);
  InfoStorage& operator=(const InfoStorage& rhs);

 public:
  static InfoStorage& GetInstance();

  ~InfoStorage();

  void Register(void* ptr, const PtrInfo& info);

  void Unregister(void* ptr);
  
 private:
  void CheckMap() const;

  std::map<void*, PtrInfo> ptr_map;
};

#endif

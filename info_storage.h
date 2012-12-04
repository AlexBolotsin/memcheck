#ifndef __INFO_STORAGE_H__
#define __INFO_STORAGE_H__

#include <map>
#include <list>

#include "ptr_info.h"

class InfoStorage {
  InfoStorage();
  /*! We don't need it
   */
  InfoStorage(const InfoStorage& rhs);
  /*! We don't need it
   */
  InfoStorage& operator=(const InfoStorage& rhs);

 public:
  /*! Method to provide simple Singleton
    @return Reference to static IntoStorage
   */
  static InfoStorage& GetInstance();

  ~InfoStorage();

  /*! Register pointer with info in ptr_map
    @param[in] ptr
    @param[in] info
  */
  void Register(void* ptr, const PtrInfo& info);

  /*! Unregister pointer from ptr_map
    @param[in] ptr
   */
  void Unregister(void* ptr);
  
 private:
  /*! Uses in destructor to send ptr_map with unfreed pointers to logger
   */
  void CheckMap() const;

  std::map<void*, PtrInfo> ptr_map;
};

#endif

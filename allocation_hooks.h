void* operator new(size_t size, const char* file, int line);
void* operator new[](size_t size, const char* file, int line);
void operator delete(void* ptr);
void operator delete[](void* ptr);
void check_map();

#define new new(__FILE__, __LINE__)

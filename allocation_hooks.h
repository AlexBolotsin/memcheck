void* operator new(size_t size, const char* file, int line);
void* operator new[](size_t size, const char* file, int line);
void operator delete(void* ptr);
void operator delete[](void* ptr);
void* malloc(size_t size, const char* file, int line);
void* calloc(size_t num, size_t size, const char* file, int line);
void* realloc(void* ptr, size_t size, const char* file, int line);
void free(void* ptr, const char* file, int line);

#define new             new(__FILE__, __LINE__)
#define malloc(A)       malloc((A), __FILE__, __LINE__)
#define calloc(A, B)    calloc((A), (B), __FILE__, __LINE__)
#define realloc(A, B)   realloc((A), (B), __FILE__, __LINE__)
#define free(A)         free((A), __FILE__, __LINE__)

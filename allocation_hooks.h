/*! This header is common part of all. It's redefine all memory allocating operations.
  Also it redefine free operations.
  So the major point: we register ptr with info about it (file of use, line ans stuff)
  on allocation. Then at free call we unregister it. So at the end we have map of unfreed ptr.
  That is the point.
  
  It has logger wrapper and lib for it. Now it's only do output into cout but it's possible to write
  your own logger or wrapper on existing one. There is only one major dependencie - it has to overload
  operator<<(ostream).

  It will have error hanlder to keep away situations when we free ptr which doesn't exist in the info storage.
  Now it writes common errors in cout ^_^

  So good luck and be cool!

  AlexBolotsin@GMail.com
 */

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

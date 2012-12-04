#include <iostream>
#ifdef MEMCHECK
#include "allocation_hooks.h"
#else
#include <cstdlib>
#endif

int main(int argc, char** argv) {
  int* num = new int;
  num = new int[1];
  void* chunk = malloc(sizeof(int));
  chunk = calloc(1, sizeof(int));
  chunk = calloc(1, sizeof(int));
  chunk = realloc(chunk, 2*sizeof(num));
}

#include <iostream>
#include "allocation_hooks.h"

int main(int argc, char** argv) {
  int* num = new int;
  num = new int[1];
  void* chunk = malloc(sizeof(int));
  chunk = calloc(1, sizeof(int));
  chunk = realloc(num, sizeof(int));
  check_map();
}

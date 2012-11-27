#include <iostream>
#include "allocation_hooks.h"

int main(int argc, char** argv) {
  int* num = new int;
  num = new int[1];
  check_map();
}

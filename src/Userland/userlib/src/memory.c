#include <memory.h>

void * malloc(unsigned int size) {
  return reserve_memory(size);
}

void * calloc(unsigned int size) {
  return reserve_memory(size);
}

void free() {
  return;
}

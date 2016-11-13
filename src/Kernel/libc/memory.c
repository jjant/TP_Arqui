#include <memory.h>
void * __malloc(unsigned int size) {
  static void * ptr = 0x90000;

  unsigned int i = 0;
  void * ret = ptr;
  ptr += size;

  for(i = 0; i < size; i++)
    ((char *)ret)[i] = 0;

  return ret;
}

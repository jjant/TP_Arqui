#ifndef MEMORY_H
#define MEMORY_H

void * reserve_memory(unsigned int size);
void * malloc(unsigned int size);
void * calloc(unsigned int size);
void free();

#endif
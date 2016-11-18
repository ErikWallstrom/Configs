#ifndef MEMORY_H
#define MEMORY_H

#include "Base.h"

#ifndef STDLIB_ALLOC
#	define malloc(size) Memory_alloc(stdalloc, size)
#	define free(ptr) Memory_free(stdalloc, ptr)
#	define realloc
#endif

#define STDALLOC_SIZE 10000000
extern struct Allocator* stdalloc;

__attribute__((constructor)) 
void Memory_init_stdalloc(void);

struct Allocator* Allocator_new(size_t size);
void* Memory_alloc(struct Allocator* a, size_t size);
void Memory_free(struct Allocator* a, void* memory);
void Allocator_delete(struct Allocator** allocator);

#endif

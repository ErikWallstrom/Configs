#define STDLIB_ALLOC
#include "Memory.h"
#include <assert.h>

#define MEMORY_ALIGNMENT _Alignof(void*)
#define MEMORY_NEW_SIZE 1.5

struct Allocator
{
	struct Allocator* next;
	size_t memory_size;
	char* head;
	char memory[];
} *stdalloc;

static inline size_t get_aligned_size(size_t size)
{
	if(size % MEMORY_ALIGNMENT)
		return size + (MEMORY_ALIGNMENT - (size % MEMORY_ALIGNMENT));
	return size;
}

static void Memory_cleanup_stdalloc(void)
{
	assert(stdalloc);
	puts("stdalloc terminated");
	Allocator_delete(&stdalloc);
}

void Memory_init_stdalloc(void)
{
	puts("stdalloc initialized");
	stdalloc = Allocator_new(STDALLOC_SIZE);
	atexit(Memory_cleanup_stdalloc);
}

struct Allocator* Allocator_new(size_t size)
{
	assert(size > 0);
	size_t memory_size = get_aligned_size(size);
	struct Allocator* a = aligned_alloc(MEMORY_ALIGNMENT, sizeof(struct Allocator) + memory_size);
	if(!a)
		debug(DEBUG_ALLOC_FAILURE);

	a->next = NULL;
	a->head = a->memory;
	a->memory_size = memory_size;
	return a;
}

void* Memory_alloc(struct Allocator* a, size_t size)
{
	assert(a && size > 0);
	size_t alloc_size = get_aligned_size(size);
	char* alloc_memory = NULL;
	for(struct Allocator* alloc = a; alloc; alloc = alloc->next)
	{
		if(alloc->head + alloc_size < alloc->memory + alloc->memory_size)
		{
			alloc_memory = alloc->head;
			alloc->head += alloc_size;
			break;
		}
	}

	if(!alloc_memory)
	{
		struct Allocator* new_a = Allocator_new(a->memory_size + size * MEMORY_NEW_SIZE);
		a->next = new_a;
		alloc_memory = new_a->head;
		new_a->head += alloc_size;
	}
	return alloc_memory;
}

void Memory_free(struct Allocator* a, void* memory)
{
	assert(a && memory);
	assert(0);
}

void Allocator_delete(struct Allocator** allocator)
{
	assert(allocator && *allocator);
	{
		struct Allocator* a = *allocator;
		for(struct Allocator* n; a ? (n = a->next, 1) : 0; a = n)
			free(a);
	}
	*allocator = NULL;
}


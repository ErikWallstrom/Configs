#include "Vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VEC_DEFAULT_SIZE 5
#define VEC_NEW_SIZE 5
#define VEC_ALLOC_FAILED "Memory allocation failed"
#define VEC_NULL_ARGUMENT "vec is NULL"

#define null_check(p, msg) \
	do { \
		if(!p) \
		{ \
			printf("Error: %s, at {%s} [%s, %i]\n", \
					(msg), __func__, __FILE__, __LINE__); \
			abort(); \
		} \
	} while(0)

#define magic_check(vec) \
	do { \
		if((vec)->magic == MAGIC_ALLOCATED) \
			if(*(unsigned int*)((vec)->buffer + (vec)->buffer_size) == MAGIC_ALLOCATED) \
				break; \
			else \
				if(*(unsigned int*)((vec)->buffer + (vec)->buffer_size) == MAGIC_FREED) \
					printf("Error: Vector passed to {%s} [%s, %i] has had an unknown error\n", \
						__func__, __FILE__, __LINE__); \
				else \
					printf("Error: Vector passed to {%s} [%s, %i] has been written to out of bound\n", \
						__func__, __FILE__, __LINE__); \
		else if((vec)->magic == MAGIC_FREED) \
			printf("Error: Vector passed to {%s} [%s, %i] is already destroyed\n", \
					__func__, __FILE__, __LINE__); \
		else \
			printf("Error: Value passed to {%s} [%s, %i] is not a vector\n", \
					__func__, __FILE__, __LINE__); \
		abort(); \
	} while(0)

#define to_vector(vp) (struct _Vector*)((*(char**)(vp)) - offsetof(struct _Vector, buffer))

enum Magic_Numbers
{
	MAGIC_ALLOCATED = 0xA110CA7E,
	MAGIC_FREED 	= 0xDEADEDED
};

struct _Vector
{
	VECTOR_STRUCT;
	unsigned int magic;
	char buffer[];
};

struct Vector Vector(Vec(void) vec)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	return *(struct Vector*)self;
}

Vec(void) Vec_ctor(size_t element_size, size_t elements)
{
	if(element_size < 1)
	{
		printf("Error: element_size must be at least 1, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}

	size_t buffer_size = (elements ?
			elements : VEC_DEFAULT_SIZE) * element_size;
	struct _Vector* self = malloc(sizeof(struct _Vector) + 
			buffer_size + sizeof(unsigned int));
	null_check(self, VEC_ALLOC_FAILED);

	self->buffer_size = buffer_size;
	self->element_size = element_size;
	self->size = 0;
	self->magic = MAGIC_ALLOCATED;
	*(unsigned int*)(self->buffer + self->buffer_size) = MAGIC_ALLOCATED;

	return self->buffer;
}

Vec(void) Vec_copy(Vec(void) vec)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	void* dest = Vec_ctor(self->element_size, self->buffer_size / self->element_size);
	struct _Vector* d = to_vector(&dest);
	d->size = self->size;
	memcpy(dest, self->buffer, self->buffer_size);
	*(unsigned int*)(self->buffer + self->buffer_size) = MAGIC_ALLOCATED;
	return dest;
}

void Vec_dtor(Vec(void) vec)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	self->magic = MAGIC_FREED;
	*(unsigned int*)(self->buffer + self->buffer_size) = MAGIC_FREED;
	free(self);
}

void Vec_expand(Vec(void) vec, size_t pos, size_t elements)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	if(elements < 1)
	{
		printf("Error: Expanding with 0 is useless, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	if(self->size < pos)
	{
		printf("Error: Index is out of bounds, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}

	self->size += elements;
	if(self->buffer_size < self->size * self->element_size)
	{
		self->buffer_size = self->size * self->element_size + self->element_size * VEC_NEW_SIZE;
		self = realloc(self, sizeof(struct _Vector) + self->buffer_size + sizeof(unsigned int));
		*(void**)vec = self->buffer;
		null_check(self, VEC_ALLOC_FAILED);
	}

	memmove(self->buffer + (pos + elements) * self->element_size, 
			self->buffer + pos * self->element_size, (self->size - elements - pos) * self->element_size);
	*(unsigned int*)(self->buffer + self->buffer_size) = MAGIC_ALLOCATED;
}

void Vec_collapse(Vec(void) vec, size_t pos, size_t elements)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	if(elements < 1)
	{
		printf("Error: Collapsing 0 is useless, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}
	struct _Vector* self = to_vector(vec);
	if(self->size <= pos)
	{
		printf("Error: Index is out of bounds, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}
	magic_check(self);

	memmove(self->buffer + pos * self->element_size, 
			self->buffer + (pos + elements) * self->element_size,
			(self->size - elements - pos) * self->element_size);
	self->size -= elements;
}

void Vec_set(Vec(void) vec, void* data, size_t elements)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	/*null_check(data, VEC_NULL_ARGUMENT);
	if(elements < 1)
	{
		printf("Error: Setting an empty array is useless, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}*/
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	self->size = elements;
	if(self->buffer_size < self->element_size * elements)
	{
		self->buffer_size = elements * self->element_size;
		self = realloc(self, sizeof(struct _Vector) + self->buffer_size + sizeof(unsigned int));
		*(void**)vec = self->buffer;
		null_check(self, VEC_ALLOC_FAILED);
	}

	memmove(self->buffer, data, self->size * self->element_size);
	*(unsigned int*)(self->buffer + self->buffer_size) = MAGIC_ALLOCATED;
}

void Vec_append(Vec(void) vec, void* data, size_t elements)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	null_check(data, VEC_NULL_ARGUMENT);
	if(elements < 1)
	{
		printf("Error: Setting an empty array is useless, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	Vec_expand(vec, self->size, elements);
	self = to_vector(vec);
	memcpy(self->buffer + (self->size - elements) * self->element_size, data, elements * self->element_size);
}

void Vec_prepend(Vec(void) vec, void* data, size_t elements)
{
	null_check(vec, VEC_NULL_ARGUMENT);
	null_check(data, VEC_NULL_ARGUMENT);
	if(elements < 1)
	{
		printf("Error: Setting an empty array is useless, at {%s} [%s, %i]\n", __func__, __FILE__, __LINE__);
		abort();
	}
	struct _Vector* self = to_vector(vec);
	magic_check(self);

	Vec_expand(vec, 0, elements);
	self = to_vector(vec);
	memcpy(self->buffer, data, elements * self->element_size);
}


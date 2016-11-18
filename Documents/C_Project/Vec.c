#include "Vec.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define Vec_error(msg) \
	do { \
		printf("Error: \"%s\", in %s at [%i] %s\n", msg, __FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)
#define VEC_ALLOC_FAILED "Memory allocation failed"
#define VEC_DEFAULT_SIZE 5 /* must be >= 1 */
#define VEC_NEW_SIZE 2 /* must be >= 1 */

void* Vec_ctor(void* vec, size_t element_size, size_t elements)
{
	assert(vec); 
	assert(element_size > 0);
	Vec(char)* self = vec;

	self->buffer_size = (elements ? elements : VEC_DEFAULT_SIZE) * element_size;
	self->element_size = element_size;
	self->size = 0;

	self->buffer = malloc(self->buffer_size);
	if(!self->buffer)
		Vec_error(VEC_ALLOC_FAILED);
	return self;
}

void* Vec_copy(void* vec, void* dest)
{
	assert(vec);
	assert(dest);
	Vec(char)* self = vec;
	assert(self->buffer);

	Vec(char)* d = Vec_ctor(dest, self->element_size, self->size);
	d->size = self->size;
	memcpy(d->buffer, self->buffer, d->element_size * d->size);

	return d;
}

void Vec_make_space(void* vec, size_t pos, size_t elements)
{
	assert(vec);
	assert(elements);
	Vec(char)* self = vec;
	assert(self->buffer);
	assert(self->size >= pos); 

	self->size += elements;
	if(self->buffer_size < self->size * self->element_size)
	{
		self->buffer_size = self->size * self->element_size * VEC_NEW_SIZE;
		self->buffer = realloc(self->buffer, self->buffer_size);
		if(!self->buffer)
			Vec_error(VEC_ALLOC_FAILED);
	}

	memmove(self->buffer + (pos + elements) * self->element_size, self->buffer + pos * self->element_size, (self->size - elements - pos) * self->element_size);
}

void Vec_remove(void* vec, size_t pos, size_t elements)
{
	assert(vec);
	Vec(char)* self = vec;
	assert(self->buffer);
	assert(self->size > pos);

	memmove(self->buffer + pos * self->element_size, self->buffer + (pos + elements) * self->element_size, (self->size - elements - pos) * self->element_size);

	self->size -= elements;
}

void Vec_set(void* vec, void* data, size_t elements)
{
	assert(vec);
	assert(data);
	assert(elements);
	Vec(char)* self = vec;
	assert(self->buffer);

	self->size = elements;
	if(self->buffer_size < self->element_size * elements)
	{
		self->buffer_size = elements * self->element_size;
		free(self->buffer);
		self->buffer = malloc(self->buffer_size);
	}

	memcpy(self->buffer, data, self->size * self->element_size);
}

void Vec_append(void* vec, void* data, size_t elements)
{
	assert(vec);
	assert(data);
	assert(elements);
	Vec(char)* self = vec;
	assert(self->buffer);

	Vec_make_space(self, self->size, elements);

	memcpy(self->buffer + (self->size - elements) * self->element_size, data, elements * self->element_size);
}

void Vec_prepend(void* vec, void* data, size_t elements)
{
	assert(vec);
	assert(data);
	assert(elements);
	Vec(char)* self = vec;
	assert(self->buffer);

	Vec_make_space(self, 0, elements);
	memcpy(self->buffer, data, elements * self->element_size);
}

void Vec_dtor(void* vec)
{
	assert(vec);
	Vec(char)* self = vec;
	assert(self->buffer);
	free(self->buffer);
	self->buffer = NULL;
}


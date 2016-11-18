#include "Arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Arr_error(msg) \
	do { \
		printf("Error: \"%s\", in %s at [%i] %s\n", msg, __FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)
#define Arr_ALLOC_FAILED "Memory allocation failed"

struct Arr
{
	_Bool is_dynamic;
	size_t elements;
	size_t element_size;
	size_t data_size;
	char data[];
};

void* Arr_new(size_t elements, size_t element_size, _Bool is_dynamic)
{
	assert(element_size > 0);
	struct Arr* self;
	if(is_dynamic)
	{
		self = malloc(sizeof(struct Arr) + elements * element_size);
		if(!self)
			Arr_error(Arr_ALLOC_FAILED);
		*self = (struct Arr){
			.is_dynamic = 1,
			.elements = 0,
			.element_size = element_size,
			.data_size = elements * element_size
		};
	}
	else
	{
		assert(elements > 0);
		self = aligned_alloc(element_size, sizeof(struct Arr) + elements * element_size);
		if(!self)
			Arr_error(Arr_ALLOC_FAILED);
		*self = (struct Arr){
			.is_dynamic = 0,
			.elements = elements,
			.element_size = element_size,
			.data_size = elements * element_size
		};
	}
	return self->data;
}

size_t Arr_len(void* array)
{
	assert(array);
	struct Arr* self = (struct Arr*)((char*)array - sizeof(struct Arr));
	return self->elements;
}

void* Arr_make_space(void* array, size_t pos)
{
	assert(array);
	struct Arr* self = (struct Arr*)((char*)array - sizeof(struct Arr));
	assert(self->is_dynamic && pos <= self->elements);
	self->elements++;
	if(self->data_size / self->element_size < self->elements)
	{
		self->data_size = self->elements * self->element_size * 2;
		self = realloc(self, sizeof(struct Arr) + self->data_size);
		if(!self)
			Arr_error(Arr_ALLOC_FAILED);
	}

	memmove(self->data + ((pos + 1) * self->element_size), self->data + pos * self->element_size, (self->elements - pos - 1) * self->element_size);
	return self->data;
}

void Arr_remove(void* array, size_t pos)
{
	assert(array);
	struct Arr* self = (struct Arr*)((char*)array - sizeof(struct Arr));
	assert(self->is_dynamic && pos < self->elements);
	memmove(self->data + (pos * self->element_size), self->data + ((pos + 1) * self->element_size), (self->elements - pos - 1) * self->element_size);
	self->elements--;
}

void Arr_set(void* array, void* literal)
{
	assert(array && literal);
	struct Arr* self = (struct Arr*)((char*)array - sizeof(struct Arr));
	assert(!self->is_dynamic);
	memcpy(self->data, literal, self->data_size);
}

void Arr_delete(void* array_ptr)
{
	void** array = array_ptr;
	assert(array && *array);
	free((char*)*array - sizeof(struct Arr));
	*array = NULL;
}


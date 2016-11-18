#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#define Vec(T) T *

#define Vec_insert(vec, pos, ...) Vec_expand(vec, pos, 1), (*(vec))[pos] = __VA_ARGS__
#define Vec_push(vec, ...) Vec_insert(vec, 0, __VA_ARGS__)
#define Vec_push_back(vec, ...) Vec_expand(vec, Vector(vec).size, 1), (*(vec))[Vector(vec).size - 1] = __VA_ARGS__
#define Vec_pop(vec) Vec_collapse(vec, 0, 1)
#define Vec_pop_back(vec) Vec_collapse(vec, Vector(vec).size - 1, 1)

#define VECTOR_STRUCT \
	size_t size; \
	size_t buffer_size; \
	size_t element_size

struct Vector { VECTOR_STRUCT; };
struct Vector Vector(Vec(void) vec);

Vec(void) Vec_ctor(size_t element_size, size_t elements);
Vec(void) Vec_copy(Vec(void) vec);
void Vec_dtor(Vec(void) vec);

void Vec_expand(Vec(void) vec, size_t pos, size_t elements);
void Vec_collapse(Vec(void) vec, size_t pos, size_t elements);

void Vec_set(Vec(void) vec, void* data, size_t elements);
void Vec_append(Vec(void) vec, void* data, size_t elements);
void Vec_prepend(Vec(void) vec, void* data, size_t elements);

#endif


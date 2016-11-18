#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define Vec(T) struct {size_t element_size; size_t size; size_t buffer_size; T* buffer;}

#define Vec_insert(vec, pos, val) Vec_make_space(vec, pos, 1), (vec)->buffer[pos] = val
#define Vec_push(vec, val) Vec_insert(vec, 0, val)
#define Vec_push_back(vec, ...) Vec_make_space(vec, (vec)->size, 1), (vec)->buffer[(vec)->size - 1] = __VA_ARGS__
#define Vec_pop(vec) Vec_remove(vec, 0, 1)
#define Vec_pop_back(vec) Vec_remove(vec, (vec)->size - 1, 1)

void* Vec_ctor(void* vec, size_t element_size, size_t elements);
void* Vec_copy(void* vec, void* dest);
void Vec_make_space(void* vec, size_t pos, size_t elements);
void Vec_remove(void* vec, size_t pos, size_t elements);
void Vec_set(void* vec, void* data, size_t elements);
void Vec_append(void* vec, void* data, size_t elements);
void Vec_prepend(void* vec, void* data, size_t elements);
void Vec_dtor(void* vec);

#endif

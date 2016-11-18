#ifndef ARR_H
#define ARR_H

#include <assert.h>
#include <stddef.h>

#define Arr_insert(arr, pos, val) \
	({ \
	 	size_t _pos = pos; \
		arr = Arr_make_space(arr, _pos); \
		arr[_pos] = val; \
	 })
#define Arr_push(arr, val) Arr_insert(arr, 0, val)
#define Arr_pop(arr) \
	({ \
	 	assert(arr); \
	 	__auto_type _val = *arr; \
	 	_val = arr[0]; \
		Arr_remove(arr, 0); \
		_val; \
	 })
#define Vec(T, n) Arr_new(n, sizeof(T), 1)
#define Arr(...) \
	({ \
	 	void* _arr = Arr_new(sizeof(__VA_ARGS__) / sizeof(__VA_ARGS__[0]), sizeof(__VA_ARGS__[0]), 0);\
		Arr_set(_arr, __VA_ARGS__);\
	 	_arr; \
	 })

void* Arr_new(size_t elements, size_t element_size, _Bool is_dynamic);
size_t Arr_len(void* array);
void* Arr_make_space(void* array, size_t pos);
void Arr_remove(void* array, size_t pos);
void Arr_set(void* array, void* literal);
void Arr_delete(void* array_ptr);

#endif

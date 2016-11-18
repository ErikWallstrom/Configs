#ifndef BASE_H
#define BASE_H

#include <stdlib.h>
#include <stdio.h>
#include "Str.h"
#include "Arr.h"

#define debug(msg) \
	do { \
		printf("Error: \"%s\", in %s at [%i] %s\n", msg, __FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)
#define DEBUG_ALLOC_FAILURE "Memory allocation failed"

#define gc(T) T __attribute__((__cleanup__(T##_delete)))
#define typeof __typeof__
#define auto __auto_type
#define range(i, v) typeof(v) i = 0; i < v; i++
#define new(T) \
	_Generic((T), \
	char*: ({ \
			auto _val = T; \
			String_new(*(char**)(void*)&_val); \
		}), \
	default: ({ \
			auto _val = T;\
			auto _ptr = &_val;\
			_ptr = malloc(sizeof(_val));\
			if(!_ptr) \
			  debug("Memory allocation failed");\
			*_ptr = _val;\
			_ptr; \
		})\
	)

#define for_each(array, i) \
	for(range(i, Array_len(array)))
#define push(a, v) Array_insert(&a, 0, v)
#define pop(a) \
	({ \
	 	auto _ptr = &a; \
	 	void* _val = (*_ptr)[0]; \
		Array_remove(_ptr, 0); \
	 	_val; \
	 })
#define dynamic(v) \
	({ \
	 	auto _arr = Array_new(); \
	 	auto _s_arr = v; \
		size_t _len = sizeof(v) / sizeof(*_s_arr); \
	 	for(size_t _i = 0; _i < _len; _i++) \
		{ \
			 push(_arr, new(_s_arr[_i])); \
		} \
		_arr; \
	 })

#endif

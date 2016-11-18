#include "Str.h"
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define Str_error(msg) \
	do { \
		printf("Error: \"%s\", in %s at [%i] %s\n", msg, __FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)
#define Str_ALLOC_FAILED "Memory allocation failed"

struct Str
{
	_Bool is_dynamic;
	size_t len;
	size_t data_size;
	char data[];
};

char* Str_new(const char* const str, _Bool is_dynamic)
{
	assert(str);
	size_t str_len = strlen(str);
	struct Str* self;
	if(is_dynamic)
	{
		size_t data_size = str_len * 2 + 1;
		self = malloc(sizeof(struct Str) + data_size);
		if(!self)
			Str_error(Str_ALLOC_FAILED);
		*self = (struct Str){
			.is_dynamic = 1,
			.len = str_len,
			.data_size = data_size
		};
	}
	else
	{
		self = malloc(sizeof(struct Str) + str_len + 1);
		if(!self)
			Str_error(Str_ALLOC_FAILED);
		*self = (struct Str){
			.is_dynamic = 0,
			.len = str_len,
			.data_size = str_len + 1
		};
	}

	memcpy(self->data, str, str_len + 1);
	return self->data;
}

size_t Str_len(const char* string)
{
	assert(string);
	struct Str* self = (struct Str*)(string - sizeof(struct Str));
	return self->len;
}

void Str_set(char** string, const char* const data)
{
	assert(string && *string && data);
	struct Str* self = (struct Str*)(*string - sizeof(struct Str));
	assert(self->is_dynamic);
	size_t data_len = strlen(data);
	if(data_len + 1 > self->data_size)
	{
		self->data_size = data_len * 2 + 1;
		self->len = data_len;
		self = realloc(self, sizeof(struct Str) + self->data_size);
		if(!self)
			Str_error(Str_ALLOC_FAILED);
	}

	*string = self->data;
	memcpy(self->data, data, data_len + 1);
}

void Str_append(char** string, const char* const data)
{
	assert(string && *string && data);
	struct Str* self = (struct Str*)(*string - sizeof(struct Str));
	assert(self->is_dynamic);
	size_t data_len = strlen(data);
	if(self->len + data_len + 1 > self->data_size)
	{
		self->data_size = (self->len + data_len) * 2 + 1;
		self = realloc(self, sizeof(struct Str) + self->data_size);
		if(!self)
			Str_error(Str_ALLOC_FAILED);
		*string = self->data;
	}

	memcpy(self->data + self->len, data, data_len + 1); 
	self->len += data_len;
} 

void Str_prepend(char** string, const char* const data)
{
	assert(string && *string && data);
	struct Str* self = (struct Str*)(*string - sizeof(struct Str));
	assert(self->is_dynamic);
	size_t data_len = strlen(data);

	if(self->len + data_len + 1 > self->data_size)
	{
		self->data_size = (self->len + data_len) * 2 + 1;
		struct Str* new_self = malloc(sizeof(struct Str) + self->data_size);
		if(!new_self)
			Str_error(Str_ALLOC_FAILED);
		*new_self = (struct Str){
			.is_dynamic = 1,
			.len = data_len + self->len,
			.data_size = self->data_size
		};

		puts("Alloc");
		memcpy(new_self->data + data_len, self->data, self->len + 1);
		memcpy(new_self->data, data, data_len);
		free(self);
		*string = new_self->data;
	}
	else
	{
		memmove(self->data + data_len, self->data, self->len + 1);
		memcpy(self->data, data, data_len);
		self->len += data_len;
	}
}

void Str_format(char** string, const char* const fmt, ...)
{
	assert(string && *string && fmt);
	va_list list_1, list_2;
	va_start(list_1, fmt);
	va_copy(list_2, list_1);

	int fmt_len = vsnprintf(NULL, 0, fmt, list_1) - 1;
	struct Str* self = (struct Str*)(*string - sizeof(struct Str));
	assert(self->is_dynamic);
	self->len = fmt_len;

	if((size_t)fmt_len + 1 > self->data_size)
	{
		self->data_size = fmt_len * 2 + 1;
		struct Str* new_self = malloc(sizeof(struct Str) + self->data_size);
		if(!new_self)
			Str_error(Str_ALLOC_FAILED);
		*new_self = (struct Str){
			.is_dynamic = 1,
			.len = self->len,
			.data_size = self->data_size
		};
		free(self);
		self = new_self;
	}

	vsprintf(self->data, fmt, list_2);
	va_end(list_2);
	va_end(list_1);
	*string = self->data;
}

void Str_lower(char* string)
{
	assert(string && *string);
	struct Str* self = (struct Str*)(string - sizeof(struct Str));
	for(size_t i = 0; i < self->len + 1; i++)
		self->data[i] = tolower(self->data[i]);
}

void Str_upper(char* string)
{
	assert(string);
	struct Str* self = (struct Str*)(string - sizeof(struct Str));
	for(size_t i = 0; i < self->len + 1; i++)
		self->data[i] = toupper(self->data[i]);
}

size_t Str_chars(const char* string, char ch)
{
	assert(string);
	struct Str* self = (struct Str*)(string - sizeof(struct Str));
	size_t num = 0;
	for(size_t i = 0; i < self->len + 1; i++)
		if(self->data[i] == ch)
			num++;
	return num;
}

void Str_insert(char** string, size_t pos, char ch)
{
	assert(string && *string);
	struct Str* self = (struct Str*)(*string - sizeof(struct Str));
	assert(self->is_dynamic && pos <= self->len);
	if(self->len + 2 > self->data_size)
	{
		self->data_size = self->data_size * 2 + 1;
		self = realloc(self, sizeof(struct Str) + self->data_size);
		if(!self)
			Str_error(Str_ALLOC_FAILED);
	}

	self->len++;
	memmove(self->data + pos + 1, self->data + pos, self->len - pos);
	self->data[pos] = ch;
	*string = self->data;
}

void Str_delete(char** string)
{
	assert(string && *string);
	free(*string - sizeof(struct Str));
	*string = NULL;
}


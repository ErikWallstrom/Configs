#ifndef STR_H
#define STR_H

#include <stddef.h>

typedef char* Str;

char* Str_new(const char* const data, _Bool is_dynamic);
size_t Str_len(const char* string);
size_t Str_chars(const char* string, char ch);
void Str_lower(char* string);
void Str_upper(char* string);

void Str_set(char** string, const char* const data);
void Str_append(char** string, const char* const data);
void Str_prepend(char** string, const char* const data);
void Str_format(char** string, const char* const fmt, ...);
void Str_insert(char** string, size_t pos, char ch);
void Str_delete(char** string);

#endif


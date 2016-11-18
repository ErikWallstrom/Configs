#ifndef VEC_2F_H
#define VEC_2F_H

typedef struct Vec_2f Vec_2f;
struct Vec_2f
{
	float x, y;
};

struct Vec_2f* Vec_2f_ctor(struct Vec_2f* self, float x, float y);
void Vec_2f_add(struct Vec_2f* self, struct Vec_2f* vector, struct Vec_2f* dest);
void Vec_2f_sub(struct Vec_2f* self, struct Vec_2f* vector, struct Vec_2f* dest);
void Vec_2f_mul(struct Vec_2f* self, float times, struct Vec_2f* dest);
void Vec_2f_normalize(struct Vec_2f* self, struct Vec_2f* dest);
float Vec_2f_len(struct Vec_2f* self);
int Vec_2f_equal(struct Vec_2f* self, struct Vec_2f* vector);
void Vec_2f_print(struct Vec_2f* self);

#endif

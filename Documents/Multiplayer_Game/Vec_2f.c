#include "Vec_2f.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

struct Vec_2f* Vec_2f_ctor(struct Vec_2f* self, float x, float y)
{
	assert(self);
	self->x = x;
	self->y = y;
	return self;
}

void Vec_2f_add(struct Vec_2f* self, struct Vec_2f* vector, struct Vec_2f* dest)
{
	assert(self);
	assert(vector);
	assert(dest);

	dest->x = self->x + vector->x;
	dest->y = self->y + vector->y;
}

void Vec_2f_sub(struct Vec_2f* self, struct Vec_2f* vector, struct Vec_2f* dest)
{
	assert(self);
	assert(vector);
	assert(dest);

	dest->x = self->x - vector->x;
	dest->y = self->y - vector->y;
}

void Vec_2f_mul(struct Vec_2f* self, float times, struct Vec_2f* dest)
{
	assert(self);
	assert(dest);
	
	dest->x = self->x * times;
	dest->y = self->y * times;
}

void Vec_2f_normalize(struct Vec_2f* self, struct Vec_2f* dest)
{
	assert(self);
	assert(dest);

	if(!Vec_2f_len(self))
	{
		dest->x = 0;
		dest->y = 0;
	}
	else
	{
		dest->x = self->x / Vec_2f_len(self);
		dest->y = self->y / Vec_2f_len(self);
	}
}

float Vec_2f_len(struct Vec_2f* self)
{
	assert(self);
	return sqrtf(powf(self->x, 2) + powf(self->y, 2));
}

int Vec_2f_equal(struct Vec_2f* self, struct Vec_2f* vector)
{
	assert(self);
	assert(vector);

	if(self->x == vector->x && self->y == vector->y)
		return 1;
	return 0;
}

void Vec_2f_print(struct Vec_2f* self)
{
	assert(self);
	printf("[Vec_2f] {x: %g}, {y: %g}\n", self->x, self->y);
}

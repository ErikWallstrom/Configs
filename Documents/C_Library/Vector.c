#include "Vector.h"
#include <math.h>
#include <assert.h>

struct Vector Vector_add(Vector self, Vector vector)
{
	assert(self && vector);
	return (struct Vector){
		self->x + vector->x,
		self->y + vector->y
	};
}
struct Vector Vector_sub(Vector self, Vector vector)
{
	assert(self && vector);
	return (struct Vector){
		self->x - vector->x,
		self->y - vector->y
	};
}

struct Vector Vector_mul(Vector self, double times)
{
	assert(self);
	return (struct Vector){
		self->x * times,
		self->y * times
	};
}

struct Vector Vector_normalize(Vector self)
{
	assert(self);
	if(!Vector_len(self))
		return (struct Vector){
			0, 0
		};
	return (struct Vector){
		self->x / Vector_len(self),
		self->y / Vector_len(self)
	};
}

double Vector_len(Vector self)
{
	return sqrt(pow(self->x, 2) + pow(self->y, 2));
}

int Vector_equal(Vector self, Vector vector)
{
	assert(self && vector);
	if(self->x == vector->x && self->y == vector->y)
		return 1;
	return 0;
}

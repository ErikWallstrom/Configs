#include "Point.h"
#include <stdio.h>
#include <assert.h>

void Point_print(struct Point* self)
{
	assert(self);
	printf("[Point] {x: %i}, {y: %i}\n", self->x, self->y);
}


#include "Point.h"
#include <stdio.h>
#include <assert.h>

void Point_print(struct Point* self)
{
	assert(self);
	printf("[Point] {x: %" PRIiFAST32 "}, {y: %" PRIiFAST32 "}\n", self->x, self->y);
}


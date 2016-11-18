#ifndef POINT_H
#define POINT_H

#include <inttypes.h>

typedef struct Point Point;
struct Point
{
	int32_t x, y;
};

void Point_print(struct Point* self);

#endif

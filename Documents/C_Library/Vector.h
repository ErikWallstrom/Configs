#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector* Vector;
struct Vector
{
	float x, y;
};

struct Vector Vector_add(Vector self, Vector vector);
struct Vector Vector_sub(Vector self, Vector vector);
struct Vector Vector_mul(Vector self, double times);
struct Vector Vector_normalize(Vector self);
double Vector_len(Vector self);
int Vector_equal(Vector self, Vector vector);

#endif

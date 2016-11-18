#include "Base.h"

int main(void)
{
	double* numbers = Arr((double[]){3.14, 33.5, 28.2});
	for(range(i, Arr_len(numbers)))
		printf("%f\n", numbers[i]);
	
	Arr_delete(&numbers);
}

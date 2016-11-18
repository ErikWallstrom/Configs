#include <cstdio>
#include <vector>

#define range(i, v) __typeof__(v) i = 0; i < v; i++

int main()
{
	std::vector<int> vec;

	for(range(i, 50000))
		vec.insert(vec.begin(), i);

	for(range(i, vec.size()))
		printf("%i\n", vec[i]);
}

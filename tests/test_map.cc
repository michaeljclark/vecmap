#include <cstdio>
#include <cassert>

#include "vecmap.h"

void test_map()
{
	vecmap<int,int> m;

	m[6]++;
	m[4]++;
	m[6]++;

	assert(m[4] == 1);
	assert(m[6] == 2);

	for (auto e : m) {
		printf("%d: %d\n", e.first, e.second);
	}
}

int main(int argc, char **argv)
{
	test_map();
}
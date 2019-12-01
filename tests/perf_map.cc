#include <cstdio>
#include <chrono>

#include <map>
#include "vecmap.h"

using namespace std::chrono;

template <typename Map>
void bench(Map &map, size_t count, size_t spread)
{
	for (size_t i = 0; i < count; i++) {
		map[i&spread]++;
	}
}

template <typename Map>
void bench(const char *name, size_t count, size_t spread)
{
	Map map;
	bench(map,count,spread);
}

int main(int argc, char **argv)
{
#if STDMAP
	bench<std::map<size_t,size_t>>("std::map",10000000,16383);
#endif
#if VECMAP
	bench<vecmap<size_t,size_t>>("vecmap",10000000,16383);
#endif
}
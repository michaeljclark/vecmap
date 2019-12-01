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
	auto t1 = system_clock::now();
	bench(map,count,spread);
	auto t2 = system_clock::now();
	printf("|%-10s|%8zu|%12zu|%8.1f|\n", name, spread, count,
		duration_cast<nanoseconds>(t2-t1).count()/(float)count);
}

void heading()
{
	printf("|%-10s|%8s|%12s|%8s|\n",
		"container", "spread", "count", "time_ns");
	printf("|%-10s|%8s|%12s|%8s|\n",
		":--------", "-----:", "----:", "------:");
}

int main(int argc, char **argv)
{
	heading();
	bench<std::map<size_t,size_t>>("std::map",10000000,255);
	bench<std::map<size_t,size_t>>("std::map",10000000,1023);
	bench<std::map<size_t,size_t>>("std::map",10000000,16383);
	bench<vecmap<size_t,size_t>>("vecmap",10000000,255);
	bench<vecmap<size_t,size_t>>("vecmap",10000000,1023);
	bench<vecmap<size_t,size_t>>("vecmap",10000000,16383);
}
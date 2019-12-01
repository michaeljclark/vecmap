#include <cstdio>
#include <chrono>

#include <map>
#include "vecmap.h"

using namespace std::chrono;

template <typename Map>
void bench(const char *name, size_t limit, size_t spread)
{
	Map map;

	auto t1 = system_clock::now();
	for (size_t i = 0; i < limit; i++) {
		map[i&spread]++;
	}
	auto t2 = system_clock::now();

	printf("|%-10s|%8zu|%12zu|%12zu|\n", name, spread, limit,
		duration_cast<microseconds>(t2-t1).count());
}

void heading()
{
	printf("|%-10s|%8s|%12s|%12s|\n",
		"container", "spread", "limit", "time_us");
	printf("|%-10s|%8s|%12s|%12s|\n",
		":--------", "-----:", "----:", "------:");
}

int main(int argc, char **argv)
{
	heading();
	bench<vecmap<size_t,size_t>>("vecmap",10000000,255);
	bench<vecmap<size_t,size_t>>("vecmap",10000000,1023);
	bench<vecmap<size_t,size_t>>("vecmap",10000000,16383);
	bench<std::map<size_t,size_t>>("std::map",10000000,255);
	bench<std::map<size_t,size_t>>("std::map",10000000,1023);
	bench<std::map<size_t,size_t>>("std::map",10000000,16383);
}
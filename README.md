# vecmap

Fast C++ map using `lower_bound` and `vector<pair<Key,T>>`.

### Overview

Nowadays, small maps are invariably much faster using binary search
lookup and insertion into linear memory using `std::vector` compared
to the pointer chasing red-black tree implementation in `std::map`.

These small maps are useful for histograms and other frequently
accessed data structures where performance is critical.

### Benchmarks

The following benchmarks were performed on an Intel Core i9-7980XE
using GCC 9.2:

|container |  spread|       count| time_ns|
|:-------- |  -----:|       ----:| ------:|
|std::map  |     255|    10000000|    10.4|
|std::map  |    1023|    10000000|    30.9|
|std::map  |   16383|    10000000|    52.7|
|vecmap    |     255|    10000000|     8.7|
|vecmap    |    1023|    10000000|    29.1|
|vecmap    |   16383|    10000000|    31.0|

### Analysis

The speed gains are mostly due to the performance of modern caches,
specifically the asymmetry between time required for cached vs uncached
memory accesses. An algorithm that minimizes the _total memory span_ will
often perform much beter than one that minimizes _total memory accesses_.

This is because it is not the total number of accesses that count,
rather the total number of uncached accesses, and that can be minimized
by minimizing the total span of memory used by the data structure.

The cost of duplicate accesses during insert with `std::vector` is lowerer
than the cost of pointer chasing in `std::map`.
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
specifically the asymmetry between cached and uncached memory accesses.

An algorithm that minimizes the _total memory span_ will often perform
much beter than one that minimizes _total memory accesses_ . Modern
processors can serve memory from cache very quickly. The key to good
performance is eliminating costly pointer-chasing, which in addition
to increasing the memory footprint, introduces memory access dependencies.

Statistics using the `perf` tool on an Intel Core i9-7980XE:

- `vecmap` has more instructions
- `vecmap` has less cpu cycles
- `vecmap` loads are almost all L1 hits
- `std::map` spends a lot of time stalled
- `std::map` has many L1 cache misses
- `std::map` has more memory accesses

The number of stores is approximately the same for both algorithms.

#### performance counter stats for `perf_vecmap`:
```
     1,532,627,400      cpu-cycles                                                    (14.41%)
     1,716,330,918      instructions              #    1.12  insn per cycle           (18.94%)
       358,278,447      branches                                                      (20.08%)
        34,025,896      branch-misses             #    9.50% of all branches          (21.21%)
           158,165      cache-references                                              (22.34%)
             1,381      cache-misses              #    0.873 % of all cache refs      (22.66%)
       167,196,790      L1-dcache-loads                                               (18.13%)
         3,230,582      L1-dcache-load-misses     #    1.93% of all L1-dcache hits    (18.12%)
        10,450,952      L1-dcache-stores                                              (18.12%)
       176,426,052      mem_inst_retired.all_loads                                    (18.12%)
        10,486,445      mem_inst_retired.all_stores                                   (18.12%)
       175,575,277      mem_load_retired.l1_hit                                       (18.13%)
         1,504,878      mem_load_retired.l1_miss                                      (18.13%)
         1,496,781      mem_load_retired.l2_hit                                       (18.13%)
               971      mem_load_retired.l2_miss                                      (18.13%)
               789      mem_load_retired.l3_hit                                       (18.13%)
             2,753      mem_load_retired.l3_miss                                      (17.62%)
        22,514,617      cycle_activity.cycles_l1d_miss                                (16.49%)
         1,421,809      cycle_activity.cycles_l2_miss                                 (15.35%)
     1,042,095,220      cycle_activity.cycles_mem_any                                 (14.22%)
         8,189,181      cycle_activity.stalls_l1d_miss                                (13.59%)
            94,132      cycle_activity.stalls_l2_miss                                 (13.59%)
       134,967,971      cycle_activity.stalls_mem_any                                 (13.59%)
       605,353,494      cycle_activity.stalls_total                                   (13.59%)

       0.353564463 seconds time elapsed
```

#### performance counter stats for `perf_stdmap`:
```
     2,508,522,757      cpu-cycles                                                    (15.84%)
       947,927,686      instructions              #    0.38  insn per cycle           (20.05%)
       320,784,570      branches                                                      (20.05%)
        38,948,370      branch-misses             #   12.14% of all branches          (20.17%)
         3,709,964      cache-references                                              (20.88%)
            16,492      cache-misses              #    0.445 % of all cache refs      (21.04%)
       329,078,790      L1-dcache-loads                                               (16.83%)
        52,898,721      L1-dcache-load-misses     #   16.07% of all L1-dcache hits    (16.83%)
        10,513,256      L1-dcache-stores                                              (16.83%)
       341,509,608      mem_inst_retired.all_loads                                    (16.83%)
        10,496,537      mem_inst_retired.all_stores                                   (16.83%)
       257,329,402      mem_load_retired.l1_hit                                       (16.83%)
        42,896,437      mem_load_retired.l1_miss                                      (16.83%)
        41,955,672      mem_load_retired.l2_hit                                       (16.83%)
           579,285      mem_load_retired.l2_miss                                      (16.83%)
           567,335      mem_load_retired.l3_hit                                       (16.83%)
                95      mem_load_retired.l3_miss                                      (16.83%)
       499,828,315      cycle_activity.cycles_l1d_miss                                (16.83%)
        64,315,858      cycle_activity.cycles_l2_miss                                 (16.83%)
     2,101,952,506      cycle_activity.cycles_mem_any                                 (16.83%)
       437,286,870      cycle_activity.stalls_l1d_miss                                (16.83%)
        55,752,570      cycle_activity.stalls_l2_miss                                 (16.83%)
     1,586,344,093      cycle_activity.stalls_mem_any                                 (16.70%)
     2,024,648,237      cycle_activity.stalls_total                                   (16.00%)

       0.570764623 seconds time elapsed
```
#!/bin/bash

METRICS="cpu-cycles,instructions,branches,branch-misses,
cache-references,cache-misses,
L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,
mem_inst_retired.all_loads,mem_inst_retired.all_stores,
mem_load_retired.l1_hit,mem_load_retired.l1_miss,
mem_load_retired.l2_hit,mem_load_retired.l2_miss,
mem_load_retired.l3_hit,mem_load_retired.l3_miss,
cycle_activity.cycles_l1d_miss,
cycle_activity.cycles_l2_miss,
cycle_activity.cycles_mem_any,
cycle_activity.stalls_l1d_miss,
cycle_activity.stalls_l2_miss,
cycle_activity.stalls_mem_any,
cycle_activity.stalls_total"

echo vecmap
perf stat -e ${METRICS//[[:space:]]/} ./build/perf_vecmap
echo stdmap
perf stat -e ${METRICS//[[:space:]]/} ./build/perf_stdmap

#!/bin/bash
#command to compile parallel_bfs program.
export PATH=/opt/gcc-10.2.0/bin:$PATH
export LD_LIBRARY_PATH=/opt/gcc-10.20/lib64:$LD_LIBRARY_PATH
g++ PARALLEL_BFS.cpp -o BitByBit
exit 0

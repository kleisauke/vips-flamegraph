# libvips flame graphs

A collection of flame graphs used to identify the most frequent code-paths in libvips.

## Build
```bash
# Compile libvips with
CFLAGS="-O2 -g1" CXXFLAGS="-O2 -g1" meson setup build --prefix=/usr --default-library=shared --buildtype=release \
  -Ddeprecated=false -Dintrospection=false
ninja -C build
sudo ninja -C build install

# Compile bench program with
g++ -O2 -g1 `pkg-config vips-cpp --cflags --libs` -o bench.out copy-bench.cpp

# Timings
/usr/bin/time -f %M:%e vips copy images/x.jpg output/x2.png
```

## Capture stacks
```bash
perf record --call-graph=dwarf ./bench.out images/x.jpg output/x2.png
```

## Create flame graph
```bash
perf script | 
  ./FlameGraph/stackcollapse-perf.pl | 
  ./FlameGraph/flamegraph.pl --title="On-CPU Flame Graph for libvips" > output/bench.svg
```

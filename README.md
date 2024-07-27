# libvips flame graphs

A collection of flame graphs used to identify the most frequent code-paths in libvips.

## Build

```bash
# Compile libvips with
meson setup build --prefix=/usr -Dexamples=false -Ddeprecated=false \
  -Dintrospection=disabled -Dc_args=-g1 -Dcpp_args=-g1
meson compile -C build
sudo meson install -C build

# Compile bench program with
g++ -O2 -g1 `pkg-config vips-cpp --cflags --libs` -o bench.out bench.cpp

# Timings
/usr/bin/time -f %M:%e vips copy images/x.jpg output/x2.jpg --vips-concurrency=1
```

## Capture stacks

```bash
VIPS_CONCURRENCY=1 perf record --call-graph=dwarf ./bench.out images/x.jpg output/x2.jpg
```

## Create flame graph

```bash
perf script | 
  ./FlameGraph/stackcollapse-perf.pl | 
  ./FlameGraph/flamegraph.pl --title="On-CPU Flame Graph for libvips" > output/bench.svg
```

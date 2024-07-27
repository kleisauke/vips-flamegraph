# Image provenance
`sample2.v`:
```
https://github.com/libvips/vips-bench/blob/master/sample2.v
```

`x.jpg`:
```bash
vips colourspace sample2.v t1.v srgb
vips replicate t1.v t2.v 40 30
vips extract_area t2.v x.jpg[strip] 0 0 10000 10000
rm t{1,2}.v
```

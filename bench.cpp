#include <vips/vips8>

using namespace vips;

int main(int argc, char **argv) {
  if (VIPS_INIT(argv[0]))
    vips_error_exit(nullptr);

  if (argc != 3)
    vips_error_exit("usage: %s input-file output-file", argv[0]);

  VImage in = VImage::new_from_file(
          argv[1], VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));

  VImage mask = VImage::new_matrixv(3, 3,
                                    -1.0, -1.0, -1.0,
                                    -1.0, 16.0, -1.0,
                                    -1.0, -1.0, -1.0);
  mask.set("scale", 8);

  in.extract_area(100, 100, in.width() - 200, in.height() - 200)
    .reduce(1.0 / 0.9, 1.0 / 0.9,
            VImage::option()->set("kernel", VIPS_KERNEL_LINEAR))
    .conv(mask, VImage::option()->set("precision", VIPS_PRECISION_INTEGER))
    .write_to_file(argv[2]);

  vips_shutdown();

  return 0;
}

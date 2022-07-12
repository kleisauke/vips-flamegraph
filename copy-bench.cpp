#include <vips/vips8>

using namespace vips;

int main(int argc, char **argv) {
  if (VIPS_INIT(argv[0]))
    vips_error_exit(nullptr);

  if (argc != 3)
    vips_error_exit("usage: %s input-file output-file", argv[0]);

  VImage in = VImage::new_from_file(
          argv[1], VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));
  in.write_to_file(argv[2]);

  vips_shutdown();

  return 0;
}

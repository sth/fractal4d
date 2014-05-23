
#include "gd.hpp"
#include <cstdio>

namespace gd {

image::image(int sx, int sy) : handle(nullptr) {
	handle = gdImageCreateTrueColor(sx, sy);
}

image::~image() {
	if (handle) {
		gdImageDestroy(handle);
	}
}

void image::setPixel(int x, int y, int color) {
	gdImageSetPixel(handle, x, y, color);
}

void image::writePng(const char *filename, int level) {
	FILE *file = std::fopen(filename, "w");
	if (file) {
		gdImagePngEx(handle, file, level);
		std::fclose(file);
	}
}

} // namespace gd


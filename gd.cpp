
#include "gd.hpp"
#include <stdexcept>
#include <cstdio>
#include <cerrno>
#include <cstring>

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
	FILE *file = std::fopen(filename, "wb");
	if (file) {
		gdImagePngEx(handle, file, level);
		std::fclose(file);
	}
	else {
		throw std::runtime_error(std::strerror(errno));
	}
}

} // namespace gd


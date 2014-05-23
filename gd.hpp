
#include <string>
#include <gd.h>

namespace gd {

class image {
	gdImage *handle;

public:
	image(int xs, int sy);
	~image();

	void setPixel(int x, int y, int color);

	void writePng(const char *filename, int level=-1);
	void writePng(const std::string &filename, int level=-1) { writePng(filename.c_str(), level); }

	int sx() const;
	int sy() const;
};

inline int image::sx() const {
	return gdImageSX(handle);
}
inline int image::sy() const {
	return gdImageSY(handle);
}

static inline int trueColor(int red, int green, int blue) {
	return gdTrueColor(red, green, blue);
}

} // namespace gd


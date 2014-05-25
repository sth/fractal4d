
#if !defined(GD_HPP_INCLUDED)
#define GD_HPP_INCLUDED

#include <string>
#include <gd.h>

// Minimal C++ wrapper for libgd images with just the functionality we use

namespace gd {

class image {
	gdImage *handle;

public:
	image(int xs, int sy);
	~image();

	void setPixel(int x, int y, int color);

	void writePng(const char *filename, int level=-1);
	void writePng(const std::string &filename, int level=-1);

	int sx() const;
	int sy() const;
};


/* Some function definitions that might be inlined/... */

inline void image::writePng(const std::string &filename, int level) {
	writePng(filename.c_str(), level);
}

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

#endif // GD_HPP_INCLUDED


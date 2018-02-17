
#include "area.hpp"
#include "generator.hpp"
#include "gd.hpp"

/* Some interesting planes */

// The plane corresponding to the mandelbrot set
plane4d mandelbrot_plane() {
	vec4d origin(0, 0, 0, 0);
	vec4d xside(1, 0, 0, 0);
	vec4d yside(0, 1, 0, 0);
	return plane4d(origin, xside, yside);
}

// The plane corresponding to the julia set for a constant `c`
plane4d julia_plane(std::complex<double> c) {
	vec4d origin(c.real(), c.imag(), 0, 0);
	vec4d xside(0, 0, 1, 0);
	vec4d yside(0, 0, 0, 1);
	return plane4d(origin, xside, yside);
}


/* Rendering to a png file with libgd */

// Mapping iterations to libgd colors
int colorize(int it) {
	if (it < 0)
		return gd::trueColor(0, 0, 0);
	else
		return gd::trueColor(it*2, it*2, 0);
}

// Render a fractal to a png file
void render_png(const fractal_generator &gen, const pixel_area &area, const std::string &filename) {
	gd::image img(area.xpixels, area.ypixels);
	// Call the generator. The callback is invoked once for every pixel
	gen.fill(area, [&img](int x, int y, int it) {
		img.setPixel(x, y, colorize(it));
	});
	img.writePng(filename);
}


int main() {
	// The plane in which we want to render something.
	// In this case the julia set for 0.282 + 0.01i
	plane4d plane = julia_plane({0.282, 0.01});

	// The coordinates on the plane we are interested in.
	// In this case from the x-coordinate 4 units centered around -0.5
	// (-2.5 to 1.5) and for the y-coordinate the area around 0, depending on
	// image height.
	coord_area coords(plane, -0.5, 0, 4);

	// Map the coordinates to pixels.
	// In this case image size 800x600
	pixel_area pixels(coords, 800, 600);

	// The fractal generator.
	// Limit iterations to max 250
	fractal_generator gen(250);

	// Render a png image using this data
	render_png(gen, pixels, "fractal.png");
}


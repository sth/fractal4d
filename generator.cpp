
#include <complex>
#include "gd.hpp"
#include "algebra.hpp"

// For image drawing purposes this defines an area of coordinates that
// should be drawn.
// It is specified by x. and y-coordinates of a point and the width of the area
// in x direction. The width in y direction is chooses later according to the
// image dimensions.
struct coord_area {
	plane4d plane;

	double xcenter;
	double ycenter;
	double xside;

	coord_area(const plane4d &plane_arg, double xcenter_arg, double ycenter_arg, double xside_arg)
			: plane(plane_arg), xcenter(xcenter_arg), ycenter(ycenter_arg), xside(xside_arg) {
	}

	static coord_area from_corners(const plane4d &plane, double xtopleft, double ytopleft, double xbottomright, double ybottomright);
};

coord_area coord_area::from_corners(const plane4d &plane, double xtopleft, double ytopleft, double xbottomright, double ybottomright) {
	return coord_area(
			plane,
			(xtopleft+xbottomright)/2,
			(ytopleft-ybottomright)/2,
			(xbottomright-xtopleft)
		);
}


// An mapping between an area on a plane and pixels of an image
class pixel_area {
	plane4d plane;

public:
	int xpixels;
	int ypixels;

private:
	double pixelsize;
	double xorigin;
	double yorigin;

public:
	pixel_area(const coord_area &coords, int xpixels_arg, int ypixels_arg)
			: plane(coords.plane), xpixels(xpixels_arg), ypixels(ypixels_arg),
			  pixelsize(coords.xside/xpixels),
			  xorigin(coords.xcenter - (xpixels/2) * pixelsize),
			  yorigin(coords.ycenter - (ypixels/2) * pixelsize) {
	}

	// Get the point corresponding to a pixel
	vec4d at(int x, int y) const {
		return plane.at(xorigin + x * pixelsize, yorigin + y * pixelsize);
	}
};


// A fractal image generator for a certain plane.
class fractal_gen {
	int maxiter;

public:
	fractal_gen(int maxiter_arg)
			: maxiter(maxiter_arg) {
	}

private:
	// One iteration step for the fractal generation.
	// If you loke to generate a fractal for a different generation rule
	// like z^3 + c, change it here.
	std::complex<double> iter_step(std::complex<double> z, std::complex<double> c) const {
		return z*z + c;
	}

	// Generic function to determine the number of iterations till divergence
	// Returns -1 if not found to be diverging.
	int count_iterations(const vec4d &spec) const {
		// From out 4d starting vector 
		const std::complex<double> c(spec.coords[0], spec.coords[1]);
		std::complex<double> z(spec.coords[2], spec.coords[3]); 

		int it;
		for (it = 0; it < maxiter; ++it) {
			if (abs(z) > 2)
				return it;
			z = iter_step(z, c);
		}
		return -1;
	}

public:
	// The rendering function.
	// Takes a pixel area and an output function that gets called for
	// each pixel with (x, y, number_of_iterations)
	template<typename Output>
	void fill(const pixel_area &pixels, Output output) const {
		for (int x = 0; x < pixels.xpixels; ++x) {
			for (int y = 0; y < pixels.ypixels; ++y) {
				int it = count_iterations(pixels.at(x, y));
				output(x, y, it);
			}
		}
	}
};

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


// Get a color from the number of iterations
int colorize(int it) {
	if (it < 0)
		return gd::trueColor(0, 0, 0);
	else
		return gd::trueColor(it*2, it*2, 0);
}

void render_png(const fractal_gen &gen, const pixel_area &area, const std::string &filename) {
	gd::image img(area.xpixels, area.ypixels);
	gen.fill(area, [&img](int x, int y, int it) {
		img.setPixel(x, y, colorize(it));
	});
	img.writePng(filename);
}

int main() {
	// auch mandelbrot?
	//vec4d origin(-1, -1, 1, 1);
	//vec4d xside(2, 0, -2, 0);
	//vec4d yside(0, 2, 0, -2);

	//vec4d origin(-1, -1, 0.9, 0.9);
	//vec4d xside(2, 0, -1.8, 0);
	//vec4d yside(0, 2, 0, -1.8);

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
	// Limit iterations to max 350
	fractal_gen gen(250);

	// Render a png image using this data
	render_png(gen, pixels, "fractal.png");
}



#include <complex>
#include "gd.hpp"
#include "algebra.hpp"

// For image drawing purposes this defines an area of coordinates that
// should be drawn.
// It is specified by x. and y-coordinates of a point and the width of the area
// in x direction. The width in y direction is chooses later according to the
// image dimensions.
struct area_spec {
	double xcenter;
	double ycenter;
	double xside;

	static area_spec from_center(double xcenter, double ycenter, double xside);
	static area_spec from_corners(double xtopleft, double ytopleft, double xbottomright, double ybottomright);
};

area_spec area_spec::from_center(double xcenter, double ycenter, double xside) {
	return area_spec{xcenter, ycenter, xside};
}

area_spec area_spec::from_corners(double xtopleft, double ytopleft, double xbottomright, double ybottomright) {
	return area_spec{
			(xtopleft+xbottomright)/2,
			(ytopleft-ybottomright)/2,
			(xbottomright-xtopleft)
		};
}

// An mapping between an area of a plane and pixels of an image
class discrete_view {
	plane4d plane;

	double pixelsize;
	double xorigin;
	double yorigin;

public:
	discrete_view(const plane4d &plane_arg, const area_spec &area, int xpixels, int ypixels)
			: plane(plane_arg),
			  pixelsize(area.xside/xpixels),
			  xorigin(area.xcenter - (xpixels/2) * pixelsize),
			  yorigin(area.ycenter - (ypixels/2) * pixelsize) {
	}

	// Get the point corresponding to a pixel
	vec4d at(int x, int y) const {
		return plane.at(xorigin + x * pixelsize, yorigin + y * pixelsize);
	}
};


// A fractal image generator for a certain plane.
class julia_gen {
	plane4d plane;
	int maxiter;

public:
	julia_gen(const plane4d &plane_arg, int maxiter_arg)
			: plane(plane_arg), maxiter(maxiter_arg) {
	}

private:
	// One iteration step for the fractal generation.
	std::complex<double> iter_step(std::complex<double> z, std::complex<double> c) const {
		return z*z + c;
	}

	// Get a color from the number of iterations
	int colorize(int it) const {
		if (it < 0)
			return gd::trueColor(0, 0, 0);
		else
			return gd::trueColor(it*2, it*2, 0);
	}

	// Generic function to determine the number of iterations till divergence
	// Returns -1 if not found to be diverging.
	int find_iterations(const vec4d &spec) const {
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
	// Generate an image for a certain area
	void fill(gd::image &output, const area_spec &area) const {
		const int xdim = output.sx();
		const int ydim = output.sy();
		const discrete_view view(plane, area, xdim, ydim);

		for (int x = 0; x < xdim; ++x) {
			for (int y = 0; y < ydim; ++y) {
				int it = find_iterations(view.at(x, y));
				output.setPixel(x, y, colorize(it));
			}
		}
	}
};


int main() {
	int xdim = 800;
	int ydim = 600;

	// mandelbrot
	vec4d base(-1, -1, 0, 0);
	vec4d xside(2, 0, 0, 0);
	vec4d yside(0, 2, 0, 0);

	// auch mandelbrot?
	//vec4d base(-1, -1, -1, -1);
	//vec4d xside(2, 0, 2, 0);
	//vec4d yside(0, 2, 0, 2);

	// auch mandelbrot?
	//vec4d base(-1, -1, 1, 1);
	//vec4d xside(2, 0, -2, 0);
	//vec4d yside(0, 2, 0, -2);

	//vec4d base(-1, -1, 0.9, 0.9);
	//vec4d xside(2, 0, -1.8, 0);
	//vec4d yside(0, 2, 0, -1.8);

	plane4d plane(base, xside, yside);
	julia_gen gen(plane, 250);

	area_spec area = area_spec::from_center(0, 0, 4);
	gd::image img(xdim, ydim);

	gen.fill(img, area);

	img.writePng("j.png");
}


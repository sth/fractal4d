
#include <complex>
#include "gd.hpp"

class vec4d {
public:
	double coords[4];

	vec4d(double a, double b, double c, double d)
			: coords{a, b, c, d} {
	}

	vec4d operator+(const vec4d &other) const {
		return vec4d{
				coords[0]+other.coords[0],
				coords[1]+other.coords[1],
				coords[2]+other.coords[2],
				coords[3]+other.coords[3]};
	}

	vec4d operator*(double fact) const {
		return vec4d{
				coords[0]*fact,
				coords[1]*fact,
				coords[2]*fact,
				coords[3]*fact};
	}

	vec4d operator/(double fact) const {
		return vec4d{
				coords[0]/fact,
				coords[1]/fact,
				coords[2]/fact,
				coords[3]/fact};
	}
};

class coord_plane {
	vec4d origin;
	vec4d xunit;
	vec4d yunit;

public:
	coord_plane(const vec4d &origin_arg, const vec4d &xunit_arg, const vec4d &yunit_arg)
			: origin(origin_arg), xunit(xunit_arg), yunit(yunit_arg) {
	}

	vec4d at(int x, int y) const {
		return origin + xunit * x + yunit * y;
	}
};


class julia_gen {
	int maxiter;

	coord_plane baseplane;

public:
	julia_gen(const coord_plane &baseplane_arg, int maxiter_arg)
			: baseplane(baseplane_arg), maxiter(maxiter_arg) {
	}

private:
	std::complex<double> iter_step(std::complex<double> z, std::complex<double> c) const {
		return z*z + c;
	}

	int colorize(int it) const {
		if (it < 0)
			return gd::trueColor(0, 0, 0);
		else
			return gd::trueColor(it*4, it*4, 0);
	}

	// Generic utilities
	int find_iterations(const vec4d &spec) const {
		const std::complex<double> c(spec.coords[0], spec.coords[1]);
		std::complex<double> z(spec.coords[2], spec.coords[3]); 

		int it;
		for (it = 0; it < maxiter; ++it) {
			if (abs(z) > 2)
				return it;
			z = iter_step(z, c);
			//z = z*z + c;
		}
		return -1;
	}

public:
	void fill(gd::image &output) const {
		const int xdim = output.sx();
		const int ydim = output.sy();
		for (int x = 0; x < xdim; ++x) {
			for (int y = 0; y < ydim; ++y) {
				int it = find_iterations(baseplane.at(x, y));
				output.setPixel(x, y, colorize(it));
			}
		}
	}
};


int main() {
	int xdim = 600;
	int ydim = 600;

	// mandelbrot
	//vec4d base(-1, -1, 0, 0);
	//vec4d xside(2, 0, 0, 0);
	//vec4d yside(0, 2, 0, 0);

	// auch mandelbrot?
	//vec4d base(-1, -1, -1, -1);
	//vec4d xside(2, 0, 2, 0);
	//vec4d yside(0, 2, 0, 2);

	// auch mandelbrot?
	//vec4d base(-1, -1, 1, 1);
	//vec4d xside(2, 0, -2, 0);
	//vec4d yside(0, 2, 0, -2);

	vec4d base(-1, -1, 0.9, 0.9);
	vec4d xside(2, 0, -1.8, 0);
	vec4d yside(0, 2, 0, -1.8);

	coord_plane baseplane(base, xside/xdim, yside/ydim);
	julia_gen gen(baseplane, 250);

	gd::image img(xdim, ydim);
	gen.fill(img);

	img.writePng("j.png");
}


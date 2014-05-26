
#if !defined(GENERATOR_HPP_INCLUDED)
#define GENERATOR_HPP_INCLUDED

#include <complex>
#include "area.hpp"

// A fractal image generator
class fractal_generator {
	int maxiter;

public:
	fractal_generator(int maxiter_arg);

private:
	// One iteration step for the fractal generation.
	// If you loke to generate a fractal for a different generation rule
	// like z^3 + c, change it here.
	std::complex<double> iter_step(std::complex<double> z, std::complex<double> c) const {
		return z*z + c;
	}

	// Generic function to determine the number of iterations till divergence
	// Returns -1 if not found to be diverging.
	int count_iterations(const vec4d &spec) const;

public:
	// The rendering function.
	// Takes a pixel area and an output function that gets called for
	// each pixel with (x, y, number_of_iterations)
	template<typename Output>
	void fill(const pixel_area &pixels, Output output) const;
};


/* Function implementations */

template<typename Output>
void fractal_generator::fill(const pixel_area &pixels, Output output) const {
	for (int x = 0; x < pixels.xpixels; ++x) {
		for (int y = 0; y < pixels.ypixels; ++y) {
			int it = count_iterations(pixels.at(x, y));
			output(x, y, it);
		}
	}
}

#endif // GENERATOR_HPP_INCLUDED


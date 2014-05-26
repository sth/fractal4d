
#include "generator.hpp"

fractal_generator::fractal_generator(int maxiter_arg)
		: maxiter(maxiter_arg) {
}

int fractal_generator::count_iterations(const vec4d &spec) const {
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


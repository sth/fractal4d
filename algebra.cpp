
#include "algebra.hpp"
#include <cmath>

// See other member functions are implemented directly in the header

double vec4d::dotproduct(const vec4d &other) const {
	double prod = 0;
	for (int i = 0; i < 4; ++i) {
		prod += coords[i] * other.coords[i];
	}
	return prod;
}

double vec4d::magnitude() const {
	return std::sqrt(dotproduct(*this));
}

vec4d vec4d::normalized() const {
	return *this / magnitude();
}

vec4d vec4d::projection_on(const vec4d &other) const {
	vec4d ounit = other.normalized();
	double scale = dotproduct(ounit);
	return ounit * scale;
}

vec4d vec4d::rejection_from(const vec4d &other) const {
	// Project |this| on |other|, then substracted the projected vector
	return *this - projection_on(other);
}


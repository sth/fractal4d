
#if !defined(ALGEBRA_HPP_INCLUDED)
#define ALGEBRA_HPP_INCLUDED

// Some basic linear algebra functions for 4d vectors and planes
// to help with calculations in the 4d set.

// A 4d vector
class vec4d {
public:
	double coords[4];

	vec4d(double a, double b, double c, double d);

	vec4d operator+(const vec4d &other) const;
	vec4d operator-(const vec4d &other) const;
	vec4d operator*(double fact) const;
	vec4d operator/(double fact) const;

	// The following functions are not really performance critical for out use
	// since we only use them once in preparation of rendering an image.

	// scalar product
	double dotproduct(const vec4d &other) const;

	// length of vector
	double magnitude() const;

	// vector in same direction, but with length 1
	vec4d normalized() const;

	// component of this vector that is parallel to |other|
	// (orthogonal projection of |this| to |other|
	vec4d projection_on(const vec4d &other) const;

	// component of this vector that is orthogonal to |other|
	vec4d rejection_from(const vec4d &other) const;
};


// A plane in 4d
//
// The plane is defined by a point `origin` and two (non-parallel)
// vectors `xaxis` and `yaxis`.
//
// The points { origin + x * xaxis + y * yaxis | x, y \in R } build a plane.
//
// This defines a coordinate system on the plane, with the point
// as origin and the vectors as the two axis. This can be used to access
// points on the plane by coordinates.

class plane4d {
	vec4d origin;
	vec4d xunit;
	vec4d yunit;

public:
	// Specifies a plane in 4d with a coordinate system.
	//
	// The two axis will be normalized so that the yaxis it orthogonal to
	// the xaxis and both stored vectors have size one.
	// This will fail if the vectors are zero or parallel to each other.
	plane4d(const vec4d &origin_arg, const vec4d &xaxis, const vec4d &yaxis);

	// Access points in the plane according to the internal coordinate system
	vec4d at(double x, double y) const;
};


/*
 * Following are some function definitions that we want in the header
 * for better inlining/performance
 */

inline vec4d::vec4d(double a, double b, double c, double d)
		: coords{a, b, c, d} {
}

inline vec4d vec4d::operator+(const vec4d &other) const {
	return vec4d{
			coords[0]+other.coords[0],
			coords[1]+other.coords[1],
			coords[2]+other.coords[2],
			coords[3]+other.coords[3]};
}

inline vec4d vec4d::operator-(const vec4d &other) const {
	return vec4d{
			coords[0]-other.coords[0],
			coords[1]-other.coords[1],
			coords[2]-other.coords[2],
			coords[3]-other.coords[3]};
}

inline vec4d vec4d::operator*(double fact) const {
	return vec4d{
			coords[0]*fact,
			coords[1]*fact,
			coords[2]*fact,
			coords[3]*fact};
}

inline vec4d vec4d::operator/(double fact) const {
	return vec4d{
			coords[0]/fact,
			coords[1]/fact,
			coords[2]/fact,
			coords[3]/fact};
}


inline plane4d::plane4d(const vec4d &origin_arg, const vec4d &xaxis, const vec4d &yaxis)
		: origin(origin_arg),
		  xunit(xaxis.normalized()),
		  yunit(yaxis.rejection_from(xunit).normalized()) {
}

inline vec4d plane4d::at(double x, double y) const {
	return origin + xunit * x + yunit * y;
}

#endif //  ALGEBRA_HPP_INCLUDED


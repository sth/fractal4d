
#if !defined(AREA_HPP_INCLUDED)
#define AREA_HPP_INCLUDED

#include "algebra.hpp"

// For image drawing purposes this defines an area of coordinates that
// should be drawn.
// It is specified by x. and y-coordinates of a point and the width of the area
// in x direction. The width in y direction is choosen later according to the
// image dimensions.
struct coord_area {
	plane4d plane;

	double xcenter;
	double ycenter;
	double xside;

	coord_area(const plane4d &plane_arg, double xcenter_arg, double ycenter_arg, double xside_arg);

	static coord_area from_corners(const plane4d &plane, double xtopleft, double ytopleft, double xbottomright, double ybottomright);
};


// A mapping between an area on a plane and pixels of an image
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
	pixel_area(const coord_area &coords, int xpixels_arg, int ypixels_arg);

	// Get the point corresponding to a pixel
	vec4d at(int x, int y) const;
};

inline vec4d pixel_area::at(int x, int y) const {
	return plane.at(xorigin + x * pixelsize, yorigin + y * pixelsize);
}

#endif // AREA_HPP_INCLUDED


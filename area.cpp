
#include "area.hpp"

coord_area::coord_area(const plane4d &plane_arg, double xcenter_arg, double ycenter_arg, double xside_arg)
		: plane(plane_arg), xcenter(xcenter_arg), ycenter(ycenter_arg), xside(xside_arg) {
}

coord_area coord_area::from_corners(const plane4d &plane, double xtopleft, double ytopleft, double xbottomright, double ybottomright) {
	return coord_area(
			plane,
			(xtopleft+xbottomright)/2,
			(ytopleft-ybottomright)/2,
			(xbottomright-xtopleft)
		);
}

pixel_area::pixel_area(const coord_area &coords, int xpixels_arg, int ypixels_arg)
		: plane(coords.plane), xpixels(xpixels_arg), ypixels(ypixels_arg),
		  pixelsize(coords.xside/xpixels),
		  xorigin(coords.xcenter - (xpixels/2) * pixelsize),
		  yorigin(coords.ycenter - (ypixels/2) * pixelsize) {
}


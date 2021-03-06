
# Fractal generator for arbitrary planes in the Mandelbrot/Julia 4D space

The [Mandelbrot set][1] is a fractal generated by iterating the formula *f(c) = z<sup>2</sup> + c*.
*z* starts out as zero and *c* ranges over the complex plane.

[Julia sets][2] are generated by iterating the similar formula *f(z) = z<sup>2</sup> + c*,
but here *c* is fixed and *z* ranges over the complex plane.

Both are special cases of a general function of two complex variables *f(z, c) = z<sup>2</sup> + c*.
Two complex variables, each with real and imaginary components, means that this deals with a four
dimensional space. The Julia and Mandelbrot sets are just on different planes in that four dimensional
space. Aside of them, there are of course many more possible planes in the underlying four
dimensional space, which might also be interesting to look at.

This fractal generator allows to select any of those planes in the underlying four dimensional
space and generates pictures for a sector on it. 

The generator is quite simple and separated into different components, so that it should be
easy to adjust for different fractals. Currently it generates Png pictures for fractal parameters
selected at compile time, which means that you have to edit the source and recompile to get
a new picture for different parameters (in [`main()`](main.cpp#L46)). There is nothing in the
design of the generator that would
require this, I simply didn't write a nice user interface. The advantage is that there are no
dependencies on GUI libraries and such.

The generator currently uses libgd to generate Png pictures, but could easily be adopted for other
use. The drawing functions are separated from the fractal generation code and could easily be
changed or separated into a library. The image is wrtten in [`render_png()`](main.cpp#L36),
this is the function that would need to be changed.

## Dependencies

- libgd to write PNG pictures, but adjusting it to some other image API should be quite easy.

## License

MIT Licence. See LICENSE.txt for details.

 [1]: http://en.wikipedia.org/wiki/Mandelbrot_set
 [2]: http://en.wikipedia.org/wiki/Julia_set#Quadratic_polynomials


#pragma once

#include "vec3.h"

#include <iostream>

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
	return sqrt(linear_component);
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples
	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Apply the linear to the gamma transform
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	static const interval intesity(0.000, 0.999);
	out << static_cast<int>(256 * intesity.clamp(r)) << ' '
		<< static_cast<int>(256 * intesity.clamp(g)) << ' '
		<< static_cast<int>(256 * intesity.clamp(b)) << '\n';
}
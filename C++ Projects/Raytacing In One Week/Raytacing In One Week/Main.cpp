#include <iostream>
#include <fstream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

color ray_color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	const auto aspect_ration = 16.0 / 9.0;
	int image_width = 400;

	// Calculate the image height and ensure that it is at least 1

	int image_height = static_cast<int>(image_width / aspect_ration);
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera

	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
	auto camer_center = point3(0, 0, 0);

	// Calculate the vectors along the horizontal and down the vertical edges
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the Horizontal and Vertical delta vectors from pixel to pixel
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel
	auto viewport_upper_left = camer_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;

	auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// Render

	std::ofstream out("image.ppm");

	out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	for (int j = 0; j < image_height; j++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			auto pixel_center = pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camer_center;
			ray r(camer_center, ray_direction);

			auto pixel_color = ray_color(r);
			write_color(out, pixel_color);
		}
	}

	std::clog << "\rDone.                 \n";

	out.close();

	return 0;
}
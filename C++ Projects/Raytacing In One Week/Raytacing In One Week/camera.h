#pragma once

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"

#include <fstream>
#include <string>

class camera
{
public:
	double aspec_ratio = 1.0; // Ratio of Image width over height
	int image_width = 400; // Rendererd image of width in pixel count
	int samples_per_pixel = 10; // Count of random samples per pixel
	int max_depth = 10; // Maximum number of ray bounces

	void render(const hittable& world)
	{
		initialize();

		out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++)
		{
			std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; i++)
			{
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; sample++)
				{
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(out, pixel_color, samples_per_pixel);
			}
		}

		std::clog << "\rDone.                 \n";

		out.close();
	}

private:
	std::ofstream out;
	int image_height; // Rendered Image Height
	point3 center;
	point3 pixel100_loc;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;

	void initialize()
	{
		out.open("image.ppm");

		image_height = static_cast<int>(image_width / aspec_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		center = point3(0, 0, 0);

		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}

	ray get_ray(int i, int j) const
	{
		// Get randomly sampled camera ray for the pixel at location i, j

		auto pixel_center = pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
		auto pixel_sample = pixel_center + pixel_sample_square();

		auto ray_origin = center;
		auto ray_direction = pixel_sample - ray_origin;

		return (ray(ray_origin, ray_direction));
	}

	vec3 pixel_sample_square() const
	{
		// Returns a random point in the square surrounding a pixel at the origin
		auto px = -0.5 + random_double();
		auto py = -0.5 + random_double();
		return (px * pixel_delta_u) + (py * pixel_delta_v);
	}

	color ray_color(const ray& r, int depth, const hittable& world) const
	{
		hit_record rec;

		if (depth <= 0)
		{
			return color(0, 0, 0);
		}

		if (world.hit(r, interval(0.001, infinity), rec))
		{
			vec3 direction = random_on_hemisphere(rec.normal);
			return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
		}

		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};
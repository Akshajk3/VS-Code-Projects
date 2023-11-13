#pragma once

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "material.h"

#include <fstream>
#include <string>

class camera
{
public:
	double aspec_ratio = 1.0; // Ratio of Image width over height
	int image_width = 400; // Rendererd image of width in pixel count
	int samples_per_pixel = 10; // Count of random samples per pixel
	int max_depth = 10; // Maximum number of ray bounces

	double vfov = 90; // Vertical view angle (field of view)
	point3 lookfrom = point3(0, 0, -1); // Point Camera is looking from
	point3 lookat = point3(0, 0, 0); // Point Camera is look at
	vec3 vup = vec3(0, 1, 0); // Camera-relative "up" direction

	double defocus_angle = 0; // Variation angle of rays through each pixel
	double focus_dist = 10; // Distance from camera to lookfrom point to plane of perfect focus

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
	point3 center; // Camera center
	point3 pixel100_loc; // location of pixel 0, 0
	vec3 pixel_delta_u; // Offset to pixel to the right
	vec3 pixel_delta_v; // Offset to pixel below
	vec3 u, v, w; // Camera from basis vectors
	vec3 defocus_disk_u; // Defocus disk horizontal radius
	vec3 defocus_disk_v; // Defocus disk vertical radius

	void initialize()
	{
		out.open("image.ppm");

		image_height = static_cast<int>(image_width / aspec_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		center = lookfrom;

		auto theta = deg_to_rad(vfov);
		auto h = tan(theta/2);
		auto viewport_height = 2 * h * focus_dist;
		auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		auto viewport_u = viewport_width * u; // Vector along viewport horizontal edge
		auto viewport_v = viewport_height * -v; // Vector along viewport vertical edge

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
		pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		auto defocus_radius = focus_dist * tan(deg_to_rad(defocus_angle / 2));
		defocus_disk_u = u * defocus_radius;
		defocus_disk_v = v * defocus_radius;
	}

	ray get_ray(int i, int j) const
	{
		// Get randomly sampled camera ray for the pixel at location i, j
		// the camera defocus disk

		auto pixel_center = pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
		auto pixel_sample = pixel_center + pixel_sample_square();

		auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
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

	point3 defocus_disk_sample() const
	{
		// Returns a random point in the camera focus disk
		auto p = random_in_unit_disk();
		return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
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
			ray scattered;
			color attenuation;
			if(rec.mat->scatter(r, rec, attenuation, scattered))
			{
				return attenuation * ray_color(scattered, depth - 1, world);
			}
			return color(0, 0, 0);
		}

		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
};
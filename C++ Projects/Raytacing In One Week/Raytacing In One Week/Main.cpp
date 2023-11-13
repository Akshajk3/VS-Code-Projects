#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;
	if(world.hit(r, interval(0, infinity), rec))
	{
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
	// World

	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;

	cam.aspec_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	// Render

	cam.render(world);

	return 0;
}
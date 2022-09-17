#include <iostream>

#include "util/matrix.h"
#include "util/tuple.h"
#include "util/color.h"

#include "framebuffer.h"
#include "material.h"
#include "geometry.h"
#include "light.h"

int main() {
	std::cout << "Hello world!" << std::endl;
	int dimension = 1000;
	Framebuffer framebuffer{ dimension, dimension};

	Tuple4d& ray_origin = point(0, 0, -5);
	Material mat;
	mat.m_color = Color{ 0.3, 0.5, 1 };
	mat.m_ambient = 0.1;
	mat.m_diffuse = 0.9;
	mat.m_specular = 0.9;
	mat.m_shininess = 200;
	Sphere sphere(identity(), mat);

	Light light{ point(-10, 10, -10), Color{1, 1, 1}};

	double canvas_dim = 10;
	double pixel_size = canvas_dim / dimension;
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {
			double canvas_x = -5 + x * pixel_size;
			double canvas_y = 5 - y * pixel_size;
			double canvas_z = 10;
			Tuple4d& canvas_pos = point(canvas_x, canvas_y, canvas_z);
			Ray ray(ray_origin, canvas_pos - ray_origin);
			std::vector<double> intersections = sphere.intersect(ray);
			if (intersections.size() > 0) {
				//framebuffer.set_color(x, y, Color(1, 1, 1));
				std::sort(intersections.begin(), intersections.end());
				float t_min = FLT_MAX;
				for (int i = 0; i < intersections.size(); ++i) {
					if (intersections[i] > 0 && intersections[i] < t_min) {
						t_min = intersections[i];
					}
				}
				Tuple4d point = ray.position(t_min);
				Tuple4d normal = sphere.normal(point);
				Tuple4d eye = -ray.direction().normalize();
				Color color = light.phong_shading(sphere, point, eye, normal);
				framebuffer.set_color(x, y, color);

			}
		}
	}
	framebuffer.write_file("test.ppm");
	std::cout << "Finished" << std::endl;
}
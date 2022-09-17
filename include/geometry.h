#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "util/matrix.h"
#include "material.h"
#include "ray.h"
#include <vector>

class Sphere {
private:
	Matrix4d m_transformation;
	Material m_material;

public:
	Sphere(const Matrix4d& transformation, const Material& material);

	std::vector<double> intersect(const Ray& ray) const;
	Tuple4d normal(const Tuple4d& hit_point) const;
	const Material& material() const { return m_material;};
};

#endif // __GEOMETRY_H__
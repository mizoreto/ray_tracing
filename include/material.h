#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "util/color.h"

struct Material {
	Color m_color;
	double m_ambient, m_diffuse, m_specular, m_shininess;
};

#endif // __MATERIAL_H__
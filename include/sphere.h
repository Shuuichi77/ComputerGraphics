#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <g3x.h>
#include "shape.h"

static double const SPHERE_R = 1.0;   // Sphere radius

void draw_points_sphere(Shape *shape, G3Xvector scale_factor);

void draw_faces_sphere(Shape *shape, G3Xvector scale_factor, double step);

int init_sphere(ShapePtr *sphere);

#endif
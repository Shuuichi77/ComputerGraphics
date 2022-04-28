#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include <g3x.h>
#include "shape.h"

static double const CYLINDER_H = 2;   // Cylinder height length
static double const CYLINDER_R = 1;   // Cylinder radius length

void draw_points_cylinder(Shape *shape, G3Xvector scale_factor);

void draw_faces_cylinder(Shape *shape, G3Xvector scale_factor);

int init_cylinder(ShapePtr *cylinder);

#endif
#ifndef __TORUS_H__
#define __TORUS_H__

#include <g3x.h>
#include "shape.h"

static double const TORUS_R            = 1.0;   // Torus radius
static double const WHOLE_TORUS_RADIUS = 0.5;   // Whole Torus radius

void draw_points_torus(Shape *shape, G3Xvector scale_factor);

void draw_faces_torus(Shape *shape, G3Xvector scale_factor);

int init_torus(ShapePtr *torus, double torus_radius, double total_radius);

#endif
#ifndef __TORUS_H__
#define __TORUS_H__

#include <g3x.h>
#include "shape.h"

static double const WHOLE_TORUS_RADIUS = 1.0;   // Whole Torus radius
static double const TORUS_R            = 0.2;   // Torus radius

void draw_points_torus(Shape *shape, G3Xvector scale_factor);

void draw_faces_torus(Shape *shape, G3Xvector scale_factor, double step);

int init_torus(ShapePtr *torus);

#endif
#ifndef __TORUS_H__
#define __TORUS_H__

#include <g3x.h>
#include "shape.h"

static double TORUS_R = 1.0;    // Hole radius
static double TORUS_S = 0.5;    // Tore radius

void draw_points_torus(Shape *shape, G3Xvector scale_factor);

void draw_faces_torus(Shape *shape, G3Xvector scale_factor);

Shape init_torus();

#endif
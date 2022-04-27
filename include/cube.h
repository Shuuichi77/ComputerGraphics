#ifndef __CUBE_H__
#define __CUBE_H__

#include <g3x.h>
#include "shape.h"

static double CUBE_W = 2.0; // Cube side length

void draw_points_cube(Shape *shape, G3Xvector scale_factor);

void draw_faces_cube(Shape *shape, G3Xvector scale_factor);

int init_cube(ShapePtr *cube);

#endif
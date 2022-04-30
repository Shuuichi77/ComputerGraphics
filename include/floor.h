#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <g3x.h>
#include "cube.h"
#include "node.h"

static double const FLOOR_X = 1. / 3.;
static double const FLOOR_Y = FLOOR_X;
static double const FLOOR_Z = 0.001 / 3.;

static double floor_length = FLOOR_X * CUBE_W;
static double floor_width  = FLOOR_Y * CUBE_W;
static double floor_height = FLOOR_Z * CUBE_W;

int init_floor(SceneTree *floor, Shape *cube);

#endif
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <g3x.h>
#include "cube.h"
#include "node.h"

static double const FLOOR_X = 1. * 1.5;
static double const FLOOR_Y = FLOOR_X;
static double const FLOOR_Z = 0.001;

static double floor_length = FLOOR_X * CUBE_W;
static double floor_height = FLOOR_Z * CUBE_W;

static int const NB_PAIR_TILES = 2;

int init_floor(SceneTree *floor, Shape *cube);

#endif
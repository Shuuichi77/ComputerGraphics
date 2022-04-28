#ifndef __TABLE_H__
#define __TABLE_H__

#include <g3x.h>
#include "cube.h"
#include "cylinder.h"
#include "node.h"

static double const DESK_X = 1;
static double const DESK_Y = 0.5;
static double const DESK_Z = 0.1;
static double const LEG_Z  = 0.5;

static double desk_length = DESK_X * CUBE_W;
static double desk_width  = DESK_Y * CUBE_W;
static double desk_height = DESK_Z * CUBE_W;
static double leg_height  = LEG_Z * CYLINDER_H;


int init_table(SceneTree *table, Shape *cube, Shape *cylinder);

#endif
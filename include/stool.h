#ifndef __STOOL_H__
#define __STOOL_H__

#include <g3x.h>
#include "cube.h"
#include "cylinder.h"
#include "node.h"

static double const STOOL_X     = 0.5;
static double const STOOL_Y     = STOOL_X;
static double const STOOL_Z     = 0.1;
static double const STOOL_LEG_Z = 0.4;

static double stool_length     = STOOL_X * CYLINDER_R;
static double stool_width      = STOOL_Y * CYLINDER_R;
static double stool_height     = STOOL_Z * CYLINDER_R;
static double stool_leg_height = STOOL_LEG_Z * CUBE_W;

int init_stool(SceneTree *stool, Shape *cube, Shape *cylinder);

#endif
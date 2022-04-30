#ifndef __STELE_H__
#define __STELE_H__

#include <g3x.h>
#include "cube.h"
#include "cylinder.h"
#include "floor.h"
#include "torus.h"
#include "node.h"

static double const PEDESTAL_X = FLOOR_X;
static double const PEDESTAL_Y = FLOOR_Y;
static double const PEDESTAL_Z = 0.15;

static double const TOWER_X = PEDESTAL_X / 3.;
static double const TOWER_Y = TOWER_X;
static double const TOWER_Z = 1;

static double const TOWER_RING_X = TOWER_X;
static double const TOWER_RING_Y = TOWER_RING_X;
static double const TOWER_RING_Z = TOWER_RING_X;

static double pedestal_length   = PEDESTAL_X * CUBE_W;
static double pedestal_width    = PEDESTAL_Y * CUBE_W;
static double pedestal_height   = PEDESTAL_Z * CUBE_W;
static double tower_radius      = TOWER_X * CYLINDER_R;
static double tower_height      = TOWER_Z * CYLINDER_H;
static double tower_ring_height = TOWER_RING_Z * 0.2;

int init_stele(SceneTree *stele, Shape *cube, Shape *cylinder, Shape *torus);

#endif
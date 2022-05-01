#ifndef __STELE_H__
#define __STELE_H__

#include <g3x.h>
#include "cube.h"
#include "cylinder.h"
#include "floor.h"
#include "torus.h"
#include "node.h"

extern double const pedestal_length;
extern double const pedestal_width;
extern double const pedestal_height;
extern double const tower_radius;
extern double const tower_height;

//extern double const tower_ring_height;

SceneTree initStele(Shape *cube, Shape *cylinder, Shape *torus);

#endif
#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <g3x.h>
#include "cube.h"
#include "node.h"

extern double const floor_length;
extern double const floor_width;
extern double const floor_height;

SceneTree initFloor(Shape *cube);

#endif
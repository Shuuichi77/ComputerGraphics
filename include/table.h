#ifndef __TABLE_H__
#define __TABLE_H__

#include <g3x.h>
#include "cube.h"
#include "cylinder.h"
#include "node.h"

extern double const DESK_X;
extern double const DESK_Y;
extern double const DESK_Z;
extern double const LEG_Z;

extern double const desk_length;
extern double const desk_width;
extern double const desk_height;
extern double const leg_height;

SceneTree initTable(Shape *cube, Shape *cylinder);

#endif
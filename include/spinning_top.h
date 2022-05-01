#ifndef __SPINNING_TOP_H__
#define __SPINNING_TOP_H__

#include <g3x.h>
#include "cylinder.h"
#include "sphere.h"
#include "torus.h"
#include "node.h"

extern double const stick_height;

SceneTree initSpinningTop(Shape *cylinder, Shape *sphere, Shape *torus);

#endif
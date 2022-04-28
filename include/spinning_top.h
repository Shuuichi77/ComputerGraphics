#ifndef __SPINNING_TOP_H__
#define __SPINNING_TOP_H__

#include <g3x.h>
#include "cylinder.h"
#include "sphere.h"
#include "torus.h"
#include "node.h"

static double const STICK_X = 0.04;
static double const STICK_Y = STICK_X;
static double const STICK_Z = 1;

static double const GLOBE_X = 0.35;
static double const GLOBE_Y = GLOBE_X;
static double const GLOBE_Z = GLOBE_X;

static double const TORUS_X = GLOBE_X;
static double const TORUS_Y = TORUS_X;
static double const TORUS_Z = TORUS_X;

static double bottom_stick_height = (STICK_Z * CYLINDER_H) * 0.25;

int init_spinning_top(SceneTree *spinning_top, Shape *cylinder, Shape *sphere, Shape *torus);

#endif
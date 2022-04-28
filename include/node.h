#ifndef __NODE_H__
#define __NODE_H__

#include <g3x.h>
#include "shape.h"

static G3Xcolor red   = { 1.00, 0.00, 0.00, 0.00 };
static G3Xcolor green = { 0.00, 1.00, 0.00, 0.00 };
static G3Xcolor blue  = { 0.00, 0.00, 1.00, 0.00 };

static G3Xcolor dark_yellow = { 71.0 / 255.0, 69.0 / 255.0, 11.0 / 255.0, .0 };
static G3Xcolor light_brown = { 71.0 / 255.0, 40.0 / 255.0, 11.0 / 255.0, .0 };
static G3Xcolor dark_brown  = { 40.0 / 255.0, 26.0 / 255.0, 13.0 / 255.0, .0 };
static G3Xcolor grey        = { 144.0 / 255.0, 144.0 / 255.0, 144.0 / 255.0, .0 };
static G3Xcolor dark_grey   = { 105.0 / 255.0, 105.0 / 255.0, 105.0 / 255.0, .0 };
static G3Xcolor light_grey  = { 211.0 / 255.0, 211.0 / 255.0, 211.0 / 255.0, .0 };

typedef struct _node_
{
    struct _node_ *down, *next;     /* chaînage */
    G3Xhmat       Md;               /* matrice de transformation directe */
    G3Xcolor      col;              /* couleur RGBA */
    float         mat[4];           /* 4 réels dans [0,1] : (ambi, diff, spec, shine) */
    G3Xvector     scale_factor;     /* facteurs d’échelles locaux en x, y, z */
    Shape         *instance;        /* une éventuelle instance d’objet */
}               Node, *SceneTree;

void scalef(SceneTree *node, double hx, double hy, double hz);

void translate(SceneTree *node, double tx, double ty, double tz);

void rotate_x(SceneTree *node, double dx);

void rotate_y(SceneTree *node, double dy);

void rotate_z(SceneTree *node, double dz);

int add_child(SceneTree *father);

int add_next(SceneTree *node, SceneTree *father);

void draw_node(Node *node);

#endif
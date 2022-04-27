#ifndef __NODE_H__
#define __NODE_H__

#include <g3x.h>
#include "shape.h"

typedef struct _material_
{
    float ambi;
    float diff;
    float spec;
    float shine;
} Material;

typedef struct _node_
{
    struct _node_ *down, *next;     /* chaînage */
    G3Xhmat       Md;               /* matrice de transformation directe */
    G3Xcolor      col;              /* couleur RGBA */
    Material      mat;              /* 4 réels dans [0,1] : (ambi, diff, spec, shine) */
    G3Xvector     scale_factor;     /* facteurs d’échelles locaux en x, y, z */
    Shape         *instance;        /* une éventuelle instance d’objet */
} Node, *SceneTree;


#endif
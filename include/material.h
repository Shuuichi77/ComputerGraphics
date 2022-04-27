#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <g3x.h>

typedef struct _material_
{
    float ambi;
    float diff;
    float spec;
    float shine;
} Material;

#endif
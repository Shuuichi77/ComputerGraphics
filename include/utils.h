#ifndef __UTILS_H__
#define __UTILS_H__

#include <g3x.h>

/**
 * Renvoie le minimum entre a et b.
 */
int min(int a, int b)
{
    return a < b ? a : b;
}

/**
 * Dessine un side et une normale aux coordonnées fournies.<br/>
 * La normale sert notamment à calculer les réflexions de lumières.
 */
void NormalVertex3dv(Shape shape, unsigned int index)
{
    g3x_Normal3dv(shape.norm[index]);
    g3x_Vertex3dv(shape.vrtx[index]);
}

#endif
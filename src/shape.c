#include "../include/shape.h"

double step = 1.0;

int min(int a, int b)
{
    return a < b ? a : b;
}

void NormalVertex3dv(Shape shape, unsigned int index)
{
    g3x_Normal3dv(shape.norm[index]);
    g3x_Vertex3dv(shape.vrtx[index]);
}
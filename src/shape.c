#include "../include/shape.h"

void freeShape(Shape *shape)
{
    free((*shape).vrtx);
    free((*shape).norm);
    free(shape);
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void normalAndVertex3dv(Shape shape, unsigned int index)
{
    g3x_Normal3dv(shape.norm[index]);
    g3x_Vertex3dv(shape.vrtx[index]);
}

int getSWIndex(double step, int i, int j, int max, int offset, int additional_offset)
{
    return i * offset + additional_offset + min(j + step, max - 1);
}


int getSEIndex(double step, int i, int j, int max1, int max2, int offset, int additional_offset)
{
    return (min(i + step, max1) % max1) * offset + additional_offset + min(j + step, max2 - 1);
}


int getNWIndex(int i, int j, int offset, int additional_offset)
{
    return i * offset + additional_offset + j;
}


int getNEIndex(double step, int i, int j, int max, int offset, int additional_offset)
{
    return (min(i + step, max) % max) * offset + additional_offset + j;
}


void
drawTriangleSwSeNw(Shape *shape, double step, int i, int j, int max1, int max2, int offset, int additional_offset)
{
    normalAndVertex3dv(*shape, getSWIndex(step, i, j, max1, offset, additional_offset));
    normalAndVertex3dv(*shape, getSEIndex(step, i, j, max1, max2, offset, additional_offset));
    normalAndVertex3dv(*shape, getNWIndex(i, j, offset, additional_offset));
}


void
drawTriangleNwSeNe(Shape *shape, double step, int i, int j, int max1, int max2, int offset, int additional_offset)
{
    normalAndVertex3dv(*shape, getNWIndex(i, j, offset, additional_offset));
    normalAndVertex3dv(*shape, getSEIndex(step, i, j, max1, max2, offset, additional_offset));
    normalAndVertex3dv(*shape, getNEIndex(step, i, j, max1, offset, additional_offset));
}
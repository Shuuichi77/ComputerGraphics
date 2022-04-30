#include "../include/torus.h"

void draw_points_torus(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_torus(Shape *shape, G3Xvector scale_factor, double step)
{
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * shape->n1 + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * shape->n1 + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, i * shape->n1 + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * shape->n1 + j);
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * shape->n1 + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * shape->n1 + j);
        }
    }
    glEnd();
}

int init_torus(ShapePtr *torus)
{
    if (NULL == ((*torus) = (Shape *) malloc(sizeof(Shape))))
    {
        return 0;
    }

//    (*torus)->n1 = 5 * NBM * torus_radius * total_radius;
//    (*torus)->n2 = 5 * NBP * torus_radius * total_radius;

    (*torus)->n1 = NBM;
    (*torus)->n2 = NBP;

    double       theta         = 2 * PI / (*torus)->n1;
    double       phi           = 2 * PI / ((*torus)->n2 - 1);
    unsigned int vertex_number = (*torus)->n1 * (*torus)->n2;
    (*torus)->vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    (*torus)->norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    (*torus)->draw_points = draw_points_torus;
    (*torus)->draw_faces  = draw_faces_torus;

    for (int i = 0; i < (*torus)->n1; i++)
    {
        for (int j = 0; j < (*torus)->n2; j++)
        {
            (*torus)->norm[i * (*torus)->n1 + j] = (G3Xpoint) {
                    cos(i * theta) * (WHOLE_TORUS_RADIUS + TORUS_R * cos(j * phi)),
                    -sin(i * theta) * (WHOLE_TORUS_RADIUS + TORUS_R * cos(j * phi)),
                    TORUS_R * sin(j * phi) };
            (*torus)->vrtx[i * (*torus)->n1 + j] = (G3Xpoint) {
                    cos(i * theta) * (WHOLE_TORUS_RADIUS + TORUS_R * cos(j * phi)),
                    -sin(i * theta) * (WHOLE_TORUS_RADIUS + TORUS_R * cos(j * phi)),
                    TORUS_R * sin(j * phi) };
        }
    }

    return 1;
}

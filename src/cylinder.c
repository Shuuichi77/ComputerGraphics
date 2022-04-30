#include "../include/cylinder.h"

void draw_points_cylinder(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_cylinder(Shape *shape, G3Xvector scale_factor, double step)
{
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n3 * 2) + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * (shape->n1 + shape->n3 * 2) +
                                    min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n3 * 2) + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n3 * 2) + j);
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * (shape->n1 + shape->n3 * 2) +
                                    min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * (shape->n1 + shape->n3 * 2) + j);
        }

        for (int k = 0; k < shape->n3; k += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + min(k + step, shape->n3 - 1));
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 +
                                    min(k + step, shape->n3 - 1));
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + k);


            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + k);
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 +
                                    min(k + step, shape->n3 - 1));
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + k);
        }

        for (int l = 0; l < shape->n3; l += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + shape->n3 + min(l + step, shape->n3 - 1));
            NormalVertex3dv(*shape,
                            min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + shape->n3 +
                            min(l + step, shape->n3 - 1));
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + shape->n3 + l);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + shape->n3 + l);
            NormalVertex3dv(*shape,
                            min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + shape->n3 +
                            min(l + step, shape->n3 - 1));
            NormalVertex3dv(*shape,
                            min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + shape->n3 + l);
        }
    }
    glEnd();
}

int init_cylinder(ShapePtr *cylinder)
{
    if (NULL == ((*cylinder) = (Shape *) malloc(sizeof(Shape))))
    {
        return 0;
    }

    (*cylinder)->n1 = NBM;
    (*cylinder)->n2 = NBP;
    (*cylinder)->n3 = NBC;

    double theta = 2 * PI / (*cylinder)->n1;
    double t     = CYLINDER_H / ((*cylinder)->n2 - 1);
    double r     = CYLINDER_R / ((*cylinder)->n3 - 1);

    unsigned int vertex_number = (*cylinder)->n1 * (*cylinder)->n2 + (*cylinder)->n1 * ((*cylinder)->n3 * 2);

    (*cylinder)->vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    (*cylinder)->norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    (*cylinder)->draw_points = draw_points_cylinder;
    (*cylinder)->draw_faces  = draw_faces_cylinder;

    for (int i = 0; i < (*cylinder)->n1; i++)
    {
        for (int j = 0; j < (*cylinder)->n2; j++)
        {
            (*cylinder)->norm[i * ((*cylinder)->n1 + (*cylinder)->n3 * 2) + j] =
                    (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                 CYLINDER_R * sin(i * theta),
                                 (j * t) - (CYLINDER_H / 2.) };

            (*cylinder)->vrtx[i * ((*cylinder)->n1 + (*cylinder)->n3 * 2) + j] =
                    (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                 CYLINDER_R * sin(i * theta),
                                 (j * t) - (CYLINDER_H / 2.) };
        }
        for (int k = 0; k < (*cylinder)->n3; k++)
        {
            (*cylinder)->norm[i * ((*cylinder)->n1 + (*cylinder)->n2) + (*cylinder)->n2 + k] =
                    (G3Xpoint) { (k * r) * cos(i * theta),
                                 (k * r) * sin(i * theta),
                                 CYLINDER_H / 2. };

            (*cylinder)->vrtx[i * ((*cylinder)->n1 + (*cylinder)->n2) + (*cylinder)->n2 + k] =
                    (G3Xpoint) { (k * r) * cos(i * theta),
                                 (k * r) * sin(i * theta),
                                 CYLINDER_H / 2. };
        }

        for (int l = 0; l < (*cylinder)->n3; l++)
        {
            (*cylinder)->norm[i * ((*cylinder)->n1 + (*cylinder)->n2) + (*cylinder)->n2 + (*cylinder)->n3 + l] =
                    (G3Xpoint) { (l * r) * cos(i * theta),
                                 (l * r) * sin(i * theta),
                                 -CYLINDER_H / 2. };

            (*cylinder)->vrtx[i * ((*cylinder)->n1 + (*cylinder)->n2) + (*cylinder)->n2 + (*cylinder)->n3 + l] =
                    (G3Xpoint) { (l * r) * cos(i * theta),
                                 (l * r) * sin(i * theta),
                                 -CYLINDER_H / 2. };
        }
    }

    return 1;
}


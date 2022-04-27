#include <g3x.h>
#include "../include/shape.h"
#include "../include/cylinder.h"
#include "../include/utils.h"

#define NBC 50                    // Nombre de cercles sur les bases

static double CYLINDER_H = 2;              // Hauteur du cylindre
static double CYLINDER_R = 1;             // Rayon du cylindre

void draw_points_cylinder(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_cylinder(Shape *shape, G3Xvector scale_factor)
{
    g3x_Material(G3Xr, .2, .6, .9, 1, 1);
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (shape->n1 + NBC * 2) + min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * (shape->n1 + NBC * 2) +
                                    min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, i * (shape->n1 + NBC * 2) + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (shape->n1 + NBC * 2) + j);
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * (shape->n1 + NBC * 2) +
                                    min(j + step, shape->n2 - 1));
            NormalVertex3dv(*shape, (min(i + step, shape->n1) % shape->n1) * (shape->n1 + NBC * 2) + j);
        }

        for (int k = 0; k < NBC; k += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + min(k + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 +
                                    min(k + step, NBC - 1));
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + k);


            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + k);
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 +
                                    min(k + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + k);
        }

        for (int l = 0; l < NBC; l += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + NBC + min(l + step, NBC - 1));
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + NBC +
                                    min(l + step, NBC - 1));
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + NBC + l);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * (shape->n1 + shape->n2) + shape->n2 + NBC + l);
            NormalVertex3dv(*shape, min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + NBC +
                                    min(l + step, NBC - 1));
            NormalVertex3dv(*shape,
                            min(i + step, shape->n1) % shape->n1 * (shape->n1 + shape->n2) + shape->n2 + NBC + l);
        }
    }
    glEnd();
}


Shape init_cylinder()
{
    Shape cylinder;
    cylinder.n1 = NBM;
    cylinder.n2 = NBP;

    double theta = 2 * PI / cylinder.n1;
    double t     = CYLINDER_H / (cylinder.n2 - 1);
    double r     = CYLINDER_R / (NBC - 1);

    unsigned int vertex_number = cylinder.n1 * cylinder.n2 + cylinder.n1 * (NBC * 2);

    cylinder.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cylinder.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    cylinder.draw_points = draw_points_cylinder;
    cylinder.draw_faces  = draw_faces_cylinder;

    for (int i = 0; i < cylinder.n1; i++)
    {
        for (int j = 0; j < cylinder.n2; j++)
        {
            cylinder.norm[i * (cylinder.n1 + NBC * 2) + j] = (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                                                          CYLINDER_R * sin(i * theta),
                                                                          (j * t) - (CYLINDER_H / 2.) };

            cylinder.vrtx[i * (cylinder.n1 + NBC * 2) + j] = (G3Xpoint) { CYLINDER_R * cos(i * theta),
                                                                          CYLINDER_R * sin(i * theta),
                                                                          (j * t) - (CYLINDER_H / 2.) };
        }
        for (int k = 0; k < NBC; k++)
        {
            cylinder.norm[i * (cylinder.n1 + cylinder.n2) + cylinder.n2 + k] = (G3Xpoint) { (k * r) * cos(i * theta),
                                                                                            (k * r) * sin(i * theta),
                                                                                            CYLINDER_H / 2. };

            cylinder.vrtx[i * (cylinder.n1 + cylinder.n2) + cylinder.n2 + k] = (G3Xpoint) { (k * r) * cos(i * theta),
                                                                                            (k * r) * sin(i * theta),
                                                                                            CYLINDER_H / 2. };
        }

        for (int l = 0; l < NBC; l++)
        {
            cylinder.norm[i * (cylinder.n1 + cylinder.n2) + cylinder.n2 + NBC + l] = (G3Xpoint) {
                    (l * r) * cos(i * theta),
                    (l * r) * sin(i * theta),
                    -CYLINDER_H / 2. };

            cylinder.vrtx[i * (cylinder.n1 + cylinder.n2) + cylinder.n2 + NBC + l] = (G3Xpoint) {
                    (l * r) * cos(i * theta),
                    (l * r) * sin(i * theta),
                    -CYLINDER_H / 2. };
        }
    }

    return cylinder;
}

void draw_cylinder(G3Xvector scale_factor)
{
    Shape cylinder = init_cylinder();
    cylinder.draw_faces(&cylinder, scale_factor);
}


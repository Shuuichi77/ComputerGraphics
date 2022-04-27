#include <g3x.h>
#include "../include/shape.h"
#include "../include/sphere.h"
#include "../include/utils.h"

#define NBM 100                   // Nombre de méridiens (lignes verticales)
#define NBP 100                   // Nombre de parallèles (lignes horizontales)
static double TORUS_R = 1.0;            // Rayon du trou
static double TORUS_S = 0.5;            // Rayon du tore (épaisseur)

void draw_points_torus(Shape *shape, G3Xvector scale_factor)
{
    glBegin(GL_TRIANGLES);

    // TODO

    glEnd();
}

void draw_faces_torus(Shape *shape, G3Xvector scale_factor)
{
    g3x_Material(G3Xr, .2, .6, .9, 1, 1);
    glScalef(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < NBM; i += step)
    {
        for (int j = 0; j < NBP - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            NormalVertex3dv(*shape, i * NBM + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * NBM + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, i * NBM + j);

            // Second triangle (NW -> SE -> NE)
            NormalVertex3dv(*shape, i * NBM + j);
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * NBM + min(j + step, NBP - 1));
            NormalVertex3dv(*shape, (min(i + step, NBM) % NBM) * NBM + j);
        }
    }
    glEnd();
}

Shape init_torus()
{
    Shape        torus;
    double       theta         = 2 * PI / NBM;
    double       phi           = 2 * PI / (NBP - 1); // -1 ici, car on veut NBP faces et pas NBP lignes
    unsigned int vertex_number = NBM * NBP;
    torus.vrtx        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    torus.norm        = (G3Xpoint *) calloc(sizeof(G3Xpoint), vertex_number);
    torus.draw_points = draw_points_torus;
    torus.draw_faces  = draw_faces_torus;

    for (int i = 0; i < NBM; i++)
    {
        for (int j = 0; j < NBP; j++)
        {
            torus.norm[i * NBM + j] = (G3Xpoint) { cos(i * theta) * (TORUS_R + TORUS_S * cos(j * phi)),
                                                   -sin(i * theta) * (TORUS_R + TORUS_S * cos(j * phi)),
                                                   TORUS_S * sin(j * phi) };
            torus.vrtx[i * NBM + j] = (G3Xpoint) { cos(i * theta) * (TORUS_R + TORUS_S * cos(j * phi)),
                                                   -sin(i * theta) * (TORUS_R + TORUS_S * cos(j * phi)),
                                                   TORUS_S * sin(j * phi) };
        }
    }

    return torus;
}

void draw_torus(G3Xvector scale_factor)
{
    Shape torus = init_torus();
    torus.draw_faces(&torus, scale_factor);
}


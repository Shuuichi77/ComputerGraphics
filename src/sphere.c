#include "../include/sphere.h"

static int offset;

static void drawPointsSphere(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_POINTS);

    for (int i = 0; i < shape->n1 * shape->n2; i += step)
    {
        g3x_Vertex3dv(shape->vrtx[i]);
    }

    glEnd();
}

static void drawFacesSphere(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            // Premier triangle (SW -> SE -> NW)
            drawTriangleSwSeNw(shape, step, i, j, shape->n1, shape->n2, offset, 0);
            drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n2, offset, 0);
        }
    }
    glEnd();
}

ShapePtr initSphere()
{
    ShapePtr sphere = (Shape *) malloc(sizeof(Shape));
    if (sphere == NULL) { return NULL; }

    sphere->n1 = NBM;
    sphere->n2 = NBP;
    unsigned int vertex_number = sphere->n1 * sphere->n2;
    if (NULL == (sphere->vrtx = (G3Xpoint *) malloc(sizeof(G3Xpoint) * vertex_number)))
    {
        free(sphere);
        return NULL;
    }

    if (NULL == (sphere->norm = (G3Xvector *) malloc(sizeof(G3Xvector) * vertex_number)))
    {
        free(sphere->vrtx);
        free(sphere);
        return NULL;
    }

    double theta = 2 * PI / sphere->n1;
    double phi   = PI / (sphere->n2 - 1);
    sphere->draw_points = drawPointsSphere;
    sphere->draw_faces  = drawFacesSphere;
    offset = sphere->n1;

    for (int i = 0; i < sphere->n1; i++)
    {
        for (int j = 0; j < sphere->n2; j++)
        {
            sphere->norm[i * offset + j] = (G3Xvector) { SPHERE_R * cos(i * theta) * sin(j * phi),
                                                         SPHERE_R * sin(i * theta) * sin(j * phi),
                                                         SPHERE_R * cos(j * phi) };

            sphere->vrtx[i * offset + j] = (G3Xpoint) { SPHERE_R * cos(i * theta) * sin(j * phi),
                                                        SPHERE_R * sin(i * theta) * sin(j * phi),
                                                        SPHERE_R * cos(j * phi) };
        }
    }

    return sphere;
}


#include "../include/torus.h"

static int offset;

static void drawPointsTorus(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_POINTS);

    for (int i = 0; i < shape->n1 * shape->n2; i += step)
    {
        g3x_Vertex3dv(shape->vrtx[i]);
    }

    glEnd();
}

static void drawFacesTorus(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            drawTriangleSwSeNw(shape, step, i, j, shape->n1, shape->n2, offset, 0);
            drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n2, offset, 0);
        }
    }
    glEnd();
}

ShapePtr initTorus()
{
    ShapePtr torus = (Shape *) malloc(sizeof(Shape));
    if (torus == NULL) { return NULL; }

    torus->n1 = NBM;
    torus->n2 = NBP;
    unsigned int vertex_number = torus->n1 * torus->n2;
    if (NULL == (torus->vrtx = (G3Xpoint *) malloc(sizeof(G3Xpoint) * vertex_number)))
    {
        free(torus);
        return NULL;
    }

    if (NULL == (torus->norm = (G3Xvector *) malloc(sizeof(G3Xvector) * vertex_number)))
    {
        free(torus->vrtx);
        free(torus);
        return NULL;
    }

    torus->draw_points = drawPointsTorus;
    torus->draw_faces  = drawFacesTorus;
    double theta = 2 * PI / torus->n1;
    double phi   = 2 * PI / (torus->n2 - 1);
    offset = torus->n1;

    for (int i = 0; i < torus->n1; i++)
    {
        for (int j = 0; j < torus->n2; j++)
        {
            torus->norm[i * offset + j] = (G3Xvector) {
                    cos(i * theta) * cos(j * phi),
                    -sin(i * theta) * cos(j * phi),
                    sin(j * phi) };

            torus->vrtx[i * offset + j] = (G3Xpoint) {
                    cos(i * theta) * (WHOLE_TORUS_RADIUS + TORUS_R * cos(j * phi)),
                    -sin(i * theta) * (WHOLE_TORUS_RADIUS + TORUS_R * cos(j * phi)),
                    TORUS_R * sin(j * phi) };
        }
    }

    return torus;
}

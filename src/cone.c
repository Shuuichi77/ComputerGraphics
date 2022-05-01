#include "../include/cone.h"

static int side_offset;
static int faces_offset;
static int bottom_face_additional_offset;
static int bottom_face_additional_offset;

static void drawPointsCone(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);
    glBegin(GL_POINTS);

    for (int i = 0; i < shape->n1 * shape->n2 + shape->n1 * shape->n3; i += step)
    {
        g3x_Vertex3dv(shape->vrtx[i]);
    }

    glEnd();
}

static void drawFaceCone(Shape *shape, int i, double step, int face_additional_offset)
{
    for (int j = 0; j < shape->n3; j += step)
    {
        // Premier triangle (SW -> SE -> NW)
        normalAndVertex3dv(*shape, getSWIndex(step, i, j, shape->n3, faces_offset, face_additional_offset));
        normalAndVertex3dv(*shape, getSEIndex(step, i, j, shape->n1, shape->n3,
                                              faces_offset, face_additional_offset));
        normalAndVertex3dv(*shape, getNWIndex(i, j, faces_offset, face_additional_offset));

        // Second triangle (NW -> SE -> NE)
        drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n3,
                           faces_offset, face_additional_offset);
    }
}

static void drawFacesCone(Shape *shape, G3Xvector scale_factor, double step)
{
    glScaled(scale_factor.x, scale_factor.y, scale_factor.z);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < shape->n1; i += step)
    {
//        // Circular sides
        for (int j = 0; j < shape->n2 - 1; j += step)
        {
            drawTriangleSwSeNw(shape, step, i, j, shape->n1, shape->n2, side_offset, 0);
            drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n2, side_offset, 0);
        }

        // Bottom face
        for (int j = 0; j < shape->n3; j += step)
        {
            normalAndVertex3dv(*shape, getSWIndex(step, i, j, shape->n3, faces_offset, bottom_face_additional_offset));
            normalAndVertex3dv(*shape, getSEIndex(step, i, j, shape->n1, shape->n3,
                                                  faces_offset, bottom_face_additional_offset));
            normalAndVertex3dv(*shape, getNWIndex(i, j, faces_offset, bottom_face_additional_offset));

            // Second triangle (NW -> SE -> NE)
            drawTriangleNwSeNe(shape, step, i, j, shape->n1, shape->n3,
                               faces_offset, bottom_face_additional_offset);
        }
    }
    glEnd();
}

ShapePtr initCone()
{
    ShapePtr cone = (Shape *) malloc(sizeof(Shape));
    if (cone == NULL) { return NULL; }

    cone->n1 = NBM;
    cone->n2 = NBP;
    cone->n3 = NBC;
    unsigned int vertex_number = cone->n1 * cone->n2 + cone->n1 * cone->n3;
    if (NULL == (cone->vrtx = (G3Xpoint *) malloc(sizeof(G3Xpoint) * vertex_number)))
    {
        free(cone);
        return NULL;
    }

    if (NULL == (cone->norm = (G3Xvector *) malloc(sizeof(G3Xvector) * vertex_number)))
    {
        free(cone->vrtx);
        free(cone);
        return NULL;
    }

    cone->draw_points = drawPointsCone;
    cone->draw_faces  = drawFacesCone;
    double theta = 2 * PI / cone->n1;
    double t     = CONE_H / (cone->n2 - 1);
    double r     = CONE_R / (cone->n3 - 1);
    side_offset                   = (cone->n1 + cone->n3);
    faces_offset                  = (cone->n1 + cone->n3);
    bottom_face_additional_offset = cone->n2;

    for (int i = 0; i < cone->n1; i++)
    {
        // Circular sides
        for (int j = 0; j < cone->n2; j++)
        {
            cone->norm[i * side_offset + j] = (G3Xvector) { cos(i * theta),
                                                            sin(i * theta),
                                                            1 };

            cone->vrtx[i * side_offset + j] = (G3Xpoint) { ((CONE_H - (j * t)) / CONE_H) * CONE_R * cos(i * theta),
                                                           ((CONE_H - (j * t)) / CONE_H) * CONE_R * sin(i * theta),
                                                           (j * t) - (CONE_H / 2.) };
        }

        // Bottom face 250 -> 300
        for (int j = 0; j < cone->n3; j++)
        {
            cone->norm[i * faces_offset + bottom_face_additional_offset + j] =
                    (G3Xvector) { 0, 0, -1 };

            cone->vrtx[i * faces_offset + bottom_face_additional_offset + j] =
                    (G3Xpoint) { (j * r) * cos(i * theta),
                                 (j * r) * sin(i * theta),
                                 -CONE_H / 2. };
        }
    }

    return cone;
}
#include <assert.h>
#include "../include/node.h"

void scalef(SceneTree *node, double hx, double hy, double hz)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_Homothetie3d(hx, hy, hz));
}

void translate(SceneTree *node, double tx, double ty, double tz)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_Translation3d(tx, ty, tz));
}

double deg_to_rad(double degree)
{
    return degree * PI / 180.;
}

void rotate_x(SceneTree *node, double dx)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_RotationX(deg_to_rad(dx)));
}

void rotate_y(SceneTree *node, double dy)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_RotationY(deg_to_rad(dy)));
}

void rotate_z(SceneTree *node, double dz)
{
    assert(node != NULL);
    (*node)->Md = g3x_Mat_x_Mat((*node)->Md, g3x_RotationZ(deg_to_rad(dz)));
}

SceneTree createNode()
{
    return (Node *) malloc(sizeof(Node));
}

SceneTree createLeaf(Shape *shape)
{
    SceneTree leaf = (Node *) malloc(sizeof(Node));
    leaf->instance = shape;
    return leaf;
}

int add_child(SceneTree *father)
{
    assert(father != NULL);
    return addChildWithShapeAndColor(father, NULL, (*father)->col);
}

int addChildWithShape(SceneTree *father, Shape *shape)
{
    assert(father != NULL);
    return addChildWithShapeAndColor(father, shape, (*father)->col);
}

int addChildWithShapeAndColor(SceneTree *father, Shape *shape, G3Xcolor col)
{
    assert(father != NULL);

    SceneTree child;
    if (NULL == (*father)->down)
    {
        child = (*father)->down = (Node *) malloc(sizeof(Node));
        if (NULL == child) { return 0; }
    }
    else
    {
        SceneTree tmp = (*father)->down;
        while (NULL != tmp->next) { tmp = tmp->next; }
        child = tmp->next = (Node *) malloc(sizeof(Node));
        if (NULL == child) { return 0; }
    }

    if (shape != NULL) { child->instance = shape; }
    child->Md           = (*father)->Md;
    child->col          = col;
    child->scale_factor = (*father)->scale_factor;

    memcpy(child->mat, (*father)->mat, sizeof(float) * 4);

    return 1;
}

int add_next(SceneTree *node, SceneTree *father)
{
    assert(node != NULL);
    return addNextWithShapeAndColor(node, father, NULL, (*father)->col);
}

int addNextWithShape(SceneTree *node, SceneTree *father, Shape *shape)
{
    assert(node != NULL);
    return addNextWithShapeAndColor(node, father, shape, (*father)->col);
}

int addNextWithShapeAndColor(SceneTree *node, SceneTree *father, Shape *shape, G3Xcolor col)
{
    assert(node != NULL);
    assert(father != NULL);

    if (NULL == ((*node)->next = (Node *) malloc(sizeof(Node)))) { return 0; }
    if (shape != NULL) { (*node)->next->instance = shape; }

    (*node)->next->Md  = (*father)->Md;
    (*node)->next->col = col;
    memcpy((*node)->next->mat, (*father)->mat, sizeof(float) * 4);
    (*node)->next->scale_factor = (*father)->scale_factor;

    return 1;
}

double dist3D(G3Xvector v1, G3Xvector v2)
{
    return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2) + pow((v2.z - v1.z), 2));
}


double max(double a, double b)
{
    return a > b ? a : b;
}

void draw_node(Node *node, G3Xvector pos, G3Xhmat mat)
{
    if (node == NULL) { return; }

    g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 0.);
    glPushMatrix();
    glMultMatrixd(node->Md.m);
    if (node->instance != NULL)
    {
        double dcam = dist3D((G3Xvector) { node->Md.m[12] + mat.m[12],
                                           node->Md.m[13] + mat.m[13],
                                           node->Md.m[14] + mat.m[14] }, pos);

        double scale_balanced = (node->scale_factor.x * mat.m[0] +
                                 node->scale_factor.y * mat.m[5] +
                                 node->scale_factor.z * mat.m[10]) / 3.;

        node->instance->draw_faces(node->instance, node->scale_factor, max(1., (1. / scale_balanced) * (dcam * 0.15)));
    }
    glPopMatrix();

    draw_node(node->next, pos, mat);
    draw_node(node->down, pos, mat);
}
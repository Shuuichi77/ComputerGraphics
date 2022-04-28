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

int add_child(SceneTree *node)
{
    assert(node != NULL);

    if (NULL == ((*node)->down = (Node *) malloc(sizeof(Node)))) { return 0; }

    (*node)->down->Md  = (*node)->Md;
    (*node)->down->col = (*node)->col;
    (*node)->down->mat[0] = (*node)->mat[0];
    (*node)->down->mat[1] = (*node)->mat[1];
    (*node)->down->mat[2] = (*node)->mat[2];
    (*node)->down->mat[3] = (*node)->mat[3];
    (*node)->down->scale_factor = (*node)->scale_factor;

    return 1;
}

int add_next(SceneTree *node, SceneTree *father)
{
    assert(node != NULL);

    if (NULL == ((*node)->next = (Node *) malloc(sizeof(Node)))) { return 0; }
    if (father == NULL) { return 1; }

    (*node)->next->Md  = (*father)->Md;
    (*node)->next->col = (*father)->col;
    (*node)->next->mat[0] = (*father)->mat[0];
    (*node)->next->mat[1] = (*father)->mat[1];
    (*node)->next->mat[2] = (*father)->mat[2];
    (*node)->next->mat[3] = (*father)->mat[3];
    (*node)->next->scale_factor = (*father)->scale_factor;

    return 1;
}

void draw_node(Node *node)
{
    if (node == NULL) { return; }

    g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 0.);
    glPushMatrix();
    glMultMatrixd(node->Md.m);
    if (node->instance != NULL)
    {
//        printf("%f %f %f\n", node->Md.m[12], node->Md.m[13], node->Md.m[14]);
        node->instance->draw_faces(node->instance, node->scale_factor);
    }
    glPopMatrix();

    draw_node(node->next);
    draw_node(node->down);
}
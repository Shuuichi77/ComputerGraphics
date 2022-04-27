#include "../include/node.h"


void draw_node(Node *node)
{
    printf("1\n");
    if (node == NULL)
    {
        printf("NULL\n\n");
        return;
    }

    g3x_Material(node->col, node->mat[0], node->mat[1], node->mat[2], node->mat[3], 0.);
//    glPushMatrix(); /* ouverture de la pile OpenGl */

    // TODO : qu'est-ce que c'est ?
//    glMultMatrixd(node->Md.m); /* chargement de la matrice locale */

    /* affichage avec la bonne résolution */
    if (node->instance != NULL)
    {
        printf("2\n");
        printf("n1 = %d\n", node->instance->n1);
        node->instance->draw_faces(node->instance, node->scale_factor);
    }
    else
    {
        printf("instance is NULL\n");
    }
//    glPopMatrix();  /* déchargement & fermeture de la pile */

//    draw_node(node->next);
//    draw_node(node->down);
}
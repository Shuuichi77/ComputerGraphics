#include "../include/cube.h"
#include "../include/node.h"
#include "../include/floor.h"

int init_first_pair(SceneTree *father, Shape *cube, int nb_pair)
{
    if (!add_child(father)) { return 0; }
    (*father)->down->instance = cube;
    (*father)->down->col      = dark_grey;
    translate(&(*father)->down, (nb_pair % 2) ? 0 : floor_length, floor_length * (nb_pair - 1), -floor_height);

    if (!add_next(&(*father)->down, father)) { return 0; }
    (*father)->down->next->instance = cube;
    (*father)->down->next->col      = light_grey;
    translate(&(*father)->down->next, (nb_pair % 2) ? floor_length : 0, floor_length * (nb_pair - 1), -floor_height);

    return 1;
}

int init_next_pairs(SceneTree *father, SceneTree *next, Shape *cube, int nb_pair)
{
    if (nb_pair == 0) { return 1; }

    if (!add_next(next, father)) { return 0; }
    (*next)->next->instance = cube;
    (*next)->next->col      = dark_grey;
    translate(&(*next)->next, (nb_pair % 2) ? 0 : floor_length, floor_length * (nb_pair - 1), -floor_height);

    if (!add_next(&(*next)->next, father)) { return 0; }
    (*next)->next->next->instance = cube;
    (*next)->next->next->col      = light_grey;
    translate(&(*next)->next->next, (nb_pair % 2) ? floor_length : 0, floor_length * (nb_pair - 1), -floor_height);

    return init_next_pairs(father, &(*next)->next->next, cube, nb_pair - 1);
}

int init_tiles(SceneTree *father, Shape *cube, int nb_pair)
{
    if (nb_pair == 0) { return 1; }
    if (!init_first_pair(father, cube, nb_pair)) { return 0; }

    if (nb_pair - 1 == 0) { return 1; }
    return init_next_pairs(father, &(*father)->down->next, cube, nb_pair - 1);
}

int init_floor(SceneTree *floor, Shape *cube)
{
    if (((*floor) = (Node *) malloc(sizeof(Node))) == NULL) { return 0; }
    (*floor)->mat[0] = 0.25;
    (*floor)->mat[1] = 0.5;
    (*floor)->mat[2] = 0.0;
    (*floor)->mat[3] = 1.;
    (*floor)->scale_factor = (G3Xvector) { FLOOR_X, FLOOR_Y, FLOOR_Z };
    (*floor)->Md           = g3x_Identity();

    return init_tiles(floor, cube, NB_PAIR_TILES);
}




#include "../include/cube.h"
#include "../include/node.h"
#include "../include/stool.h"

int init_stool_leg(SceneTree *father, SceneTree *next, Shape *cube, int leg_num)
{
    if (leg_num == 4) { return 1; }

    if (leg_num == 0)
    {
        if (!add_child(father)) { return 0; }
        (*father)->down->instance = cube;
        translate(&(*father)->down, stool_length * 0.5, stool_width * 0.5, 0);
        return init_stool_leg(father, &(*father)->down, cube, leg_num + 1);
    }
    else
    {
        if (!add_next(next, father)) { return 0; }
        (*next)->next->instance = cube;
        if (leg_num == 1) { translate(&(*next)->next, stool_length * 0.5, -stool_length * 0.5, 0); }
        else if (leg_num == 2) { translate(&(*next)->next, -stool_length * 0.5, stool_length * 0.5, 0); }
        else if (leg_num == 3) { translate(&(*next)->next, -stool_length * 0.5, -stool_length * 0.5, 0); }
        return init_stool_leg(father, &(*next)->next, cube, leg_num + 1);
    }
}


int init_stool_legs(SceneTree *stool, SceneTree *desk, Shape *cylinder)
{
    if (!add_next(desk, stool)) { return 0; }

    double leg_width = (stool_length + stool_width) * 0.05;
    (*desk)->next->col          = dark_yellow;
    (*desk)->next->scale_factor = (G3Xvector) { leg_width,
                                                leg_width,
                                                STOOL_LEG_Z };
    translate(&(*desk)->next, -leg_width, -leg_width, 0.);
    return init_stool_leg(&(*desk)->next, NULL, cylinder, 0);
}

int init_stool_desk(SceneTree *stool, Shape *cylinder)
{
    if (!add_child(stool)) { return 0; }
    (*stool)->down->instance     = cylinder;
    (*stool)->down->col          = dark_brown;
    (*stool)->down->scale_factor = (G3Xvector) { STOOL_X, STOOL_Y, STOOL_Z };
    translate(&(*stool)->down, 0, 0, stool_leg_height + stool_height);

    return 1;
}

int init_stool(SceneTree *stool, Shape *cube, Shape *cylinder)
{
    if (((*stool) = (Node *) malloc(sizeof(Node))) == NULL) { return 0; }
    (*stool)->mat[0] = 0.25;
    (*stool)->mat[1] = 0.5;
    (*stool)->mat[2] = 0.0;
    (*stool)->mat[3] = 1.;
    (*stool)->Md = g3x_Identity();

    return init_stool_desk(stool, cylinder) && init_stool_legs(stool, &(*stool)->down, cube);
}




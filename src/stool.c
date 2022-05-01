#include "../include/stool.h"

double const STOOL_X     = 0.5;
double const STOOL_Y     = STOOL_X;
double const STOOL_Z     = 0.1;
double const STOOL_LEG_Z = 0.4;

double const stool_length = STOOL_X * CYLINDER_R;
double const stool_width  = STOOL_Y * CYLINDER_R;
double const stool_height = STOOL_Z * CYLINDER_R;

double const stool_leg_height = STOOL_LEG_Z * CUBE_W;
double const stool_leg_width  = (stool_length + stool_width) * 0.05;

static int initStoolLeg(SceneTree *legs, Shape *cube, int leg_num)
{
    if (leg_num == 4) { return 1; }

    SceneTree leg = addChildWithShape(legs, cube);
    if (leg == NULL) { return 0; }

    switch (leg_num)
    {
        case 0:applyTranslate(&leg, stool_length * 0.5, stool_width * 0.5, 0);
            break;
        case 1:applyTranslate(&leg, stool_length * 0.5, -stool_length * 0.5, 0);
            break;
        case 2:applyTranslate(&leg, -stool_length * 0.5, stool_length * 0.5, 0);
            break;
        case 3:applyTranslate(&leg, -stool_length * 0.5, -stool_length * 0.5, 0);
            break;
    }

    return initStoolLeg(legs, cube, leg_num + 1);
}

static int initStoolLegs(SceneTree *stool, Shape *cube)
{
    SceneTree stoolLegs = addChildWithColor(stool, dark_yellow);

    if (stoolLegs == NULL) { return 0; }
    stoolLegs->scale_factor = (G3Xvector) { stool_leg_width,
                                            stool_leg_width,
                                            STOOL_LEG_Z };
    applyTranslate(&stoolLegs, -stool_leg_width, -stool_leg_width, 0.);
    return initStoolLeg(&stoolLegs, cube, 0);
}

static int initStoolDesk(SceneTree *stool, Shape *cylinder)
{
    SceneTree stoolDesk = addChildWithShapeAndColor(stool, cylinder, dark_brown);

    if (stoolDesk == NULL) { return 0; }
    stoolDesk->scale_factor = (G3Xvector) { STOOL_X, STOOL_Y, STOOL_Z };
    applyTranslate(&stoolDesk, 0, 0, stool_leg_height + stool_height);

    return 1;
}

SceneTree initStool(Shape *cube, Shape *cylinder)
{
    SceneTree stool = createNode();
    if (stool == NULL) { return NULL; }

    if (!initStoolDesk(&stool, cylinder) || !initStoolLegs(&stool, cube))
    {
        freeNode(&stool);
        return NULL;
    }

    return stool;
}




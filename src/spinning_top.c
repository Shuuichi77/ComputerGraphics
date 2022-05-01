#include "../include/spinning_top.h"

double const STICK_X = 0.04 / 3.;
double const STICK_Y = STICK_X;
double const STICK_Z = 1 / 3.;

double const GLOBE_X = 0.10;
double const GLOBE_Y = GLOBE_X;
double const GLOBE_Z = GLOBE_X;

double const TORUS_X = GLOBE_X;
double const TORUS_Y = TORUS_X;
double const TORUS_Z = TORUS_X;

double const stick_height = STICK_Z * CYLINDER_H;

static int initStick(SceneTree *spinning_top, Shape *cylinder)
{
    SceneTree stick = addChildWithShape(spinning_top, cylinder);
    if (stick == NULL) { return 0; }
    stick->scale_factor = (G3Xvector) { STICK_X, STICK_Y, STICK_Z };
    applyTranslate(&stick, 0, 0, STICK_Z);

    return 1;
}

static int initGlobe(SceneTree *spinning_top, Shape *sphere)
{
    SceneTree globe = addChildWithShape(spinning_top, sphere);
    if (globe == NULL) { return 0; }
    globe->scale_factor = (G3Xvector) { GLOBE_X, GLOBE_Y, GLOBE_Z };
    applyTranslate(&globe, 0, 0, stick_height / 4.);

    return 1;
}

static int initRing(SceneTree *spinning_top, Shape *torus)
{
    SceneTree ring = addChildWithShape(spinning_top, torus);
    if (ring == NULL) { return 0; }
    ring->scale_factor = (G3Xvector) { TORUS_X, TORUS_Y, TORUS_Z };
    applyTranslate(&ring, 0, 0, stick_height / 4.);

    return 1;
}

SceneTree initSpinningTop(Shape *cylinder, Shape *sphere, Shape *torus)
{
    SceneTree spinning_top = createNode();

    if (spinning_top == NULL) { return 0; }
    spinning_top->col = light_grey;

    if (!initStick(&spinning_top, cylinder) ||
        !initGlobe(&spinning_top, sphere) ||
        !initRing(&spinning_top, torus))
    {
        freeNode(&spinning_top);
        return NULL;
    }
    return spinning_top;
}




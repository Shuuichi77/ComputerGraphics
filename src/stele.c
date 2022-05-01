#include "../include/stele.h"

double const PEDESTAL_X = 1. / 3.;
double const PEDESTAL_Y = PEDESTAL_X;
double const PEDESTAL_Z = 0.15;

double const TOWER_X = PEDESTAL_X / 3.;
double const TOWER_Y = TOWER_X;
double const TOWER_Z = 1;

double const TOWER_RING_X = TOWER_X;
double const TOWER_RING_Y = TOWER_RING_X;
double const TOWER_RING_Z = TOWER_RING_X;

double const pedestal_length = PEDESTAL_X * CUBE_W;
double const pedestal_width  = PEDESTAL_Y * CUBE_W;
double const pedestal_height = PEDESTAL_Z * CUBE_W;

double const tower_radius      = TOWER_X * CYLINDER_R;
double const tower_height      = TOWER_Z * CYLINDER_H;
double const tower_ring_height = TOWER_RING_Z * 0.2;

static int initPedestal(SceneTree *stele, Shape *cube)
{
    SceneTree pedestal = addChildWithShape(stele, cube);
    if (pedestal == NULL) { return 0; }
    pedestal->scale_factor = (G3Xvector) { PEDESTAL_X, PEDESTAL_Y, PEDESTAL_Z };
    applyTranslate(&pedestal, -pedestal_length / 2., -pedestal_width / 2., 0);

    return 1;
}

static int initTower(SceneTree *stele, Shape *cylinder)
{
    SceneTree tower = addChildWithShape(stele, cylinder);
    if (tower == NULL) { return 0; }
    tower->scale_factor = (G3Xvector) { TOWER_X, TOWER_Y, TOWER_Z };
    applyTranslate(&tower, 0, 0, pedestal_height + tower_height / 2.);

    return 1;
}

static int initTowerRing(SceneTree *stele, Shape *torus)
{
    SceneTree tower_ring = addChildWithShape(stele, torus);
    if (tower_ring == NULL) { return 0; }
    tower_ring->scale_factor = (G3Xvector) { TOWER_RING_X, TOWER_RING_Y, TOWER_RING_Z };
    applyTranslate(&tower_ring, 0, 0, pedestal_height + tower_ring_height / 2.);

    return 1;
}

SceneTree initStele(Shape *cube, Shape *cylinder, Shape *torus)
{
    SceneTree stele = createNode();

    if (stele == NULL) { return NULL; }
    stele->col = light_grey;

    if (!initPedestal(&stele, cube) ||
        !initTower(&stele, cylinder) ||
        !initTowerRing(&stele, torus))
    {
        freeNode(&stele);
        return NULL;
    }

    return stele;
}




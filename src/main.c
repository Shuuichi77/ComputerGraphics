#include <g3x.h>
#include <time.h>

#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"

#include "../include/floor.h"
#include "../include/stool.h"
#include "../include/spinning_top.h"
#include "../include/stele.h"
#include "../include/table.h"

static G3Xpoint TARGET;

static int NB_PAIR_STELE = 2;
static int *random_radius;

static int   WWIDTH = 512, WHEIGHT = 512;
static Shape *cube;
static Shape *cylinder;
static Shape *sphere;
static Shape *spinning_top_torus;
static Shape *stele_torus;

static Node *floor_tiles;
static Node *table;
static Node *stool;

static Node *spinning_top;
static Node *stele;

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
    srand(time(0));

    if (NULL == (random_radius = (int *) malloc(sizeof(int) * NB_PAIR_STELE * 2)))
    {
        fprintf(stderr, "Error in random_radius malloc\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NB_PAIR_STELE * 2; i++)
    {
        random_radius[i] = rand();
    }

    /* Call each init function only 1 time : we'll then use an instance of each shape */
    /* ----------------------------------------------- */
    if (!init_cube(&cube))
    {
        fprintf(stderr, "Error in init_cube() malloc\n");
        exit(EXIT_FAILURE);
    }
    if (!init_cylinder(&cylinder))
    {
        fprintf(stderr, "Error in init_cylinder() malloc\n");
        exit(EXIT_FAILURE);
    }
    if (!init_sphere(&sphere))
    {
        fprintf(stderr, "Error in init_sphere() malloc\n");
        exit(EXIT_FAILURE);
    }

    double spinning_top_torus_radius = 0.2;
    if (!init_torus(&spinning_top_torus,
                    SPHERE_R * spinning_top_torus_radius,
                    SPHERE_R * (1 + spinning_top_torus_radius)))
    {
        fprintf(stderr, "Error in init_torus() malloc\n");
        exit(EXIT_FAILURE);
    }

    double stele_torus_radius = 0.1;
    if (!init_torus(&stele_torus,
                    CYLINDER_R * stele_torus_radius,
                    CYLINDER_R * (1 + stele_torus_radius)))
    {
        fprintf(stderr, "Error in init_torus() malloc\n");
        exit(EXIT_FAILURE);
    }
    /* ----------------------------------------------- */

    if (!init_floor(&floor_tiles, cube))
    {
        fprintf(stderr, "Error in init_floor() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_stool(&stool, cube, cylinder))
    {
        fprintf(stderr, "Error in init_stool() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_table(&table, cube, cylinder))
    {
        fprintf(stderr, "Error in init_table() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_spinning_top(&spinning_top, cylinder, sphere, spinning_top_torus))
    {
        fprintf(stderr, "Error in init_spinning_top() malloc\n");
        exit(EXIT_FAILURE);
    }

    if (!init_stele(&stele, cube, cylinder, stele_torus))
    {
        fprintf(stderr, "Error in init_stele() malloc\n");
        exit(EXIT_FAILURE);
    }
    /* ----------------------------------------------- */
}


static void camera_info(void)
{
    G3Xcamera *cam = g3x_GetCamera();
    fprintf(stderr, "position (x:%lf,y:%lf,z:%lf)\n", cam->pos->x, cam->pos->y, cam->pos->z);
    fprintf(stderr, "cible    (x:%lf,y:%lf,z:%lf)\n", cam->tar->x, cam->tar->y, cam->tar->z);
    fprintf(stderr, "coord. spheriques (d:%lf,theta:%lf,phi:%lf)\n", cam->dist, cam->theta, cam->phi);
}

static void ctrl(void)
{
    g3x_CreateScrollv_d("step", &step, 1, 10, 1, "Pas de rendu");
    g3x_SetKeyAction('c', camera_info, "pos./dir. de la camera => terminal");

    g3x_CreateScrollv_d("x", &(g3x_GetCamera())->tar->x, -10, 20, 1, "x");
    g3x_CreateScrollv_d("y", &(g3x_GetCamera())->tar->y, -10, 20, 1, "y");
    g3x_CreateScrollv_d("z", &(g3x_GetCamera())->tar->z, -10, 20, 1, "z");
    g3x_CreateScrollv_d("dist", &(g3x_GetCamera()->dist), 1, 20, 1, "dist");

    g3x_CreateScrollh_d("Target.z", &(TARGET).z, -10, 20, 1, "z");
    g3x_CreateScrollh_d("Target.y", &(TARGET).y, -10, 20, 1, "y");
    g3x_CreateScrollh_d("Target.x", &(TARGET).x, -10, 20, 1, "x");
}

static void draw_stool_on_desk(void)
{
    glPushMatrix();
    draw_node(table);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 1., 0., 0.);
    glTranslatef(desk_length * 0.05, -desk_width * 0.3, -2 * (leg_height + desk_height + floor_height) + desk_height);
    draw_node(stool);
    glPopMatrix();
}

static void draw_desks_and_stools(void)
{
    glPushMatrix();
    glTranslatef(-floor_length, -floor_length, 0.);
    draw_node(floor_tiles);
    glPopMatrix();

    glPushMatrix();
    glRotatef(135, 0., 0., 1.);
    glTranslatef(0, floor_length * 0.7, 0.);
    draw_stool_on_desk();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-floor_length * 0.5, floor_length * 0.5, 0.);
    draw_node(stool);
    glPopMatrix();

    glPushMatrix();
    glRotatef(130, 0., 0., 1.);
    glTranslatef(-floor_length * 0.7, 0, 0.);
    draw_node(table);
    glPopMatrix();
}

static void draw_spinning_top_on_stele(int radius_num)
{
    int radius = random_radius[radius_num];
    glPushMatrix();
    draw_node(stele);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0., 0., pedestal_height + tower_height);
    glRotatef(((radius % 2) ? -radius : radius) % 45, 1., 0., 0.);
    glRotatef(((radius % 2) ? -radius : radius) % 45, 0., 1., 0.);
    draw_node(spinning_top);
    glPopMatrix();
}

static void draw_pair_spinning_top_on_stele(int n)
{
    glPushMatrix();
    glTranslatef(floor_length + pedestal_length / 2., floor_length * n, 0.);
    draw_spinning_top_on_stele(n);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-floor_length - pedestal_length / 2., floor_length * n, 0.);
    draw_spinning_top_on_stele(n + 1);
    glPopMatrix();
}

static void draw_steles_scene()
{
    glPushMatrix();
    glScaled(0.25, 0.25, 0.25);
    for (int i = 0; i < NB_PAIR_STELE; i++)
    {

        if (i < NB_PAIR_STELE / 2)
        {
            glPushMatrix();
            glTranslatef(-floor_length, i * 2 * floor_length - floor_length / 2., 0.);
            draw_node(floor_tiles);
            glPopMatrix();
        }

        glPushMatrix();
        draw_pair_spinning_top_on_stele(i);
        glPopMatrix();
    }
    glPopMatrix();
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
    g3x_SetCameraTar(TARGET);

    glPointSize(3);
    draw_node(table);

    glTranslatef(2, 2, 0.);
    draw_node(table);


//    glPointSize(3);
//    draw_desks_and_stools();

//    glPointSize(3);
//    draw_steles_scene();
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS ou presque                    */
/***************************************************************************/
int main(int argc, char **argv)
{
    /* creation de la fenetre - titre et tailles (pixels) */
    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);
    g3x_SetInitFunction(init); /*² fonction d'initialisation */
    g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
    g3x_SetDrawFunction(draw); /* fonction de dessin        */
    g3x_SetAnimFunction(anim); /* fonction d'animation      */
    g3x_SetExitFunction(quit); /* fonction de sortie        */

    /* lancement de la boucle principale */
    return g3x_MainStart();
    /* RIEN APRES CA */
}

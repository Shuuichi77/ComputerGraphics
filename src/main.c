#include <g3x.h>
#include "cube.c"
#include "cylinder.c"
#include "sphere.c"
#include "torus.c"

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;


/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{

}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
    g3x_CreateScrollv_d("step", &step, 1, 10, 1, "Pas de rendu");
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
    glPointSize(10);
    draw_sphere((G3Xvector) { 1, 1, 1 });

    glTranslatef(2, 0, 0.);
    draw_cylinder((G3Xvector) { 1, 1, 1 });

    glTranslatef(0, 3, 0.);
    draw_torus((G3Xvector) { 1, 1, 1 });

    glTranslatef(-4, -2, 0.);
    draw_cube((G3Xvector) { 1, 1, 1 });
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
    printf("1");
    /* creation de la fenetre - titre et tailles (pixels) */
    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);

    g3x_SetCameraSpheric(0., 0.25 * PI, 18., (G3Xpoint) { 0., 0., 0. });

    g3x_SetInitFunction(init); /* fonction d'initialisation */
    g3x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
    g3x_SetDrawFunction(draw); /* fonction de dessin        */
    g3x_SetAnimFunction(anim); /* fonction d'animation      */
    g3x_SetExitFunction(quit); /* fonction de sortie        */

    /* lancement de la boucle principale */
    return g3x_MainStart();
    /* RIEN APRES CA */
}

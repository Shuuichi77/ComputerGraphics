#include <g3x.h>
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"


/* tailles de la fenêtre (en pixel) */
extern double step;
static int    WWIDTH = 512, WHEIGHT = 512;
static Shape  cube;
static Shape  cylinder;
static Shape  sphere;
static Shape  torus;

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
    cube     = init_cube();
    cylinder = init_cylinder();
    sphere   = init_sphere();
    torus    = init_torus();
}

/* la fonction de contrôle : appelée 1 seule fois, juste après <init> */
static void ctrl(void)
{
    g3x_CreateScrollv_d("step", &step, 1, 10, 1, "Pas de rendu");
}

static void table()
{

}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
    printf("\n\nMAIN STEP = %f\n", step);
    glPointSize(10);
    glRotatef(90, 1., 0., 0.);    /* une rotation autour de l'axe 'x' */
    sphere.draw_faces(&sphere, (G3Xvector) { 1, 1, 1 });

    glTranslatef(2, 0, 0.);
    cylinder.draw_faces(&cylinder, (G3Xvector) { 1, 1, 1 });

    glTranslatef(0, 3, 0.);
    torus.draw_faces(&torus, (G3Xvector) { 1, 1, 1 });

    glTranslatef(-4, -2, 0.);
    cube.draw_faces(&cube, (G3Xvector) { 1, 1, 1 });

    glTranslatef(-4, -2, 0.);
    cube.draw_faces(&cube, (G3Xvector) { 0.5, 0.5, 0.5 });

    glTranslatef(2, 0, 0.);
    cube.draw_faces(&cube, (G3Xvector) { 2, 2, 2 });


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

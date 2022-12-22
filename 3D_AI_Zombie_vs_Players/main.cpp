#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
//IMPORTANT polygons MUST be drawn counter-clockwise
//design using https://technology.cpm.org/general/3dgraph/

class fPerson{//TODO create first person shooter with shooting animation
public:
    int direction;
    //notes please don't touch
    static void drawLeftArm()
    {
        glPushMatrix();
        glColor3f(0,0.9,0);
        glCullFace(GL_NONE);
        glBegin(GL_POLYGON);
        glVertex3d(2,4,-2);
        glVertex3d(-2,4,-2);
        glVertex3d(-2,4,2);
        glVertex3d(2,4,2);
        glEnd();


        glPopMatrix();
    }


};

//NOTICE nice to do's are super hard to accomplish don't waste time on those if you don't have it

class zombie{//TODO create zombie draw function
public:
    //notes drawing the face with

    //nice to do's u can use a texture as the face of the zombie instead of drawing yourself
    //but i couldn't find enough resources that teach that

    //          ||
    //        \ || /
    //checkout \  /
    //          \/
    //https://www.youtube.com/watch?v=dV1E8vzoGb0
    //https://community.khronos.org/t/loading-a-bitmap-image-to-use-it-as-a-texture-background-on-canvas-for-drawing/72323

};
class tree{//TODO create tree draw function
public:
    //notes drawing a cone manually is gonna be hard or impossible i tried with the cylinder
    //construct the tree out of pyramids instead

    ////nice to do's same as the above
};
float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
float x=0;
//------------------------------  reshapeFunc  ---------------------------------

void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (GLdouble)w / (GLdouble)h, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

//------------------------------  display   -------------------------------

void display (void)
{

    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glTranslatef    (0.0, 0.0, -20.0);
    glRotated(x,1,0,0);
	//Your code is written here
    fPerson::drawLeftArm();//replace this with the draw function you want to test
    x+=0.1;
    glutSwapBuffers();
}

//--------------------------------  idleFunc  ----------------------------------

void idleFunc (void)
{
    zRotated += 1;
    glutPostRedisplay();
}

void texture (void){

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


}

//----------------------------------  main  ------------------------------------


int main (int argc, char **argv)
{
    glutInit               (&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // buffer mode
    glutInitWindowSize     (800, 700);
    glutInitWindowPosition (700, 200);
    glutCreateWindow       ("Sphere Rotating Animation");

    glClearColor (1.0, 1.0, 1.0, 0.0);

    glutDisplayFunc (display);
    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);

    glClearColor(1,1,1,1);
    texture(); // Lighting and textures


    glutMainLoop();
}

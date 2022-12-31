#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
//IMPORTANT polygons MUST be drawn counter-clockwise
//design using https://technology.cpm.org/general/3dgraph/
void keyboard(unsigned char key,int x,int y);

class basicShapes{
//NOTICE any basic shapes are drawn here then scaled to desired size DON'T draw basic shapes manually inside game classes
public:
    static void cuboid(double width=1.0,double length=1.0,double height=1.0){
        glPushMatrix();
        glScaled(width,height,length);
        //glCullFace(GL_NONE);
        //top
        glBegin(GL_POLYGON);
        glVertex3d(1,1,-1);
        glVertex3d(-1,1,-1);
        glVertex3d(-1,1,1);
        glVertex3d(1,1,1);
        glEnd();

        //bottom
        glBegin(GL_POLYGON);
        glVertex3d(1,-1,1);
        glVertex3d(-1,-1,1);
        glVertex3d(-1,-1,-1);
        glVertex3d(1,-1,-1);
        glEnd();

        //front
        glBegin(GL_POLYGON);
        glVertex3d(1,1,1);
        glVertex3d(-1,1,1);
        glVertex3d(-1,-1,1);
        glVertex3d(1,-1,1);
        glEnd();

        //rear
        glBegin(GL_POLYGON);
        glVertex3d(-1,1,-1);
        glVertex3d(1,1,-1);
        glVertex3d(1,-1,-1);
        glVertex3d(-1,-1,-1);
        glEnd();

        //right
        glBegin(GL_POLYGON);
        glVertex3d(1,1,-1);
        glVertex3d(1,1,1);
        glVertex3d(1,-1,1);
        glVertex3d(1,-1,-1);
        glEnd();

        //right
        glBegin(GL_POLYGON);
        glVertex3d(-1,1,1);
        glVertex3d(-1,1,-1);
        glVertex3d(-1,-1,-1);
        glVertex3d(-1,-1,1);
        glEnd();

        glPopMatrix();
    }
    static void pyramids(double baselength=1.0, double basewidth=1.0, double pyheight=1.0){
     glPushMatrix();
     glScaled(baselength,basewidth,pyheight);

      //front
      glBegin(GL_TRIANGLES);
      glVertex3f( 0, 2, 0);
      glVertex3f(-2, -2, 1);
      glVertex3f(2, -2, 1);
      glEnd();

      // Right
      glBegin(GL_TRIANGLES);
      glVertex3f(0, 2, 0);
      glVertex3f(2, -2, 1);
      glVertex3f(1.5, -2, -1);
      glEnd();

      //left
      glBegin(GL_TRIANGLES);
      glColor3f(0,0.5,0.1);
      glVertex3f(0, 2, 0);
      glVertex3f(-2.5, -2, -1);
      glVertex3f(-2, -2, 1);
      glEnd();

      //back
      glBegin(GL_TRIANGLES);
      glVertex3f(0, 2, 0);
      glVertex3f(-2.5, -2, -1);
      glVertex3f(-2, -2, 1);
      glEnd();

      glPopMatrix();
      }
      static void shperes(double radius = 1.0)
      {
       glPushMatrix ();
       glScaled(radius,1,1);
       glutSolidSphere (1.0, 5, 30);
       glPopMatrix ();

      }
};

bool right=false,left=false,forw=false,backw=false;
double movX=0,movZ=0;

//Key usage to Esc or Fullscreen
void keyboard(unsigned char key,int x,int y)
{
    if(key == 27)
        exit(0);
    else if(key == 'f')
        glutFullScreen();

    if(key=='w'){
        forw=true;
    }
    else if(key == 's'){
        backw=true;
    }
    else if(key == 'd'){
        right=true;
    }
    else if(key == 'a'){
        left=true;
    }
}
// Unclicked keys
void keyboardUp(unsigned char key,int x,int y){

    if(key=='w'){
        forw=false;
    }
    else if(key == 's'){
        backw=false;
    }
    else if(key == 'd'){
        right=false;
    }
    else if(key == 'a'){
        left=false;
    }
}

class fPerson{//TODO create first person shooter with shooting animation
public:
    int direction;
    static void drawLeftArm()
    {

        glPushMatrix();
        glTranslated(0,-0.5,18.5);
        //left arm
        glPushMatrix();
        glColor3f(0,0.9,0);

        glTranslated(-0.3,0,0);
        glRotated(80,-1,0,0);
        glRotated(20,0,0,-1);

        basicShapes::cuboid(0.125,0.125,0.6);
        glPopMatrix();

        //right arm
        glPushMatrix();
        glColor3f(0,0.6,0);

        glTranslated(0.3,0,0);
        glRotated(80,-1,0,0);
        glRotated(20,0,0,1);

        basicShapes::cuboid(0.125,0.125,0.6);
        glPopMatrix();

        glPopMatrix();


        glPushMatrix();
        //glTranslated(0,0.5,-18.5);

        glTranslated(0,-0.5,18.5);
        //glPushMatrix();
        //glTranslated(0,0.5,-18.5);
        //glRotated(0,0,1,0);
        //glTranslated(0,-0.5,18.5);
        //gun handle
        glPushMatrix();
        glColor3f(0.2,0.2,0.2);
        glTranslated(0,0,-0.5);
        glRotated(5,-1,0,0);
        basicShapes::cuboid(0.05,0.05,0.15);
        glPopMatrix();

        //gun barrel
        glPushMatrix();
        glColor3f(0.2,0.2,0.2);
        glTranslated(0,0.2,-0.6);
        glRotated(90,-1,0,0);
        basicShapes::cuboid(0.05,0.05,0.25);
        glPopMatrix();
        //glPopMatrix();
        glPopMatrix();
    }


};

//NOTICE nice to do's are super hard to accomplish don't waste time on those if you don't have it

class zombie
{
//TODO create zombie draw function
public:
    //int speed;

    static void drawZ()
    {
        zombie::drawhead();
        zombie::Body();
        zombie::leftLeg();
        zombie::rightLeg();
    }

    //Drawing head
    static void drawhead()
    {
        glPushMatrix();
        glColor3f(0,0.7,0);
        glTranslated(0,0.1,0);
        glRotated(45,0,1,0);
        basicShapes::cuboid(0.7,0.7,0.7);
        glPopMatrix();

    }
    //Drawing the body
    static void Body()
    {
        glPushMatrix();
        glColor3f(0,0.9,0);
        glTranslated(0,-2.2,0);
        glRotated(45,0,1,0);
        basicShapes::cuboid(0.5,1.2,1.5);
        glPopMatrix();
    }

    //Drawing th left leg
    static void leftLeg()
    {

        glPushMatrix();
        glColor3f(0,0.5,0);
        glTranslated(-0.2,-3.7,0);
        glRotated(45,0,1,0);
//      basicShapes::cuboid(0.4,0.2,0.4);
        basicShapes::cuboid(0.2,0.4,0.5);
        glPopMatrix();

    }

    //Drawing the right leg
    static void rightLeg()
    {

        glPushMatrix();
        glColor3f(0,0.5,0);
        //glTranslated(0.5,-3.7,2.9);
        glTranslated(0.5,-3.7,0);
        glRotated(45,0,1,0);
        //basicShapes::cuboid(0.4,0.2,0.5);
        basicShapes::cuboid(0.2,0.4,0.5);
        glPopMatrix();

    }
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
//To draw zombie snowman
class zombieSnowMan{
public:
    static void drawSnowMan()
    {
        basicShapes::shperes(1);
    }
};

class tree{//TODO create tree draw function
public:
    //notes drawing a cone manually is gonna be hard or impossible i tried with the cylinder
    //construct the tree out of pyramids instead
    //code the pyramid inside basicShapes class in a separate function
    static void drawtree()
    {
        tree::drawtreestem();
        tree::drawfirstlayer();
        tree::drawsecondlayer();
        tree::drawthirdlayer();

    }
    ////nice to do's same as thcaan;t talk e above
    static void drawtreestem()
    {
      glPushMatrix();
      glColor3f(0.4,0.2,0);
      glTranslatef(10,-3,0);
      basicShapes::cuboid(0.3,0.5,0.5);
      glPopMatrix();
    }
   static void drawfirstlayer(){
      glPushMatrix();
      glColor3f(0,0.6,0 );
      glTranslatef(10,-1.5,0);
      basicShapes::pyramids(1.0,0.5,1.0);
      glPopMatrix();
   }
  static void drawsecondlayer(){
      glPushMatrix();
      glColor3f(0,0.6,0 );
      glTranslatef(10,-0.9,0);
      basicShapes::pyramids(1.0,0.5,1.0);
      glPopMatrix();
   }
   static void drawthirdlayer(){
      glPushMatrix();
      glColor3f(0,0.6,0 );
      glTranslatef(10,0.3,0);
      basicShapes::pyramids(0.9,0.8,0.8);
      glPopMatrix();
   }
};
float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
float x=0;
//------------------------------  reshapeFunc  ---------------------------------

void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60.0, (GLdouble)w / (GLdouble)h, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

//------------------------------  display   -------------------------------

void display (void)
{

    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(100.0/255.0,128.0/255.0,122.0/255.0,0.0);
    //glClearColor(130,128,122);
    glLoadIdentity ();
    glTranslatef    (0.0, 0.0, -20.0);
    //glRotated(x,1,1,0);
	//Your code is written here
    fPerson::drawLeftArm();//replace this with the draw function you want to test

    glPushMatrix();
    //calculate position
    if(left==true)  movX+=0.1;
    if(right==true) movX-=0.1;
    if(forw==true)  movZ+=0.1;
    if(backw==true) movZ-=0.1;

    glTranslatef    (movX, 0.0, movZ);
    //Drawing the zombie
    zombie::drawZ();
    //zombieSnowMan::drawSnowMan(2);
    tree::drawtree();
    glPopMatrix();
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
    glutCreateWindow       ("Zombie vs Player");

    glClearColor (1.0, 1.0, 1.0, 0.0);

    glutDisplayFunc (display);
    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);
    glClearColor(1,1,1,1);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    texture(); // Lighting and textures


    glutMainLoop();
}
/* tree::drawtreestem();
    tree::drawfirstlayer();
    tree::drawsecondlayer();
    tree::drawthirdlayer();*/

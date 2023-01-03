#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <mmsystem.h>
#include <stdlib.h>

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
     glVertex3f(0,2,0);
     glVertex3f(-2.5,-2,-1);
     glVertex3f(-2,-2,1);
     glEnd();


      //back
      glBegin(GL_TRIANGLES);
      glVertex3f(0, 2, 0);
      glVertex3f(2, -2, -1);
      glVertex3f(-2.5, -2, -1);

      glEnd();

      glPopMatrix();
      }
      //Draw Sphere mainly for the moon
     static void shperes(double radius = 1.0)
      {
       glPushMatrix ();
       glScaled(radius,radius,radius);
       glutSolidSphere (20.0, 50, 50);
       glPopMatrix ();
      }

};

bool right=false,left=false,forw=false,backw=false,rotR=false,rotL=false;
double movX=0,movZ=0,rotAngle=0,rotangleZombie =0,hitColor=0;
int flag = 0;
//Calculate Distance between zombie and player
double calcDistance(double x1,double z1,double x2,double z2)
{
    return sqrt(pow((x1-x2),2)+pow((z1-z2),2));
}
//Key input
void specialKey(int key,int x,int y){

    if(key == GLUT_KEY_LEFT)rotL=true;
    if(key == GLUT_KEY_RIGHT)rotR=true;

}

void specialKeyUp(int key,int x,int y){
    if(key == GLUT_KEY_LEFT)rotL=false;
    if(key == GLUT_KEY_RIGHT)rotR=false;
}

void keyboard(unsigned char key,int x,int y)
{
     //Close Esc
     if(key == 27)
        exit(0);
     //Full Screen
     if(key == 'f')
        glutFullScreen();

     if(key=='w')
     {
        forw=true;
     }
     if(key == 's')
     {
        backw=true;
     }
     if(key == 'd')
     {
       right=true;
     }
     if(key == 'a')
     {
       left=true;
     }
     //Sound shooting
     if(key == ' ')
     {
       sndPlaySound("sound.wav",SND_ASYNC);
       flag = 1;
     }
}
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

class fPerson
{//TODO create first person shooter with shooting animation
public:
    static int health;
    static void drawLeftArm()
    {

        glPushMatrix();
        glTranslated(0,-0.5,-1.5);
        //left arm
        glPushMatrix();
        if(hitColor > 0)
        {
            glColor3f(0.9,0,0);
            hitColor--;
        }
        else
        {
            glColor3f(0,0.9,0);
        }


        glTranslated(-0.3,0,0);
        glRotated(80,-1,0,0);
        glRotated(20,0,0,-1);

        basicShapes::cuboid(0.125,0.125,0.6);
        glPopMatrix();

        //right arm
        glPushMatrix();
        glTranslated(0.3,0,0);
        glRotated(80,-1,0,0);
        glRotated(20,0,0,1);

        basicShapes::cuboid(0.125,0.125,0.6);
        glPopMatrix();

        glPopMatrix();


        glPushMatrix();
        //glTranslated(0,0.5,-18.5);

        glTranslated(0,-0.5,-1.5);
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

double zX,zZ,health =100;
int hitCounter;

    zombie(double x, double z)
    {
        this->zX = x;
        this->zZ = z;
        hitCounter=0;
    }
    //Detect if there is a zombie or not
    void detect()
    {

     if(flag == 0)
        return;
     //Angle we want to look at
     double detectAngle = atan( ( movX - zX) / ( movZ - zZ )) * (180 / 3.14);
     if(movZ < zZ)
     {
            detectAngle+=180;
     }


     if(detectAngle<0) detectAngle+=360;
     if(-rotAngle<0) rotAngle-=360;
     if(detectAngle - 4 <= -rotAngle  && detectAngle + 4 >= -rotAngle)
        {
        printf("Shooting\n");

        health -= 10;

        printf("%f ----",health);

        }
     printf("%f  ----",health);


    }
    void drawZ()
    {
        glPushMatrix();


        rotangleZombie = atan( (movX - zX) / ( movZ - zZ )) * (180 / 3.14);
        if(movZ > zZ)
        {
            rotangleZombie += 180;
        }
        double disFromTar = calcDistance(zX,zZ,movX,movZ);

        if(disFromTar > 5)
        {
            zZ+=0.009*sin((-rotangleZombie+270)*3.14/180);
            zX+=0.009*cos((-rotangleZombie+270)*3.14/180);
        }

        else{
            if(hitCounter==300)
                {
                PlaySound(TEXT("zsound.wav"),NULL,SND_ASYNC|SND_FILENAME);
                fPerson::health-=20;
                hitColor=30;

                if(fPerson::health<=0){
                    printf("you were eaten");
                    exit(0);
                }

                hitCounter=0;
                }

            else
                {
                hitCounter++;
                }
                }
        glTranslated(zX,0,zZ);
        glRotated(rotangleZombie,0,1,0);
        zombie::drawhead();
        zombie::Body();
        zombie::leftLeg();
        zombie::rightLeg();
        zombie::rightArm();
        zombie::leftArm();
        detect();
        glPopMatrix();
    }
    //When killed it falls on the ground
    void drawDead()
    {
        glPushMatrix();
        glTranslated(zX,-5,zZ);
        glRotated(90,1,0,0);
        zombie::drawhead();
        zombie::Body();
        zombie::leftLeg();
        zombie::rightLeg();
        zombie::rightArm();
        zombie::leftArm();
        glPopMatrix();
    }
    //Drawing head
    static void drawhead()
    {

        //right eye
        glPushMatrix();
        glColor3f(0.4,0.1,0.0);
        glTranslated(-0.3,0.1,-1.0);
        basicShapes::cuboid(0.1,0.1,0.1);
        glPopMatrix();
        //left eye
        glPushMatrix();
        glColor3f(0.4,0.1,0.0);
        glTranslated(0.3,0.1,-1.0);
        basicShapes::cuboid(0.1,0.1,0.1);
        glPopMatrix();
        // head
        glPushMatrix();
        glColor3f(0,0.7,0);
        glTranslated(0,0.1,0);
        basicShapes::cuboid(0.7,0.7,0.7);
        glPopMatrix();


    }

    //Drawing the body
    static void Body()
    {
        glPushMatrix();
        glColor3f(0,0.9,0);
        glTranslated(0,-1.7,0);
        basicShapes::cuboid(1.00,1.2,1.2);
        glPopMatrix();
    }

    //Drawing th left leg
    static void leftLeg()
    {
        glPushMatrix();
        glColor3f(0,0.5,0);
        glTranslated(-0.5,-3.7,0);
        basicShapes::cuboid(0.4,1.2,0.8);
        glPopMatrix();

    }

    //Drawing the right leg
    static void rightLeg()
    {

        glPushMatrix();
        glColor3f(0,0.5,0);
        glTranslated(0.5,-3.7,0);
        basicShapes::cuboid(0.4,1.2,0.8);
        glPopMatrix();

    }
    //Drawing right arm
    static void rightArm()
    {

        glPushMatrix();
        glColor3f(0,0.5,0);
        //glTranslated(0.5,-3.7,2.9);
        glTranslated(-1.3,-1.3,0);
        basicShapes::cuboid(0.3,1.2,0.8);
        glPopMatrix();

    }

    static void leftArm()
    {

        glPushMatrix();
        glColor3f(0,0.5,0);
        glTranslated(1.3,-1.3,0);
        basicShapes::cuboid(0.3,1.2,0.8);
        glPopMatrix();
    }

};


class tree{//TODO create tree draw function
public:

    double x,z;
    //notes drawing a cone manually is gonna be hard or impossible i tried with the cylinder
    //construct the tree out of pyramids instead
    //code the pyramid inside basicShapes class in a separate function
    tree(double x, double z)
    {
        this -> x = x;
        this -> z = z;
    }
    //To draw the tree
    void drawTree()
    {
        glPushMatrix();
        glTranslated(x,0,z);
        tree::drawtreestem();
        tree::drawfirstlayer();
        tree::drawsecondlayer();
        tree::drawthirdlayer();
        glPopMatrix();
    }

    ////nice to do's same as the above


    static void drawtreestem(){
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
//Draw Moon
class moon
{
public :
    static void drawmoon(){
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslated(10,20,-20);
    basicShapes::shperes(0.1);
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
int fPerson::health;
//double accm=0.01;

 //int xcurr , zcurr ,xcurrZ,zcurrZ;
std::vector <tree *> tObj;
std::vector <zombie *> tObjZ;


void display (void)
{
    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Background Color
    glClearColor(25.0/255.0, 25.0/255.0, 112.0/255.0,0.0);
    fPerson::drawLeftArm();//replace this with the draw function you want to test
    //Ground
    glPushMatrix();
    glColor3f(0,0.4,0.1);
    glTranslated(-1,-5,-1);
    basicShapes::cuboid(100,100,0);

    glPopMatrix();

    glPushMatrix();
    if(rotL == true) rotAngle -= 0.2;
    if(rotR == true) rotAngle += 0.2;
    if(rotAngle >= 360) rotAngle -= 360;
    if(rotAngle <= -360) rotAngle += 360;

    glRotated(rotAngle,0,1,0);
    //calculate position
    if(left==true)
    {
        movZ+=0.02*sin((rotAngle+180)*3.14/180);
        movX+=0.02*cos((rotAngle+180)*3.14/180);
    }
    if(right==true)
    {
        movZ+=0.02*sin((rotAngle)*3.14/180);
        movX+=0.02*cos((rotAngle)*3.14/180);
    }
    if(backw==true){
        movZ+=0.02*sin((rotAngle+90)*3.14/180);
        movX+=0.02*cos((rotAngle+90)*3.14/180);
    }
    if(forw==true)
    {
        movZ+=0.01*sin((rotAngle+270)*3.14/180);
        movX+=0.01*cos((rotAngle+270)*3.14/180);
    }


   ;

    glTranslatef    (-movX, 0.0, -movZ);
  //generating random trees
    if(tObj.size() <= 50)
        {
    for(int i = 0;i < 10;i++)
    {
        //Positive x and z
        double randx = rand() % 50 + 1;
        double randz =  rand() % 50 + 1;

        tree *t  = new tree(randx , randz);
        tree *t1 = new tree(randx * -1,randz * -1);
        tree *t2 = new tree(randx, randz * -1);
        tree *t3 = new tree(randx * -1,randz);
        tObj.push_back(t);
        tObj.push_back(t1);
        tObj.push_back(t2);
        tObj.push_back(t3);
    }

    }
    //Drawing of random trees
    for(int i =0 ; i < tObj.size(); i++)
    {
                tObj[i]-> drawTree();
    }
 if(tObjZ.size() <= 6)
    {

        double randx = rand() % 50 + 1;
        double randz = rand() % 50 + 1;


        zombie * ZB = new zombie(randx,randz);
        zombie * zb1 = new zombie(randx *-1,randz * -1);
        zombie * zb2 = new zombie(randx,randz * -1);
        zombie * zb3 = new zombie(randx * -1,randz);
        tObjZ.push_back(ZB);
        tObjZ.push_back(zb1);
        tObjZ.push_back(zb2);
        tObjZ.push_back(zb3);

     }
    //Check Zombie if dead or alive
     int c = 0;
     for(int i =0 ; i < tObjZ.size(); i++)
       {
        if(tObjZ[i]->health > 0)
        {
            tObjZ[i]-> drawZ();
            c++;
        }

        else
        {
            tObjZ[i]-> drawDead();
        }
        }

        if(c ==0)
        {
            printf("You win");
            exit(0);
        }
    flag = 0;

    moon::drawmoon();
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
    glutCreateWindow       ("Zombie vs Player Yasmine Karim 20102062 Mohamed Dwidar 20100361 Rowan Sherif 20102728");


    glClearColor (1.0, 1.0, 1.0, 0.0);

    glutDisplayFunc (display);
    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);
    glClearColor(1,1,1,1);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKey);
    glutSpecialUpFunc(specialKeyUp);
    texture(); // Lighting and textures

    glPointSize(5);
    fPerson::health=100;
    glutMainLoop();
    }


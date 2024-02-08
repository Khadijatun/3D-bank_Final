#include<windows.h>
#include<GL/glut.h>
#include <stdio.h>
#include <time.h>#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<mmsystem.h>
#include<math.h>
#include "BmpLoader.h"
//#include <SOIL/SOIL.h>  // You may need to include the SOIL library for texture loading

GLuint textureID;

GLfloat rotationAngle = 0.0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, Calpha= 360.0, C_hr_alpha=360.0;
GLboolean bRotate = false, fRotate= true, cRotate= true, xz_rotate=false,l_on=true;
const int width = 600;
const int height = 800;
GLboolean amb=true, spec=true, dif=true;

unsigned int ID;
float  PI= 3.14159265358979323846;
float rot = 0;
using namespace std;
int triangleAmount = 1000;
GLfloat twicePi = 2.0f * PI;

float vehicleSpeed = .003f;

bool night = false;
bool on = false;
bool cover = false;
bool vehicleStop = false;
bool rain = false;
bool waveUp = true;
bool handup= false;

float _crashB2 = 0.0f;
float _crashB1 = 0.0f;

float _rain1x = 0.0;
float _rain2x = 0.0;
float _rain3x = 0.0;
float _rain4x = 0.0;
float _rain5x = 0.0;
float _rain6x = 0.0;
float _rain7x = 0.0;
float _rain8x = 0.0;
float _rain9x = 0.0;
float _rain10x = 0.0;
float _rain11x = 0.0;

float _rain1y = 0.0;
float _rain2y = 0.0;
float _rain3y = 0.0;
float _rain4y = 0.0;
float _rain5y = 0.0;
float _rain6y = 0.0;
float _rain7y = 0.0;
float _rain8y = 0.0;
float _rain9y = 0.0;
float _rain10y = 0.0;
float _rain11y = 0.0;
float _rain12y = 0.0;
float _rain13y = 0.0;
float _rain14y = 0.0;
float _rain15y = 0.0;


bool l_on1 = false;
bool l_on2 = false;
bool l_on3 = false;



double spt_cutoff=38;

//float rot = 0;

GLfloat eyeX = .33;
GLfloat eyeY = 10;
GLfloat eyeZ = 10;

GLfloat lookX = 0;
GLfloat lookY = 10;
GLfloat lookZ = 0;


#define push glPushMatrix
#define pop glPopMatrix
#define gt(x,y,z) glTranslatef(x,y,z)
#define gs(x,y,z) glScalef(x,y,z)
#define gr(a,x,y,z) glRotatef(a,x,y,z)
#define te(x) glEnable(GL_TEXTURE_2D),glBindTexture(GL_TEXTURE_2D, x)
#define td() glDisable(GL_TEXTURE_2D)
#define PI 3.1415926
static GLfloat v_Cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};


static GLubyte quadIndices[6][4] =
{
   {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte c_quadIndices[1][4] =
{
    {0, 3, 2, 1}
};

static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0}
};


void cubeColor(float x, float y, float z, float a, float b, float c, int shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { x, y, z, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1, 1,1 , 1.0 };
    GLfloat mat_shininess[] = {shine};
//front phase niye kaaj hoche
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCube(3);

}



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}




void cube(GLfloat colr1, GLfloat colr2, GLfloat colr3)
{



    GLfloat cube_no[] = {0, 0, 0, 1.0};
    GLfloat cube_amb[] = {colr1*0.3,colr2*0.3,colr3*0.3,1};
    GLfloat cube_dif[] = {colr1,colr2,colr3,1};
    GLfloat cube_spec[] = {1,1,1,1};
    GLfloat cube_sh[] = {10};


    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_sh);
 //glutSolidCube(3);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_Cube[quadIndices[i][j]][0]);
        }

    }
    glEnd();


}
void Cube()
{


glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        for (GLint j=0; j<4; j++)
        {
             glVertex3fv(&v_Cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
            glVertex3fv(&v_Cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
            glVertex3fv(&v_Cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
            glVertex3fv(&v_Cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
        }

    }
    glEnd();


}
void drawcube()
{
    //glColor3f(1,0,0);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_Cube[quadIndices[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_Cube[quadIndices[i][1]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_Cube[quadIndices[i][2]][0]);
         glTexCoord2f(0,1);
        glVertex3fv(&v_Cube[quadIndices[i][3]][0]);

        glTexCoord2f(1,1);
    }
    glEnd();
}


void square()
{


    glBegin(GL_QUADS);
    //glColor3f(0,0,1);
    glVertex3fv(&v_Cube[quadIndices[1][0]][0]);
    glVertex3fv(&v_Cube[quadIndices[1][1]][0]);
    glVertex3fv(&v_Cube[quadIndices[1][2]][0]);
    glVertex3fv(&v_Cube[quadIndices[1][3]][0]);
    glEnd();
}

static GLfloat spin = 0.0;
//static float tx = 10.0;
//static float ty = 0.0;
double view[3]={2,2,12.9};
double look[3]={3,2,2};
int flag=-1;
void steps(void);
void window(void);
void gate(void);
double angle=0,speed=5,maino=0,tro=0,roomo=0,mgo=0;
//declarating quadric objects
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;

//float rot = 0;

GLfloat angle1;

//initialisation
void myinit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1*1366/768,1*1366/768,1,200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//defining new quadric object
    Cylinder = gluNewQuadric();
	//to set drawing style
    gluQuadricDrawStyle( Cylinder, GLU_FILL);
	//to set automatic normals
    gluQuadricNormals( Cylinder,GLU_SMOOTH);


    Disk = gluNewQuadric();
    gluQuadricDrawStyle( Disk, GLU_FILL);
    gluQuadricNormals( Disk, GLU_SMOOTH);
	GLfloat gam[]={0.2,.2,.2,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gam);

}
void material_property(GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat no_mat[] = { 1, 1, 1, 1.0 };
    GLfloat mat_ambient[] = { R, G, B, 1.0 };
    GLfloat mat_diffuse[] = { R, G, B, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1, 1.0 };
    GLfloat mat_shininess[] = {50};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}

//set material property
void matprop(GLfloat amb[],GLfloat dif[],GLfloat spec[],GLfloat shi[])
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shi);
}

//to create wall
void wall(double thickness)
{
	glPushMatrix();
	glTranslated(2,.5*thickness,2);
	glScaled(4.0,thickness,4.0);
	glutSolidCube(1.0);
	glPopMatrix();
}
//to create compound wall
void wall2(double thickness)
{
	glPushMatrix();
	glTranslated(.8,.5*thickness*4,5.0);
	glScaled(1.6,thickness*4,10.0);
	glutSolidCube(1.0);
	glPopMatrix();
}
//to create earth
void earth(void)
{
	GLfloat ambient[]={1,1,1,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={1,1,1,1};
	GLfloat shininess[]={50};


	matprop(ambient,diffuse,specular,shininess);
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={2,5,-3,0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,3);
	glTranslated(-300,-1.85,-300);
	glScaled(800,.5,800);
	//Cube();
//cubeColor(1,1,1,1,1,1,60);
	Cube();
	//glutSolidCube(1.0);
//cube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);






	glFlush();
}
void earth1(void)
{
	GLfloat ambient[]={1,1,1,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={1,1,1,1};
	GLfloat shininess[]={50};


	matprop(ambient,diffuse,specular,shininess);
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={2,5,-3,0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,3);
	glTranslated(800,-1.85,1500);
	glScaled(1500,.5,1500);
	//Cube();
//cubeColor(1,1,1,1,1,1,60);
	Cube();
	//glutSolidCube(1.0);
//cube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
	glFlush();
}


void compound(void)      //carpaser gher
{
	GLfloat ambient[]={1,1,1,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={1.0,1.,1.,1};
	GLfloat shininess[]={50};
	matprop(ambient,diffuse,specular,shininess);
	GLfloat lightIntensity[]={.7,.7,.8,1};
	GLfloat light_position[]={2,26,13.5,0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	//left wall of compound
	glPushMatrix();
	glPushMatrix();
	glTranslated(-17,0,-1-.04);
	glRotated(90.0,0,0,1);
	wall2(0.08);
	glPopMatrix();
	//right wall of compound
	glPushMatrix();

	glTranslated(17,0,-1-.02);
	glRotated(90.0,0,0,1);
	wall2(0.08);
	glPopMatrix();
	//back wall of compound
	glPushMatrix();
	glTranslated(-.2,0.8,-1);
	glRotated(-90,1,0,0);
	glScaled(34.0,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	//front left wall of compound
	glPushMatrix();
	glTranslated(-10,.8,9-.08);
	glRotated(-90,1,0,0);
	glScaled(14.2,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	//front right wall of compound
	glPushMatrix();
	glTranslated(7.9,.8,9-.08);
	glRotated(-90,1,0,0);
	glScaled(18.3,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();

	GLfloat ambient2[]={0,1,0,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={.2,.6,0.1,1};
	GLfloat shininess2[]={50};
		matprop(ambient2,diffuse2,specular2,shininess2);

	//floor
glPushMatrix();
	glTranslated(-4,-0.05,-1);
	glScaled(3,3,1.7);
	wall(0.08);
	glPopMatrix();

	gate();
    glFlush();

}

void terece(void)  //chader boder
{

	GLfloat	ambient1[]={1,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0,0,0.502,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	glTranslated(0,4,0);
	glScaled(1,.1,1);

	//left wall
	//glPushMatrix();
	//glTranslated(0,0,-.02-.25);
	//glScaled(2.0,2.0,2.0);
	//glRotated(90.0,0,0,1);
	//wall(0.08);
	//glPopMatrix();
	//right wall
	//glPushMatrix();
	//glTranslated(6+.12,0,-.02-.27);
	//glScaled(1,1,1.1);
	//glRotated(90.0,0,0,1);
	//wall(0.08);
	//glPopMatrix();
	//back wall
	//glPushMatrix();
	//glTranslated(-.08,0,-.21);
	//glScaled(1.5+.05,1,1);
	//glRotated(-90.0,1,0,0);
	//wall(0.08);
	//glPopMatrix();
	//front wall
	//glPushMatrix();
	//glTranslated(-.08,0,4+.11);
	//glScaled(1.5+.05,1,1);
	//glRotated(-90.0,1,0,0);
	//wall(0.08);
	//glPopMatrix();
	//glPushMatrix();
	//glTranslated(-.04,2,4);
	//glScaled(.08,4,.1);
	//glutSolidCube(1);
	//glPopMatrix();

     glPopMatrix();
}

void fanwing(float winglen)// fan er pakha
{
    glPushMatrix();

	glRotated(90,1,0,0);
	glRotated(90,0,1,0);
	glScaled(1,15,1);
	gluCylinder(Cylinder,.01,.01,1,4,1);
	glPopMatrix();
}

void fanbottom()
{
	glPushMatrix();

	glTranslated(1,3.2,1);
	glPushMatrix();
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .2, .2,.05, 128, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0.00025,0);
	glRotated(90,1,0,0);
	gluDisk(Disk,0,.2,32,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-.05,0);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder,.2,.15,.1,128,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-.1,0);
	glRotated(90,1,0,0);
	gluDisk(Disk,0,.15,32,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1,0.0,0);
	fanwing(.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(120,0,1,0);
	glTranslated(.1,0,0);
	fanwing(.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(240,0,1,0);
	glTranslated(0.1,0.0,0);
	fanwing(.6);
	glPopMatrix();
	glPopMatrix();
}
void fan(void)
{	glPushMatrix();
	glTranslated(2.5,1.9,0);
	glScaled(.5,.5,.5);
	GLfloat mat_ambient[]={.5,0,0,1};
	GLfloat mat_specular[]={0,1,1,0};
	GLfloat mat_diffuse[]={0,.502,0,1};
	GLfloat mat_shininess[]={50};


	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


if(flag==-1)
{
	glPushMatrix();
	fanbottom();
	glPopMatrix();
}
else

{

	angle+=speed;
	glPushMatrix();
	glTranslated(1,0,1);
	glRotated(angle,0,1,0);
	glTranslated(-1,0,-1);
	fanbottom();
	glPopMatrix();
}

	glPushMatrix();
	glTranslatef(1,3.3,1);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(1,4,1);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .006, 0.006, .6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,3.96,1);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
	glPopMatrix();
	glPopMatrix();
	if(flag==1)
		glutPostRedisplay();
}
void cleg(float cllen,float clwid)
{
	glRotated(90,1,0,0);
	gluCylinder(Cylinder,clwid,clwid,cllen,32,32);

}
void sleg(float len,float thk)
{
	glScaled(thk,len,thk);
	glutSolidCube(1);

}
void solar(void)
{
	GLfloat	ambient1[]={1,1.,1.,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={1,1,1,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={-10,20,30,0};
	glLightfv(GL_LIGHT2,GL_POSITION,light_position);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,lightIntensity);
	glEnable(GL_LIGHT2);
}

void myclock()
{
	GLfloat mat_ambient[]={.4,.8,.4,1};
	GLfloat mat_specular[]={1,1,1,1};
	GLfloat mat_diffuse[]={0,.749,1,1};
	GLfloat mat_shininess[]={50};
	matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);


	int hour_ticks , sec_ticks;
	glPushMatrix();
	glTranslated(2,3.2,-.02);
	glScaled(.03,.06,.03);



	glPushMatrix(); // clock face
	glTranslatef( 0, 0, 1.0);
	gluDisk(Disk, 0, 7, 32, 16);

	glPopMatrix();
	GLfloat mat_ambien[]={1,0,0,1};
	matprop(mat_ambien,mat_diffuse,mat_specular,mat_shininess);

	glPushMatrix();
	glTranslatef( 0, 0, 1.95);
	gluDisk(Disk, 0, .8, 32, 16);

	glPopMatrix();

	GLfloat	ambient[]={0,0,0,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={0,0,0,1};
  	matprop(ambient,diffuse,specular,mat_shininess);
	// hourer kata
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef( 0, 0, 1.5);
	glRotatef( -(360/12) * (newtime->tm_hour+newtime->tm_min/60.0), 0.0, 0.0, 1.0);

	glRotatef( -90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.45, 0, 4, 16, 16);
	glPopMatrix();
	GLfloat	ambient1[]={0,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0,0,1,1};
  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	// minuter kata
	glPushMatrix();
	glColor3f(1.0, 0.5, 1.0);
	glTranslatef( 0, 0, 1.25);
	glRotatef( -(360/60) * newtime->tm_min, 0.0, 0.0, 1.0);

	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.4, 0, 6, 16, 16);
	glPopMatrix();

	GLfloat	ambient2[]={1,0,0,1};
	GLfloat specular2[]={0,1,1,1};
	GLfloat diffuse2[]={1,0,0,1};
  	matprop(ambient2,diffuse2,specular2,mat_shininess);
	// seconder kata
	glPushMatrix();
	glTranslatef( 0, 0, 1);
	glRotatef(-(360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
	glRotatef( -90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.3, 0, 6, 16, 16);
	glPopMatrix();



	GLfloat	ambient3[]={1,1,1,1};
	GLfloat specular3[]={1,1,1,1};
	GLfloat diffuse3[]={0,0,0,1};
  	matprop(ambient3,diffuse3,specular3,mat_shininess);

	for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
	  {
		glPushMatrix();// Draw next arm axis.
        glTranslatef(0.0, 0.0, 1);
		glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
		glTranslatef( 6.0, 0.0, 0.0);
		glutSolidCube(.8);
		glPopMatrix();
	}

	for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
	 {
   	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.1);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(6.0, 0.0, 0.0);
	glutSolidCube(0.25);
	glPopMatrix();
	}
  glPopMatrix();
}
void clock1(){
glPushMatrix();
glScalef(4.1,1,1.);
	glTranslatef(1., 20.6,- 20.1);
	glRotatef(360,0,1,1);

	myclock();
	glPopMatrix();


}

void window()
{
    glPushMatrix();
    glScalef(.1,5.5,7.0);
    glTranslatef(-120,0.15,-1.75);
    cube(0.5, 1, 1);
    glPopMatrix();
//glass

}
void window2()
{
    glPushMatrix();
    glScalef(0.1,5.9,2.15);
    glTranslatef(-140,0.0,-2.1);
    cube(0.5, 1, 1);
    glPopMatrix();
//glass

}
void window3()
{
    glPushMatrix();
    glScalef(0.2,5.0,3.30);
    glTranslatef(-140,0.01,-2.0);
    cube(0.5, 1, 1);
    glPopMatrix();
//glass

}

void windows()
{

glPushMatrix();
 glTranslatef(20.0,-.2,.23);
    glRotatef(90,0,1,0);
    window();
    glPopMatrix();


}


void gate(void){
	int i;
	GLfloat	ambient1[]={1,.5,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={.6,.2,.8,1};
	GLfloat mat_shininess[]={120};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	// main gate
	if(mgo==1)
		glTranslated(1.5,0,0);
	glTranslated(-1.3,0,6);
	//top frame gate
	glPushMatrix();
	glTranslated(-0.75,1.6,3);
	glScaled(1.7,.04,.04);
	glutSolidCube(1);
	glPopMatrix();
	//bottom fram gate
	glPushMatrix();
	glTranslated(-0.75,.05,3);
	glScaled(1.7,.04,.04);
	glutSolidCube(1);
	glPopMatrix();
	//left frame gate
	glPushMatrix();
	glTranslated(-1.4,.85,2.9);
	glScaled(.04,1.5,.04);
	glutSolidCube(1);
	glPopMatrix();
	//right frame gate
	glPushMatrix();
	glTranslated(.0,.85,3);
	glScaled(.04,1.5,.04);
	glutSolidCube(1);
	glPopMatrix();
	//horizantal pipes gate

	//vertical strips gate
	for(i=1;i<=5;i++)
	{
	glPushMatrix();
	glTranslated(-1.6+.3*i,.85,3);
	glScaled(.2,1.5,.02);
	glutSolidCube(1);
	glPopMatrix();
	}
	glPopMatrix();
}
 void house(void)
{
float scale = 62;
float scale2 = 68;
float scale3 = 82;
float scale4 = 67;
float scale5 = 60;
float scale6 = 85;
float scale7 = 30;
float scale9 = 48;
float scale8 = 90;
float scale11 = 155;
float scale13 = 140;
float scale14 = 130;
float scale15 = 1000;

    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,3);
    glScalef(scale14,2,170);
    glTranslatef(-.53,-1.1,-0.7);
 //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    Cube();
    //cube(2.0,1.0,1.0);
   //Cube();;
    glPopMatrix();
//glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glScalef(scale8,2,scale11);
    glTranslatef(-.50,-1.05,-.75);
 //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    Cube();
    cube(0.8,0.8,.8);
   //Cube();;
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,23);
    glScalef(scale9,2,scale8);
    glTranslatef(-2.2,-1.05,-1.2);
 //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    //Cube();
    cube(0.8,0.8,.8);
   //Cube();;
    glPopMatrix();
 // glDisable(GL_TEXTURE_2D);


//right wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(scale/2,scale/4,0);
    glScalef(1,80/2,scale4);
    glTranslatef(2.0,-0.5,-0.48);
    //cube(.55, .55, .55);
    //cube(1.000, 0.755, 0.725);
    Cube();
    glPopMatrix();
 glDisable(GL_TEXTURE_2D);

    //right wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(scale/2,scale/4,0);
    glScalef(1,80/2,scale4);
    glTranslatef(2.0,-0.5,-1.48);
    //cube(.55, .55, .55);
    //cube(1.000, 0.755, 0.725);
    Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);


//left wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(-scale/2+1,scale2/4,0);
    glScalef(1,80/2,scale4);
    glTranslatef(-4.5,-0.5,-0.48);
//cube(3.000, 0.0, 0.0);
    Cube();
    glPopMatrix();
 glDisable(GL_TEXTURE_2D);

   //glDisable(GL_TEXTURE_2D);
//left wall
    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// Set material properties for transparency
GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTranslatef(-scale/2+1,scale/4,0);
    glScalef(1,85/2,58);
    glTranslatef(-4.5,-0.5,-1.80);
//cube(1.000, .2, 0.3);
    Cube();
    glPopMatrix();
glDisable(GL_BLEND);


glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);


    glTranslatef(-scale/2+1,scale/4,0);
    glScalef(1,85/2,68);
    glTranslatef(-50.5,-0.5,-1.4);
//cube(1.000, .2, 0.3);
    Cube();
    glPopMatrix();
glDisable(GL_BLEND);

glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);


    glTranslatef(-scale/2+1,scale/4,0);
    glScalef(1,45/2,34);
    glTranslatef(-50.2,-0.35,-2.2);
//cube(1.000, 1.0, 1.0);
    Cube();
    glPopMatrix();
glDisable(GL_BLEND);


// font wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(-4.0,scale5/4,scale5/2);
    glScalef(scale7,80/2,1);
    glTranslatef(-1.0,-0.48,4);
    cube(0.7,0.7,0.7);
   Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);

// font wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(-4.0,scale5/4,scale5/2);
    glScalef(scale7,80/2,1);
    glTranslatef(.25,-0.48,4);
    cube(0.7,0.7,0.7);
   Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  //font back

  glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(-4.0,scale5/4,scale5/2);
    glScalef(8,80/2,1);
    glTranslatef(-1.0,-0.48,-127.8);
   // cube(0.2,0.2,0.2);
   Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);


   glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(-4.0,scale5/4,scale5/2);
    glScalef(8,80/2,1);
    glTranslatef(-2.8,-0.48,-127.8);
    //cube(0.2,0.2,0.2);
   Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);

   glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(-4.0,scale5/4,scale5/2);
    glScalef(8,80/2,1);
    glTranslatef(1.0,-0.48,-127.8);
    //cube(0.2,0.2,0.2);
   Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(-4.0,scale5/4,scale5/2);
    glScalef(8,80/2,1);
    glTranslatef(3.0,-0.48,-127.8);
    //cube(0.2,0.2,0.2);
   Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);



    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glTranslatef(0,scale/4,scale/2);
    glScalef(scale2,82/2,2);
    glTranslatef(-0.5,-0.51,-65.);
    cube(.48, .25, 0.0);
    Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(0,scale/4,scale/2);
    glScalef(48,82/2,2);
    glTranslatef(-1.7,-0.51,-63.);
    //cube(.960, .87, 0.70);
    Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);

   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(0,scale/4,scale/2);
    glScalef(48,82/2,2);
    glTranslatef(-1.7,-0.51,-30.);
    //cube(.260, .26, 0.26);
    Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);


     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(15.0,8.0,2);
    glTranslatef(-0.5,3.7,18.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     //show door right
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(4.0,30.0,2);
    glTranslatef(.84,0,18.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    //show door light
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(4.0,30.0,2);
    glTranslatef(-1.84,0,18.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     //show door light font
  // glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    //glScalef(1.2,18.0,2);
   // glTranslatef(-3.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
   // cube(1,1,1.2);
    //Cube();
    //glPopMatrix();
     //show door light font
  // glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    ////glScalef(1.2,18.0,2);
    //glTranslatef(3.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1,1,1.2);
    //Cube();
    //glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.2,18.0,2);
    glTranslatef(10.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1.2);
    //Cube();
    glPopMatrix();


    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.2,18.0,2);
    glTranslatef(18.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1.2);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.2,18.0,2);
    glTranslatef(26.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1.2);
    //Cube();
    glPopMatrix();

    //show door light font
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.2,18.0,2);
    glTranslatef(-11.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1.2);
    //Cube();
    glPopMatrix();

    //show door light font
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.2,18.0,2);
    glTranslatef(-19.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1.2);
    //Cube();
    glPopMatrix();
     //show door light font
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.2,18.0,2);
    glTranslatef(-30.00,0,38.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1.2);
    //Cube();
    glPopMatrix();

    //show door light font
  //// glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    //glScalef(1.2,18.0,2);
    //glTranslatef(-35.00,0,20.21);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1,1,1.2);
    //Cube();
    //glPopMatrix();
    //show WINSOWoor right
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(3.0,20.0,1);
    glTranslatef(4.8,0.0,35);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();

    //show WINSOWoor right
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(3.0,20.0,1);
    glTranslatef(8.8,0.0,35);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


 //show WINSOWoor left
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(3.0,20.0,1);
    glTranslatef(-9.8,0.0,35);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


 //show WINSOWoor left1
   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(3.0,20.0,1);
    glTranslatef(-5.8,0.0,35);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();



    //window left up2
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(-4.8,4.05,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();


     //window left up2 nis
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(-4.8,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    //window left  up1
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(-2.9,4.05,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();





    //window left  up1 nis
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(-2.9,0.0,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     //window right  up1
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(1.95,4.05,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     //window right  up1 nis
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(1.95,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     //window right  up2
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(3.8,4.05,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    //window right  up2 nis
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(6.5,5.0,2);
    glTranslatef(3.8,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();



//window side left1
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(-9.3,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();
   // window side left1
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(-12.5,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

// window side left2
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(-17.5,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    // window side left2
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(-20.8,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();


    // window side right1
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(8.5,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    // window side rightt1
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(11.7,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     // window side rightt2
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(16.5,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    // window side rightt2
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,20.7,2);
    glTranslatef(19.8,0.00,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    //upper house front
    //FRONT WALL
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(55,35.7,2);
    glTranslatef(-.58,1.20,17.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.85,0.7,0.7);
    //Cube();
    glPopMatrix();
    //upper house back wall
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,24);
    glScalef(55,37.7,2);
    glTranslatef(-.59,1.11,-8.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(0.85,0.7,0.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//right upper
glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(2,37.7,51.2);
    glTranslatef(10.4,1.09,-0.28);
 //glRotatef(250, 1.0, 1, 1.0);

    //cube(0.85,0.7,0.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);


    glScalef(2,37.7,41.2);
    glTranslatef(-16.6,1.09,-0.42);
 //glRotatef(250, 1.0, 1, 1.0);

    //cube(0.85,0.7,0.7);
    Cube();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);


    //letter
    //B
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,21.0,2);
    glTranslatef(-17.1,2.22,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(5.1,2.7,2);
    glTranslatef(-4.7,24.42,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(5.1,2.7,2);
    glTranslatef(-4.7,17.02,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();
    //up



 glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(5.1,2.7,2);
    glTranslatef(-4.7,20.82,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,8.5,2);
    glTranslatef(-13.2,5.62,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();
      glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,8.5,2);
    glTranslatef(-13.2,6.72,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    //A
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,7.0,2);
    glTranslatef(-11,7.1,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,12.5,2);
    glTranslatef(-7.8,4.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(4.5,2.75,2);
    glTranslatef(-3.4,22.7,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

       glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(4.3,2.75,2);
    glTranslatef(-3.7,20.,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(4.5,2.75,2);
    glTranslatef(-3.45,17.4,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

   //N
  glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,15.8,2);
    glTranslatef(-5.8,3.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,15.8,2);
    glTranslatef(-2.8,3.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(4.5,2.75,2);
    glTranslatef(-1.74,23.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();
//K

glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.5,17.8,2);
    glTranslatef(-.8,2.69,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,1);
    //Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(-.30,20.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(0.5,21.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(1.0,22.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(1.7,22.9,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();


   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(0.5,19.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(1.0,18.0,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();

   glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1.5,2.75,2);
    glTranslatef(1.7,17.5,18.5);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1,1,1);
    //Cube();
   glPopMatrix();


//roof
   // glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    //glScalef(2,1.7,.2);
   // glTranslatef(-2.8,.19,-0.32);
 //glRotatef(250, 1.0, 1, 1.0);

   // cube(1.00,1.0,1.0);
    //Cube();
    //glPopMatrix();






float scale10 = 100;
float scale12 = 160;
//roof
    glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(0,scale6/2,0);
    glScalef(scale10,6,scale12);
    glTranslatef(-0.51,-1.08,-.7);

    cube(0.7,0.7,0.7);

  // Cube();
    glPopMatrix();
//glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0,scale5/2,0);
    glScalef(scale9,1.8,60);
    glTranslatef(.70,-1.3,-.5);

    cube(2.0,1.0,1.0);

   //Cube();
    glPopMatrix();

     glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0,scale5/2,0);
    glScalef(scale9,1.8,60);
    glTranslatef(.70,-.4,-.5);

    cube(.7,.7,.7);

   //Cube();
    glPopMatrix();

     glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0,scale5/2,0);
    glScalef(scale9,1.8,60);
    glTranslatef(.70,-2.0,-0.5);

    cube(.7,.7,.7);

   //Cube();
    glPopMatrix();
  //glDisable(GL_TEXTURE_2D);
	//window();
	//windows();
	solar();
	GLfloat	ambient6[]={1,0.5,.5,1};
	GLfloat specular6[]={1,1,1,1};
	GLfloat diffuse6[]={0.502, 0.502, 0.000,1};
	GLfloat mat_shininess6[]={50};
  	matprop(ambient6,diffuse6,specular6,mat_shininess6);
//	main door
glPushMatrix();
	glTranslated(1.75,0.0,13.5);
	glRotated(maino,1,0,5);
	glTranslated(0,0,-4);
	glPushMatrix();
	glTranslated(-7.5,0.1,25.02);
	glScaled(2.30,7.95,2.4);
	glRotated(-90.0,1,0,0);
	  //cube(0.5, 0.2,0.0);
wall(0.14);
glPopMatrix();
glPushMatrix();
glTranslated(1.75,10.0,13.5);
	glRotated(maino,1,0,5);
	glTranslated(0,0,-4);
	glPushMatrix();
	glTranslated(-35.5,30.6,3.02);
	glScaled(1.30,260.95,3.4);
//glRotated(180.0,1,0,0);
	  //cube(0.5, 0.2,0.0);
wall(0.14);
	glPopMatrix();
	//door up







	glFlush();
}

void floorWallsCeiling()
{
    float scale = 62;
float scale2 = 68;
float scale3 = 82;
float scale4 = 67;
float scale5 = 60;
float scale6 = 85;
float scale7 = 30;
float scale8 = 90;

    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,11);
    //glTranslatef(-0.5,-1,-0.5);
    glScalef(scale3,1,scale4);
    glTranslatef(-.46,42.0,-.3);
    // Cube();
     cube(1.0,1.0,3);
glPopMatrix();

      glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,11);
    //glTranslatef(-0.5,-1,-0.5);
    glScalef(50,1,77);
    glTranslatef(-1.73,35.0,-1.25);
    // Cube();
     cube(1.0,1.,1);

      //Cube();
//cubeColor(1.2, 1.8, 1, 1, 1, 1,60);
   // Cube();
  // cube(1.0,1.0,1.0);
  //Cube();
   //cubeColor(1, 1, 1, 1, 1, 1,60);
    //cube(1.0,1.0,1.0);
glPopMatrix();


 glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,11);
    //glTranslatef(-0.5,-1,-0.5);
    glScalef(75,1.5,35);
    glTranslatef(-1.3,46.0,-.55);
    // Cube();
     cube(.4,.4,.4);


glPopMatrix();

 glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,11);
    //glTranslatef(-0.5,-1,-0.5);
    glScalef(75,1.5,35);
    glTranslatef(-1.3,47.0,-.55);
    // Cube();
     cube(1.5,1.0,1);


glPopMatrix();

    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,11);
    //glTranslatef(-0.5,-1,-0.5);
    glScalef(scale4,1,scale4);
    glTranslatef(-.58,77.5,-.32);
    // Cube();
     cube(1.0,1.0,1);



 glPopMatrix();






glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(12,20.7,2);
    glTranslatef(-20.20,87.00,1.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1,1,3);
    //Cube();
    glPopMatrix();



// glDisable(GL_TEXTURE_2D);




glFlush();

}


void drawStrokeChar(char c,float x,float y,float z)
{
	  glPushMatrix();
          glTranslatef(x, y+8,z);
          glScalef(0.002f,0.002f,z);
          glutStrokeCharacter(GLUT_STROKE_ROMAN , c);
	  glPopMatrix();
}


void AC()
{
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glScalef(3.0,25.0,1);
    glTranslatef(-1.55,0.0,55.21);
 glRotatef(-360, 1.0, 1, 1.0);
    cube(0.6, 0.5,0.8);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glScalef(3.0,28.0,1);
    glTranslatef(-3.55,0.0,50.21);
 glRotatef(-360, 1.0, 1, 1.0);
    cube(0.6, 0.5,0.8);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

     glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(3.0,25.0,1);
    glTranslatef(1.9,0.0,55.21);
 glRotatef(-360, 1.0, 1, 1.0);
    cube(0.6, 0.5,0.8);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glScalef(3.0,28.0,1);
    glTranslatef(3.9,0.0,50.21);
 glRotatef(-360, 1.0, 1, 1.0);
    cube(0.6, 0.5,.8);
   // Cube();
    glPopMatrix();


    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glScalef(8.0,32.0,1);
    glTranslatef(-.27,0.0,34.21);
 glRotatef(-360, 1.0, 1, 1.0);
    cube(2.0, .85,.9);
   // Cube();
    glPopMatrix();


    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glScalef(8.0,32.0,1);
    glTranslatef(3.8,0.0,34.21);
 glRotatef(-360, 1.0, 1, 1.0);
    cube(2.0, .8,.9);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

   // glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
   // glScalef(5.0,3.0,1);
    //glTranslatef(2.75,1.3,12.21);
 //glRotatef(-360, 1.0, 1, 1.0);
   // cube(.8, .8,.8);
    //Cube();
    //glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

}



void table()
{
    float length = .7;
    float height = 3;
    float width= .3;
      float length1 = 1.0;
    float height1 = 3.8;
    float width1= 0.9;

    glPushMatrix();
    glTranslatef(length1/2,0,0);
    glScalef(length,height1,width);
    glTranslatef(-17.6,0.0,-15.0);
    cube(0.5,0.2,0.3);
    glPopMatrix();













    glPushMatrix();
    glTranslatef(length1/2,0,0);
    glScalef(length,height1,width);
    glTranslatef(-17.6,0.0,-7.0);
    cube(0.5,0.2,0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length1/2,0,0);
    glScalef(length,height1,width);
    glTranslatef(-12.6,0.0,-15.0);
    cube(0.5,0.2,0.2);
    glPopMatrix();

glPushMatrix();
    glTranslatef(length1/2,0,0);
    glScalef(length,height1,width);
    glTranslatef(-13.1,0,-7.0);
    cube(0.5,0.2,0.2);
    glPopMatrix();

    glPushMatrix();
       glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(length1*6,height1/6,width1*5);
    glTranslatef(-2.2,6.1,-1.2);
    //cube(0.8,.5,.2);
      Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}



void large_table(){


    float scale = 62;
float scale2 = 68;
float scale3 = 82;
float scale4 = 67;
float scale5 = 60;
float scale6 = 85;
float scale7 = 30;
float scale9 = 48;
float scale8 = 90;
float scale11 = 155;
float scale13 = 140;
float scale14 = 130;
float scale15 = 1000;

   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glTranslatef(scale/2,scale/4,0);
    glScalef(1,50/2,37);
    glTranslatef(1.9,-0.39,-2.4);
    cube(1.0, 1.0, 1.0);
    //cube(1.000, 0.755, 0.725);
   // Cube();
    glPopMatrix();
 glDisable(GL_TEXTURE_2D);


  glPushMatrix();
  // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,3);
    glTranslatef(scale/2,scale/4,0);
    glScalef(1,50/2,33);
    glTranslatef(1.9,-0.39,-1.3);
    cube(1.0, 1.0, 1.0);
    //cube(1.000, 0.755, 0.725);
    //Cube();
    glPopMatrix();
// glDisable(GL_TEXTURE_2D);

 glPushMatrix();
   // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(scale/2,scale/4,0);
    glScalef(1,50/2,33);
    glTranslatef(1.9,-0.39,-.1);
    //cube(1.0, .75, 0.8);
    cube(1.000, 1.0, 1.0);
    //Cube();
    glPopMatrix();
 //glDisable(GL_TEXTURE_2D);

 //large table
   // window side right1
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(50.5,10.7,9);
    glTranslatef(-.5,0.00,-8.0);
 //glRotatef(-360, 1.0, 1, 1.0);
   // cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
//large side
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(5.5,10.7,20);
    glTranslatef(3.6,0.00,-4.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(5.5,10.7,20);
    glTranslatef(-4.6,0.00,-4.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(5.5,19.7,20);
    glTranslatef(-6.15,0.00,-4.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.55,.55,.55);
    //Cube();
    glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(5.5,10.7,15);
    glTranslatef(-6.1,0.40,-5.8);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(.48,.25,00);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


 glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(10.5,26.7,1.5);
    glTranslatef(-6.1,0.00,-20.8);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(.48,.25,00);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(10.5,2.7,2.5);
    glTranslatef(-6.1,0.00,-13.4);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(.48,.25,00);
   // Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(10.5,2.7,2.5);
    glTranslatef(-6.1,3.00,-13.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.48,.25,00);
   // Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(10.5,2.7,2.5);
    glTranslatef(-6.1,6.00,-13.4);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(.48,.25,00);
   // Cube();
    glPopMatrix();
 glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(10.5,2.7,2.5);
    glTranslatef(-6.1,9.00,-13.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.48,.25,00);
   // Cube();
    glPopMatrix();



     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,8);
    glScalef(1.0,24.7,1.5);
    glTranslatef(-54.7,0.010,-22.0);
 //glRotatef(90, 0.0, 1, 1.0);
   cube(.48,.25,00);
   // Cube();
    glPopMatrix();

glPushMatrix();
    // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,18);
    glScalef(1.0,24.7,1.5);
    glTranslatef(-63.9,0.010,-22.0);
 //glRotatef(90, 0.0, 1, 1.0);
    cube(.48,.25,00);
    //Cube();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);

    //blend


     glPushMatrix();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

// Set the transparency of the entire object
//glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Adjust the alpha value (0.0 to 1.0) for desired transparency

glScalef(50.5, 6.7, 0.5);
glTranslatef(-.5, 2.0, -131.0);
glRotatef(360, 0, 1, 1.0);
//cube(1.5, 1, 1.7);
Cube();

// Reset color to opaque
glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

glDisable(GL_BLEND);
glPopMatrix();

//nis glass midd;le
glPushMatrix();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
GLfloat mat_ambient6[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse6[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular6[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess6[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient6);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse6);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular6);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess6);

// Set the transparency of the entire object
//glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Adjust the alpha value (0.0 to 1.0) for desired transparency

glScalef(5.5, 6.7, 0.5);
glTranslatef(-.5, 1.0, -131.0);
glRotatef(360, 0, 1, 1.0);
//cube(1.5, 1, 1.7);
Cube();

// Reset color to opaque
glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

glDisable(GL_BLEND);
glPopMatrix();
// glass side


glPushMatrix();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
GLfloat mat_ambient7[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse7[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular7[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess7[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient7);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse7);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular7);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess7);

// Set the transparency of the entire object
//glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Adjust the alpha value (0.0 to 1.0) for desired transparency

glScalef(5.5, 6.7, 0.5);
glTranslatef(-4.5, 1.0, -131.0);
glRotatef(360, 0, 1, 1.0);
//cube(1.5, 1, 1.7);
Cube();

// Reset color to opaque
glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

glDisable(GL_BLEND);
glPopMatrix();

glPushMatrix();
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
GLfloat mat_ambient8[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse8[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular8[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess8[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient8);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse8);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular8);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess8);

// Set the transparency of the entire object
//glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Adjust the alpha value (0.0 to 1.0) for desired transparency

glScalef(5.5, 6.7, 0.5);
glTranslatef(3.58, 1.0, -131.0);
glRotatef(360, 0, 1, 1.0);
//cube(1.5, 1, 1.7);
Cube();

// Reset color to opaque
glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

glDisable(GL_BLEND);
glPopMatrix();



  glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(0,scale6/2,0);
    glScalef(20,4,5);
    glTranslatef(-0.51,1.08,-.7);

    cube(1.0,1.0,1.0);

   Cube();
    glPopMatrix();
//glDisable(GL_TEXTURE_2D);


}
void chair()
{
    float length = .5;
    float height = 2;
    float height1 = 3;
    float width= .5;
glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(-15.9,0,2.0);
    //glRotatef(45,1.0,0,1);
    cube(0.5, 0.2, 0.2);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(-13.9,0,2.0);
    cube(0.5, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(-15.9,0,-.5);
   cube(0.5, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(-13.9,0,-.5);
    cube(0.5, 0.2, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(-15.,1,2.5);
    cube(0.5, 0.2, 0.2);
    glPopMatrix();



    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glTranslatef(length/2,0,0);
    glScalef(length*4,height/6,width*4);
    glTranslatef(-4.15,5.7,-.2);
    cube(.48,.25,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glTranslatef(length/2,0,0);
    glScalef(.5*4,height1*1.2,width);
    glTranslatef(-4.15,.8,2.5);
    //cube(.8, 0.5, 0.2);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void inside_wall3()
{
    float length = .5;
    float height = 2;
    float height1 = 3;
    float width= .2;

  glPushMatrix();

// Enable blending for transparency


// Your translation, scaling, and rotation code remains unchanged
glTranslatef(length/2, 0, 0);
glScalef(20, 6, width);
glTranslatef(-1.42, 0, -150.5);
//glRotatef(45, 1.0, 0, 1);

// Draw the transparent cube
cube(1.5, 0.2, 0.2);


glPopMatrix();

//glDisable(GL_BLEND);

    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();

// Enable blending for transparency
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

// Your translation, scaling, and rotation code remains unchanged
glTranslatef(length/2, 0, 0);
glScalef(20, 4, width);
glTranslatef(-1.42, 1.5, -150.5);
//glRotatef(45, 1.0, 0, 1);

// Draw the transparent cube
Cube();

cube(0.5, 1.2, 2.2);

// Disable blending after drawing the transparent object
glDisable(GL_BLEND);

glPopMatrix();

   // glDisable(GL_TEXTURE_2D);
   //glDisable(GL_BLEND);



glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(length/2,0,0);
    glScalef(20,6,width);
    glTranslatef(-1.42,0,-99.5);
    //glRotatef(45,1.0,0,1);
    cube(0.5, 0.2, 0.2);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
   glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient12[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse12[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular12[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess12[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient12);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse12);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular12);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess12);
    glTranslatef(length/2,0,0);
    glScalef(20,4,width);
    glTranslatef(-1.42,1.5,-99.5);
    //glRotatef(45,1.0,0,1);
    //cube(0.5, 1.2, 0.2);
    Cube();
glDisable(GL_BLEND);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(length/2,0,0);
    glScalef(20,6,width);
    glTranslatef(-1.42,0,-46.5);
    //glRotatef(45,1.0,0,1);
    cube(0.5, 0.2, 0.2);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
   glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient13[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse13[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular13[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess13[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient13);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse13);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular13);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess13);
    glTranslatef(length/2,0,0);
    glScalef(20,4,width);
    glTranslatef(-1.42,1.5,-46.5);
    //glRotatef(45,1.0,0,1);

   Cube();
   glDisable(GL_BLEND);
    glPopMatrix();


glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(length/2,0,0);
    glScalef(20,6,width);
    glTranslatef(-1.42,0,1.5);
    //glRotatef(45,1.0,0,1);
    cube(0.5, 0.2, 0.2);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient14[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse14[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular14[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess14[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient14);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse14);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular14);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess14);
    glTranslatef(length/2,0,0);
    glScalef(20,4,width);
    glTranslatef(-1.42,1.5,1.5);
    //glRotatef(45,1.0,0,1);
    //cube(0.5, 1.2, 0.2);
    Cube();
    glDisable(GL_BLEND);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


   glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(length/2,0,0);
    glScalef(20,6,width);
    glTranslatef(-1.42,0,45.5);
    //glRotatef(45,1.0,0,1);
    cube(0.5, 0.2, 0.2);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient15[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse15[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular15[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess15[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient15);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse15);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular15);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess15);
    glTranslatef(length/2,0,0);
    glScalef(20,4,width);
    glTranslatef(-1.42,1.5,45.5);
    //glRotatef(45,1.0,0,1);
    //cube(0.5, 1.2, 0.2);
    Cube();
    glDisable(GL_BLEND);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

     glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(length/2,0,0);
    glScalef(20,6,width);
    glTranslatef(-1.42,0,90.5);
    //glRotatef(45,1.0,0,1);
    cube(0.5, 0.2, 0.2);
   // Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
//glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,4);
     glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient16[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse16[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular16[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess16[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient16);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse16);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular16);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess16);
    glTranslatef(length/2,0,0);
    glScalef(20,4,width);
    glTranslatef(-1.42,1.5,90.5);
    //glRotatef(45,1.0,0,1);
    //cube(0.5, 1.2, 0.2);
   Cube();
    glPopMatrix();
    glDisable(GL_BLEND);
    //glDisable(GL_TEXTURE_2D);

}





void full_set()
{

   //1st set
    glPushMatrix();
   glTranslatef(-16.0, 0.0, 24.301);
   glRotatef(270.0, 0.0, 1.0, 0.0);
    table();
  glPopMatrix();
  //1st chair
   glPushMatrix();
   glTranslatef(-15.0, 0.0, 21.301);
  glRotatef(270.0, 0.0, 1.0, 0.0);
   chair();
   //glRotatef(180,1.0,0,1);
   glPopMatrix();

    glPushMatrix();
 glTranslatef(-11.0, 0.0, 9.0);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
   chair();
   glPopMatrix();
glPushMatrix();
 glTranslatef(-11.0, 0.0, 5.0);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  chair();
   glPopMatrix();



   //glPushMatrix();
    //glTranslatef(-17.0, 0.0, -6.301);
   // glRotatef(180.0, 0.0, 1.0, 0.0);
  // chair();
   //glPopMatrix();


//  glPushMatrix();
 //   glTranslatef(3.0, 0.0, 1.301); // Move to the left for the reflected chair
 ///   glRotatef(180.0, 0.0, 1.0, 0.0);
 ///   chair();
  //  glPopMatrix();
}

full_set1(){
//2nd set
    glPushMatrix();
   glTranslatef(-16.0, 0.0, 14.301);
   glRotatef(270.0, 0.0, 1.0, 0.0);
    table();
  glPopMatrix();
  //1st chair
   glPushMatrix();
   glTranslatef(-15.0, 0.0, 10.6525);
  glRotatef(270.0, 0.0, 1.0, 0.0);
   chair();
   //glRotatef(180,1.0,0,1);
   glPopMatrix();

    glPushMatrix();
 glTranslatef(-11.0, 0.0, -1.1);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
   chair();
   glPopMatrix();
glPushMatrix();
 glTranslatef(-11.0, 0.0, -4.3);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  chair();
   glPopMatrix();






}



full_set2(){
//2nd set
    glPushMatrix();
   glTranslatef(-16.0, 0.0, 4.301);
   glRotatef(270.0, 0.0, 1.0, 0.0);
    table();
  glPopMatrix();
  //1st chair
   glPushMatrix();
   glTranslatef(-15.0, 0.0, 1.6525);
  glRotatef(270.0, 0.0, 1.0, 0.0);
   chair();
   //glRotatef(180,1.0,0,1);
   glPopMatrix();

    glPushMatrix();
 glTranslatef(-11.0, 0.0, -11.1);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
   chair();
   glPopMatrix();
glPushMatrix();
 glTranslatef(-11.0, 0.0, -14.3);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  chair();
   glPopMatrix();






}

full_set3(){
//2nd set
    glPushMatrix();
   glTranslatef(-16.0, 0.0, -6.301);
   glRotatef(270.0, 0.0, 1.0, 0.0);
    table();
  glPopMatrix();
  //1st chair
   glPushMatrix();
   glTranslatef(-15.0, 0.0, -9.6525);
  glRotatef(270.0, 0.0, 1.0, 0.0);
   chair();
   //glRotatef(180,1.0,0,1);
   glPopMatrix();

    glPushMatrix();
 glTranslatef(-11.0, 0.0, -21.1);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
   chair();
   glPopMatrix();
glPushMatrix();
 glTranslatef(-11.0, 0.0, -24.3);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  chair();
   glPopMatrix();






}

full_set4(){
//2nd set
    glPushMatrix();
   glTranslatef(-16.0, 0.0, -16.301);
   glRotatef(270.0, 0.0, 1.0, 0.0);
    table();
  glPopMatrix();
  //1st chair
   glPushMatrix();
   glTranslatef(-15.0, 0.0, -19.6525);
  glRotatef(270.0, 0.0, 1.0, 0.0);
   chair();
   //glRotatef(180,1.0,0,1);
   glPopMatrix();

    glPushMatrix();
 glTranslatef(-11.0, 0.0, -31.1);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
   chair();
   glPopMatrix();
glPushMatrix();
 glTranslatef(-11.0, 0.0, -34.3);
  glRotatef(270.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  chair();
   glPopMatrix();






}






void light()
{


    GLfloat l_amb[] = {0.2, 0.2, 0.6, 1.0};
    GLfloat l_dif[] = {0.961, 0.871, 0.702};
    GLfloat l_spec[] = {0.2,0.2,0.2,1};
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_pos1[] = {-20,-20,20,1.0};
    GLfloat l_pos2[] = {34,30,-5,1.0};
    GLfloat l_pos3[] = {0,30,0,1.0};



    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if(l_on1)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);







    if(l_on2)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);



    if(l_on3)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
        }

    }
    else
    {
        glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
    }

    glLightfv(GL_LIGHT2,GL_POSITION,l_pos3);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
}

void light1()
{


     GLfloat l_amb[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat l_dif[] = {1.0, 1.0,1.0, 1.0};
    GLfloat l_spec[] = {1.0,1.0,1.0,1};
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_pos1[] = {12.0,40,14.0,1.0};
    GLfloat l_pos2[] = {8,8.0,30,1.0};
    GLfloat l_pos3[] = {-5,34,16,1.0};




    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if(l_on1)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);







    if(l_on2)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);



    if(l_on3)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
        }

    }
    else
    {
        glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
    }

    glLightfv(GL_LIGHT2,GL_POSITION,l_pos3);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
}



void drawCircle(float cx, float cy,float cz, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);

    GLfloat triangle_amb[] = {1.000, 0.969, 0.49, 5.0};  // Ambient color
    GLfloat triangle_dif[] = {1.000, 0.969, 0.49, 5.0};  // Diffuse color
    GLfloat triangle_spec[] = {1.000, 0.969, 0.49, 5.0}; // Specular color
    GLfloat triangle_sh[] = {10};  // Shininess

    glMaterialfv(GL_FRONT, GL_AMBIENT, triangle_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, triangle_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, triangle_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, triangle_sh);

    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex3f(x + cx, y + cy,cz);
    }
    glEnd();

}








void drawSofa2()
{
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(10.5,4,6.5);
    glTranslatef(1.2,0.00,3.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(10.5,6,2);
    glTranslatef(1.2,.66,12.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




}

void drawSofa4()
{
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(10.5,8,6.5);
    glTranslatef(1.2,0.00,3.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(10.5,12,2);
    glTranslatef(1.2,.66,12.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);









}


void sofa()

{
  glPushMatrix();
  glTranslatef(35,0.0,25.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

   glPushMatrix();
  glTranslatef(5,0.0,30.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,10);
    glScalef(10.5,4,6.5);
    glTranslatef(1.1,0.00,1.6);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.4, 0.2, 0.0);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient15[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse15[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular15[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess15[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient15);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse15);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular15);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess15);
    glScalef(12.5,.5,8.5);
    glTranslatef(0.85,7.80,1.13);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.0,1,1.7);
    Cube();
     glDisable(GL_BLEND);
    glPopMatrix();



//void sofa()


  glPushMatrix();
  glTranslatef(35,0.0,-9.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

   glPushMatrix();
  glTranslatef(5,0.0,-1.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,10);
    glScalef(10.5,4,6.5);
    glTranslatef(1.1,0.00,-3.2);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.4, 0.2, 0.0);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient72[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse72[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular72[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess72[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient72);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse72);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular72);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess72);
    glScalef(12.5,.5,8.5);
    glTranslatef(0.85,7.80,-2.6);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.0,1,1.7);
    Cube();
     glDisable(GL_BLEND);
    glPopMatrix();

//void sofa3



  glPushMatrix();
 // glScalef(8.5,15,5.5);
  glTranslatef(35,0.2,-9.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

   glPushMatrix();
  glTranslatef(-75,0.0,-42.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  drawSofa4();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-50,0.0,-78.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa4();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,10);
    glScalef(12.5,11,10.5);
    glTranslatef(-5.5,0.00,-6.2);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.4, 0.2, 0.0);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient73[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse73[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular73[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess73[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient73);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse73);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular73);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess73);
    glScalef(14.5,1.7,15);
   glTranslatef(-4.8,6.00,-4.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.0,1,1.7);
    Cube();
     glDisable(GL_BLEND);
    glPopMatrix();

// atm root


  glPushMatrix();
 // glScalef(8.5,15,5.5);
  glTranslatef(8,47.3,21.5);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();


  glPushMatrix();
 // glScalef(8.5,15,5.5);
  glTranslatef(18,47.1,21.6);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

   glPushMatrix();
 // glScalef(8.5,15,5.5);
  glTranslatef(27,47.0,21.7);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();


  glPushMatrix();
 // glScalef(8.5,15,5.5);






}

void drawSofa3(){

glPushMatrix();
glTranslatef(.0,0.0,-28.0);
  drawSofa2();
  glPopMatrix();

}

void light3()
{//middle
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-.5,35.86,4.0);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    //2
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-.5,35.86,.5);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //3
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-.5,35.86,-3);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);


    //4

    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-.5,35.86,-6.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    //5

    //4

    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-.5,35.86,-10);
 //glRotatef(-360, 1.0, 1, 1.0);
 cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //6
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-.5,35.86,-13.5);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

  //right side

glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,4.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //1
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,.5);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //2
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,-3);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //3
     glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,-6.5);
 //glRotatef(-360, 1.0, 1, 1.0);
  cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //4

     glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,-10);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //5
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,-13.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
     glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-3.5,35.86,-13.5);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //right side2

glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-6.5,35.86,4.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //2
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-6.5,35.86,.5);
 //glRotatef(-360, 1.0, 1, 1.0);
  cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //3
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-6.5,35.86,-3);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //4
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-6.5,35.86,-6.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();

     //5
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-6.5,35.86,-10);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //6
     //5
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(-6.5,35.86,-13.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();

//left side1
//1
glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(2.5,35.86,4.0);
 //glRotatef(-360, 1.0, 1, 1.0);
   cube(1.,1,1.);
    //Cube();
    glPopMatrix();
//2
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(2.5,35.86,.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);;
    //Cube();
    glPopMatrix();

    //3
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(2.5,35.86,-3);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //4

    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(2.5,35.86,-6.5);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();
//5
glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(2.5,35.86,-10);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //6
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(2.5,35.86,-13.5);
 //glRotatef(-360, 1.0, 1, 1.0);
     cube(1.,1,1.);
    //Cube();
    glPopMatrix();


    //left side2
//1
glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(5.5,35.86,4.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.0,1,1.);
    //Cube();
    glPopMatrix();
    //2
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(5.5,35.86,.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //3
 glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(5.5,35.86,-3);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //4
     glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(5.5,35.86,-6.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();
    //5
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(5.5,35.86,-10);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();

    //6
    glPushMatrix();
     ////glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,7);
    glScalef(4.5,1,6);
    glTranslatef(5.5,35.86,-13.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(1.,1,1.);
    //Cube();
    glPopMatrix();





}

void insidewall()
{
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(25.5,8.7,.8);
    glTranslatef(-1.3,0.00,23.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.6,.5,.5);
    //Cube();
    glPopMatrix();



     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(25.5,8.7,.8);
    glTranslatef(-1.3,0.00,37.);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.6,.5,.5);
    //Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(25.5,8.7,.8);
    glTranslatef(-1.3,0.00,10.3);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.6,.5,.5);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(25.5,8.7,.8);
    glTranslatef(-1.3,0.00,-4.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.6,.5,.5);
    //Cube();
    glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(25.5,8.7,.8);
    glTranslatef(-1.3,0.00,-17.0);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.6,.5,.5);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(25.5,8.7,.8);
    glTranslatef(-1.3,0.00,-32.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(.6,.5,.5);
    //Cube();
    glPopMatrix();

//blend

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient55[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse55[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular55[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess55[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient55);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse55);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular55);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess55);
    glScalef(25.5,12.7,.5);
    glTranslatef(-1.301,0.00,-27.);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1,1,3);
    Cube();
    glDisable(GL_BLEND);
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
     glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient50[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse50[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular50[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess50[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient50);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse50);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular50);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess50);
    glScalef(25.5,12.7,.5);
    glTranslatef(-1.301,0.00,-6.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(.5,.5,.5);
    Cube();
    glPopMatrix();


        glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
     glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient51[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse51[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular51[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess51[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient51);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse51);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular51);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess51);
    glScalef(25.5,12.7,.5);
    glTranslatef(-1.301,0.00,59.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(.5,.5,.5);
    Cube();
    glPopMatrix();


            glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
     glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient52[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse52[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular52[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess52[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient52);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse52);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular52);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess52);
    glScalef(25.5,12.7,.5);
    glTranslatef(-1.301,0.00,17);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(.5,.5,.5);
    Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
     glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient53[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse53[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular53[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess53[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient53);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse53);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular53);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess53);
    glScalef(25.5,12.7,.5);
    glTranslatef(-1.301,0.00,38);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(.5,.5,.5);
    Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
     glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Set material properties for transparency
GLfloat mat_ambient56[] = {0.5, 0.5, 0.5, 0.5}; // RGBA ambient material
GLfloat mat_diffuse56[] = {0.5, 0.5, 0.5, 0.5}; // RGBA diffuse material
GLfloat mat_specular56[] = {1.0, 1.0, 1.0, 0.5}; // RGBA specular material
GLfloat mat_shininess56[] = {50.0}; // Shininess (0 to 128)

glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient56);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse56);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular56);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess56);
    glScalef(25.5,12.7,.5);
    glTranslatef(-1.301,0.00,-51.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(.5,.5,.5);
    Cube();
    glPopMatrix();
}
void stairs(){


glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-25.2,.00,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-24.4,1.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-23.6,2.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-22.8,3.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-22.1,4.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-21.4,5.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-20.6,6.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-19.8,7.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
        glPushMatrix();

     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-19,8.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


        glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-18.2,9.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-17.4,10.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-16.6,11.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-15.8,12.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(3.5,3,10);
    glTranslatef(-15,13.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void reling(){
    //right
  glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,72.0,1);
    glTranslatef(-58.6,0.0,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();
    //Left
    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,72.0,1);
    glTranslatef(-58.6,0.0,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,62.0,1);
    glTranslatef(-54.6,0.1,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,62.0,1);
    glTranslatef(-54.6,0.1,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


 glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,62.0,1);
    glTranslatef(-51.2,0.2,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();

glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,62.0,1);
    glTranslatef(-51.2,0.2,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();



    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,57.0,1);
    glTranslatef(-47.2,0.32,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,57.0,1);
    glTranslatef(-47.2,0.32,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();



    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,52.0,1);
    glTranslatef(-43.5,0.46,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();

    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,52.0,1);
    glTranslatef(-43.5,0.46,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();

     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,47.0,1);
    glTranslatef(-40.2,0.66,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


      glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,47.0,1);
    glTranslatef(-40.2,0.66,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();

glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,40.0,1);
    glTranslatef(-37.9,.82,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,40.0,1);
    glTranslatef(-37.9,.82,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


    glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,34.0,1);
    glTranslatef(-34.9,1.2,3.8);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


     glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);4
    glScalef(1.50,34.0,1);
    glTranslatef(-34.9,1.2,-4.4);
 //glRotatef(-360, 1.0, 1, 1.0);
    cube(0.5, 0.2,0.0);
    //Cube();
    glPopMatrix();


}
void floorWallsCeiling2(float scale)
{



    //bottom

    //glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,3);
    //glScalef(700,1,900);
   // glTranslatef(-0.5,-1.5,-0.5);
    //cube(0.8, 0.8, 0.8);
   // Cube();
    //glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //



   ;




}


void building2()
{
    material_property(1,1,1);

    glPushMatrix();
    glTranslatef(0,30,0);
    glScalef(10,2.2,4);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(20,180,12);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void building3()
{
    material_property(1,1,1);

    glPushMatrix();
    glTranslatef(0,25,0);
    glScalef(6,.2,5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glTranslatef(0,12.5,0);
    glScalef(10,100,5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void building4()
{
    material_property(1,1,1);

    glPushMatrix();
    glTranslatef(0,30,0);
    glScalef(10,2.2,4);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(20,180,12);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void sky()
{
     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,110);
    glScalef(250,.2,18);
    glTranslatef(-.5,-.5,-.5);
    cube(.3,.3,.3);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14)0
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(-.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();
 glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(-2.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(1.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(3.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(-4.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(-6.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(6,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(8,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(10,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(-8.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();

     glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,0.1,112);
    glScalef(6,.3,1);
    glTranslatef(-10.5,0,-.5);
    cube(1,1,1);
    glPopMatrix();



    //glDisable(GL_TEXTURE_2D);
}
void pc() {

 glPushMatrix();
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glScalef(7,6,1);
    glTranslatef(0,2.18,-78);
    cube(0,0,0);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
 glPushMatrix();
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glScalef(2,3,1);
    glTranslatef(1.3,3.4,-78.2);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glScalef(3,1.,1.5);
    glTranslatef(.76,10.3,-52.2);
    cube(0,0,0);
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);



  glPushMatrix();
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glScalef(5,1.,1.5);
    glTranslatef(.22,10.3,-54.0);
    Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void pc2(){
glPushMatrix();
glTranslatef(-12.76,.1,11);
pc();
glPopMatrix();


glPushMatrix();
glTranslatef(-23.76,.1,11);
pc();
glPopMatrix();

glPushMatrix();
glTranslatef(12.76,.1,11);
pc();
glPopMatrix();

glPushMatrix();
glTranslatef(0,.1,11);
pc();
glPopMatrix();

}
void pc3(){
glPushMatrix();
glScalef(1,3,3.7);
glTranslatef(-11.5,2.0,.5);
cube(0,0,0);
glPopMatrix();

glPushMatrix();
glScalef(1,2.5,1.4);
glTranslatef(-11.5,2.0,2.2);
cube(0,0,0);
glPopMatrix();

}

pc4(){
glPushMatrix();

glTranslatef(-1.8,-.8,11.4);
pc3();
//cube(0,0,0);
glPopMatrix();
//

glPushMatrix();

glTranslatef(-1.8,-.8,18.7);
pc3();
//cube(0,0,0);
glPopMatrix();

glPushMatrix();

glTranslatef(-1.8,-.8,-13.);
pc3();
//cube(0,0,0);
glPopMatrix();

glPushMatrix();

glTranslatef(-1.8,-.8,-26.);
pc3();
//cube(0,0,0);
glPopMatrix();


}
void pc5(){
glPushMatrix();
glScalef(1,4.2,4.5);
glTranslatef(-11.5,2.0,.5);
cube(0,0,0);
glPopMatrix();

glPushMatrix();
glScalef(1,2.9,1.9);
glTranslatef(-11.5,2.0,2.0);
cube(0,0,0);
glPopMatrix();

}

void pc6(){

glPushMatrix();

glTranslatef(-52.8,6.5,-65.);
pc5();
//cube(0,0,0);
glPopMatrix();




}

void tob()

{
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
glScalef(3.5,3.8,3.7);
glTranslatef(8.44,1,7.8);
Cube();
//cube(0,3,0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);

 glPushMatrix();
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
glScalef(3.5,3.8,3.7);
glTranslatef(8.44,1.8,7.8);

Cube();
glPopMatrix();
glDisable(GL_TEXTURE_2D);

glPushMatrix();
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
glScalef(2.5,2.9,2.85);
glTranslatef(12.0,3.5,10.3);

Cube();
glPopMatrix();
glDisable(GL_TEXTURE_2D);

glPushMatrix();
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
glScalef(2.5,2.9,2.85);
glTranslatef(12.0,0.8,10.3);

Cube();
glPopMatrix();
glDisable(GL_TEXTURE_2D);

glPushMatrix();
glScalef(.7,3.9,.8);
glTranslatef(44.5,0.0,38.);

cube(3,.7,0);
glPopMatrix();

glPushMatrix();
glScalef(2.5,2.9,2.85);
glTranslatef(12.0,-0.8,10.3);

cube(1,3,1.4);
glPopMatrix();

}

void tob2(){
glPushMatrix();
glTranslatef(8.0,-0.8,21.3);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-10.0,-0.8,21.3);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-25.6,-0.8,22.3);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-38.0,-0.8,22.3);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-58.0,-0.8,22.3);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-78.0,-0.8,22.3);
tob();
glPopMatrix();

//inside bank

glPushMatrix();
glTranslatef(-9.0,0.0,1.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-15.0,0.0,1.0);
tob();
glPopMatrix();

//atm room
glPushMatrix();
glTranslatef(-60.0,44.0,-14.0);
tob();
glPopMatrix();


glPushMatrix();
glTranslatef(-60.0,44.0,-21.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-60.0,44.0,-29.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-60.0,44.0,-37.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-55.0,44.0,-44.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-40.0,44.0,-44.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-25.0,44.0,-44.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-10.0,44.0,-44.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-68.0,2.0,-120.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-78.0,2.0,-120.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-88.0,2.0,-120.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-98.0,2.0,-120.0);
tob();
glPopMatrix();

glPushMatrix();
glTranslatef(-108.0,2.0,-120.0);
tob();
glPopMatrix();
}

void atm(){
glPushMatrix;
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);
glScalef(5,9,5.5);

glTranslatef(1.0,4.0,.5);
//cube(0,0,0);
Cube();
glPopMatrix();
glDisable(GL_TEXTURE_2D);

//atm room

}

void atm2(){

glPushMatrix;


glTranslatef(-15.0,7.5,11);
atm();
glPopMatrix();




}

void atm3(){
glPushMatrix;

glScalef(5,9,5.5);
glTranslatef(-15.0,8.5,11);
cube(1,1,1);
glPopMatrix();
}

void table3()
{


   glPushMatrix();
   glScalef(.61,1.8,1);
  glTranslatef(28.5,0.0,-50.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

    glPushMatrix();
   glScalef(.61,1.8,1);
  glTranslatef(45.0,0.0,-50.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

    glPushMatrix();
   glScalef(.61,1.8,1);
  glTranslatef(10.5,0.0,-50.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.61,1.8,1);
  glTranslatef(-4.5,0.0,-50.0);
  glRotatef(180.0, 0.0, 1.0, 0.0);
  drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  glPopMatrix();


}
void locker()
{
glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-110.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2,0,0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-111.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2,.5,0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-112.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2,.5,3);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-113.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.5,.5,3);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-114.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.5,1.5,3);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-115.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.5,.5,.3);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-118.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.5,.5,.8);
  glPopMatrix();


  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-119.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.5,.5,.8);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-120.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.5,.5,.5);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-121.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.5,1.5,.5);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-122.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(3.0,1.5,1.5);
  glPopMatrix();

 glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-123.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(3.0,1.5,3.0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-124.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.0,3.0,3.0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-125.5,3.78,-11.3);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.0,3.0,2.5);
  glPopMatrix();


   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-125.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.4,.5,2.5);
  glPopMatrix();
glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-124.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.4,.5,2.5);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-123.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(0,0,2.5);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-122.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1,0,2.5);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-120.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1,2,2.5);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-119.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1,0,0);
  glPopMatrix();

    glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-118.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(0,2,0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-116.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(.4,2,0);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-115.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1,2,.7);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-114.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1.5,.8,.7);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-113.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1.5,.8,1.0);
  glPopMatrix();

 glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-111.5,2.16,-11.2);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1.5,.8,1.9);
  glPopMatrix();



   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-111.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(1.5,2.8,1.9);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-110.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.5,2.8,1.9);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-112.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.5,.8,1.9);
  glPopMatrix();

    glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-113.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.,.8,.9);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-114.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(0.,.0,.9);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-115.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.,.8,.9);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-116.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(3.,.8,1.9);
  glPopMatrix();

   glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-119.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(3.,.0,0);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-120.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(3.,.0,3);
  glPopMatrix();
  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-121.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(0.,.0,3);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-122.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.,.0,3);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-123.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.,3.0,.6);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-124.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.,.6,1.6);
  glPopMatrix();

  glPushMatrix();
   glScalef(.5,5.,3);
  glTranslatef(-125.5,0.52,-11.1);
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  //drawSofa2();
  //glRotatef(180.0, 0.0, 1.0, 0.0);
  cube(2.,2.6,3.0);
  glPopMatrix();

}

void wheel()
{
    material_property(0,0,0);
    glPushMatrix(); //Wheel1
    glTranslatef(-1.5,1.65,.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();
    //back
    glPushMatrix(); //Wheel1
    glTranslatef(1,1.65,.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();

    glPushMatrix(); //Wheel1
    glTranslatef(-1.5,1.65,-.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();
    //back
    glPushMatrix(); //Wheel1
    glTranslatef(1,1.65,-.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();
}
double bus_switch=true;
double busx=-10, busy, busz=7;


void bus()
{
    GLfloat no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_diffuse[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

   // glBindTexture(GL_TEXTURE_2D,21);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(0,3,0);
    glScalef(5,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    Cube();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    //bus front side
   // glBindTexture(GL_TEXTURE_2D,21);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-2.5,3,0);
    glScalef(.1,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    Cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,21);

    glPushMatrix();
    glTranslatef(0,4.4,0);
    glScalef(5,.1,2);
    glTranslatef(-.5,-.5,-.5);
    Cube();
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);

    wheel();
}
void bus_animation()
{
    if(busx<=70)
    {

        busx +=0.2;
    }
    if(busx>=70)
    {
        busx = -70;

    }

    glutPostRedisplay();

}
void busmove()
{
        //glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,18);
        glTranslatef(busx,-2.8,107);
        glScalef(2,2,1);
        bus();
        if (bus_switch)
        {

            bus_animation();
        }

        glPopMatrix();
}

void busmove2()
{
        //glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,18);
        glTranslatef(-busx,-2.8,109);
        glScalef(2,2,1);
        bus();
        if (bus_switch)
        {

            bus_animation();
        }

        glPopMatrix();
}
void bus2()
{
    GLfloat no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_diffuse[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

   // glBindTexture(GL_TEXTURE_2D,21);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(0,3,0);
    glScalef(5,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    Cube();
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
    //bus front side
   // glBindTexture(GL_TEXTURE_2D,21);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(-2.5,3,0);
    glScalef(.1,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    Cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,21);

    glPushMatrix();
    glTranslatef(0,4.4,0);
    glScalef(5,.1,2);
    glTranslatef(-.5,-.5,-.5);
    Cube();
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);

    wheel();
}
 void tob4(){
 glPushMatrix();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
glScalef(2.0,2.0,2.0);
glTranslatef(8.84,2.3,-9.8);
Cube();
cube(1.0,1.0,1.0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);

glPushMatrix();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
glScalef(2.0,2.0,2);
glTranslatef(7.84,2.3,-9.8);
Cube();
cube(1.0,1.0,1.0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);


 glPushMatrix();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
glScalef(2.0,2.0,2);
glTranslatef(7.84,2.3,6.6);
Cube();
cube(1.0,1.0,1.0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);


 glPushMatrix();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
glScalef(2.0,2.0,2);
glTranslatef(8.84,2.3,6.6);
Cube();
cube(1.0,1.0,1.0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);


}
void ac2()
{
   glPushMatrix();
  glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,25);
glScalef(2.0,2.0,7);
glTranslatef(-17.1,13.5,-1.);
//glRotatef(180,0,1,1);
Cube();
//cube(1.0,1.0,1.0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);


glPushMatrix();
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,25);
glScalef(2.0,2.0,7);
glTranslatef(-17.1,13.5,1.8);
//glRotatef(180,0,1,1);
Cube();
//cube(1.0,1.0,1.0);
glPopMatrix();
glDisable(GL_TEXTURE_2D);
}
void cube4()
{

//2nd
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-11.0,8.7,-12.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-13.0,8.7,-12.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-15.0,8.7,-12.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-17.0,8.7,-12.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-19.0,8.7,-12.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

//1st


//2nd
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-11.0,8.7,-9.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-13.0,8.7,-9.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-15.0,8.7,-9.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-17.0,8.7,-9.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-19.0,8.7,-9.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

//3rd

//1st


//2nd
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-11.0,8.7,-15.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-13.0,8.7,-15.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-15.0,8.7,-15.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-17.0,8.7,-15.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-19.0,8.7,-15.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

//4th

//1st


//2nd
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-11.0,8.7,-18.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-13.0,8.7,-18.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-15.0,8.7,-18.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-17.0,8.7,-18.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-19.0,8.7,-18.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();


//5th


//1st


//2nd
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-11.0,8.7,-21.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();
    glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-13.0,8.7,-21.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-15.0,8.7,-21.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-17.0,8.7,-21.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();

 glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(4.0,4.0,4);
glTranslatef(-19.0,8.7,-21.8);
//glRotatef(180,0,1,1);
//Cube();
cube(1.0,.992,.816);
glPopMatrix();



//pc

glPushMatrix();
  //glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,23);
glScalef(2.8,1.2,3.0);
glTranslatef(-23.3,9.5,-20.6);
//glRotatef(180,0,1,1);
//Cube();
cube(0.0,.0,.0);
glPopMatrix();
}
char *c;

void start() {
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glClearColor(.45f, .25f, 0.5f, 1.0f); // Set background color to black and opaque


    glColor3ub(255, 255, 255);
    c="BANK";
    glRasterPos2f(2.1, 5.7);
    for(int i = 0; c[i] !='\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    glColor3ub(0, 0, 0);
    c="NAME: KHADIJATUN NUR";
    float x = 0.3f;
    glRasterPos2f(0.5, 2.1);
    for(int i = 0; c[i] !='\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
        if(c[i] == '\n')
            glRasterPos2f(-1.5, x = x-0.1);
    }

    glColor3ub(0, 0, 0);
    c="ID:1903710201905 \n SEMESTER:7th(B)";
    glRasterPos2f(0.5, x = 1.0);
    for(int i = 0; c[i] !='\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
        if(c[i] == '\n')
            glRasterPos2f(0.5, x =.1);
    }

    glColor3ub(255, 0, 0);
    c="Press F to START ";
    glRasterPos2f(7.3, .01);
    for(int i = 0; c[i] !='\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

    glFlush();
}
void display(void)
{
	time(&ltime); // Get time
    newtime = localtime(&ltime); // Convert to local time
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0);
	gluLookAt(view[0],view[1],view[2],look[0],look[1],look[2],0.0,1.0,0.0);
	//earth();
	//earth1();
	//clock1();
	//floorWallsCeiling2(300);
    //compound();
//glMatrixMode( GL_PROJECTION );
    //glLoadIdentity();
    ////gluPerspective(60,1,1,500);
    //gluOrtho2D(60,1,1,100);
    //glMatrixMode( GL_MODELVIEW );
    //glLoadIdentity()
   // glRotatef(rotationAngle, 0.0, 1.0, 0.0);
//AC();
// pc();
 pc2();
 pc3();
 pc4();
 pc6();
 large_table();
sky();
//tob();
//glPushMatrix();
//sky();
//glTranslatef(0,200,-6100);
//glRotatef(180,1,1,1);
//glPopMatrix();
stairs();
reling();
//large_table();
insidewall();
//drawSofa();
//house();
drawSofa2();
//house();
 sofa();
  drawSofa3();
 light3();
//drawMulSofa();
//drawSofas();
//glPushMatrix();

tob();
tob2();
 //atm();
//house();
//floorWallsCeiling();
    //glTranslatef(-.5,12.5,-150);
    //atm();
	//atm2();

	house();
	atm();
	atm2();
 //atm2();

	//atm();
	//atm2();
	//floorWallsCeiling();
	//atm3();
	//glPopMatrix();
//tob();
//tob2();
//door();
light();
light1();

floorWallsCeiling();
//atm();
	//atm2();
earth();
	earth1();
 //floorWallsCeiling(30.0);
	//glFlush();
	//glPushMatrix();
	//glTranslated(3,5,20);
	//full_set1();
	//table();

	//glPopMatrix();
	//chair();
	//inside_wall3();

	glPushMatrix();
glTranslated(-3,0,9);
full_set();
glPopMatrix();
glPushMatrix();
glTranslated(1,0,11);

full_set1();
glPopMatrix();
glPushMatrix();
glTranslated(1,0,9);
full_set2();
glPopMatrix();
glPushMatrix();
glTranslated(1,0,7);
full_set3();
glPopMatrix();

glPushMatrix();
glTranslated(1,0,5);
full_set4();
glPopMatrix();

glPushMatrix();
glTranslated(1.8,0,49);
full_set4();
glPopMatrix();

//full_set5();
//1st left flower
glPushMatrix();

 //glScalef(5, 13, 0.3);
//drawCircle();
 drawCircle(-12.0, 18.6,79.5, 2.5, 100);
 //glTranslatef(2.0,17.0,18.5);

// glRotatef(-30,0.0,1,.0);
 glPopMatrix();


glPushMatrix();

 //glScalef(5, 13, 0.3);
//drawCircle();
 drawCircle(12.2, 18.6,79.5, 2.5, 100);
 //glTranslatef(2.0,17.0,18.5);

// glRotatef(-30,0.0,1,.0);
 glPopMatrix();
glPushMatrix();

 //glScalef(5, 13, 0.3);
//drawCircle();
 drawCircle(-21.5, 18.6,79.5, 2.5, 100);
 //glTranslatef(2.0,17.0,18.5);

// glRotatef(-30,0.0,1,.0);
 glPopMatrix();

 glPushMatrix();

 //glScalef(5, 13, 0.3);
//drawCircle();
 drawCircle(21.5, 18.6,79.5, 2.5, 100);
 //glTranslatef(2.0,17.0,18.5);

// glRotatef(-30,0.0,1,.0);
 glPopMatrix();


 glPushMatrix();

 //glScalef(5, 13, 0.3);
//drawCircle();
 drawCircle(-34.5, 18.6,79.5, 2.5, 100);
 //glTranslatef(2.0,17.0,18.5);

// glRotatef(-30,0.0,1,.0);
 glPopMatrix();

glPushMatrix();

 //glScalef(5, 13, 0.3);
//drawCircle();
 drawCircle(30.5, 18.6,79.5, 2.5, 100);
 //glTranslatef(2.0,17.0,18.5);

// glRotatef(-30,0.0,1,.0);
 glPopMatrix();


//sky...............................................................................................................




// building_all();


 glPushMatrix();
    glTranslatef(-150,0,-57);
    building4();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170,0,-34);
    building2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-185,0,-7);
    building2();
    glPopMatrix();

   // glPushMatrix();
        //glTranslatef(0,0,-22);
        glPushMatrix();
        glTranslatef(-180,0,-30);
        building2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(100,0,-40);
        building2();
        glPopMatrix();
 glPushMatrix();
        glTranslatef(120,0,6);
        building2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(90,0,-10);
        building4();
        glPopMatrix();

         glPushMatrix();
        glTranslatef(100,0,-20);
        building2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(33,0,125);
        building2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-10,0,148);
        building3();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-6,0,158);
        building2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-15,0,148);
        building4();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-35,0,128);
        building3();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(45,0,128);
        building3();
        glPopMatrix();
 glPushMatrix();
        glTranslatef(55,0,126);
        building4();
        glPopMatrix();

         glPushMatrix();
        glTranslatef(-45,0,126);
        building4();
        glPopMatrix();
         glPushMatrix();
        glTranslatef(-120,0,-70);
        building2();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-130,0,-7);
        building2();
        glPopMatrix();

   // glPopMatrix();
glPushMatrix();
    glTranslatef(70,0,-120);
    building3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18,0,-135);
    building4();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(-18,0,-145);
    building2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-135,0,1);
    building4();
    glPopMatrix();
    table3();
    locker();
    //glEnable(GL_TEXTURE_2D);
   // glPushMatrix();
     //glEnable(GL_TEXTURE_2D);
   //// glBindTexture(GL_TEXTURE_2D,23);
    //glScalef(5,2.7,2);
    //glTranslatef(18,-.9,90);
    //glRotatef(90,0,1,0);
    //bus2();
    //glPopMatrix();

    //glEnable(GL_TEXTURE_2D);
   // atm();
	//atm2();
busmove();
busmove2();
tob4();
 ac2();
 cube4();
 //start();
	glutSwapBuffers();
	glutPostRedisplay();

}
static void getMouseInputs(GLint mouseButton, GLint mouseAction, int Xmouse , int Ymouse){
if(mouseButton==GLUT_RIGHT_BUTTON&&mouseAction==GLUT_DOWN){
glPushMatrix();
glPopMatrix();
glFlush();
}else if(mouseButton==GLUT_LEFT_BUTTON&&mouseAction==GLUT_DOWN){
glPushMatrix();
glPopMatrix();
glFlush();
}
}
void clearMyScreen(){
glClear(GL_COLOR_BUFFER_BIT);
}
void mySpecialKeyFunc(GLint specialKey, int Xmouse, int Ymouse){
switch(specialKey){
        case GLUT_KEY_HOME:
            display();

   break;

   case GLUT_KEY_LEFT:
            rotationAngle += 5.0;  // Adjust the rotation angle as needed
            glutPostRedisplay();
            break;
}
glFlush();

}

void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
          //go inside
	    case '1':
				view[2]-=2.1;
				glutPostRedisplay();

	break;

	case 'z':
				view[2]-=3;
				glutPostRedisplay();

	break;


	//go outside
	case '2':
				view[2]+=2.1;
				glutPostRedisplay();
				break;

    //to run and stop the fan
	case 'S':

				view[1]+=.5;
				glutPostRedisplay();


	break;


	case 's':
	    view[1]-=.5;
				glutPostRedisplay();
break;
	//to open and close the main door
	case 'P':
	  //  bRotate== true;
	  //  break;
	//case 'P':0
	  //// bRotate== false;
	   // break;
				if(maino==0)
				  maino=90;
            else
                maino=0;
	break;
	//to open and close inside room door
	case 'o':
	    view[0]+=.5;
				glutPostRedisplay();
break;
	case 'O':
				if(roomo==0)
				  roomo=75;
				else
					roomo=0;
	break;
	//to open and close main gate
	case 'g':
	     view[0]-=.5;
				glutPostRedisplay();

break;
	case 'G':
				if(mgo==0)
				  mgo=1;
				else
					mgo=0;
	break;

	//inside view
	case 'i':
	case 'I':
				view[0]=2.8;
				view[1]=2;
				view[2]=4.8;
				look[0]=2.8;
				look[1]=2;
				look[2]=1;
	break;
	//top view
	case 'T':
	case 't':
				view[0]=56;
				view[1]=56;
				view[2]=56;
				look[0]=29;
				look[1]=29;
				look[2]=31;
	break;
	//top view
	case 'v':

				view[0]=22;
				view[1]=22;
				view[2]=22;
				look[0]=19;
				look[1]=19;
				look[2]=21;

	break;


	case 'f':

				view[0]=22;
				view[1]=22;
				view[2]=22;
				look[0]=19;
				look[1]=19;
				look[2]=21;

	break;

//front view

	case 'F':

				view[1]+=66;

glutPostRedisplay();
				break;
	break;
	//back view
	case 'b':
	    view[1]+=.5;
				glutPostRedisplay();
				break;

	case 'B':
 view[0]+=.5;
				glutPostRedisplay();
				break;

	break;
	 case 'e':
              view[2]-=.1;
				glutPostRedisplay();
                  break;

case 'a':
       view[2]+=15;
				glutPostRedisplay();
        break;
case 'k':
    // Assuming you have a rotation angle variable (in radians)
    rotationAngle += 0.1;

    // Apply rotation to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(rotationAngle * 180.0 / M_PI, 0.0, 1.0, 0.0);  // Rotate around the y-axis

    glutPostRedisplay();
    break;

    case 'm':
    // Assuming you have a rotation angle variable (in radians)
    rotationAngle -= 1.5;

    // Apply rotation to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(rotationAngle * 180.0 / M_PI, 0.0, 1.0, 0.0);  // Rotate around the y-axis

    glutPostRedisplay();
    break;

    case 'n':
    // Assuming you have a rotation angle variable (in radians)
    rotationAngle += 1.5;

    // Apply rotation to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(rotationAngle * 180.0 / M_PI, 0.0, 1.0, 0.0);  // Rotate around the y-axis

    glutPostRedisplay();
    break;
     case 'u':
        rot++;
        break;

    case 'c':
        rot--;
        break;


    case '5':
        l_on1=!l_on1;
        break;
    case '6':
        l_on2=!l_on2;
        break;
    case '7':
        l_on3=!l_on3;
        break;

    case '8':
        amb= !amb;
        break;
    case '9':
        spec =!spec;
        break;
    case '0':
        dif=!dif;
         break;



    case 'L':
        l_on1=!l_on1;
        break;
    case 'K':
        l_on2=!l_on2;
        break;
    case 'J':
        l_on3=!l_on3;
        break;

    case 'H':
        amb= !amb;
        break;
    case 'V':
        spec =!spec;
        break;
    case 'Y':
        dif=!dif;
         break;


 exit(0);
    default:
clearMyScreen();




}

	}
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'd':
        rot++;
        break;

    case 'a':
        rot--;
        break;

    case 'w':
        eyeY++;
        break;

    case 's':
        eyeY--;
        break;

    case 'z':
        eyeX=0;
        eyeZ++;
        lookZ++;
        break;

    case 'x':
        eyeZ--;
        break;


    case '5':
        l_on1=!l_on1;
        break;
    case '6':
        l_on2=!l_on2;
        break;
    case '7':
        l_on3=!l_on3;
        break;

    case '8':
        amb= !amb;
        break;
    case '9':
        spec =!spec;
        break;
    case 'k':
        dif=!dif;
        break;


    }
}
double Eyex=0, Eyey=15, Eyez=20, Eyex_tem, Eyey_tem, Eyez_tem;
double lookatx=0, lookaty=15, lookatz=0;
double headx=0, heady=1, headz=0;
double fovy=120;
double speed_turbine=1.5;
//pitch variable
///double dx;
//double dz;
double dx2_dz2;
double pitch_theta=.004;
double lookaty_tem, lookatz_tem;
double roll_value = 0.2, pi = acos(-1), cs_angle=cos(pi/180), sn_angle=sin(pi/180);
GLfloat dx, dy, dz, dxyz;
//unsigned int ID;

//yaw variabl
double lookatx_tem;

//GLfloat alpha = 0.0, theta = 0.0, gama=0.0, axis_x=0.0, axis_y=0.0, axis_z=0,
GLfloat eyethetax=0, eyethetay=0, eyethetaz=0;
GLfloat turbine_theta=0;
GLboolean xRotate = false, yRotate = false, zRotate = false, eyerotatex=false, eyerotatey=false, eyerotatez=false;
GLboolean turbine_rotate = true;

//double bus_switch=true;
//double busx=-10, busy, busz=7;

const int L=20;
int anglex= 0, angley = 0, anglez = 0;          //rotation angles
//int window;
int wired=0;
int shcpt=1;
int animat = 0;
//const int L=20;
const int dgre=3;
int ncpt=L+1;
int clikd=0;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;

void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }


    if (fRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

  if(eyerotatex==true)
    {

        eyethetax -= 0.0000002;
        if(eyethetax > 360.0)
            eyethetax -= 360.0*floor(eyethetax/360.0);
        Eyex=Eyex;
        Eyey=Eyey*cos(eyethetax)-Eyez*sin(eyethetax);
        Eyez=Eyey*sin(eyethetax)+Eyez*cos(eyethetax);

    }
    if(eyerotatey==true)
    {

        eyethetay -= 0.0000002;
        if(eyethetay > 360.0)
            eyethetay -= 360.0*floor(eyethetay/360.0);
        Eyex=Eyex*cos(eyethetay)+Eyez*sin(eyethetay);
        Eyey=Eyey;
        Eyez=-Eyex*sin(eyethetay)+Eyez*cos(eyethetay);

    }
    if(eyerotatez==true)
    {

        eyethetaz -= 0.00000002;
        if(eyethetaz > 360.0)
            eyethetaz -= 360.0*floor(eyethetaz/360.0);
        Eyex=Eyex*cos(eyethetaz)-Eyey*sin(eyethetaz);
        Eyey=-Eyex*sin(eyethetaz)+Eyey*cos(eyethetaz);
        Eyez=Eyez;
    }

    if(turbine_rotate==true)
    {
        turbine_theta += speed_turbine;
        if(turbine_theta > 360.0)
            turbine_theta -= 360.0*floor(turbine_theta/360.0);
    }


    ///light();
    //bus();

    glutPostRedisplay();

}
void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


int main(int argc,char**argv)

{

    printf("**<<Press G for Gate on & off>>**\n");
    printf("**<<Press P for Main door & O for insider door on & off>>**\n");
    printf("**<<Press I for inside view & T for top view >>**\n");
    printf("**<<Press B for back view & F for front view>>**\n");
    printf("**<<Press S for Fan on & off>>**\n");
    printf("**<<Press 1 for go inside slow & 2 for back outside>>**\n");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(3066,2068);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bank");
	myinit();
	//glutReshapeFunc(res);
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);

LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\ci.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\flo1.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\images.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\high.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\cilling.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\right.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\sofa.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\floor4.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\wall11.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\cill.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\high.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\building1.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\sky.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\road.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\black.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\ke.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\gras.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\atm2.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\wood2.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\wood3.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\atm2.bmp");

LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\gg.bmp");
LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\white.bmp");

LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\wall8.bmp");
//LoadTexture("C:\\Users\\ASUS\\Desktop\\bank2\\bmp\\ac.bmp");
//LoadTexture("C:\\Users\\ASUS\\Desktop\\ri\\bmp\\chr.bmp");
	glutSpecialFunc(mySpecialKeyFunc);
	glutMouseFunc(getMouseInputs);
	glutIdleFunc(animate);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);//smooth shaded
	glEnable(GL_DEPTH_TEST);//to remove hidden surface
	glEnable(GL_NORMALIZE);//to make normal vector to unit vector
	glEnable(GL_BLEND);
	glClearColor(0.53,0.81,0.92,1);
	sndPlaySound("sound1.wav",SND_ASYNC);
	glutMainLoop();
	return 0;
}



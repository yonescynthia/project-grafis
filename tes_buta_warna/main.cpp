#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "imageloader.h"

GLUquadric *bola;
GLuint bolaTexture;

GLUquadric *bola2;
GLuint bolaTexture2;

int zoom = 0;
boolean twist = true, twistR= true, twistG= true, twistB= true, twistM= true, twistJ= true, twistS= true, twistN= true, twistU= true, twistP= true;
float Cx = 0.0f, Cy = 2.5f, Cz = 10.0f;
float Lx = 0.0f, Ly = 2.5f, Lz = -50.0f;
float sudut_x = 0.0f;
float sudut_x2 = 0.0f;
float sudut_z = 0.0f;
float sudut_z2 = 0.0f;
float sudut_y = 0.0f;
float sudut_y2 = 0.0f;


char jawaban[4] = {'1', '2', '3', '4'};
int posisi = 0;

GLUquadric *bola;
GLuint bolaTexture;

GLuint loadTexture(Image* image) {

    GLuint textureId;

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    return textureId;

}

float toRadians(float angle){
    return angle * M_PI / 180;
}

class Vector{
public :
    float x, y, z;
    void set_values (float startX, float startY, float startZ){
         x = startX;
         y = startY;
         z = startZ;
    }

    void vectorRotation(Vector refs, float angle){
        Vector temp = refs;
        float magnitude = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
        temp.x = temp.x / magnitude;
        temp.y = temp.y / magnitude;
        temp.z = temp.z / magnitude;
        float dot_product = (x * temp.x)+(y * temp.y)+(z * temp.z);
        float cross_product_x = (y * temp.z) - (temp.z * z);
        float cross_product_y = -((x * temp.z) - (z * temp.x));
        float cross_product_z = (x * temp.y) - (y * temp.x);
        float last_factor_rodrigues = 1.0f - cos(toRadians(fmod(angle, 360.0f)));
        x = (x * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_x * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * x);
        y = (y * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_y * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * y);
        z = (z * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_z * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * z);
    }
};

void cameraRotation(Vector refer, double angle){
    float M = sqrt(pow(refer.x, 2) + pow(refer.y, 2) + pow(refer.z, 2));
    float Up_x1 = refer.x / M;
    float Up_y1 = refer.y / M;
    float Up_z1 = refer.z / M;
    float VLx = Lx - Cx;
    float VLy = Ly - Cy;
    float VLz = Lz - Cz;
    float dot_product = (VLx * Up_x1) + (VLy * Up_y1) + (VLz * Up_z1);
    float cross_product_x = (Up_y1 * VLz) - (VLy * Up_z1);
    float cross_product_y = -((Up_x1 * VLz) - (Up_z1 * VLx));
    float cross_product_z = (Up_x1 * VLy) - (Up_y1 * VLx);
    float last_factor_rodrigues = 1.0f - cos(toRadians(angle));
    float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLx);
    float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLy);
    float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLz);
    Lx = Lx1+Cx;
    Ly = Ly1+Cy;
    Lz = Lz1+Cz;
}

void initGL(int width, int height)
{
    const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);

    bola = gluNewQuadric();
    gluQuadricTexture( bola, GL_TRUE);

    //Image* bolaImage=loadBMP("./image2.bmp");
    //bolaTexture = loadTexture(bolaImage);

    bola2 = gluNewQuadric();
    gluQuadricTexture( bola2, GL_TRUE);
    //Image* bolaImage2=loadBMP("./earth.bmp");
    //bolaTexture2 = loadTexture(bolaImage2);

    Image* bolaImage=loadBMP("./image2.bmp");
    bolaTexture1 = loadTexture(bolaImage);

    bola2 = gluNewQuadric();
    gluQuadricTexture( bola2, GL_TRUE);
    Image* bolaImage2=loadBMP("./earth.bmp");
    bolaTexture2 = loadTexture(bolaImage2);

    gluPerspective(80.0f, (GLfloat)width/(GLfloat)height, 2.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

}


Vector sumbu_z, sumbu_x, sumbu_y;

float Ex = 0 ,Ey = 0,Ez,Cex,Cey,Cez;
static void display(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
glMatrixMode(GL_MODELVIEW);

glLoadIdentity();
gluLookAt(Cx, Cy, Cz,
            Lx, Ly, Lz,
            0, 1, 0);



    glPushMatrix();
    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, bolaTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0.0f,0.0f,-5);
    glTranslatef(0.0f,0.0f,0.0f);
    gluSphere(bola, 7, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, bolaTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0.0f,0.0f,-5);
    glTranslatef(30.0f,0.0f,0.0f);
    gluSphere(bola, 7, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, bolaTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0.0f,0.0f,-5);
    glTranslatef(60.0f,0.0f,0.0f);
    gluSphere(bola, 7, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, bolaTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0.0f,0.0f,-5);
    glTranslatef(90.0f,0.0f,0.0f);
    gluSphere(bola, 7, 20, 20);
    glPopMatrix();


   glPushMatrix();
      glTranslatef(0.0,0.0,1.0);
      glScalef(0.5,0.5,0.5);
   glPopMatrix();

glDisable ( GL_TEXTURE_2D );

glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void keyboard(unsigned char key,int x,int y)
{
    if (zoom < -40){
            zoom = -40;
         }
    if (zoom > 60){
            zoom = 60;
         }
	switch(key)
	{


case '1':
    if ('1' == jawaban[posisi]){
        posisi += 1;
        Lz -= 1;
        Lx += 1;
    }
    break;

case '2':
    if ('2' == jawaban[posisi]){
        posisi += 1;
        Lz -= 1;
        Lx += 1;
    }
    break;

case '3':
    if ('3' == jawaban[posisi]){
        posisi += 1;
        Lz -= 1;
        Lx += 1;
    }
    break;

case '4':
    if ('4' == jawaban[posisi]){
        posisi += 1;
        Lz -= 1;
        Lx += 1;
    }
    break;


    case 'f':
        Lz -= 1;
        Lx += 1;
        break;

    case 'g':
        Cx += 20;
        Lx += 20;
        break;

    case 'a':
        Cx -= 1;
        Lx -= 1;
        break;
    case 's':
        Cz = Cz +1;
        break;
    case 'd':
        Cx += 1;
        Lx += 1;
        break;
    case 'w':
        Cz = Cz -1;
        break;
    case 'e': /* exit */
	     exit(0);
        break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    int width = 640;
    int height = 480;
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Tes Buta Warna");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    initGL(width, height);
    glutMainLoop();
    return 0;
}

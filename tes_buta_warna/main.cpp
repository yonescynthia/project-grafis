#include <windows.h>
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "imageloader.h"

using namespace std;

GLuint loadTexture(Image* image) {
  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,
               0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    return textureId;
}
    GLuint _textureId;
    GLUquadric *quad;
    float rotate;
    //GLUquadricObj quad;

void initRendering(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    quad = gluNewQuadric();

    Image* image = loadBMP("tes_2.bmp");
    _textureId = loadTexture(image);
    delete image;

    }
void Resize(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

float view_rotx = 20.0f, view_roty = 30.0f;
int oldMouseX, oldMouseY;

    void initGL(){
    glShadeModel(GL_FLAT);

    float ambient[] = {1.0f,1.0f,1.0f,1.0f};
    float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
    float specular[] = {0.2f,1.0f,0.2f,1.0f};
    float position[] = {20.0f,30.0f,20.0f,0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    float mambient[] ={0.1745f, 0.01175f, 0.01175f, 0.55f};
    float mdiffuse[] ={0.61424f, 0.04136f, 0.04136f, 0.55f };
    float mspecular[] ={0.727811f, 0.626959f, 0.626959f, 0.55f };
    float mshine =76.8f;

    glMaterialfv(GL_FRONT,GL_AMBIENT,mambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mdiffuse);


    glMaterialfv(GL_FRONT,GL_SPECULAR,mspecular);
    glMaterialf (GL_FRONT,GL_SHININESS,mshine);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    }

void Bola(){
    glColor3f(0,1,1);
    float BODY_RADIUS=0.5f;
    int SLICES=30;
    int STACKS=30;
    GLUquadric *q = gluNewQuadric();
    gluSphere(q, BODY_RADIUS, SLICES, STACKS);
    }

double putaran = 0.0;
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluLookAt(4,4,4, // eye pos
    0,0,0, // look at
    0,0,1); // up
    putaran+=0.2;

    glTranslatef(0.5f, 0.5f, 0.5f);
    glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(view_roty, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.5f, -0.5f, -0.5f);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluQuadricTexture(quad, 1);
    gluSphere(quad, 2, 20, 20);
    Bola();

    glFlush();
    glutSwapBuffers();
    }

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0);
    }

void reshape(GLsizei width, GLsizei height){
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(30, 6, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

void mouseControl(int button, int state, int x, int y){
    oldMouseX = x;
    oldMouseY = y;
}

void mouseMotion(int x, int y){
    int getX = x;
    int getY = y;
    float thetaY = 360.0f*(getX - oldMouseX)/640;
    float thetaX = 360.0f*(getY - oldMouseY)/480;
    oldMouseX = getX;
    oldMouseY = getY;
    view_rotx += thetaX;
    view_roty += thetaY;
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("TES BUTA WARNA");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

initGL();
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

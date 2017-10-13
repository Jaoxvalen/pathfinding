#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Constants.h"
#include "Utils.h"
#include "Context.h"
#include "InputFile.h"

using namespace std;

Context mContext;

void onLoad()
{
    Utils::initialize_randomness(-1);
    mContext.loadGraph("../gtest.txt");
    
}

void onEnterFrame()
{
    mContext.drawGraph();
}

void init()
{
    Utils::initialize_randomness(-1);
    glClearColor(0.0,0.0,0.0,0.0);
    onLoad();
}

void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    onEnterFrame();
    glutSwapBuffers();
}


void reShapeCallback(int w,int h)
{
    // Set the viewport according to the window's dimensions
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Orthographic projection
    glOrtho(0,WIDTH*SCALE,HEIGHT*SCALE,0.0,0.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timerCallback(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timerCallback,0);
}

int main(int argc, char** argv)
{
    
    glutInit(&argc,argv);
    // RGBA mode and a double buffered window
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Test");
    // Registration of the display callback function 
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reShapeCallback);
    glutTimerFunc(0,timerCallback,0);
    init();
    glutMainLoop();
    return 0;
}

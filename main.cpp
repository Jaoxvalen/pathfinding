#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Constants.h"
#include "Utils.h"
#include "Context.h"
#include "InputFile.h"
#include "Menu.h"
#include "Drawer.h"

using namespace std;
using namespace glm;

Context* mContext;
Menu* mMenu;

GLFWwindow* window;
Drawer oDrawer;


//manager
void onLoad()
{
    oDrawer.loadGraph();
}

void onEnterFrame()
{
    oDrawer.drawGraph();
}

void onFinish()
{
    oDrawer.cleanUP();
}


//no tocar
int init()
{
	if( !glfwInit() )
	{
        cout<<"Failed to initialize GLFW"<<endl;
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( WIDTH, HEIGHT, "Titulo", NULL, NULL);
	if( window == NULL ){
		cout<<"Failed to open GLFW window"<<endl;
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
        cout<<"Failed to initialize GLEW"<<endl;
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    onLoad();
    
}

void loopMain()
{
    do{
		glClear( GL_COLOR_BUFFER_BIT );
        onEnterFrame();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&glfwWindowShouldClose(window) == 0 );
}

void cleanUP()
{
    onFinish();
	glfwTerminate();
}

int main( void )
{
	init();
    loopMain();
    cleanUP();
	return 0;
}

/*
void onLoad()
{
    mContext=new Context();
    mMenu=new Menu(mContext);
    mContext->mDrawer.loadGraph();
    mContext.loadGraph("../10000points.data");
    //mContext.generatedGraph("../gtest.txt",100);
    //mContext.PreSolverGraph();
    //mContext.solver();
    mContext.loadPresolver();
}

void onEnterFrame()
{
    mMenu->main();
    mContext->mDrawer.drawGraph();
    //mContext.drawGraph();
    //mContext.drawPath();
}

void init()
{
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
    
    if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		return -1;
	}
    
    glutInit(&argc,argv);
    // RGBA mode and a double buffered window
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(WIDTH,HEIGHT);
    //glEnable(GL_BLEND);
    glutCreateWindow("Test");
    // Registration of the display callback function 
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reShapeCallback);
    glutTimerFunc(0,timerCallback,0);
    init();
    glutMainLoop();
    return 0;
}

*/
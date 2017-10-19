#pragma once
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include "Shaders.hpp"

using namespace glm;
using namespace std;

namespace visual
{
    
class Point
{
public:
    int x,y;
    Point(int _x, int _y)
    {
        x=_x;
        y=_y;
    }
};
class Color
{
public:
    float R, G, B, A;
    Color(float _R, float _G, float _B, float _A)
    {
        R = _R;
        G = _G;
        B = _B;
        A = _A;
    }
};

class Drawer
{
public:
    //Color* RED = new Color(1.0, 0.0, 0.0, 1.0);
    //Color* GREEN = new Color(0.0, 1.0, 0.0, 1.0);
    //Color* BLUE = new Color(0.0, 0.0, 1.0, 1.0);
    
    
    GLuint vertexbuffer;
    GLuint VertexArrayID;
    GLuint programID;
    
    Drawer()
    {
        
    }
    
    void loadGraph()
    {
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        // Create and compile our GLSL program from the shaders
        programID = LoadShaders( "../SimpleVertexShader.vertexshader", "../SimpleFragmentShader.fragmentshader" );

        GLfloat g_vertex_buffer_data[] = { 
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
        };

        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    }
    void drawGraph()
    {
       glUseProgram(programID);

		// 1rst attribute buffer : vertices
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
        glEnableVertexAttribArray(0);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

    }
    
    void cleanUP()
    {
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteVertexArrays(1, &VertexArrayID);
    }
    
    
    void line(int x1, int y1, int x2, int y2, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
        glEnd();
        delete color;
    }
    void line(int x1, int y1, int x2, int y2, Color* color, int tam)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(tam);
        glBegin(GL_LINES);
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
        glEnd();
        delete color;
    }
    void line(Point p1, Point p2, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2d(p1.x,p1.y);
        glVertex2d(p2.x,p2.y);
        glEnd();
        delete color;
    }
    

    void rect(int x1, int y1, int x2, int y2, int x3, int y3,int x4, int y4, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(1);
        glBegin(GL_LINES);
        
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);
        
        glVertex2f(x3,y3);
        glVertex2f(x4,y4);
        
        glVertex2f(x4,y4);
        glVertex2f(x1,y1);
        
        glEnd();
        delete color;
    }
    
    void rect(Point p1, Point p2, Point p3, Point p4, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(1);
        glBegin(GL_LINES);
        
        glVertex2f(p1.x,p1.y);
        glVertex2f(p2.x,p2.y);
        
        glVertex2f(p2.x,p2.y);
        glVertex2f(p3.x,p3.y);
        
        glVertex2f(p3.x,p3.y);
        glVertex2f(p4.x,p4.y);
        
        glVertex2f(p4.x,p4.y);
        glVertex2f(p1.x,p1.y);
        glEnd();
        delete color;
    }
    void circ(int x, int y, int radius, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        int i;
        int lineAmount = 100;
        GLfloat twicePi = 2.0f * PI;
        glBegin(GL_LINE_LOOP);
        for(i = 0; i <= lineAmount; i++) {
            glVertex2f(x + (radius * cos(i * twicePi / lineAmount)), y + (radius * sin(i * twicePi / lineAmount)));
        }
        glEnd();
        delete color;
    }
    
    void circ(Point point, int radius, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        int i;
        int lineAmount = 100;
        GLfloat twicePi = 2.0f * PI;
        glBegin(GL_LINE_LOOP);
        for(i = 0; i <= lineAmount; i++) {
            glVertex2f(point.x + (radius * cos(i * twicePi / lineAmount)), point.y + (radius * sin(i * twicePi / lineAmount)));
        }
        glEnd();
        delete color;
    }
    
    
    void circFill(int x, int y, int radius, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        int i;
        int triangleAmount = 4; //# of triangles used to draw circle
        // GLfloat radius = 0.8f; //radius
        GLfloat twicePi = 2.0f * PI;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),
                       y + (radius * sin(i * twicePi / triangleAmount)));
        }
        glEnd();
        delete color;
    }
};
}
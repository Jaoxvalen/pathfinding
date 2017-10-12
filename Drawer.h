#pragma once
#include <math.h>
#include <vector>

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
    Color* RED = new Color(255, 0, 0, 255);
    Color* GREEN = new Color(0, 255, 0, 255);
    Color* BLUE = new Color(0, 0, 255, 255);
    Drawer()
    {
    }

    void line(int x1, int y1, int x2, int y2, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
        glEnd();
    }
    void line(Point p1, Point p2, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2d(p1.x,p1.y);
        glVertex2d(p2.x,p2.y);
        glEnd();
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
    }
    
    
    void circFill(int x, int y, int radius, Color* color)
    {
        glColor4f(color->R, color->G, color->B, color->A);
        int i;
        int triangleAmount = 20; //# of triangles used to draw circle
        // GLfloat radius = 0.8f; //radius
        GLfloat twicePi = 2.0f * PI;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),
                       y + (radius * sin(i * twicePi / triangleAmount)));
        }
        glEnd();
    }
};
}
//
//  main.cpp
//  Paint_Project
//
//  Created by Derek J Wene on 9/4/14.
//  Copyright (c) 2014 Derek Wene. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

int SIZE = 8;
int HEIGHT = 600;
int WIDTH = 800;
int STATE = 1;
int BRUSH = 3;
int ANGLE = 0;
double PI = 3.14;
bool sprayPaint = false;
int color[3] = {1, 1, 1};


void keyboard(unsigned char, int, int);
void click(int, int, int, int);
void drag (int, int);
void drawCurrent (int, int);
void drawCircle (int, int);
void drawSpray(int x, int y);
int main(int argc, char ** argv)
{
    
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Lab 1");
    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1, 1, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(click);
    glutMotionFunc(drag);
//    glClearColor(0,0,0,1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glOrtho(0, 1, 0, 1, 0, 1);
    glutMainLoop();
    return 0;
}

void display()
{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1, 1, 0);
//    glBegin(GL_LINES);
//    glEnd();

    std::cout<<"display was just called\n";
    glFlush();
    /* swap the back and front buffers so we can see what we just drew */
//    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    std::cout<<"x: " <<x << " y: " << y << " key: ";
    std::cout<<key;
    std::cout<<std::endl;
    if (key == '+' && SIZE < 64){
        SIZE*=2;
        glFlush();
    }
    if (key == '-' && SIZE > 1){
        SIZE/=2;
        glFlush();
    }
    if (key == 'c'){
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
    if (key == '1'){
        color[0] = 0;
        color[1] = 0;
        color[2] = 1;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == '2'){
        color[0] = 0;
        color[1] = 1;
        color[2] = 0;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == '3'){
        color[0] = 0;
        color[1] = 1;
        color[2] = 1;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == '4'){
        color[0] = 1;
        color[1] = 0;
        color[2] = 0;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == '5'){
        color[0] = 1;
        color[1] = 0;
        color[2] = 1;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == '6'){
        color[0] = 1;
        color[1] = 1;
        color[2] = 0;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == '7'){
        color[0] = 1;
        color[1] = 1;
        color[2] = 1;
        glColor3f(color[0], color[1], color[2]);
        glFlush();
    }
    if (key == 'b'){
        if (BRUSH < 3){
            BRUSH++;
        }
        else{
            BRUSH = 0;
        }
    }
    if (key == 'r'){
        if (ANGLE == 350){
            ANGLE = 0;
        }
        else{
            ANGLE += 10;
        }
    }
    if (key == 'a' && BRUSH == 3){
        sprayPaint = !sprayPaint;
    }
}


void click(int button , int state, int x, int y){
    STATE = state;
    drawCurrent(x, y);

//    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0,0,width,height);
    WIDTH = width;
    HEIGHT = height;
//    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(0,width,height,0);
//    glMatrixMode(GL_MODELVIEW);
}

double xoffset(float angle, float length){
    return SIZE * length * cos(PI*(ANGLE+angle)/180);
}
double yoffset(float angle, float length){
    return SIZE * length * sin(PI*(ANGLE+angle)/180);
}


void drawCurrent(int x, int y){
//    int xoffset =  (SIZE*cos(PI*ANGLE/180));
//    int yoffset =  (SIZE*sin(PI*(ANGLE+90)/180));
    if (BRUSH == 0){
        glBegin(GL_POLYGON);
        glVertex2f(x+xoffset(45, sqrt(2)), y+yoffset(45, sqrt(2)));
        glVertex2f(x+xoffset(135, sqrt(2)), y+yoffset(135, sqrt(2)));
        glVertex2f(x+xoffset(-135, sqrt(2)), y+yoffset(-135, sqrt(2)));
        glVertex2f(x+xoffset(-45, sqrt(2)), y+yoffset(-45, sqrt(2)));
        glEnd();
    }
    else if (BRUSH == 1){
        glBegin(GL_POLYGON);
        glVertex2f(x+xoffset(-135, sqrt(2)), y+yoffset(-135, sqrt(2)));
        glVertex2f(x+xoffset(-45, sqrt(2)), y+yoffset(-45, sqrt(2)));
        glVertex2f((x + xoffset(90, 1)), y + yoffset(90, 1));
        glEnd();
//        glRotatef(ANGLE, 0, 0, 1);
//        glTranslatef(x, y, 0);
    }
    else if (BRUSH == 2){
        glBegin(GL_LINES);
        glVertex2f(x + xoffset(90, 1),y+yoffset(90, 1));
        glVertex2f(x + xoffset(-90, 1),y+yoffset(-90, 1));
        glEnd();
    }
    else if (BRUSH == 3){
        if (sprayPaint){
            drawSpray(x, y);
        }
        else{
            drawCircle(x, y);
        }
    }
    glFlush();
}

void drawCircle(int x, int y){
    glBegin(GL_POLYGON);
    float newx = 0;
    float newy = 0;
    for (int i = 0; i < 360; i++){
        newx = (x+SIZE*cos((i*PI)/180.0));
        newy = (y+SIZE*sin((i*PI)/180.0));
            glVertex2f(newx, newy);
    }
    glEnd();
}

void drawSpray(int x, int y){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    glColor4f(color[0], color[1], color[2], 0);
    for (int i = 0; i < 360; i++){
        glVertex2f((x+SIZE*cos((i*PI)/180.0)), (y+SIZE*sin((i*PI)/180.0)));
    }
    glEnd();
    glColor4f(color[0], color[1], color[2], 1);
}

void drag (int x, int y){
    if (!STATE){
        drawCurrent(x, y);
    }
    std::cout<<STATE<<" "<<x<<" "<<y<<std::endl;
}


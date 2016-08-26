//
//  Dennis Bounded
//  CS3600 Computer Graphics I
//  Raster Project
//
//  bresenham.cpp
//
//  Created by Dennis Bounded on 3/4/16.
//  Copyright © 2016 Dennis Bounded. All rights reserved.
//  An interactive demostration of Bresenham's line algorithm
//  using "simulated" pixels

#include <iostream>
#include "Point.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


/* Global Constants */
static const int
PIXEL_SIZE = 10,
GAP_SIZE = 1,
WIN_SIZE = 500,
RDIM = WIN_SIZE / (PIXEL_SIZE + GAP_SIZE);
Point raster[RDIM][RDIM];

/* Global Variables */
static bool firstPixelChosen = false;
static int
raster_x,
raster_y,
start_x,
start_y = 0;

// Turns pixel on
void setPixelOn(int x, int y)
{
    glColor3ub(255, 0, 0);
    glVertex2i(raster[x][y].get_x(), raster[x][y].get_y());
}

// Translates pixel coordinate to raster coordinate
// y is in screen coordinate
void pixelToRaster(int x, int y)
{
    raster_x = (x - (2 * GAP_SIZE)) / (PIXEL_SIZE + GAP_SIZE); // x - 2 * GAP_SIZE to "round down"
    raster_y = (WIN_SIZE - y) / (PIXEL_SIZE + GAP_SIZE);
}


// Draw a raster RDIM by RDIM size
void drawRaster()
{
    
    int i,j,k,l = 0;
    
    
    /* Clear Window */
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(PIXEL_SIZE);  // Sets Pixel Size
    
    glColor3ub(255, 255, 255);
    
    glBegin(GL_POINTS);
    
        /* Draw Raster */
        for (i = PIXEL_SIZE - (2 * GAP_SIZE), k = 0; i < WIN_SIZE; i += (PIXEL_SIZE + GAP_SIZE), k++) {
            for (j = PIXEL_SIZE- (2 * GAP_SIZE), l = 0; j < WIN_SIZE; j += (PIXEL_SIZE + GAP_SIZE), l++){
                glVertex2i(i, j);
                // Save Pixel Coordinate as Raster Coordinate
                raster[k][l].set(i,j);
            }
        }
    
    glEnd();
    
}

// Draws a line between two pixels using
// Bresenham's Algorithm
void lineBresenham(int x0, int y0, int x1, int y1)
{
    int dx, dy;
    int stepx, stepy;
    
    dx = x1 - x0;
    dy = y1 - y0;
    
    if (dy<0) {dy=-dy; stepy=-1;} else {stepy=1;}
    if (dx<0) {dx=-dx; stepx=-1;} else {stepx=1;}
    dy <<= 1; /* dy is now 2*dy */
    dx <<= 1; /* dx is now 2*dx */
    
    if ((0 <= x0) && (x0 < RDIM) && (0 <= y0) && (y0 < RDIM))
        setPixelOn(x0, y0);
    
    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            x0 += stepx;
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            fraction += dy;
            if ((0 <= x0) && (x0 < RDIM) && (0 <= y0) && (y0 < RDIM))
                setPixelOn(x0, y0);
            
        }
        
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            if ((0 <= x0) && (x0 < RDIM) && (0 <= y0) && (y0 < RDIM))
                setPixelOn(x0, y0);
        }
    }
    
    
}


void display()
{
    
    drawRaster();
    
    /* Draw lines using Bresenham's Algorithm */
    /*
    lineBresenham(6, 33,  3, 13);
    lineBresenham(9, 33, 12, 13);
    lineBresenham(4,  4, 23,  3);
    lineBresenham(10,  38, 33, 42);
    lineBresenham(28, 12, 14, 30);
    lineBresenham(8, 5, 21, 24);
    */
    
    std::cout << "PICK TWO PIXELS WITH MOUSE\n";
    
    /* Flush GL buffers */
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    // Set raster coordinate from corresponding pixel coordinate
    pixelToRaster(x,y);
    
    if (!firstPixelChosen && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        std::cout << "START PIXEL: (" << raster_x << "," << raster_y << ")\n";
        glBegin(GL_POINTS);
            setPixelOn(raster_x,raster_y);
        glEnd();
        
        // Save first raster coordinate
        start_x = raster_x;
        start_y = raster_y;
        firstPixelChosen = true;
        
        glFlush();
       
    }
    
    else if(firstPixelChosen && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        std::cout << "END PIXEL: (" << raster_x << "," << raster_y << ")\n";
        glBegin(GL_POINTS);
            lineBresenham(start_x, start_y, raster_x, raster_y);
        glEnd();
        firstPixelChosen = false;
        
        glFlush();
    }
    /* */
}

void init()
{
    /* Initializations */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_SIZE, WIN_SIZE);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Raster Bresenham Line");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIN_SIZE, 0.0, WIN_SIZE);
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    
}


int main(int argc, char ** argv)
{
    
    glutInit(&argc , argv);
    init();
    glutMainLoop();
    
    return 0;
}

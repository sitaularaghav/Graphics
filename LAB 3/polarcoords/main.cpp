#include <GL/glut.h>
#include <cmath>
#include<iostream>
// Function to draw a circle using Polar Coordinate system
void draw_circle_polar(float x_centre, float y_centre, float radius, int num_segments = 360) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; ++i) {
        float theta = 2.0 * M_PI * i / num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x + x_centre, y + y_centre);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f); // yellow color
    draw_circle_polar(220.0f, 140.0f, 100.0f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Drawing (Polar Coordinate System)");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

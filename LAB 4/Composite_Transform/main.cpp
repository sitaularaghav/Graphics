#include <GL/glut.h>
#include <iostream>
#include <cmath>

void multiplyMatrices(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2.0);

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    float vertices[3][3] = {
        {0.05, 0.3, 0.6},
        {0.05, 0.7, 0.1},
        {1, 1, 1}
    };

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[0][i], vertices[1][i]);
    }
    glEnd();

    float translate1[3][3]={
        {1, 0, -0.25},
        {0, 1, -0.5},
        {0, 0, 1}
    };

    float translate2[3][3]={
        {1, 0, 0.5},
        {0, 1, 0.5},
        {0, 0, 1}
    };

    float angle1 = -45 * 3.14159 / 180;

    float rotate1[3][3]={
        {cos(angle1), sin(angle1), 0},
        {-sin(angle1), cos(angle1), 0},
        {0, 0, 1}
    };

    float angle2 = 45 * 3.14159 / 180;

    float rotate2[3][3]={
       {cos(angle2), sin(angle2), 0},
        {-sin(angle2), cos(angle2), 0},
        {0, 0, 1}
    };

    float reflectYMatrix[3][3] = {
        {-1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    float trans1[3][3];
    float rot1[3][3];
    float reflY[3][3];
    float rot2[3][3];
    float trans2[3][3];

    multiplyMatrices(translate1, vertices, trans1);
    multiplyMatrices(rotate1, trans1, rot1);
    multiplyMatrices(reflectYMatrix, rot1, reflY);
    multiplyMatrices(rotate2, reflY, rot2);
    multiplyMatrices(translate2, rot2, trans2);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    for(int i = 0; i < 3; i++) {
        glVertex2f(trans2[0][i], trans2[1][i]);
    }
    glEnd();
    glFlush();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Composite Transformation");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

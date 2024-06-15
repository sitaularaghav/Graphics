#include <GL/glut.h>
#include <iostream>

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

void display() {
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
        {0.25, 0.25, 1.0},
        {0.5, 0.9, 1.0},
        {0.8, 0.3, 1.0}
    };

    float reflectionXMatrix[3][3] = {
        {-1, 0, 0},
        {0, -1, 0},
        {0, 0, 1}
    };

    float reflectionYMatrix[3][3] = {
        {-1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    float reflectedXVertices[3][3];
    float reflectedYVertices[3][3];

    multiplyMatrices(vertices, reflectionXMatrix, reflectedXVertices);
    multiplyMatrices(vertices, reflectionYMatrix, reflectedYVertices);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color for original triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Blue color for triangle reflected on X axis
    for (int i = 0; i < 3; i++) {
        glVertex2f(reflectedXVertices[i][0], reflectedXVertices[i][1]);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < 3; i++) {
        glVertex2f(reflectedYVertices[i][0], reflectedYVertices[i][1]);
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Reflection on X and Y axis");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

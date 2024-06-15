#include <GL/glut.h>
#include <cmath>

enum PerspectiveType { ONE_POINT, TWO_POINT, THREE_POINT };
PerspectiveType currentPerspective = ONE_POINT;

void initRendering() {
    glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawAxes() {
    glColor3f(1.0f, 1.0f, 1.0f); // Set axes color to white
    glBegin(GL_LINES);
    // X-axis
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);

    // Y-axis
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);

    // Z-axis
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();
}

void drawCubeOutline(float r, float g, float b) {
    glBegin(GL_LINES);
    glColor3f(r, g, b); // Set color for the cube
    // Bottom face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Top face
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);

    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Connecting lines
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);

    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (currentPerspective) {
        case ONE_POINT:
            gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 1-point perspective
            drawAxes();
            drawCubeOutline(1.0f, 0.0f, 0.0f); // Red cube
            break;
        case TWO_POINT:
            gluLookAt(5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 2-point perspective
            drawAxes();
            drawCubeOutline(0.0f, 1.0f, 0.0f); // Green cube
            break;
        case THREE_POINT:
            gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 3-point perspective
            drawAxes();
            drawCubeOutline(1.0f, 1.0f, 0.0f); // yellow cube
            break;
    }

    glutSwapBuffers();
}

void timer(int value) {
    currentPerspective = static_cast<PerspectiveType>((currentPerspective + 1) % 3); // Cycle through perspectives
    glutPostRedisplay();
    glutTimerFunc(2000, timer, 0); // Repeat every 2 seconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("1-Point, 2-Point, and 3-Point Perspective Views");
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(2000, timer, 0); // Switch perspective every 2 seconds
    glutMainLoop();
    return 0;
}

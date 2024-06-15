#include <windows.h>
#include <GL/glut.h>

int x1 = -100, x2 = -30, y3 = -70, y2 = -20;
float u1 = 0, u2 = 1;
int xmin = -60, ymin = -60, xmax = 60, ymax = 60;
double p[4], q[4];

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-400, 400, -300, 300);
}

void clip(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1, i;
    double t;

    p[0] = -dx; q[0] = x1 - xmin;
    p[1] = dx;  q[1] = xmax - x1;
    p[2] = -dy; q[2] = y1 - ymin;
    p[3] = dy;  q[3] = ymax - y1;

    for (i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0)
            return;
        if (p[i] < 0) {
            t = q[i] / p[i];
            if (t > u1 && t < u2)
                u1 = t;
        } else if (p[i] > 0) {
            t = q[i] / p[i];
            if (t > u1 && t < u2)
                u2 = t;
        }
    }

    if (u1 < u2) {
        x1 = x1 + u1 * (x2 - x1);
        y1 = y1 + u1 * (y2 - y1);
        x2 = x1 + u2 * (x2 - x1);
        y2 = y1 + u2 * (y2 - y1);
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2i(x1, y3);
        glVertex2i(x2, y2);
    glEnd();
    glFlush();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2i(-60, -60);
        glVertex2i(-60, 60);
        glVertex2i(-60, 60);
        glVertex2i(60, 60);
        glVertex2i(60, 60);
        glVertex2i(60, -60);
        glVertex2i(60, -60);
        glVertex2i(-60, -60);
    glEnd();
    glFlush();
}

void myKey(unsigned char key, int x, int y) {
    if (key == 'l') {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex2i(-60, -60);
            glVertex2i(-60, 60);
            glVertex2i(-60, 60);
            glVertex2i(60, 60);
            glVertex2i(60, 60);
            glVertex2i(60, -60);
            glVertex2i(60, -60);
            glVertex2i(-60, -60);
        glEnd();
        glFlush();
        glColor3f(0.0, 0.0, 0.0);
        clip(::x1, y3, x2, y2);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang Barsky");
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    init();
    glutMainLoop();
    return 0;
}

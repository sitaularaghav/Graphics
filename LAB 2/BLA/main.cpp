#include <GL/glut.h>
#include <cmath>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    int x1 = 5, x2 = 2;
    int y1 = 10, y2 = 5;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int P0 = 2 * dy - dx;

    float x = x1, y = y1;
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(x, y);

    int P = P0;
    for (int i = 0; i < dx; i++) {
        if (P < 0) {
            x++;
            P += 2 * dy;
        } else {
            x++;
            y++;
            P += 2 * dy - 2 * dx;
        }
        glVertex2f(x, y);
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("BLA Line");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0.0, 20.0, 0.0, 20.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

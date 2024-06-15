#include <GL/glut.h>
#include <cmath>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int x1 = 5, x2 = 2;
    int y1 = 10, y2 = 5;
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;
    float x = x1, y = y1;

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(x, y); // Start point

    for (int i = 0; i < steps; i++)
    {
        x += xinc;
        y += yinc;
        glVertex2f(x, y); // Plot each point along the line
    }

    glEnd();
    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("DDA Line");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0.0, 20.0, 0.0, 20.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

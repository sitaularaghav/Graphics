#include <GL/glut.h>
#include <cmath>

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;
    float x = x1, y = y1;

    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(x, y);

    for (int i = 0; i < steps; i++)
    {
        x += xIncrement;
        y += yIncrement;
        glVertex2f(x, y);
    }

    glEnd();
}

void drawHistogram()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the histogram lines
    drawLine(5, 7, 5, 18); // Vertical line
    drawLine(5, 7, 16, 7); // Horizontal line

    // Swap the drawing instructions for the first and fifth bars

    //fifth bar (originally the first bar)
    drawLine(6,7,6,17);
    drawLine(5,9, 6, 9);

    //second bar
    drawLine(7,7,7,17);
    drawLine(6,17, 7, 17);

    //third bar
    drawLine(8,7, 8, 15);
    drawLine(7,13, 8, 13);

    //fourth bar
    drawLine(9,7, 9, 15);
    drawLine(8,15, 9, 15);

    //first bar (originally the fifth bar)
    drawLine(10,7, 10, 15);
    drawLine(9,10, 10, 10);

    //sixth bar
    drawLine(11,7, 11, 15);
    drawLine(10,15, 11, 15);

    //seventh bar
    drawLine(12,7, 12, 13);
    drawLine(11,13, 12, 13);

    //eighth bar
    drawLine(13,7, 13, 11);
    drawLine(12,11, 13, 11);

    //ninth bar
    drawLine(14,7, 14, 9);
    drawLine(13,9, 14, 9);

    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Histogram Line");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0.0, 20.0, 0.0, 20.0);
    glutDisplayFunc(drawHistogram);
    glutMainLoop();
    return 0;
}

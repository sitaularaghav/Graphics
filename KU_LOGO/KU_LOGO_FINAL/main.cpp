#include <GL/glut.h>
#include <cmath>
// Drawing Circle
void drawCircle(float centerX, float centerY, float radius)
{
glBegin(GL_POINTS);
float x = radius;
float y = 0;
float err = 0;
while (x >= y)
{
glVertex2f(centerX + x, centerY + y);
glVertex2f(centerX - x, centerY + y);
glVertex2f(centerX + x, centerY - y);
glVertex2f(centerX - x, centerY - y);
glVertex2f(centerX + y, centerY + x);
glVertex2f(centerX - y, centerY + x);
glVertex2f(centerX + y, centerY - x);
glVertex2f(centerX - y, centerY - x);
if (err <= 0)
{
y += 1;
err += 2 * y + 1;
}
if (err > 0)
{
x -= 1;
err -= 2 * x + 1;
}
}
glEnd();
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
// circle of radius 200 units
glColor3f(1.0, 0.0, 0.0); // Red color
glBegin(GL_POLYGON);
float an;
for (int i = 0; i < 360; i++)
{
an = i * 3.14159 / 180;
glVertex2f(230 * cos(an), 230 * sin(an));
}
glEnd();
drawCircle(0, 0, 200);
// circle of radius 175 units
glColor3f(0.0, 1.0, 1.0); // Blue color
glBegin(GL_POLYGON);
float a;
for (int i = 0; i < 360; i++)
{
a = i * 3.14159 / 180;
glVertex2f(190 * cos(a), 190 * sin(a));
}
glEnd();
drawCircle(0, 0, 175); // Center at (0, 0) with radius 175
// circle of radius 150 units
glColor3f(1.0, 1.0, 0.5); // yellow color
glBegin(GL_POLYGON);
float ang;
for (int i = 0; i < 360; i++)
{
ang = i * 3.14159 / 180;
glVertex2f(150 * cos(ang), 150 * sin(ang));
}
glEnd();
drawCircle(0, 0, 150);
glColor3f(0.0, 0.0, 0.0); // Set circle color black
// drawing triangle of light pink
glColor3f(1.0, 0.71, 0.76); // Light Pink
glBegin(GL_TRIANGLES);
glVertex2f(-133, 70);
glVertex2f(133, 70);
glVertex2f(0, -150);
glEnd();
glColor3f(0.0, 0.0, 0.0);
glLineWidth(10.0);
glBegin(GL_LINES);
// verticglColor3f(0.0, 0.0, 0.0);
glLineWidth(10.0);
glBegin(GL_LINES);
// vertical line
glVertex2f(-22.25, -50); // Starting point of the line
glVertex2f(-22.25, 50); // End point of the line
// h
glColor3f(0.0, 0.0, 0.0);
glLineWidth(10.0);
glBegin(GL_LINES);
glColor3f(0.0, 0.0, 0.0);
glLineWidth(10.0);
glBegin(GL_LINES);
// for U rotating in 60 degree
float angle = 60.0 * 3.14159 / 180.0; // degree into radian
float dx = cos(angle) * 50.5; // new x
float dy = sin(angle) * 50.5; // new y
// drawing the line for U in top
glVertex2i(-20, 0);
glVertex2i((int)dx, (int)dy);
glVertex2i(-20, 2);
glVertex2i((int)dx, (int)(dy + 2));

// for U rotating in negative 60 degree
float negangle = -60.0 * 3.14159 / 180.0;
float negdx = cos(negangle) * 50.5;
float negdy = sin(negangle) * 50.5;
// drawing line for U in the bottom
glVertex2f(-20.25, 0.0);
glVertex2f(negdx, negdy);
glVertex2f(-20.25, -2.75);
glVertex2f(negdx, negdy - 2.75);

// another line starting from the end of the bottom U
glVertex2f(negdx, negdy);
glVertex2f(3 * dx, 0);
glVertex2f(negdx, negdy - 2.75);
glVertex2f(3 * dx, -2.75);
glEnd();


glFlush();
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutCreateWindow("KU Logo");
glClearColor(1.0, 1.0, 1.0, 0.0);
gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
glutDisplayFunc(display);
glutMainLoop();
return 0;
}

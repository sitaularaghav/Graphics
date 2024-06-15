#include <windows.h>
#include <gl/glut.h>

struct Point {
    float x, y;
} windowVertices[4], outputVertices[4];
int numOutputVertices;

void drawPolygon(Point vertices[], int numVertices) {
    glBegin(GL_POLYGON);
    for(int i = 0; i < numVertices; i++)
        glVertex2f(vertices[i].x, vertices[i].y);
    glEnd();
}

bool isInside(Point p) {
    if((p.x >= windowVertices[0].x) && (p.x <= windowVertices[2].x))
        if((p.y >= windowVertices[0].y) && (p.y <= windowVertices[2].y))
            return true;
    return false;
}

void addVertex(Point p) {
    outputVertices[numOutputVertices] = p;
    numOutputVertices++;
}

Point getIntersection(Point start, Point end, int edge) {
    Point intersection;
    float slope;
    if(windowVertices[edge].x == windowVertices[(edge+1)%4].x) { // Vertical edge
        slope = (end.y - start.y) / (end.x - start.x);
        intersection.x = windowVertices[edge].x;
        intersection.y = start.y + slope * (intersection.x - start.x);
    } else { // Horizontal edge
        slope = (end.y - start.y) / (end.x - start.x);
        intersection.y = windowVertices[edge].y;
        intersection.x = start.x + (intersection.y - start.y) / slope;
    }
    return intersection;
}

void clipAndDraw(Point inputVertices[], int numInputVertices) {
    Point start, end, intersection;
    for(int i = 0; i < 4; i++) { // Loop through all edges of the clipping window
        numOutputVertices = 0;
        start = inputVertices[numInputVertices - 1];
        for(int j = 0; j < numInputVertices; j++) {
            end = inputVertices[j];
            if(isInside(end)) {
                if(isInside(start)) {
                    addVertex(end);
                } else {
                    intersection = getIntersection(start, end, i);
                    addVertex(intersection);
                    addVertex(end);
                }
            } else {
                if(isInside(start)) {
                    intersection = getIntersection(start, end, i);
                    addVertex(intersection);
                }
            }
            start = end;
        }
        inputVertices = outputVertices;
        numInputVertices = numOutputVertices;
    }
    drawPolygon(outputVertices, numOutputVertices);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, 0.0, 100.0);
    glClear(GL_COLOR_BUFFER_BIT);
    windowVertices[0].x = 20, windowVertices[0].y = 10;
    windowVertices[1].x = 20, windowVertices[1].y = 80;
    windowVertices[2].x = 80, windowVertices[2].y = 80;
    windowVertices[3].x = 80, windowVertices[3].y = 10;
}

void display(void) {
    Point inputVertices[4];
    init();
    glColor3f(1.0f, 1.0f, 0.0f);
    drawPolygon(windowVertices, 4);
    glColor3f(1.0f, 0.0f, 0.0f);
    inputVertices[0].x = 10, inputVertices[0].y = 40;
    inputVertices[1].x = 10, inputVertices[1].y = 60;
    inputVertices[2].x = 60, inputVertices[2].y = 60;
    inputVertices[3].x = 60, inputVertices[3].y = 40;
    drawPolygon(inputVertices, 4);
    glColor3f(0.0f, 1.0f, 0.0f);
    clipAndDraw(inputVertices, 4);
    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sutherland Hodgeman Polygon Clipping");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

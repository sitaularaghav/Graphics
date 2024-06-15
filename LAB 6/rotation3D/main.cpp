#include <GL/glut.h>
#include <cmath>

bool displayOriginal = true;

void setupRendering() {
    glEnable(GL_DEPTH_TEST);
}

void reshapeWindow(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawCoordinateAxes() {
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

void drawWireframeCube(float red, float green, float blue) {
    glBegin(GL_LINES);
    glColor3f(red, green, blue); // Set color for the cube
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

void applyMatrixTransform(float vertexArray[][4], int totalVertices, float transformationMatrix[4][4]) {
    for (int i = 0; i < totalVertices; ++i) {
        float x = vertexArray[i][0];
        float y = vertexArray[i][1];
        float z = vertexArray[i][2];
        float w = vertexArray[i][3];

        vertexArray[i][0] = transformationMatrix[0][0] * x + transformationMatrix[0][1] * y + transformationMatrix[0][2] * z + transformationMatrix[0][3] * w;
        vertexArray[i][1] = transformationMatrix[1][0] * x + transformationMatrix[1][1] * y + transformationMatrix[1][2] * z + transformationMatrix[1][3] * w;
        vertexArray[i][2] = transformationMatrix[2][0] * x + transformationMatrix[2][1] * y + transformationMatrix[2][2] * z + transformationMatrix[2][3] * w;
        vertexArray[i][3] = transformationMatrix[3][0] * x + transformationMatrix[3][1] * y + transformationMatrix[3][2] * z + transformationMatrix[3][3] * w;
    }
}

void drawTransformedCube(float red, float green, float blue) {
    float vertexArray[8][4] = {
        {-0.5f, -0.5f, -0.5f, 1.0f},
        {0.5f, -0.5f, -0.5f, 1.0f},
        {0.5f, 0.5f, -0.5f, 1.0f},
        {-0.5f, 0.5f, -0.5f, 1.0f},
        {-0.5f, -0.5f, 0.5f, 1.0f},
        {0.5f, -0.5f, 0.5f, 1.0f},
        {0.5f, 0.5f, 0.5f, 1.0f},
        {-0.5f, 0.5f, 0.5f, 1.0f}
    };

    // Rotation matrix (45 degrees around Y-axis)
    float angle = 45.0f * M_PI / 180.0f;
    float rotationMatrix[4][4] = {
        {cos(angle), 0.0f, sin(angle), 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {-sin(angle), 0.0f, cos(angle), 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    // Apply rotation
    applyMatrixTransform(vertexArray, 8, rotationMatrix);

    glBegin(GL_LINES);
    glColor3f(red, green, blue);
    for (int i = 0; i < 4; ++i) {
        glVertex3f(vertexArray[i][0], vertexArray[i][1], vertexArray[i][2]);
        glVertex3f(vertexArray[(i + 1) % 4][0], vertexArray[(i + 1) % 4][1], vertexArray[(i + 1) % 4][2]);
        glVertex3f(vertexArray[i + 4][0], vertexArray[i + 4][1], vertexArray[i + 4][2]);
        glVertex3f(vertexArray[(i + 1) % 4 + 4][0], vertexArray[(i + 1) % 4 + 4][1], vertexArray[(i + 1) % 4 + 4][2]);
        glVertex3f(vertexArray[i][0], vertexArray[i][1], vertexArray[i][2]);
        glVertex3f(vertexArray[i + 4][0], vertexArray[i + 4][1], vertexArray[i + 4][2]);
    }
    glEnd();
}

void handleKeyPress(unsigned char key, int x, int y) {
    if (key == 's') {
        displayOriginal = !displayOriginal; // Toggle the value of displayOriginal
        glutPostRedisplay();
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 3.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Changed viewpoint

    drawCoordinateAxes();

    if (displayOriginal) {
        drawWireframeCube(1.0f, 1.0f, 0.0f); // Red cube
    } else {
        drawTransformedCube(0.0f, 1.0f, 0.0f); // Green rotated cube
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Rotation");
    setupRendering();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeWindow);
    glutKeyboardFunc(handleKeyPress); // Register keyboard handler
    glutMainLoop();
    return 0;
}

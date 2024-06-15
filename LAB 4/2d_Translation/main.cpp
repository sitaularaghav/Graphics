#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>
#include <cmath>

// Define constants
const int WIDTH = 800;
const int HEIGHT = 600;

// Initial vertices of the shape (triangle)
float vertices[] = {
    -0.5f, -0.5f, 1.0f,
     0.5f, -0.5f, 1.0f,
     0.0f,  0.5f, 1.0f
};

// Function to apply transformation matrix
void applyTransformation(float matrix[3][3]) {
    for (int i = 0; i < 3; ++i) {
        float newX = matrix[0][0] * vertices[i * 3] + matrix[0][1] * vertices[i * 3 + 1] + matrix[0][2] * vertices[i * 3 + 2];
        float newY = matrix[1][0] * vertices[i * 3] + matrix[1][1] * vertices[i * 3 + 1] + matrix[1][2] * vertices[i * 3 + 2];
        float newW = matrix[2][0] * vertices[i * 3] + matrix[2][1] * vertices[i * 3 + 1] + matrix[2][2] * vertices[i * 3 + 2];

        vertices[i * 3] = newX / newW;
        vertices[i * 3 + 1] = newY / newW;
    }
}

// Function to handle key inputs
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_T: {
                // Translation
                float translationMatrix[3][3] = {
                    {1.0f, 0.0f, 0.2f},
                    {0.0f, 1.0f, 0.3f},
                    {0.0f, 0.0f, 1.0f}
                };
                applyTransformation(translationMatrix);
                break;
            }
            case GLFW_KEY_R: {
                // Rotation (45 degrees)
                float angle = 45.0f * M_PI / 180.0f;
                float rotationMatrix[3][3] = {
                    {cos(angle), -sin(angle), 0.0f},
                    {sin(angle), cos(angle), 0.0f},
                    {0.0f, 0.0f, 1.0f}
                };
                applyTransformation(rotationMatrix);
                break;
            }
            case GLFW_KEY_S: {
                // Scaling
                float scalingMatrix[3][3] = {
                    {0.5f, 0.0f, 0.0f},
                    {0.0f, 0.5f, 0.0f},
                    {0.0f, 0.0f, 1.0f}
                };
                applyTransformation(scalingMatrix);
                break;
            }
            case GLFW_KEY_F: {
                // Reflection over x-axis
                float reflectionMatrix[3][3] = {
                    {1.0f, 0.0f, 0.0f},
                    {0.0f, -1.0f, 0.0f},
                    {0.0f, 0.0f, 1.0f}
                };
                applyTransformation(reflectionMatrix);
                break;
            }
            case GLFW_KEY_H: {
                // Shearing
                float shearingMatrix[3][3] = {
                    {1.0f, 0.5f, 0.0f},
                    {0.5f, 1.0f, 0.0f},
                    {0.0f, 0.0f, 1.0f}
                };
                applyTransformation(shearingMatrix);
                break;
            }
            case GLFW_KEY_C: {
                // Reset shape
                float initialVertices[] = {
                    -0.5f, -0.5f, 1.0f,
                     0.5f, -0.5f, 1.0f,
                     0.0f,  0.5f, 1.0f
                };
                std::copy(std::begin(initialVertices), std::end(initialVertices), std::begin(vertices));
                break;
            }
            default:
                break;
        }
    }
}

// Function to render
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(vertices[0], vertices[1]);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(vertices[3], vertices[4]);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(vertices[6], vertices[7]);
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "2D Transformations", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the key callback
    glfwSetKeyCallback(window, key_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        render();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();
    return 0;
}

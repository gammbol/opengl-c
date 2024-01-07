#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

#include <shaderlib.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "  ourColor = aColor;\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "in vec3 ourColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "  FragColor = vec4(ourColor, 1.0);\n"
                                     "}\n\0";

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // shaders: build and compile
    SHADER_ST shader = shaderInit("shaders/shader.vs", "shaders/shader.fs");

    // vertex: set up data and buffers and configure attributes
    float triangle[] = {
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
    };
    float texCords[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f,
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // triangle: setup
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbinding
    glBindVertexArray(0);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // triangle: drawing
        use(&shader);
        setFloat(&shader, "offset", 0.2f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocating all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all allocated GLFW resources
    glfwTerminate();
    return 0;
}

// process all input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// glfw: resize hadler
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
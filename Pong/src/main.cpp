#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

// settings
unsigned int scrWidth = 800;
unsigned int scrHeight = 600;
const char* title = "Pong";


/*
    initialization methods
*/

// initialize GLFW
void initGLFW(unsigned int versionMajor, unsigned int versionMinor) {}

// create window
void createWindow(GLFWwindow*& window, const char* title, unsigned int width, unsigned int height, GLFWframebuffersizefun framebufferSizeCallback) {}

// callback for window size change
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {}

// load GLAD library
bool loadGlad() {}

/*
    shader methods
*/

// read file
std::string readFile(const char* filename) {}

//generate shader
int genShader(const char* filepath, GLenum type) {}

//generate shader program
int genShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {}

// bind shader
void bindShader (int shaderProgram) {}

// set projection
void setOrthographicProjection(int shaderProgram,
    float left, float right,
    float bottom, float top,
    float near,float far) {}

// delete shader
void deleteShader(int shaderProgram) {}

/*
    Vertex Array Object / Buffer Object Methods
*/

// structe for VAO storing Array Object and its Buffer Objects
struct VAO
{
    GLuint val;
    GLuint posVBO;
    GLuint offsetVBO;
    GLuint sizeVBO;
    GLuint EBO;
};

// generate VAO
void genVAO(VAO* vao) {}

// generate buffer of certain type and set data
template<typename T>
void genBufferObject(GLuint& bo, GLenum type, GLuint noElements, T* data, GLenum usage) {}

// update data in a buffer object
template<typename T>
void updateData(GLuint& bo, GLintptr offset, GLuint noElements, T* data) {}

// set attribute pointers
template<typename T>
void setAttPointer(GLuint& bo, GLuint idx, GLint size, GLenum type, GLuint stride, GLuint offset, GLuint divisor =0) {}

// draw VAO
void draw(VAO vao, GLenum mode, GLuint count, GLenum type, GLint indices, GLuint instanceCount = 1) {}

//unbind Buffer
void unbindBuffer(GLenum type) {}

// unbind VAO
void unbindVAO() {}

// deallocate VAO/VBO memory
void cleanup (VAO vao) {}

/*
    main loop methods
*/

// process input
void processInput(GLFWwindow* window) {}

// clear screen
void clearScreen() {}

// new frame
void newFrame(GLFWwindow* window) {}

/*
    cleanup methods
*/

// terminate glfw
void cleanup() {}



int main() {
    std::cout << "Hello World!" << '\n';

    double dt = 0.0;
    double lastFrame = 0.0;

    // initialization
    initGLFW(3,3);

    // create window
    GLFWwindow* window = nullptr;
    createWindow(window, title, scrWidth, scrHeight, framebufferSizeCallback);
    if (!window)
    {
        std::cout << "Could not create window" << std::endl;
        cleanup();
        return -1;
    }

    // load glad
    if (!loadGlad())
    {
        std::cout << "Could not init glad" << std::endl;
        cleanup();
        return -1;
    }

    // shaders
    GLuint shaderProgram = genShaderProgram("main.vs", "main.fs");
    setOrthographicProjection(shaderProgram, 0, scrWidth, 0, scrHeight, 0.0f, 1.0f);

    // setup vertex data
    float vertices[] = {
    //     x      y
         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f
    };

    // setup index data
    unsigned int indices[] = {
        0, 1, 2,  // top left triangle
        2, 3, 0   // bottom right triangle
    };

    // offsets array
    float offsets[] = {
    200.0f, 200.0f
    };

    // size array
    float sizes[] = {
        50.0f, 50.0f
    };

    // setup VAO/VBOs
    VAO vao;
    genVAO(&vao);

    // pos VBO
    genBufferObject<float>(vao.posVBO, GL_ARRAY_BUFFER, 2 * 4, vertices, GL_STATIC_DRAW);
    setAttPointer<float>(vao.posVBO, 0, 2, GL_FLOAT, 2, 0);

    // offset VBO
    genBufferObject<float>(vao.offsetVBO, GL_ARRAY_BUFFER, 1 * 2, offsets, GL_DYNAMIC_DRAW);
    setAttPointer<float>(vao.offsetVBO, 1, 2, GL_FLOAT, 2, 0, 1);

    // size VBO
    genBufferObject<float>(vao.sizeVBO, GL_ARRAY_BUFFER, 1 * 2, offsets, GL_DYNAMIC_DRAW);
    setAttPointer<float>(vao.sizeVBO, 2, 2, GL_FLOAT, 2, 0, 1);

    // EBO
    genBufferObject<unsigned int>(vao.EBO, GL_ELEMENT_ARRAY_BUFFER, 3 * 2, indices, GL_STATIC_DRAW);

    // unbind VBO and VAO
    unbindVAO();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // update time
        dt = glfwGetTime() - lastFrame;
        lastFrame += dt;

        // input
        processInput(window);

        // clear screen for new frame
        clearScreen();

        // render object
        bindShader(shaderProgram);
        draw(vao, GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, 0);

        // swap frames
        newFrame(window);
    }

    cleanup(vao);
    deleteShader(shaderProgram);
    cleanup();

    return 0;
    
}






















#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main(){
    
    GLFWwindow* window;

    if(!glfwInit()){
        std::cout<<"Failed to initialise GLFW"<<std::endl;
        return -1;
    }

    int height = 600, width = 800;

    window = glfwCreateWindow(width, height, "openglmaxxing", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"Failed to load OpenGL"<<std::endl;
        glfwTerminate();
        return -2;
    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
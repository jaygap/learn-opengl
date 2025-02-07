#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

int main(){
    
    GLFWwindow* window;

    if(!glfwInit()){
        std::cout<<"Failed to initialise GLFW"<<std::endl;
        return -1;
    }

    int height = 600, width = 800;

    //create window
    window = glfwCreateWindow(width, height, "triangle (not yet)", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"Failed to load OpenGL"<<std::endl;
        glfwTerminate();
        return -2;
    }

    double time;

    //while the window shouldnt close
    while(!glfwWindowShouldClose(window)){
        //poll events (mouse clicks, keyboard presses etc)
        glfwPollEvents();

        time = glfwGetTime();

        float r = sin(time / 2.0f);
        float g = sin(time / 2.0f + M_PI / 3.0f);
        float b = sin(time / 2.0f + 2 * M_PI / 3.0f);

        glClearColor(r * r, g * g, b * b, 1.0f);

        //clear colour buffer bit (shows clear colour)
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
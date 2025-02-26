#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <shader.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(){
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);

    GLFWwindow* window;

    if(!glfwInit()){
        std::cout<<"Failed to initialise GLFW"<<std::endl;
        return -1;
    }

    int height = 600, width = 800;

    //create window
    window = glfwCreateWindow(width, height, "this is the name of the window !!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"Failed to load OpenGL"<<std::endl;
        glfwTerminate();
        return -2;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader = Shader("/home/joseg/Programming/cpp-projects/learn-opengl/src/shaders/basic.vert", "/home/joseg/Programming/cpp-projects/learn-opengl/src/shaders/basic.frag");

    float vertices[] = {
        // vertices         //colours
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   //bottom left
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   //bottom right
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,   //top left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f    //top right
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    //generating and binding buffers (vertex array objects and vertex buffer objects)
    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int stride = 8 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    //load + create texture

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int img_width, img_height, channels;
    unsigned char* data = stbi_load("/home/joseg/Programming/cpp-projects/learn-opengl/src/images/container.jpg", &img_width, &img_height, &channels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("/home/joseg/Programming/cpp-projects/learn-opengl/src/images/awesomeface.png", &img_width, &img_height, &channels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    double time;

    shader.use();
    shader.setInt("base_image", 0);
    shader.setInt("overlay_image", 1);

    //while the window shouldnt close
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        time = glfwGetTime();

        //clear colour buffer bit (shows clear colour)
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.setFloat("rotation_degree", time / 2.0f);
        shader.setVec3("offset", sin(time) / 2.0f, cos(time) / 2.0f, 0.0f);

        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        //poll events (mouse clicks, keyboard presses etc)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
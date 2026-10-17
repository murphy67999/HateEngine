#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Window.hpp"
#include "Shader.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"

int main(){
    std::cout << "hello Hate Engine\n";

    Window window(800, 600, "Hate Engine");
    if (!window.isValid) return 1;

    Shader testShader("shaders/test.vs", "shaders/test.fs");

    float vertices[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f 
    };

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    VBO vbo;
    VAO vao;
    EBO ebo;

    vbo.bind();
    vbo.setData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    vao.bind();
    // pos attribute
    vao.setAttribute(0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
    // color attribute
    vao.setAttribute(1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
    // texture attribute
    vao.setAttribute(2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));

    ebo.bind();
    ebo.setData(sizeof(indices), indices, GL_STATIC_DRAW);

    vbo.unbind();
    vao.unbind();
    ebo.unbind();

    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* ptr_data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);

    if (ptr_data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ptr_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else{
        std::cout << stbi_failure_reason() << '\n';
    }
    stbi_image_free(ptr_data);

    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    ptr_data = stbi_load("assets/wall.jpg", &width, &height, &nrChannels, 0);

    if (ptr_data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ptr_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else{
        std::cout << stbi_failure_reason() << '\n';
    }
    stbi_image_free(ptr_data);

    testShader.use();
    testShader.setUniformInt("texture1", 0);
    testShader.setUniformInt("texture2", 1);
    

    // main loop
    while (!window.shouldClose()){
        // render
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
    }
    
    return 0;
}
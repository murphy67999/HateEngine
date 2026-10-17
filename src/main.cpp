#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Shader.hpp"
#include "VBO.hpp"
#include "VAO.hpp"

int main(){
    std::cout << "hello Hate Engine\n";

    Window window(800, 600, "Hate Engine");
    if (!window.isValid) return 1;

    Shader testShader("shaders/test.vs", "shaders/test.fs");

    float vertices[] = {
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    VBO vbo;
    VAO vao;

    vbo.bind();
    vbo.setData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    vao.bind();
    // pos attribute
    vao.setAttribute(0, 3, GL_FLOAT, 6*sizeof(float), (void*)0);
    // color attribute
    vao.setAttribute(1, 3, GL_FLOAT, 6*sizeof(float), (void*)(3*sizeof(float)));

    vbo.unbind();
    vao.unbind();

    // main loop
    while (!window.shouldClose()){
        // render
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        testShader.use();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }
    
    return 0;
}
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Shader.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "Texture.hpp"

int main(){
    std::cout << "hello Hate Engine\n";

    Window window(800, 600, "Hate Engine");
    if (!window.isValid) return 1;

    Shader testShader("shaders/test.vs", "shaders/test.fs");

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f 
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
    vao.setAttribute(0, 3, GL_FLOAT, 5*sizeof(float), (void*)0);
    // texture attribute
    vao.setAttribute(1, 2, GL_FLOAT, 5*sizeof(float), (void*)(3*sizeof(float)));

    ebo.bind();
    ebo.setData(sizeof(indices), indices, GL_STATIC_DRAW);

    vbo.unbind();
    vao.unbind();
    ebo.unbind();

    Texture awesomeFace("assets/awesomeface.png", GL_RGBA);
    Texture container("assets/container.jpg", GL_RGB);

    glActiveTexture(GL_TEXTURE0);
    awesomeFace.bind();

    glActiveTexture(GL_TEXTURE1);
    container.bind();

    testShader.use();
    testShader.setUniformInt("texture1", 0);
    testShader.setUniformInt("texture2", 1);




    // main loop
    while (!window.shouldClose()){
        // render
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // test math
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::rotate(matrix, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
        matrix = glm::scale(matrix, glm::vec3(1.5f, 1.5f, 1.5f));
        testShader.setUniformMatrix4fv("transformMatrix", glm::value_ptr(matrix));

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
    }
    
    return 0;
}

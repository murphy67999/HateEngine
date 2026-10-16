#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include "glad/glad.h"

std::string loadTextFile(const std::string& path){
    std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}   

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath){
    std::string vertexText = loadTextFile(vertexShaderPath);
    std::string fragmentText = loadTextFile(fragmentShaderPath);

    const char* ptr_vertexShaderSource = vertexText.c_str();
    const char* ptr_fragmentShaderSource = fragmentText.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &ptr_vertexShaderSource, nullptr);
    glShaderSource(fragmentShader, 1, &ptr_fragmentShaderSource, nullptr);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader(){
    glDeleteProgram(m_shaderProgram);
}

void Shader::use() const{
    glUseProgram(m_shaderProgram);
}
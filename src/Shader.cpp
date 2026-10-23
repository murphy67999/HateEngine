#include "Shader.hpp"

#include <fstream>
#include <sstream>

std::string loadTextFile(const std::string &path)
{
    std::ifstream file(path);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    std::string vertexText = loadTextFile(vertexShaderPath);
    std::string fragmentText = loadTextFile(fragmentShaderPath);

    const char *ptr_vertexShaderSource = vertexText.c_str();
    const char *ptr_fragmentShaderSource = fragmentText.c_str();

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

Shader::~Shader()
{
    glDeleteProgram(m_shaderProgram);
}

void Shader::use() const
{
    glUseProgram(m_shaderProgram);
}

void Shader::setUniformInt(const std::string &uniformName, int value) const
{
    glUniform1i(glGetUniformLocation(m_shaderProgram, uniformName.c_str()), value);
}

void Shader::setUniformMatrix4fv(const std::string &uniformName, const GLfloat *value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, uniformName.c_str()), 1, GL_FALSE, value);
}

void Shader::setUniformVec3(const std::string &uniformName, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(m_shaderProgram, uniformName.c_str()), value.x, value.y, value.z);
}

void Shader::setUniformFloat(const std::string &uniformName, float value) const
{
    glUniform1f(glGetUniformLocation(m_shaderProgram, uniformName.c_str()), value);
}
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    GLuint compileShader(GLuint type);
    std::string get_file_contents(const char* filename);
    std::string shader_source;
public:
    GLuint id;
    Shader(const char* shader_file_path, GLuint type)
    {
        shader_source = get_file_contents(shader_file_path);
        id = compileShader(type);
    }
    ~Shader() noexcept
    {
        glDeleteShader(id);
    }

};

class ShaderProgram
{
    GLuint id;
    std::vector<GLuint> shaders;
    const static ShaderProgram* used;
public:
    ShaderProgram()
    {
        id = glCreateProgram();
    }
    ~ShaderProgram() noexcept
    {
        stop();
        for(GLuint shaderID : shaders)
        {
            glDetachShader(id, shaderID);
        }
        glDeleteProgram(id);
    }
    void bindShader(Shader&& shader)
    {
        glAttachShader(id, shader.id);
        shaders.push_back(shader.id);
    }
    void compile()
    {
        glLinkProgram(id);
        glValidateProgram(id);
    }
    void use()
    {
        if (used != this)
        {
            glUseProgram(id);
            used = this;
        }
    }
    void stop()
    {
        if(used == this)
        {
            glUseProgram(0);
            used = nullptr;
        }
    }
    GLubyte findUniform(const GLchar* name)
    {
        return glGetUniformLocation(id, name);
    }
    void setUniform1i(GLubyte location, GLint value)
    {
        glUniform1i(location, value);
    }
    void setUniform4f(GLubyte location, GLfloat i, GLfloat j, GLfloat k, GLfloat l)
    {
        glUniform4f(location, i, j, k, l);
    }
    void setUniformMat4f(GLubyte location, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
};
#endif
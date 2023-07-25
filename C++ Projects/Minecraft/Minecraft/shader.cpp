#include "shader.h"

const ShaderProgram* ShaderProgram::used = nullptr;

std::string Shader::get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    throw(errno);
}

GLuint Shader::compileShader(GLuint type)
{
    GLuint _id = glCreateShader(type);
    const char* src = shader_source.c_str();
    glShaderSource(_id, 1, &src, nullptr);
    glCompileShader(_id);

    int result;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &result);
    if(!result)
    {
        int length;
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(_id, length, &length, message);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        delete[] message;
        glDeleteShader(_id);
        return 0;
    }
    return _id;
}

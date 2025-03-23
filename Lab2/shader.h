#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    GLuint ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexCode = loadShaderFromFile(vertexPath);
        std::string fragmentCode = loadShaderFromFile(fragmentPath);

        GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        checkProgramLinkErrors(ID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use() {
        glUseProgram(ID);
    }

    void setUniform(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setUniform(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setUniform(const std::string& name, float v1, float v2) {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2);
    }

    void setUniform(const std::string& name, float v1, float v2, float v3) {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
    }

    void setUniform(const std::string& name, float v1, float v2, float v3, float v4) {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
    }

private:
    std::string loadShaderFromFile(const std::string& filePath) {
        std::ifstream shaderFile(filePath);
        if (!shaderFile.is_open()) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << std::endl;
            return "";
        }
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }

    GLuint compileShader(const std::string& source, GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        checkShaderCompileErrors(shader);
        return shader;
    }

    void checkShaderCompileErrors(GLuint shader) {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void checkProgramLinkErrors(GLuint program) {
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
};

#endif
#include <graphics/shader.hpp>

#include <glad/glad.h>

#include <iostream>

using namespace ai_framework::graphics;

GLenum mapShaderType(ShaderType type) {
    switch (type) {
    default:
        return GL_NONE;
    case ShaderType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    case ShaderType::VERTEX:
        return GL_VERTEX_SHADER;
    }
}

bool Shader::compile() {
    int ret;

    if (shader_id == -1) {
        std::cout << "Shader::compile - no shader found, time to create a new one!" << std::endl;
        shader_id = glCreateShader(mapShaderType(type));
    }

    const char *shaderCode = data.c_str();

    std::cout << "Shader::compile - proceeding to compile the shader..." << std::endl;
    glShaderSource(shader_id, 1, &shaderCode, NULL);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &ret);
    is_compiled = ret == GL_TRUE;

    if (!is_compiled) {
        // some trickery to get full message size;
        GLint msgLen;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &msgLen);

        if (msgLen != -1) {
            // now malloc a buffer with our error message and get it in there
            char *errBuf = (char *) malloc(msgLen);

            if (errBuf) {
                glGetShaderInfoLog(shader_id, msgLen, NULL, errBuf);

                // print our message
                std::cout << "Shader::compile - shader compilation failed! :(" << std::endl
                          << errBuf << std::endl;

                // free!!!
                free(errBuf);
            } else {
                std::cout << "Shader::compile - shader compilation failed! :(" << std::endl;
            }
        } else {
            std::cout << "Shader::compile - shader compilation failed! :(" << std::endl;
        }
    }

    if (is_compiled)
        std::cout << "Shader::compile - shader '" << name << "' compiled successfully!" << std::endl;

    return is_compiled;
}

void Shader::destroy() {
    if (shader_id >= 0)
        glDeleteShader(shader_id);

    is_compiled = false;
}
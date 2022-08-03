#include <graphics/shader_program.hpp>

#include <glad/glad.h>

using namespace ai_framework::graphics;

bool ShaderProgram::compile() {
    if (compiled() || shaders.size() == 0)
        return false;

    int ret;

    program_id = glCreateProgram();
    if (!program_id)
        return false;

    for (auto &p : shaders) {
        if (!p.compiled()) {
            if (!p.compile()) {
                printf("ShaderProgram::compile - Failed to compile shader!\n");
                return false;
            }
        }

        glAttachShader(program_id, p.id());
    }

    printf("ShaderProgram::compile - linking shader program...\n");

    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &ret);
    is_compiled = ret == GL_TRUE;

    if (!is_compiled) {
        // some trickery to get full message size;
        int msgLen = -1;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &msgLen);

        if (msgLen != -1) {
            // now malloc a buffer with our error message and get it in there
            char *errBuf = (char *) malloc(msgLen);

            if (errBuf) {
                glGetProgramInfoLog(program_id, msgLen, NULL, errBuf);

                // print our message
                printf("ShaderProgram::compile - shader program linking failed! :(\n%s\n", errBuf);

                // free!!!
                free(errBuf);
            } else {
                printf("ShaderProgram::compile - shader program linking failed! :(\n");
            }
        } else {
            printf("ShaderProgram::compile - shader program linking failed! :(\n");
        }
    }

    for (auto &p : shaders) {
        if (p.compiled())
            p.destroy();
    }

    return true;
}

void ShaderProgram::use() {
    if (!compiled())
        if (!compile())
            return;

    glUseProgram(program_id);
}
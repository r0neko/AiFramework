#ifdef _GL
#ifdef _ANDROID
#    include <GLES3/gl3.h>
#else
#    include <glad/glad.h>
#endif
#    include <platform/gl/open_gl_api.hpp>

#    include <stdexcept>

using namespace ai_framework;
using namespace api;

GLenum data_type_to_gl_enum(DataType type) {
    switch (type) {
    default:
        return GL_NONE;
    case UNSIGNED_BYTE:
        return GL_UNSIGNED_BYTE;
    case UNSIGNED_INT:
        return GL_UNSIGNED_INT;
    case FLOAT:
        return GL_FLOAT;
    case INT:
        return GL_INT;
    }
}

GLenum buffer_type_to_gl_enum(BufferType type) {
    switch (type) {
    default:
        return GL_NONE;
    case ARRAY_BUFFER:
        return GL_ARRAY_BUFFER;
    case ELEMENT_ARRAY_BUFFER:
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}

GLenum usage_mode_to_gl_enum(UsageMode type) {
    switch (type) {
    default:
        return GL_NONE;
    case STATIC_DRAW:
        return GL_STATIC_DRAW;
    case DYNAMIC_DRAW:
        return GL_DYNAMIC_DRAW;
    }
}
GLenum draw_mode_to_gl_enum(DrawMode type) {
    switch (type) {
    default:
        return GL_NONE;
    case TRIANGLES:
        return GL_TRIANGLES;
    case LINES:
        return GL_LINES;
    case POINTS:
        return GL_POINTS;
    }
}

GLenum shader_type_to_gl_enum(ShaderType type) {
    switch (type) {
    default:
        return GL_NONE;
    case ShaderType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    case ShaderType::VERTEX:
        return GL_VERTEX_SHADER;
    }
}

void OpenGLAPI::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLAPI::set_clear_color(const Color &color) {
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
}

void OpenGLAPI::set_viewport(const IntVector2 &viewport) {
    glViewport(0, 0, viewport.x, viewport.y);
}

void OpenGLAPI::upload_texture(const Image &tex) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.size.x, tex.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.pixels.data());
}

std::uintptr_t OpenGLAPI::create_texture() {
    std::uintptr_t x{AI_FRAMEWORK_NULL};

    glGenTextures(1, (GLuint *) &x);
    return x;
}

void OpenGLAPI::delete_texture(std::uintptr_t texture) {
    glDeleteTextures(1, (GLuint *) &texture);
}

void OpenGLAPI::bind_texture(std::uintptr_t texture) {
    glBindTexture(GL_TEXTURE_2D, (GLuint) texture);
}

void OpenGLAPI::enable_vertex_attribute(unsigned int attribute) {
    glEnableVertexAttribArray(attribute);
}

void OpenGLAPI::disable_vertex_attribute(unsigned int attribute) {
    glDisableVertexAttribArray(attribute);
}

void OpenGLAPI::define_vertex_attribute(unsigned int attribute, int count, DataType type, int stride, size_t offset) {
    auto _type = data_type_to_gl_enum(type);

    if (_type == GL_NONE)
        throw std::runtime_error("invalid data type!");

    glVertexAttribPointer(attribute, count, _type, 0, stride, (void *) offset);
}

std::uintptr_t OpenGLAPI::create_buffer() {
    std::uintptr_t x{AI_FRAMEWORK_NULL};

    glGenBuffers(1, (GLuint *) &x);
    return x;
}

void OpenGLAPI::delete_buffer(std::uintptr_t buffer) {
    glDeleteTextures(1, (GLuint *) &buffer);
}

std::uintptr_t OpenGLAPI::create_vertex_array() {
    std::uintptr_t x{AI_FRAMEWORK_NULL};

    glGenBuffers(1, (GLuint *) &x);
    return x;
}

void OpenGLAPI::delete_vertex_array(std::uintptr_t buffer) {
    glDeleteVertexArrays(1, (GLuint *) &buffer);
}

void OpenGLAPI::bind_vertex_array(std::uintptr_t buffer) {
    glBindVertexArray((GLuint) buffer);
}

void OpenGLAPI::bind_buffer(std::uintptr_t buffer, BufferType type) {
    auto _type = buffer_type_to_gl_enum(type);

    if (_type == GL_NONE)
        throw std::runtime_error("invalid buffer type!");

    glBindBuffer(_type, (GLuint) buffer);
}

void OpenGLAPI::set_buffer_data(BufferType type, size_t size, void *data, UsageMode usage) {
    auto buf_type = buffer_type_to_gl_enum(type);
    auto usage_mode = usage_mode_to_gl_enum(usage);

    if (buf_type == GL_NONE)
        throw std::runtime_error("invalid buffer type!");

    if (usage_mode == GL_NONE)
        throw std::runtime_error("invalid usage mode!");

    glBufferData(buf_type, size, data, usage_mode);
}

void OpenGLAPI::draw_buffer(DrawMode mode, int start, size_t size) {
    auto _mode = draw_mode_to_gl_enum(mode);

    if (_mode == GL_NONE)
        throw std::runtime_error("invalid drawing mode!");

    glDrawArrays(_mode, start, size);
}

std::uintptr_t OpenGLAPI::create_program() {
    auto p = glCreateProgram();
    return (std::uintptr_t) p;
}

void OpenGLAPI::use_program(std::uintptr_t program) {
    glUseProgram((GLuint) program);
}

void OpenGLAPI::attach_shader_to_program(std::uintptr_t program, std::uintptr_t shader) {
    glAttachShader((GLuint) program, (GLuint) shader);
}

bool OpenGLAPI::link_program(std::uintptr_t program) {
    int ret;

    glLinkProgram((GLuint) program);
    glGetProgramiv((GLuint) program, GL_LINK_STATUS, &ret);

    return ret == GL_TRUE;
}

std::string OpenGLAPI::get_program_log(std::uintptr_t program) {
    int log_len = 0;
    std::string program_log = "none";

    glGetProgramiv((GLuint) program, GL_INFO_LOG_LENGTH, &log_len);

    if (log_len) {
        program_log.resize(log_len);
        glGetProgramInfoLog((GLuint) program, log_len, NULL, &program_log[0]);
    }

    return program_log;
}

std::uintptr_t OpenGLAPI::get_uniform(std::uintptr_t program, std::string_view uniform) {
    auto uf = glGetUniformLocation((GLuint) program, uniform.data());
    if (uf <= -1)
        return AI_FRAMEWORK_NULL;
    return (std::uintptr_t) uf;
}

std::uintptr_t OpenGLAPI::create_shader(ShaderType type) {
    auto _type = shader_type_to_gl_enum(type);

    if (_type == GL_NONE)
        throw std::runtime_error("invalid shader type!");

    auto s = glCreateShader(_type);

    return (std::uintptr_t) s;
}

void OpenGLAPI::set_shader_source(std::uintptr_t shader, std::string_view source) {
    GLint s = source.size();

    // messy way
    const char *x[1] = {source.data()};
    const GLint size[1] = {s};

    glShaderSource((GLuint) shader, 1, x, size);
}

bool OpenGLAPI::compile_shader(std::uintptr_t shader) {
    int ret;

    glCompileShader((GLuint) shader);
    glGetShaderiv((GLuint) shader, GL_COMPILE_STATUS, &ret);

    return ret == GL_TRUE;
}

std::string OpenGLAPI::get_shader_log(std::uintptr_t shader) {
    int log_len = 0;
    std::string shader_log = "none";

    glGetShaderiv((GLuint) shader, GL_INFO_LOG_LENGTH, &log_len);

    if (log_len) {
        shader_log.resize(log_len);
        glGetShaderInfoLog((GLuint) shader, log_len, NULL, &shader_log[0]);
    }

    return shader_log;
}

void OpenGLAPI::delete_shader(std::uintptr_t shader) {
    glDeleteShader((GLuint) shader);
}

void OpenGLAPI::uniform_set(std::uintptr_t uniform, const glm::mat4 &mat) {
    glUniformMatrix4fv((GLint) uniform, 1, GL_FALSE, &mat[0][0]);
}

void OpenGLAPI::draw_elements(DrawMode mode, int start, size_t size, DataType type) {
    auto _type = data_type_to_gl_enum(type);
    auto _mode = draw_mode_to_gl_enum(mode);

    if (_type == GL_NONE)
        throw std::runtime_error("invalid data type!");

    if (_mode == GL_NONE)
        throw std::runtime_error("invalid drawing mode!");

    glDrawElements(_mode, (GLsizei) size, _type, (void *) start);
}

#endif
#ifndef OPEN_GL_API
#define OPEN_GL_API

#include <graphics/i_graphics_api.hpp>

using namespace ai_framework::graphics;

namespace ai_framework::api {
    struct AI_API OpenGLAPI : IGraphicsAPI {
        void set_clear_color(const Color &color) override;
        void clear() override;

        void set_viewport(const IntVector2 &viewport) override;

        std::uintptr_t create_buffer() override;
        void delete_buffer(std::uintptr_t buffer) override;
        void bind_buffer(std::uintptr_t buffer, BufferType type) override;
        void set_buffer_data(BufferType type, size_t size, void *data, UsageMode usage) override;
        void draw_buffer(DrawMode mode, int start, size_t size) override;
        void draw_elements(DrawMode mode, int start, size_t size, DataType type) override;

        std::uintptr_t create_vertex_array() override;
        void delete_vertex_array(std::uintptr_t buffer) override;
        void bind_vertex_array(std::uintptr_t buffer) override;

        std::uintptr_t create_program() override;
        void use_program(std::uintptr_t program) override;
        void attach_shader_to_program(std::uintptr_t program, std::uintptr_t shader) override;
        bool link_program(std::uintptr_t program) override;
        std::string get_program_log(std::uintptr_t program) override;

        std::uintptr_t create_shader(ShaderType type) override;
        void set_shader_source(std::uintptr_t shader, std::string_view source) override;
        bool compile_shader(std::uintptr_t shader) override;
        std::string get_shader_log(std::uintptr_t shader) override;
        void delete_shader(std::uintptr_t shader) override;

        std::uintptr_t create_texture() override;
        void upload_texture(const Image &tex) override;
        void bind_texture(std::uintptr_t texture) override;
        void delete_texture(std::uintptr_t texture) override;

        void enable_vertex_attribute(unsigned int attribute) override;
        void disable_vertex_attribute(unsigned int attribute) override;
        void define_vertex_attribute(unsigned int attribute, int count, DataType type, int stride, size_t offset) override;

        std::uintptr_t get_uniform(std::uintptr_t program, std::string_view uniform) override;

        void uniform_set(std::uintptr_t uniform, const glm::mat4 &mat) override;
    };
} // namespace ai_framework::api

#endif
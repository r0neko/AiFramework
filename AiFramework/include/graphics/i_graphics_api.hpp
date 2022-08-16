#ifndef I_GRAPHICS_API_HPP
#define I_GRAPHICS_API_HPP

#include <framework_build.hpp>

#include <generic/vector2.hpp>
#include <graphics/color.hpp>
#include <graphics/enums.hpp>
#include <graphics/image.hpp>

#include <string>

#include <glm/glm.hpp>

namespace ai_framework::graphics {
    /// <summary>
    /// Abstract interface that allows communication to the graphics library API.
    /// </summary>
    struct AI_API IGraphicsAPI {
        virtual void set_clear_color(const Color &color) = 0;
        virtual void clear() = 0;

        virtual void set_viewport(const IntVector2 &viewport) = 0;

        virtual opaque_t create_buffer() = 0;
        virtual void delete_buffer(opaque_t buffer) = 0;
        virtual void bind_buffer(opaque_t buffer, BufferType type) = 0;
        virtual void set_buffer_data(BufferType type, size_t size, void *data, UsageMode usage) = 0;
        virtual void draw_buffer(DrawMode mode, int start, size_t size) = 0;
        virtual void draw_elements(DrawMode mode, int start, size_t size, DataType type) = 0;

        virtual opaque_t create_vertex_array() = 0;
        virtual void delete_vertex_array(opaque_t buffer) = 0;
        virtual void bind_vertex_array(opaque_t buffer) = 0;

        virtual opaque_t create_program() = 0;
        virtual void use_program(opaque_t program) = 0;
        virtual void attach_shader_to_program(opaque_t program, opaque_t shader) = 0;
        virtual bool link_program(opaque_t program) = 0;
        virtual std::string get_program_log(opaque_t program) = 0;

        virtual opaque_t create_shader(ShaderType type) = 0;
        virtual void set_shader_source(opaque_t shader, std::string_view source) = 0;
        virtual bool compile_shader(opaque_t shader) = 0;
        virtual std::string get_shader_log(opaque_t shader) = 0;
        virtual void delete_shader(opaque_t shader) = 0;

        virtual opaque_t create_texture() = 0;
        virtual void upload_texture(const Image &tex) = 0;
        virtual void bind_texture(opaque_t texture) = 0;
        virtual void delete_texture(opaque_t texture) = 0;

        virtual void enable_vertex_attribute(unsigned int attribute) = 0;
        virtual void disable_vertex_attribute(unsigned int attribute) = 0;
        virtual void define_vertex_attribute(unsigned int attribute, int count, DataType type, int stride, size_t offset = 0) = 0;

        virtual opaque_t get_uniform(opaque_t program, std::string_view uniform) = 0;

        virtual void uniform_set(opaque_t uniform, const glm::mat4 &mat) = 0;
    };
} // namespace ai_framework::graphics

#endif
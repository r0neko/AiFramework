#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <framework_build.hpp>

#include "shader.hpp"

#include <string>
#include <vector>

namespace ai_framework::graphics {
    /// <summary>
    /// This represents a shader program that links shaders and it offers basic operations.
    /// </summary>
    struct AI_API ShaderProgram {
        ShaderProgram(std::string_view name)
            : p_name(name) {
        }

        void add_shader(const Shader &shader) {
            shaders.push_back(shader);
        }

        bool compiled() const {
            return is_compiled || program_id != -1;
        }

        void use();
        bool compile();

      private:
        unsigned int program_id = -1;
        bool is_compiled = false;

        std::string p_name;
        std::vector<Shader> shaders;
    };
} // namespace ai_framework::graphics

#endif
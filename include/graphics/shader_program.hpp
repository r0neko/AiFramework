#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <framework_build.hpp>
#include <graphics/shader.hpp>

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <cstdint>

namespace ai_framework::graphics {
    struct AI_API IShaderProgram {
        void set(std::string_view uniform, const glm::mat4 &mat);

      protected:
        std::uintptr_t program_id{AI_FRAMEWORK_NULL};
    };

    /// <summary>
    /// This represents a shader program that links shaders and it offers basic operations.
    /// </summary>
    struct AI_API ShaderProgram : IShaderProgram {
        ShaderProgram(std::string_view name)
            : p_name(name) {
        }

        void add_shader(const Shader &shader) {
            shaders.push_back(shader);
        }

        bool compiled() const {
            return is_compiled || program_id != AI_FRAMEWORK_NULL;
        }

        void use();
        bool compile();

      private:
        bool is_compiled = false;

        std::string p_name;
        std::vector<Shader> shaders;
    };
} // namespace ai_framework::graphics

#endif
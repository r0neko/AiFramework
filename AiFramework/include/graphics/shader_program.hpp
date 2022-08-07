#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <framework_build.hpp>

#include "shader.hpp"

#include <string>
#include <vector>

// #ifdef TARGET_OPENGL
#include <glm/glm.hpp>
// #endif

namespace ai_framework::graphics {
    struct AI_API IShaderProgram {
        void set(std::string_view uniform, const glm::mat4 &mat);

      protected:
        unsigned int program_id = -1;
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
            return is_compiled || program_id != -1;
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
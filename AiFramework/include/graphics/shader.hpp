#ifndef SHADER_HPP
#define SHADER_HPP

#include <framework_build.hpp>

#include <string>
#include <vector>

namespace ai_framework::graphics {
    enum class ShaderType { FRAGMENT,
                            VERTEX };

    /// <summary>
    /// A base Shader class that handles the most basic operations, like loading/destruction and compilation/linking, using the right graphics system calls.
    /// </summary>
    struct AI_API Shader {
        Shader(std::string_view name, std::string_view data, ShaderType type)
            : name(name), data(data), type(type){};

        Shader(const Shader &rhs)
            : name(rhs.name), data(rhs.data), type(rhs.type), is_compiled(rhs.is_compiled), shader_id(rhs.shader_id) {
        }

        static Shader from_file(std::string_view name, std::string_view path, ShaderType type);

        bool compile();
        void destroy();

        bool compiled() const {
            return is_compiled;
        }

        unsigned int id() const {
            return shader_id;
        }

      private:
        unsigned int shader_id = -1;

        bool is_compiled = false;
        std::string name;
        std::string data;
        ShaderType type;
    };
} // namespace ai_framework::graphics

#endif
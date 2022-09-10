#include <graphics/graphics_api.hpp>
#include <graphics/shader_program.hpp>
#include <generic/logger.hpp>

#include <glm/glm.hpp>

using namespace ai_framework::graphics;

CLogger _shader_program_logger("ShaderProgram");

bool ShaderProgram::compile() {
    if (compiled() || shaders.size() == 0)
        return false;

    program_id = api->create_program();
    if (!program_id)
        return false;

    for (auto &p : shaders) {
        if (!p.compiled()) {
            if (!p.compile()) {
                _shader_program_logger.log(LoggerLevel::DEBUG, "ShaderProgram::compile [%s] - Failed to compile one or more shaders!", p_name.c_str());
                return false;
            }
        }

        api->attach_shader_to_program(program_id, p.id());
    }

    is_compiled = api->link_program(program_id);

    if (!is_compiled) {
        _shader_program_logger.log(LoggerLevel::DEBUG, "ShaderProgram::compile [%s] - shader program linking failed! :(", p_name.c_str());
        _shader_program_logger.log(LoggerLevel::DEBUG, "%s", api->get_program_log(program_id).c_str());
    } else
        _shader_program_logger.log(LoggerLevel::DEBUG, "ShaderProgram::compile [%s] - linked successfully!", p_name.c_str());

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

    api->use_program(program_id);
}

void IShaderProgram::set(std::string_view uniform, const glm::mat4 &mat) {
    api->use_program(program_id);
    auto uf_loc = api->get_uniform(program_id, uniform);

    if (uf_loc != GRAPHICS_API_NULL)
        api->uniform_set(uf_loc, mat);
    else
        _shader_program_logger.log(LoggerLevel::DEBUG, "uniform '%s' could not be found!", uniform.data());
}
#include <graphics/graphics_api.hpp>
#include <graphics/shader_program.hpp>

#include <glm/glm.hpp>

using namespace ai_framework::graphics;

bool ShaderProgram::compile() {
    if (compiled() || shaders.size() == 0)
        return false;

    program_id = api->create_program();
    if (!program_id)
        return false;

    for (auto &p : shaders) {
        if (!p.compiled()) {
            if (!p.compile()) {
                printf("ShaderProgram::compile [%s] - Failed to compile one or more shaders!\n", p_name.c_str());
                return false;
            }
        }

        api->attach_shader_to_program(program_id, p.id());
    }

    is_compiled = api->link_program(program_id);

    if (!is_compiled) {
        printf("ShaderProgram::compile [%s] - shader program linking failed! :(\n", p_name.c_str());
        printf("%s\n", api->get_program_log(program_id).c_str());
    } else
        printf("ShaderProgram::compile [%s] - linked successfully!\n", p_name.c_str());

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
        printf("uniform '%s' could not be found!\n", uniform.data());
}
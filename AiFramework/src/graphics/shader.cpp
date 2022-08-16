#include <graphics/graphics_api.hpp>
#include <graphics/shader.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

#include <stdexcept>

using namespace ai_framework::graphics;

Shader Shader::from_file(std::string_view name, std::string_view path, ShaderType type) {
    std::ifstream inFile;
    std::stringstream strStream;

    inFile.open(std::string{path});

    if (!inFile)
        throw std::runtime_error("Could not open the shader file!");

    strStream << inFile.rdbuf();

    return {name, strStream.str(), type};
}

bool Shader::compile() {
    if (shader_id == nullptr)
        shader_id = api->create_shader(type);

    api->set_shader_source(shader_id, data);

    is_compiled = api->compile_shader(shader_id);

    if (!is_compiled) {
        printf("Shader::compile - failed to compile shader '%s' :(\n", name.c_str());
        printf("%s\n", api->get_shader_log(shader_id).c_str());
    } else
        printf("Shader::compile - shader '%s' compiled successfully!\n", name.c_str());

    return is_compiled;
}

void Shader::destroy() {
    if (shader_id)
        api->delete_shader(shader_id);

    is_compiled = false;
}
#include <graphics/shader.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace ai_framework::graphics;

Shader Shader::from_file(std::string_view name, std::string_view path, ShaderType type) {
    std::ifstream inFile;
    std::stringstream strStream;

    std::cout << "Shader::from_file - " << name << ": loading shader file "
              << path << std::endl;

    inFile.open(std::string{path});

    if (!inFile)
        throw std::exception("Could not open the shader file!");

    strStream << inFile.rdbuf();

    return {name, strStream.str(), type};
}
#ifndef SHADER_SRC_HPP
#define SHADER_SRC_HPP

namespace ai_framework::shaders::sources {
    constexpr auto
    ColorVertex2D_Fragment = "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "\n"
                             "in vec3 mColor;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "    FragColor = vec4(mColor, 1);\n"
                             "} ";

    constexpr auto
    ColorVertex2D_Vertex = "#version 330 core\n"
                           "layout (location = 0) in vec2 aPos;\n"
                           "layout (location = 1) in vec3 aColor;\n"
                           "\n"
                           "uniform mat4 uProjMatrix;\n"
                           "\n"
                           "out vec3 mColor;\n"
                           "\n"
                           "void main()\n"
                           "{\n"
                           "    gl_Position = uProjMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                           "    mColor = vec3(aColor.x / 255, aColor.y / 255, aColor.z / 255);\n"
                           "}";

    constexpr auto
    TexturedVertex2D_Fragment = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "  \n"
                                "in vec4 mColor;\n"
                                "in vec2 TexCoord;\n"
                                "\n"
                                "uniform sampler2D mTexture;\n"
                                "\n"
                                "void main()\n"
                                "{\n"
                                "    FragColor = texture(mTexture, TexCoord) * mColor;\n"
                                "}";

    constexpr auto
    TexturedVertex2D_Vertex = "#version 330 core\n"
                              "layout (location = 0) in vec2 aPos;\n"
                              "layout (location = 1) in vec4 aColor;\n"
                              "layout (location = 2) in vec2 aTexCoord;\n"
                              "\n"
                              "uniform mat4 uProjMatrix;\n"
                              "\n"
                              "out vec4 mColor;\n"
                              "out vec2 TexCoord;\n"
                              "\n"
                              "void main()\n"
                              "{\n"
                              "    gl_Position = uProjMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                              "    mColor = vec4(aColor.x / 255, aColor.y / 255, aColor.z / 255, aColor.w / 255);\n"
                              "    TexCoord = aTexCoord;\n"
                              "}";

    constexpr auto
    Vertex2D_Vertex = "#version 330 core\n"
                      "layout (location = 0) in vec2 aPos;\n"
                      "\n"
                      "out vec3 mColor;\n"
                      "\n"
                      "uniform mat4 uProjMatrix;\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "    gl_Position = uProjMatrix * vec4(aPos.xy, 1.0, 1.0);\n"
                      "    mColor = vec3(1, 1, 1);\n"
                      "}";
}

#endif //SHADER_SRC_HPP

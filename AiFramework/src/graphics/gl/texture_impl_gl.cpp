#include <glad/glad.h>
#include <graphics/texture.hpp>

using namespace ai_framework::graphics;

void Texture::create() {
    if (is_created())
        return;

    if (texture.size.x > 0 && texture.size.y > 0) {
        glGenTextures(1, &tex_id);

        // set params
        use();

        // set data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.size.x, texture.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.pixels.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void Texture::destroy() {
    if (is_created()) {
        glDeleteTextures(1, &tex_id);
        tex_id = -1;
    }
}

void Texture::use() {
    if (!is_created()) {
        create();

        if (!is_created())
            return;
    }

    glBindTexture(GL_TEXTURE_2D, tex_id);
}
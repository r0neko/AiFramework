#include <glad/glad.h>
#include <graphics/texture.hpp>

using namespace ai_framework::graphics;

void Texture::create() {
    if (is_created())
        return;

    glGenTextures(1, &tex_id);

    // set params
    use();

    // set data
    auto da = texture.pixels.data();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.size.x, texture.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, da);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::destroy() {
    // empty for now
}

void Texture::use() {
    if (!is_created()) {
        create();

        if (!is_created())
            return;
    }

    glBindTexture(GL_TEXTURE_2D, tex_id);
}
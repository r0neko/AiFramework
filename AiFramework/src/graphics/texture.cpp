#include <graphics/texture.hpp>
#include <graphics/graphics_api.hpp>

using namespace ai_framework::graphics;

void Texture::create() {
    if (is_created())
        return;

    if (texture.size.x > 0 && texture.size.y > 0) {
        tex_id = graphics::api->create_texture();

        // set params
        use();

        // set data
        graphics::api->upload_texture(texture);

        // OpenGL calls
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
    }
}

void Texture::destroy() {
    if (is_created()) {
        graphics::api->delete_texture(tex_id);
        tex_id = nullptr;
    }
}

void Texture::use() {
    if (!is_created()) {
        create();

        if (!is_created())
            return;
    }

    graphics::api->bind_texture(tex_id);
}
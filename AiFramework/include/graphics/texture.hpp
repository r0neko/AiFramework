#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <framework_build.hpp>

#include <graphics/image.hpp>

namespace ai_framework::graphics {
    struct AI_API Texture {
        Texture() {
        }

        Texture(const Image &image)
            : texture(image) {
        }

        bool is_created() const {
            return tex_id != -1;
        }

        void create();
        void destroy();
        void use();

      private:
        unsigned int tex_id = -1;
        Image texture;
    };
} // namespace ai_framework::graphics

#endif
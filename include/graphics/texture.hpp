#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <framework_build.hpp>

#include <graphics/image.hpp>

#include <cstdint>

namespace ai_framework::graphics {
    struct AI_API Texture {
        Texture() {
        }

        Texture(const Image &image)
            : texture(image) {
        }

        bool is_created() const {
            return tex_id != AI_FRAMEWORK_NULL;
        }

        void create();
        void destroy();
        void use();

      private:
        std::uintptr_t tex_id{AI_FRAMEWORK_NULL};
        Image texture;
    };
} // namespace ai_framework::graphics

#endif
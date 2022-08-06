#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <framework_build.hpp>

#include <generic/vector2.hpp>
#include <graphics/color.hpp>

#include <string>

using namespace ai_framework;

namespace ai_framework::graphics {
    struct AI_API Image {
        Image(std::string_view filename);
        Image(const Image &rhs)
            : size(rhs.size), pixels(rhs.pixels) {
        }

        IntVector2 size;
        ColorPixelArray pixels;
    };
} // namespace ai_framework::graphics

#endif
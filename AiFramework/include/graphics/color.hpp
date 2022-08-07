#ifndef COLOR_HPP
#define COLOR_HPP

#include <stdint.h>
#include <vector>

namespace ai_framework::graphics {
#pragma pack(push, 1)
    struct RGBPixel {
        uint8_t r, g, b;
    };

    struct Color {
        Color()
            : Color(0, 0, 0, 0) {
        }

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            : r(r), g(g), b(b), a(a) {
        }

        Color(const Color &rhs)
            : Color(rhs.r, rhs.g, rhs.b, rhs.a) {
        }

        Color(const RGBPixel &rhs)
            : Color(rhs.r, rhs.g, rhs.b) {
        }

        uint8_t r, g, b, a;
    };
#pragma pack(pop)

    using ColorPixelArray = std::vector<Color>;

    namespace colors {
        static Color black(0, 0, 0);
        static Color white(255, 255, 255);

        static Color red(255, 0, 0);
        static Color green(0, 255, 0);
        static Color blue(0, 0, 255);

        static Color yellow(255, 255, 0);
    } // namespace colors
} // namespace ai_framework::graphics

#endif
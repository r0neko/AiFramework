#ifndef COLOR_HPP
#define COLOR_HPP

namespace ai_framework::graphics {
#pragma pack(push, 1)
    struct Color {
        Color(int r, int g, int b, int a = 255)
            : r(r), g(g), b(b), a(a) {
        }

        Color(const Color &rhs)
            : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a) {
        }

        int r, g, b, a;
    };
#pragma pack(pop)

    namespace colors {
        static Color black(0, 0, 0);
        static Color white(255, 255, 255);

        static Color red(255, 0, 0);
        static Color green(0, 255, 0);
        static Color blue(0, 0, 255);
    } // namespace colors
} // namespace ai_framework::graphics

#endif
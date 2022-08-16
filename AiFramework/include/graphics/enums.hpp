#ifndef GRAPHICS_ENUMS_HPP
#define GRAPHICS_ENUMS_HPP

namespace ai_framework::graphics {
    enum DataType {
        BYTE,
        UNSIGNED_BYTE,
        INT,
        UNSIGNED_INT,
        FLOAT
    };

    enum BufferType {
        ARRAY_BUFFER,
        ELEMENT_ARRAY_BUFFER
    };

    enum UsageMode {
        STATIC_DRAW,
        DYNAMIC_DRAW
    };

    enum DrawMode {
        POINTS,
        LINES,
        TRIANGLES
    };

    enum ShaderType {
        FRAGMENT,
        VERTEX
    };

    const opaque_t GRAPHICS_API_NULL = (opaque_t) -1;
} // namespace ai_framework::graphics

#endif
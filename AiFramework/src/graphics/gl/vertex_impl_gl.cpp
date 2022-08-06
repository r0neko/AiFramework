#include <glad/glad.h>
#include <graphics/vertex.hpp>

using namespace ai_framework;
using namespace ai_framework::graphics;

int _max_enabled_attr = 0;

void graphics::enable_attributes(int amount) {
    if (_max_enabled_attr == amount)
        return;

    for (int i = 0; i < amount; i++) {
        if (i < amount)
            glEnableVertexAttribArray(i);
        else
            glDisableVertexAttribArray(i);
    }

    _max_enabled_attr = amount;
}

void Vertex2D::set_attributes() {
    /*
     * Each vertex has the following structure in memory:
     * +-------+
     * | X | Y |
     * +-------+
     * | 0 | 1 |
     * +-------+
     * Therefore, there are 2 floats(X and Y) that serve the purpose of setting
     * the position.
     */

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);

    enable_attributes(1);
}

void ColorVertex2D::set_attributes() {
    /*
     * Each vertex has the following structure in memory:
     * +-------------------+
     * | X | Y | R | G | B |
     * +-------------------+
     * | 0 | 1 | 2 | 3 | 4 |
     * +-------------------+
     * Therefore, there are 2 floats(X and Y) that serve the purpose of setting
     * the position and 3 bytes(R, G, B) which serve as the color.
     */

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ColorVertex2D), 0);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(ColorVertex2D), (void *) sizeof(FloatVector2));

    enable_attributes(2);
}

void TexturedVertex2D::set_attributes() {
    /*
     * Each vertex has the following structure in memory:
     * +-------------------+-------+
     * | X | Y | R | G | B | X | Y |
     * +---------------------------+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
     * +---------------------------+
     * Therefore, there are 2 floats(X and Y) that serve the purpose of setting
     * the position, 4 bytes(R, G, B, A) which serve as the color,
     * and 2 more floats(X and Y) which serve the purpose of translating the texture sample.
     */

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex2D), 0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(TexturedVertex2D), (void *) sizeof(FloatVector2));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex2D), (void *) (sizeof(FloatVector2) + sizeof(Color)));

    enable_attributes(3);
}
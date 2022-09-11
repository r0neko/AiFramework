#define STB_IMAGE_IMPLEMENTATION

#include <graphics/image.hpp>
#include <vendor/stb/stb_image.h>

#include <stdexcept>

using namespace ai_framework::graphics;

// use stb image internally for now to make image loading easier
Image::Image(std::string_view filename) {
    int chan_nbr;

    stbi_set_flip_vertically_on_load(true);
    auto image_data = stbi_load(filename.data(), &size.x, &size.y, &chan_nbr, 0);

    if (!image_data)
        throw std::runtime_error("failed to load this image!");

    for (int i = 0; i < (size.x * size.y); i++) {
        if (chan_nbr == 3) {
            auto pixel = (RGBPixel *) (image_data + (i * sizeof(RGBPixel)));
            pixels.push_back(*pixel);
        } else if (chan_nbr == 4) {
            auto pixel = (Color *) (image_data + (i * sizeof(Color)));
            pixels.push_back(*pixel);
        }
    }

    stbi_image_free(image_data);
}
#ifndef GRAPHICS_API_HPP
#define GRAPHICS_API_HPP

#include <graphics/i_graphics_api.hpp>

#include <memory>

namespace ai_framework::graphics {
    inline std::shared_ptr<IGraphicsAPI> api{nullptr};
}

#endif
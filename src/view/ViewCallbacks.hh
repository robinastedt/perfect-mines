#pragma once

#include <functional>
#include <cstddef>

namespace intmines {
    namespace view {
        struct ViewCallbacks {
            std::function<void(size_t, size_t)> tile_left_clicked;
            std::function<void(size_t, size_t)> tile_right_clicked;
        };
    }
}
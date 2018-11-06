#pragma once

#include <functional>
#include <cstddef>

namespace pmines {
    namespace view {
        struct ViewCallbacks {
            std::function<void(int, int)> tile_left_clicked;
            std::function<void(int, int)> tile_right_clicked;
        };
    }
}
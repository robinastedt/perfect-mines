#pragma once

#include <cstddef>
#include <vector>

namespace pmines {
    namespace model {
        class GameState {
        public:
            GameState(size_t width, size_t height, size_t mines);
            bool is_mine(size_t x, size_t y);
        protected:
            std::vector<std::vector<bool>> m_mines;
        };
    }
}
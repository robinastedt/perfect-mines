#pragma once

#include <cstddef>
#include <vector>

namespace pmines {
    namespace model {
        class GameState {
        public:
            GameState(int width, int height, int mines);
            bool is_mine(int x, int y);
        protected:
            std::vector<std::vector<bool>> m_mines;
        };
    }
}
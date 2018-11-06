#pragma once

#include <cstddef>
#include <vector>

namespace pmines {
    namespace model {
        class GameState {
        public:
            GameState(int width, int height, int mines);
            bool is_mine(int x, int y);
            int get_neighbouring_mines(int x, int y);
        protected:
            int m_width;
            int m_height;
            std::vector<std::vector<bool>> m_mines;
        };
    }
}
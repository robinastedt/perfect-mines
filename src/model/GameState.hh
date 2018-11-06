#pragma once

#include <cstddef>
#include <vector>

namespace pmines {
    namespace model {
        class GameState {
        public:
            GameState(int width, int height, int mines);
            int get_width();
            int get_height();
            bool is_mine(int x, int y);
            int get_neighbouring_mines(int x, int y);
            bool is_revealed(int x, int y);
            void reveal(int x, int y);
        protected:
            int m_width;
            int m_height;
            std::vector<std::vector<bool>> m_mines;
            std::vector<std::vector<bool>> m_revealed;
        };
    }
}
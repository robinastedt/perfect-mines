#include "GameState.hh"

#include <numeric>
#include <algorithm>

namespace pmines {
    namespace model {
        GameState::GameState(size_t width, size_t height, size_t mines) :
        m_mines(width, std::vector<bool>(height, false)) {
            const size_t total_tiles = width * height;
            std::vector<size_t> tiles(total_tiles);
            std::iota(tiles.begin(), tiles.end(), 0u);
            std::random_shuffle(tiles.begin(), tiles.end());
            for (auto it = tiles.begin(); it != tiles.begin() + mines; it++) {
                const size_t x = *it % width;
                const size_t y = *it / width;
                m_mines[x][y] = true;
            }
        }

        bool GameState::is_mine(size_t x, size_t y) {
            return m_mines[x][y];
        }
    }
}


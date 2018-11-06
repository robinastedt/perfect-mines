#include "GameState.hh"

#include <numeric>
#include <algorithm>

namespace pmines {
    namespace model {
        GameState::GameState(int width, int height, int mines) :
        m_mines(width, std::vector<bool>(height, false)) {
            const int total_tiles = width * height;
            std::vector<int> tiles(total_tiles);
            std::iota(tiles.begin(), tiles.end(), 0u);
            std::random_shuffle(tiles.begin(), tiles.end());
            for (auto it = tiles.begin(); it != tiles.begin() + mines; it++) {
                const int x = *it % width;
                const int y = *it / width;
                m_mines[x][y] = true;
            }
        }

        bool GameState::is_mine(int x, int y) {
            return m_mines[x][y];
        }
    }
}


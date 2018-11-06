#include "GameState.hh"

#include <numeric>
#include <algorithm>

#include <iostream>

namespace pmines {
    namespace model {



        GameState::GameState(int width, int height, int mines) :
        m_width(width),
        m_height(height),
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

        int GameState::get_neighbouring_mines(int _x, int _y) {
            int neighbours = 0;
            for (int x = std::max(0, _x-1); x < std::min(m_width, _x + 2); x++) {
                for (int y = std::max(0, _y-1); y < std::min(m_height, _y + 2); y++) {
                    neighbours += m_mines[x][y] ? 1 : 0;
                }
            }
            return neighbours;
        }
    }
}


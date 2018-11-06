#include "GameState.hh"

#include <numeric>
#include <algorithm>

#include <iostream>

namespace pmines {
    namespace model {



        GameState::GameState(int width, int height, int mines) :
        m_width(width),
        m_height(height),
        m_mines(width, std::vector<bool>(height, false)),
        m_revealed(width, std::vector<bool>(height, false)) {
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

        int GameState::get_width() {
            return m_width;
        }

        int GameState::get_height() {
            return m_height;
        }

        bool GameState::is_mine(int x, int y) {
            return m_mines[x][y];
        }

        int GameState::get_neighbouring_mines(int x, int y) {
            int neighbours = 0;
            for (int _x = std::max(0, x-1); _x < std::min(m_width, x + 2); _x++) {
                for (int _y = std::max(0, y-1); _y < std::min(m_height, y + 2); _y++) {
                    neighbours += m_mines[_x][_y] ? 1 : 0;
                }
            }
            return neighbours;
        }

        bool GameState::is_revealed(int x, int y) {
            return m_revealed[x][y];
        }

        void GameState::reveal(int x, int y) {
            m_revealed[x][y] = true;
        }
    }
}


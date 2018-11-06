#include "GameState.hh"

#include <numeric>

#include <random>

namespace pmines {
    namespace model {

        namespace {
            std::vector<std::vector<bool>> get_random_minefield(int width, int height, int mines, unsigned seed) {
                const int total_tiles = width * height;
                std::vector<int> tiles(total_tiles);
                std::iota(tiles.begin(), tiles.end(), 0);
                std::minstd_rand generator(seed);
                std::vector<std::vector<bool>> minefield(width, std::vector<bool>(height, false));
                for (int i = 0; i < mines; i++) {
                    std::uniform_int_distribution<int> distribution(i, total_tiles - 1);
                    const int selected = distribution(generator);
                    const int x = selected % width;
                    const int y = selected / height;
                    minefield[x][y] = true;
                    tiles[selected] = tiles[i];
                }
                return minefield;
            }
        }

        GameState::GameState(int width, int height, int mines, unsigned seed) :
        m_width(width),
        m_height(height),
        m_mines(get_random_minefield(width, height, mines, seed)),
        m_tile_state(width, std::vector<TileState>(height, HIDDEN)) {
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
            return m_tile_state[x][y] == REVEALED;
        }
        
        bool GameState::is_flagged(int x, int y) {
            return m_tile_state[x][y] == FLAGGED;
        }

        bool GameState::is_hidden(int x, int y) {
            return m_tile_state[x][y] == HIDDEN;
        }

        void GameState::reveal(int x, int y) {
            m_tile_state[x][y] = REVEALED;
        }

        void GameState::flag(int x, int y) {
            m_tile_state[x][y] = FLAGGED;
        }

        void GameState::unflag(int x, int y) {
            m_tile_state[x][y] = HIDDEN;
        }
    }
}


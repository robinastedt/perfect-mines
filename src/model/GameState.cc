#include "GameState.hh"

#include <numeric>
#include <random>

#include <algorithm>

namespace pmines::model {

    std::unordered_set<int>
    GameState::_get_reserved(int width, int height, GameState::point_t point) {
        std::unordered_set<int> reserved_tiles;
        for (int _x = std::max(0, point.x-1); _x < std::min(width, point.x + 2); _x++) {
            for (int _y = std::max(0, point.y-1); _y < std::min(height, point.y + 2); _y++) {
                const int reserved = _x * height + _y;
                reserved_tiles.insert(reserved);
            }
        }
        return reserved_tiles;
    }

    GameState::mine_grid_t
    GameState::_random_minefield(int width, int height, int mines, unsigned seed,const std::unordered_set<int>& reserved) {
        const int total_tiles = width * height;
        std::vector<int> tiles(total_tiles);
        std::iota(tiles.begin(), tiles.end(), 0);
        std::minstd_rand generator(seed);
        GameState::mine_grid_t minefield(width, height, GameState::EMPTY);

        for (int i = 0, end = total_tiles - 1; i < mines; i++) {
            std::uniform_int_distribution<int> distribution(i, end);
            const int selected = distribution(generator);
            if (reserved.find(tiles[selected]) != reserved.end()) {
                std::swap(tiles[selected], tiles[end]);
                i--;
                end--;
            }
            else {
                const point_t point = {tiles[selected] / height, tiles[selected] % height};
                minefield[point] = MINE;
                std::swap(tiles[selected], tiles[i]);
            }
            
        }
        return minefield;
    }

    GameState::mine_grid_t
    GameState::_random_minefield(int width, int height, int mines, unsigned seed, GameState::point_t point) {
        return _random_minefield(width, height, mines, seed, _get_reserved(width, height, point));
    }

    GameState::GameState(int width, int height, int mines, unsigned seed, point_t initial_point) :
    m_width(width),
    m_height(height),
    m_initial_point(initial_point),
    m_num_mines(mines),
    m_mines(_random_minefield(width, height, mines, seed, initial_point)),
    m_tile_state(width, height, HIDDEN) {
    }

    int
    GameState::get_width() {
        return m_width;
    }

    int
    GameState::get_height() {
        return m_height;
    }

    bool
    GameState::is_mine(point_t point) {
        return m_mines[point] == MINE;
    }

    std::vector<GameState::point_t>
    GameState::get_neighbours(point_t point) {
        std::vector<point_t> neighbours;
        for (int _x = std::max(0, point.x-1); _x < std::min(m_width, point.x + 2); _x++) {
            for (int _y = std::max(0, point.y-1); _y < std::min(m_height, point.y + 2); _y++) {
                if (point.x != _x or point.y != _y) {
                    neighbours.push_back({_x, _y});
                }
            }
        }
        return neighbours;
    }

    std::vector<GameState::point_t>
    GameState::get_neighbourhood(point_t point) {
        std::vector<point_t> neighbours;
        for (int _x = std::max(0, point.x-1); _x < std::min(m_width, point.x + 2); _x++) {
            for (int _y = std::max(0, point.y-1); _y < std::min(m_height, point.y + 2); _y++) {
                neighbours.push_back({_x, _y});
            }
        }
        return neighbours;
    }

    int
    GameState::get_neighbouring_mines(point_t point) {
        const std::vector<point_t> neighbours = get_neighbours(point);
        return std::count_if(neighbours.begin(), neighbours.end(), [this](point_t p){return m_mines[p] == MINE;});
    }

    GameState::TileState
    GameState::get_state(point_t point) {
        return m_tile_state[point];
    }

    void
    GameState::set_state(point_t point, TileState state) {
        m_tile_state[point] = state;
    }
}


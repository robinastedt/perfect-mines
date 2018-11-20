#pragma once

#include <vector>
#include <unordered_set>

namespace pmines {
    namespace model {
        class GameState {
        public:
            enum TileState {
                HIDDEN,
                REVEALED,
                FLAGGED
            };

            enum MineState {
                EMPTY,
                MINE
            };

            struct point_t {
                int x;
                int y;
            };

            friend class ISolver;

            GameState(int width, int height, int mines, unsigned seed, point_t point);
            int get_width();
            int get_height();
            bool is_mine(point_t point);
            std::vector<point_t> get_neighbours(point_t point);
            std::vector<point_t> get_neighbourhood(point_t point);
            int get_neighbouring_mines(point_t point);
            TileState get_state(point_t point);
            void set_state(point_t point, TileState state);

        protected:
            template<typename T>
            class EnumGrid {
            public:
                EnumGrid(int width, int height, T default_value) :
                m_value(width, std::vector<T>(height, default_value)) {
                };

                T& operator[](point_t point) {
                    return m_value[point.x][point.y];
                }
            private:
                std::vector<std::vector<T>> m_value;
            };

            using mine_grid_t  = EnumGrid<MineState>;
            using state_grid_t = EnumGrid<TileState>;

            static std::unordered_set<int> _get_reserved(int width, int height, GameState::point_t point);
            static mine_grid_t _random_minefield(int width, int height, int mines, unsigned seed,const std::unordered_set<int>& reserved);
            static mine_grid_t _random_minefield(int width, int height, int mines, unsigned seed, GameState::point_t point);

            int m_width;
            int m_height;
            point_t m_initial_point;
            int m_num_mines;

            mine_grid_t  m_mines;
            state_grid_t m_tile_state;

            
        };
    }
}
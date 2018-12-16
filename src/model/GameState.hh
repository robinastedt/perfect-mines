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

            friend class SimpleSolver;

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
            class Grid {
            public:
                Grid(int width, int height, T default_value) :
                m_width(width),
                m_value(width * height, default_value) {
                };

                Grid(int width, int height) :
                m_width(width),
                m_value(width * height) {
                };

                T& operator[](const point_t point) {
                    return m_value[point.x + m_width * point.y];
                }

                const T& operator[](const point_t point) const {
                    return m_value[point.x + m_width * point.y];
                }

            private:
                int m_width;
                std::vector<T> m_value;
            };

            using mine_grid_t  = Grid<MineState>;
            using state_grid_t = Grid<TileState>;

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
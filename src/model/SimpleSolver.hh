#pragma once

#include <model/ISolver.hh>

namespace pmines {
    namespace model {
        class SimpleSolver : public ISolver {
        public:
            SimpleSolver(const GameState& gamestate);
            ~SimpleSolver();
            bool solve();
            bool solve_iterate();
            bool is_solved();
            GameState& get_solution();
        private:
            void mark_revealed(GameState::point_t point);

            GameState m_gamestate;
            GameState::Grid<int> m_mineinfo;
            int m_num_tiles;
            int m_num_revealed;
        };
    }
}
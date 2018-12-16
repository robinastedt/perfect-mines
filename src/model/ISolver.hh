#pragma once

#include <model/GameState.hh>

namespace pmines {
    namespace model {
        class ISolver {
        public:
            ISolver() {}
            virtual ~ISolver() {}
            virtual bool solve() = 0;
            virtual bool solve_iterate() = 0;
            virtual bool is_solved() = 0;
            virtual GameState& get_solution() = 0;
        };
    }
}
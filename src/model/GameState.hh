#pragma once

#include <cstddef>
#include <vector>
#include <random>

namespace intmines {
    namespace model {
        class GameState {
        public:
            GameState(size_t width, size_t height, unsigned int mines, std::seed_seq seed);
        
        protected:
            std::vector<std::vector<bool>> m_mines;
        };
    }
}
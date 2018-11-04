#include "GameState.hh"

namespace intmines {
    namespace model {
        GameState::GameState(size_t width, size_t height, unsigned int, std::seed_seq) :
        m_mines(height, std::vector<bool>(width)) {
            
        }
    }
}


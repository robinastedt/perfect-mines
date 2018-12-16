#include "SimpleSolver.hh"

namespace pmines {
    namespace model {
        SimpleSolver::SimpleSolver(const GameState& gamestate) :
        ISolver(),
        m_gamestate(gamestate),
        m_mineinfo(gamestate.m_width, gamestate.m_height),
        m_num_tiles(gamestate.m_width * gamestate.m_height),
        m_num_revealed(0) {

        }

        SimpleSolver::~SimpleSolver() {

        }

        bool SimpleSolver::solve() {
            mark_revealed(m_gamestate.m_initial_point);
            while (not is_solved()) {
                if (not solve_iterate()) {
                    return false;
                }
            }
            return true;
        }

        bool SimpleSolver::solve_iterate() {
            bool progressed = false;
            for (int x = 0; x < m_gamestate.m_width; x++) {
                for (int y = 0; y < m_gamestate.m_height; y++) {
                    const GameState::point_t point {x, y};
                    if (m_gamestate.get_state(point) == GameState::REVEALED) {
                        auto neighbours = m_gamestate.get_neighbours(point);
                        int flagged = 0;
                        int hidden = 0;
                        for (GameState::point_t neighbour : neighbours) {
                            const GameState::TileState state = m_gamestate.get_state(neighbour);
                            if (state == GameState::HIDDEN) {
                                hidden++;
                            }
                            else if (state == GameState::FLAGGED) {
                                flagged++;
                            }
                        }
                        if (flagged == m_mineinfo[point]) {
                            for (GameState::point_t neighbour : neighbours) {
                                const GameState::TileState state = m_gamestate.get_state(neighbour);
                                if (state == GameState::HIDDEN) {
                                    mark_revealed(neighbour);
                                    progressed = true;
                                }
                            }
                        }
                        else if (flagged + hidden == m_mineinfo[point]) {
                            for (GameState::point_t neighbour : neighbours) {
                                const GameState::TileState state = m_gamestate.get_state(neighbour);
                                if (state == GameState::HIDDEN) {
                                    m_gamestate.set_state(neighbour, GameState::FLAGGED);
                                    progressed = true;
                                }
                            }
                        }
                    }
                }
            }
            return progressed;
        }

        bool SimpleSolver::is_solved() {
            return m_num_revealed == m_num_tiles - m_gamestate.m_num_mines;
        }

        GameState& SimpleSolver::get_solution() {
            return m_gamestate;
        }

        void SimpleSolver::mark_revealed(GameState::point_t point) {
            m_num_revealed++;
            m_gamestate.set_state(point, GameState::REVEALED);
            m_mineinfo[point] = m_gamestate.get_neighbouring_mines(point);
        }
    }
}
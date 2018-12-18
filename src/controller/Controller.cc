#include "Controller.hh"

#include <view/ViewCallbacks.hh>
#include <model/ISolver.hh>
#include <model/SimpleSolver.hh>

#include <iostream>
#include <chrono>

namespace pmines {
    namespace controller {

        Controller::Controller() {
            
        }

        Controller::~Controller() {

        }

        int Controller::run(int argc, char** argv) {
            // TODO:: Add options for headless modes, etc.
            auto callbacks = create_callbacks();
            m_view = std::make_unique<view::View>(callbacks);
            return m_view->run(argc, argv);
        }

        std::shared_ptr<view::ViewCallbacks> Controller::create_callbacks() {
            std::shared_ptr<view::ViewCallbacks> callbacks = std::make_shared<view::ViewCallbacks>();
            callbacks->tile_left_clicked = sigc::mem_fun(*this, &Controller::action_tile_left_clicked);
            callbacks->tile_right_clicked = sigc::mem_fun(*this, &Controller::action_tile_right_clicked);
            return callbacks;
        }

        void Controller::action_tile_left_clicked(int x, int y) {
            const model::GameState::point_t point {x, y};
            if (not m_gamestate) {
                initialize_gamestate(x, y);
                //m_gamestate = std::make_unique<model::GameState>(10, 10, 16, 1u, point);
            }
            if (m_gamestate->get_state(point) == model::GameState::HIDDEN) {
                reveal_tile(x, y);
            }
            else if (m_gamestate->get_state(point) == model::GameState::REVEALED) {
                int flagged = 0;
                auto neighbours = m_gamestate->get_neighbours(point);
                for (model::GameState::point_t neighbour : neighbours) {
                    if (m_gamestate->get_state(neighbour) == model::GameState::FLAGGED) {
                        flagged++;
                    }
                }
                if (flagged == m_gamestate->get_neighbouring_mines(point)) {
                    for (model::GameState::point_t neighbour : neighbours) {
                        if (m_gamestate->get_state(neighbour) == model::GameState::HIDDEN) {
                            reveal_tile(neighbour.x, neighbour.y);
                        }
                    }
                }
            }
        }

        void Controller::initialize_gamestate(int x, int y) {
            int generation = 1;
            std::unique_ptr<model::ISolver> solver;
            do {
                std::cout << "Generating new game, try: " << generation << std::endl;
                const model::GameState::point_t point {x, y};
                const auto now_clock = std::chrono::high_resolution_clock::now();
                const auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(now_clock.time_since_epoch()).count();
                m_gamestate = std::make_unique<model::GameState>(30, 16, 99, now, point);
                solver = std::make_unique<model::SimpleSolver>(*m_gamestate);
                generation++;
            } while (not solver->solve());
        }


        void Controller::action_tile_right_clicked(int x, int y) {
            switch (m_gamestate->get_state({x, y})) {
                case model::GameState::FLAGGED:
                    unflag_tile(x, y);
                    break;
                case model::GameState::HIDDEN:
                    flag_tile(x, y);
                    break;
                default:
                    break;
            }
        }

        void Controller::reveal_safe_tile(int x, int y) {
            model::GameState::point_t point = {x, y};
            m_gamestate->set_state(point, model::GameState::REVEALED);
            const int mines = m_gamestate->get_neighbouring_mines(point);
            m_view->set_tile_empty(x, y, mines);
            if (mines > 0) {
                return;
            }
            for (const auto neighbour : m_gamestate->get_neighbours(point)) {
                if (m_gamestate->get_state(neighbour) == model::GameState::HIDDEN) {
                    reveal_safe_tile(neighbour.x , neighbour.y);
                }
            }
        }

        void Controller::reveal_tile(int x, int y) {
            if (m_gamestate->is_mine({x, y})) {
                // TODO: Handle properly, can now be reset by flagging
                m_view->set_tile_mine(x, y);
            }
            else {
                reveal_safe_tile(x, y);
            }
        }

        void Controller::flag_tile(int x, int y) {
            m_gamestate->set_state({x, y}, model::GameState::FLAGGED);
            m_view->set_tile_flagged(x, y);
        }

        void Controller::unflag_tile(int x, int y) {
            m_gamestate->set_state({x, y}, model::GameState::HIDDEN);
            m_view->set_tile_hidden(x, y);
        }
    }
}

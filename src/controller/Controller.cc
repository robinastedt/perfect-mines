#include "Controller.hh"

#include <view/ViewCallbacks.hh>

namespace pmines {
    namespace controller {

        Controller::Controller() :
        m_gamestate(10, 10, 16, 1u) {

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
            if (m_gamestate.is_hidden(x, y)) {
                if (m_gamestate.is_mine(x, y)) {
                    // TODO: Handle properly, can now be reset by flagging
                    m_view->set_tile_mine(x, y);
                }
                else {
                    reveal_tile(x, y);
                }
            }
        }

        void Controller::action_tile_right_clicked(int x, int y) {
            if (m_gamestate.is_flagged(x, y)) {
                unflag_tile(x, y);
            }
            else if (m_gamestate.is_hidden(x, y)) {
                flag_tile(x, y);
            }
        }

        void Controller::reveal_tile(int x, int y) {
            const int mines = m_gamestate.get_neighbouring_mines(x, y);
            m_gamestate.reveal(x, y);
            m_view->set_tile_empty(x, y, mines);
            if (mines == 0) {
                for (int _x = std::max(0, x-1); _x < std::min(m_gamestate.get_width(), x + 2); _x++) {
                    for (int _y = std::max(0, y-1); _y < std::min(m_gamestate.get_height(), y + 2); _y++) {
                        if (m_gamestate.is_hidden(_x, _y)) {
                            reveal_tile(_x, _y);
                        }
                    }
                }
            }
        }

        void Controller::flag_tile(int x, int y) {
            m_gamestate.flag(x, y);
            m_view->set_tile_flagged(x, y);
        }

        void Controller::unflag_tile(int x, int y) {
            m_gamestate.unflag(x, y);
            m_view->set_tile_hidden(x, y);
        }

        
    }
}

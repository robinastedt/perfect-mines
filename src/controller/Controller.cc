#include "Controller.hh"

#include <view/ViewCallbacks.hh>

namespace pmines {
    namespace controller {

        Controller::Controller() :
        m_gamestate(10,10,16) {

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

        void Controller::action_tile_left_clicked(size_t x, size_t y) {
            if (m_gamestate.is_mine(x, y)) {
                m_view->set_tile_flagged(x, y);
            }
            else {
                m_view->set_tile_empty(x, y, 5);
            }
        }

        void Controller::action_tile_right_clicked(size_t x, size_t y) {
            m_view->set_tile_hidden(x, y);
        }
    }
}

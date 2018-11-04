#include "Controller.hh"

#include <ViewCallbacks.hh>

#include <iostream>



namespace intmines {
    namespace controller {

        Controller::Controller(Gtk::Window& window) :
        m_view(window, create_callbacks()) {

        }

        Controller::~Controller() {

        }

        std::shared_ptr<view::ViewCallbacks> Controller::create_callbacks() {
            std::shared_ptr<view::ViewCallbacks> callbacks = std::make_shared<view::ViewCallbacks>();
            callbacks->tile_left_clicked = sigc::mem_fun(*this, &Controller::action_tile_left_clicked);
            callbacks->tile_right_clicked = sigc::mem_fun(*this, &Controller::action_tile_right_clicked);
            return callbacks;
        }

        void Controller::action_tile_left_clicked(size_t x, size_t y) {
            m_view.set_tile_empty(x, y, 5);
        }

        void Controller::action_tile_right_clicked(size_t x, size_t y) {
            m_view.set_tile_flagged(x, y);
        }
    }
}

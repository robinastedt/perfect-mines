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
            callbacks->tile_clicked = sigc::mem_fun(*this, &Controller::action_tile_clicked);
            return callbacks;
        }

        void Controller::action_tile_clicked(size_t x, size_t y) {
            m_view.set_tile_empty(x, y, 5);
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }
    }
}

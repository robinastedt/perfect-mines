#pragma once

#include <view/View.hh>
#include <model/GameState.hh>

#include <gtkmm/window.h>

#include <memory>
#include <cstddef>

namespace intmines {
    namespace controller {
        class Controller {
        public:
            Controller(Gtk::Window& window);
            ~Controller();
            
            void action_tile_left_clicked(size_t x, size_t y);
            void action_tile_right_clicked(size_t x, size_t y);

        protected:
            std::shared_ptr<view::ViewCallbacks> create_callbacks();

            view::View m_view;
            model::GameState m_gamestate;
        };
    }
}
#pragma once

#include <view/View.hh>
#include <model/GameState.hh>

#include <memory>
#include <cstddef>

namespace pmines {
    namespace controller {
        class Controller {
        public:
            Controller();
            ~Controller();

            int run(int argc, char** argv);
            
            void action_tile_left_clicked(size_t x, size_t y);
            void action_tile_right_clicked(size_t x, size_t y);

        protected:
            std::shared_ptr<view::ViewCallbacks> create_callbacks();
            model::GameState m_gamestate;
            std::unique_ptr<view::View> m_view;
        };
    }
}
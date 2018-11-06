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
            
            void action_tile_left_clicked(int x, int y);
            void action_tile_right_clicked(int x, int y);

        protected:
            std::shared_ptr<view::ViewCallbacks> create_callbacks();
            model::GameState m_gamestate;
            std::unique_ptr<view::View> m_view;
            void reveal_tile(int x, int y);
        };
    }
}
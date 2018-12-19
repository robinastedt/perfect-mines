#pragma once

#include <view/View.hh>
#include <model/GameState.hh>

#include <memory>

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
            void initialize_gamestate(int x, int y);
            std::shared_ptr<view::ViewCallbacks> create_callbacks();
            void reveal_safe_tile(int x, int y);
            void reveal_tile(int x, int y);
            void flag_tile(int x, int y);
            void unflag_tile(int x, int y);
            std::unique_ptr<model::GameState> m_gamestate;
            std::unique_ptr<view::View> m_view;
            
        };
    }
}
#pragma once

#include <view/Gameboard.hh>
#include <view/ViewCallbacks.hh>

#include <gtkmm/box.h>
#include <gtkmm/window.h>

namespace pmines {
    namespace view {

        class View {
        public:
            View(std::shared_ptr<ViewCallbacks> callbacks);
            ~View();

            int run(int argc, char** argv);

            void reset_gameboard(int width, int height);

            void set_tile_hidden(int x, int y);
            void set_tile_flagged(int x, int y);
            void set_tile_mine(int x, int y);
            void set_tile_empty(int x, int y, int adjecent_count);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;

            // Memory managed by Gtk
            Gtk::Window* m_window;
            Gtk::Box* m_container;
            Gameboard* m_gameboard;
        };

    }
}
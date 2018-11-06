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

            void reset_gameboard(size_t width, size_t height);

            void set_tile_hidden(size_t x, size_t y);
            void set_tile_flagged(size_t x, size_t y);
            void set_tile_mine(size_t x, size_t y);
            void set_tile_empty(size_t x, size_t y, int adjecent_count);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;

            // Memory managed by Gtk
            Gtk::Window* m_window;
            Gtk::Box* m_container;
            Gameboard* m_gameboard;
        };

    }
}
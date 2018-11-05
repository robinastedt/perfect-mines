#pragma once

#include <view/Gameboard.hh>
#include <view/ViewCallbacks.hh>

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/button.h>
#include <gtkmm/separator.h>

namespace intmines {
    namespace view {

        class View {
        public:
            View(Gtk::Window& window, std::shared_ptr<ViewCallbacks> callbacks);
            View();
            ~View();

            void set_tile_hidden(size_t x, size_t y);
            void set_tile_flagged(size_t x, size_t y);
            void set_tile_mine(size_t x, size_t y);
            void set_tile_empty(size_t x, size_t y, int adjecent_count);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;
            Gtk::Box* m_container;
            Gameboard m_gameboard;
        };

    }
}
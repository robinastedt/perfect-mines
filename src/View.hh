#pragma once

#include <Gameboard.hh>
#include <ViewCallbacks.hh>

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

            void mark_mine(size_t x, size_t y);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;
            Gtk::Box* m_container;
            Gameboard m_gameboard;
        };

    }
}
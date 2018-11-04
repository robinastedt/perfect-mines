#include "View.hh"

#include <iostream>

#include <gtkmm/application.h>

namespace intmines {
    namespace view {
        View::View(Gtk::Window& window, std::shared_ptr<ViewCallbacks> callbacks) :
        m_callbacks(callbacks),
        m_container(Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL))),
        m_gameboard(*m_container, callbacks, 10, 10)
        {
            window.add(*m_container);
            m_container->set_border_width(0);
        }

        View::~View() {

        }

        void
        View::mark_mine(size_t x, size_t y) {
            //m_gameboard.mark_mine(x, y);
        }
    }
}
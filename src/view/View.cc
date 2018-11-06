#include "View.hh"

#include <iostream>

#include <gtkmm/application.h>

namespace pmines {
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

        void View::set_tile_hidden(size_t x, size_t y) {
            m_gameboard.set_tile_state(x, y, Tile::DrawState::HIDDEN);
        }
        void View::set_tile_flagged(size_t x, size_t y) {
            m_gameboard.set_tile_state(x, y, Tile::DrawState::FLAGGED);
        }
        void View::set_tile_mine(size_t x, size_t y) {
            m_gameboard.set_tile_state(x, y, Tile::DrawState::MINE);
        }
        void View::set_tile_empty(size_t x, size_t y, int adjecent_count) {
            m_gameboard.set_tile_state(x, y, Tile::DrawState::EMPTY, adjecent_count);
        }
    }
}
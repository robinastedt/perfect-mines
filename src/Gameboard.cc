#include "Gameboard.hh"

#include <ViewCallbacks.hh>

#include <gtkmm/image.h>


#include <iostream>
#include <functional>

namespace intmines {
    namespace view {


        Gameboard::Gameboard(Gtk::Box& parent, std::shared_ptr<ViewCallbacks> callbacks, size_t width, size_t height) :
        m_callbacks(callbacks),
        m_container(Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL))),
        m_tiles(height, std::vector<std::shared_ptr<Tile>>(width)) {
            m_container->set_border_width(0);
            for (size_t y = 0; y < height; y++) {
                Gtk::Box* row_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
                row_box->set_border_width(0);
                for (size_t x = 0; x < width; x++) {
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(*row_box, callbacks, x, y);
                    m_tiles[y][x] = tile;
                }
                m_container->pack_start(*row_box, true, true, 0);
            }
            parent.pack_start(*m_container, true, true, 0);
        }

        void Gameboard::set_tile_state(size_t x, size_t y, Tile::DrawState state) {
            m_tiles[y][x]->set_tile_state(state);
        }

        void Gameboard::set_tile_state(size_t x, size_t y, Tile::DrawState state, int adjecent_count) {
            m_tiles[y][x]->set_tile_state(state, adjecent_count);
        }
    }
}
#include "Gameboard.hh"

namespace pmines {
    namespace view {


        Gameboard::Gameboard(std::shared_ptr<ViewCallbacks> callbacks, int width, int height) :
        Gtk::Box(Gtk::ORIENTATION_VERTICAL),
        m_callbacks(callbacks),
        m_tiles(height, std::vector<Tile*>(width)) {
            set_border_width(0);
            for (int y = 0; y < height; y++) {
                Gtk::Box* row_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
                pack_start(*row_box, true, true, 0);
                row_box->set_border_width(0);
                for (int x = 0; x < width; x++) {
                    Tile* tile = Gtk::manage(new Tile(callbacks, x, y));
                    row_box->pack_start(*tile, true, true, 0);
                    m_tiles[y][x] = tile;
                }
            }
        }

        void Gameboard::set_tile_state(int x, int y, Tile::DrawState state) {
            m_tiles[y][x]->set_tile_state(state);
        }

        void Gameboard::set_tile_state(int x, int y, Tile::DrawState state, int adjecent_count) {
            m_tiles[y][x]->set_tile_state(state, adjecent_count);
        }
    }
}
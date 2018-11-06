#pragma once

#include <view/ViewCallbacks.hh>
#include <view/Tile.hh>

#include <gtkmm/box.h>

#include <vector>
#include <memory>

namespace pmines {
    namespace view {

        class Gameboard {
        public:
            Gameboard(Gtk::Box& parent, std::shared_ptr<ViewCallbacks> callbacks, size_t width, size_t height);

            void set_tile_state(size_t x, size_t y, Tile::DrawState state);
            void set_tile_state(size_t x, size_t y, Tile::DrawState state, int adjecent_count);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;
            Gtk::Box* m_container;
            std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
        };
    }
}

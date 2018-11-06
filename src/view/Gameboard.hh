#pragma once

#include <view/ViewCallbacks.hh>
#include <view/Tile.hh>

#include <gtkmm/box.h>

#include <vector>
#include <memory>

namespace pmines {
    namespace view {

        class Gameboard : public Gtk::Box {
        public:
            Gameboard(std::shared_ptr<ViewCallbacks> callbacks, int width, int height);

            void set_tile_state(int x, int y, Tile::DrawState state);
            void set_tile_state(int x, int y, Tile::DrawState state, int adjecent_count);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;

            // Memory managed by Gtk
            std::vector<std::vector<Tile*>> m_tiles;
        };
    }
}

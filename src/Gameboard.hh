#pragma once

#include <ViewCallbacks.hh>
#include <Tile.hh>

#include <gtkmm/box.h>

#include <vector>
#include <memory>

namespace intmines {
    namespace view {

        class Gameboard {
        public:
            Gameboard(Gtk::Box& parent, std::shared_ptr<ViewCallbacks> callbacks, size_t width, size_t height);

            void mark_mine(size_t x, size_t y);
        protected:
            std::shared_ptr<ViewCallbacks> m_callbacks;
            Gtk::Box* m_container;
            std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
        };
    }
}

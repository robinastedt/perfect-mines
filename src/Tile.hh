#pragma once

#include <ViewCallbacks.hh>

#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

namespace intmines {
    namespace view {
        

        class Tile {
        public:
            Tile(Gtk::Box& parent, std::shared_ptr<ViewCallbacks> callbacks, size_t x, size_t y);
        protected:
            enum TileState {
                HIDDEN,
                MINE,
                EMPTY
            };

            class TileDrawingArea : public Gtk::DrawingArea {
            public:
                TileDrawingArea();
                void set_tile_state(TileState state);
                
            protected:
                TileState m_state;
                bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
                void force_redraw();
            };

            bool on_tile_pressed(GdkEventButton*);
            bool on_tile_released(GdkEventButton*);

            std::shared_ptr<ViewCallbacks> m_callbacks;
            size_t m_x;
            size_t m_y;

            Gtk::EventBox* m_event_box;
            TileDrawingArea* m_drawing_area;

        };
    }
}


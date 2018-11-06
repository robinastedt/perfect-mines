#pragma once

#include <view/ViewCallbacks.hh>

#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

namespace pmines {
    namespace view {
        
        

        class Tile : public Gtk::EventBox {
        public:
            enum DrawState {
                HIDDEN,
                FLAGGED,
                MINE,
                EMPTY
            };

            Tile(std::shared_ptr<ViewCallbacks> callbacks, size_t x, size_t y);
            void set_tile_state(DrawState state);
            void set_tile_state(DrawState state, int adjecent_count);

        protected:
            class TileDrawingArea : public Gtk::DrawingArea {
            public:
                TileDrawingArea();
                bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
                void force_redraw();

                DrawState m_state;
                int m_adjecent_count;
                bool m_pressed_down;
            private:
                void draw_state_hidden(const Cairo::RefPtr<Cairo::Context>& cr);
                void draw_state_flagged(const Cairo::RefPtr<Cairo::Context>& cr);
                void draw_state_mine(const Cairo::RefPtr<Cairo::Context>& cr);
                void draw_state_empty(const Cairo::RefPtr<Cairo::Context>& cr);
            };

            bool on_tile_pressed(GdkEventButton*);
            bool on_tile_released(GdkEventButton*);

            std::shared_ptr<ViewCallbacks> m_callbacks;
            size_t m_x;
            size_t m_y;

            // Memory managed by Gtk
            TileDrawingArea* m_drawing_area;
        };
    }
}


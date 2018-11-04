#include "Tile.hh"

#include <gtkmm/window.h>

namespace intmines {
    namespace view {

        Tile::Tile(Gtk::Box& parent, std::shared_ptr<ViewCallbacks> callbacks, size_t x, size_t y) :
        m_callbacks(callbacks),
        m_x(x),
        m_y(y),
        m_event_box(Gtk::manage(new Gtk::EventBox())),
        m_drawing_area(Gtk::manage(new TileDrawingArea())) {
            m_event_box->add(*m_drawing_area);
            parent.pack_start(*m_event_box);

            m_event_box->signal_button_press_event().connect(sigc::mem_fun(*this, &Tile::on_tile_pressed));
            m_event_box->signal_button_release_event().connect(sigc::mem_fun(*this, &Tile::on_tile_released));
        }

        bool
        Tile::on_tile_pressed(GdkEventButton*) {
            return true;
        }

        bool
        Tile::on_tile_released(GdkEventButton*) {
            m_callbacks->tile_clicked(m_x, m_y);
            m_drawing_area->set_tile_state(TileState::EMPTY);
            return true;
        }

        Tile::TileDrawingArea::TileDrawingArea() :
        m_state(HIDDEN) {
        }

        void Tile::TileDrawingArea::set_tile_state(TileState state) {
            m_state = state;
            force_redraw();
        }

        void Tile::TileDrawingArea::force_redraw() {
            Glib::RefPtr<Gdk::Window> window = get_window();
            if (window) {
                Gtk::Allocation allocation = get_allocation();
                Gdk::Rectangle rect(0, 0, allocation.get_width(), allocation.get_height());
                window->invalidate_rect(rect, false);
            }
        }

        bool Tile::TileDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
            Gtk::Allocation allocation = get_allocation();
            const int width = allocation.get_width();
            const int height = allocation.get_height();
            
            // coordinates for the center of the window
            int xc, yc;
            xc = width / 2;
            yc = height / 2;

            switch (m_state) {
                case HIDDEN: {
                    cr->set_line_width(10.0);
                    cr->set_source_rgb(0.8, 0.0, 0.0);
                    cr->move_to(0, 0);
                    cr->line_to(width, 0);
                    cr->line_to(width, height);
                    cr->line_to(0, height);
                    cr->line_to(0, 0);
                } break;
                case EMPTY: {
                    cr->set_line_width(10.0);
                    cr->set_source_rgb(0.0, 0.8, 0.0);
                    cr->move_to(0, 0);
                    cr->line_to(width, 0);
                    cr->line_to(width, height);
                    cr->line_to(0, height);
                    cr->line_to(0, 0);
                } break;
            }

            cr->stroke();

            return true;
        }
    }
}

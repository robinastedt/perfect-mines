#include "Tile.hh"

#include <DrawingUtils.hh>

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
            m_drawing_area->m_pressed_down = true;
            m_drawing_area->force_redraw();
            return true;
        }

        bool
        Tile::on_tile_released(GdkEventButton*) {
            m_drawing_area->m_pressed_down = false;
            m_drawing_area->force_redraw();
            m_callbacks->tile_clicked(m_x, m_y);
            return true;
        }

        Tile::TileDrawingArea::TileDrawingArea() :
        m_state(HIDDEN),
        m_adjecent_count(0),
        m_pressed_down(false) {

        }

        void Tile::set_tile_state(Tile::DrawState state) {
            m_drawing_area->m_state = state;
            m_drawing_area->force_redraw();
        }

        void Tile::set_tile_state(Tile::DrawState state, int adjecent_count) {
            m_drawing_area->m_state = state;
            m_drawing_area->m_adjecent_count = adjecent_count;
            m_drawing_area->force_redraw();
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
            const Gtk::Allocation allocation = get_allocation();
            const int width = allocation.get_width();
            const int height = allocation.get_height();  
            switch (m_state) {
                case HIDDEN: {
                    draw_state_hidden(cr);
                } break;
                case FLAGGED: {
                    draw_state_flagged(cr);
                } break;
                case MINE: {
                    draw_state_mine(cr);
                } break;
                case EMPTY: {
                    draw_state_empty(cr);
                } break;
            }

            return true;
        }

        void Tile::TileDrawingArea::draw_state_hidden(const Cairo::RefPtr<Cairo::Context>& cr) {
            drawing_utils::BoundingBox bounding_box = drawing_utils::get_outer_bounding_box(*this).scale_center(0.8);
            if (m_pressed_down) {
                cr->set_source_rgb(0.3, 0.3, 0.3);
            }
            else {
                cr->set_source_rgb(0.2, 0.2, 0.2);
            }
            drawing_utils::draw_curved_rectangle(cr, bounding_box, bounding_box.get_height() * 0.1);
        }

        void Tile::TileDrawingArea::draw_state_flagged(const Cairo::RefPtr<Cairo::Context>& cr) {
        }

        void Tile::TileDrawingArea::draw_state_mine(const Cairo::RefPtr<Cairo::Context>& cr) {
        }

        void Tile::TileDrawingArea::draw_state_empty(const Cairo::RefPtr<Cairo::Context>& cr) {
            drawing_utils::BoundingBox bounding_box = drawing_utils::get_outer_bounding_box(*this).scale_center(0.8);
            cr->set_source_rgb(0.8, 0.8, 0.8);
            drawing_utils::draw_curved_rectangle(cr, bounding_box, bounding_box.get_height() * 0.1);
            cr->set_source_rgb(0.0, 0.0, 0.0);
            drawing_utils::draw_number(cr, *this, bounding_box.get_center_x(), bounding_box.get_center_y(), m_adjecent_count);
        }
    }
}

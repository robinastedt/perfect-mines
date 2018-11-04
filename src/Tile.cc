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
                    draw_state_hidden(cr, width, height);
                } break;
                case FLAGGED: {
                    draw_state_flagged(cr, width, height);
                } break;
                case MINE: {
                    draw_state_mine(cr, width, height);
                } break;
                case EMPTY: {
                    draw_state_empty(cr, width, height);
                } break;
            }

            return true;
        }

        void Tile::TileDrawingArea::draw_state_hidden(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
            cr->set_line_width(10.0);
            if (m_pressed_down) {
                cr->set_source_rgb(0.0, 0.0, 0.8);
            }
            else {
                cr->set_source_rgb(0.8, 0.0, 0.0);
            }
            cr->move_to(0, 0);
            cr->line_to(width, 0);
            cr->line_to(width, height);
            cr->line_to(0, height);
            cr->line_to(0, 0);
            cr->stroke();
        }

        void Tile::TileDrawingArea::draw_state_flagged(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
        }

        void Tile::TileDrawingArea::draw_state_mine(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
        }

        void Tile::TileDrawingArea::draw_state_empty(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
            cr->set_line_width(10.0);
            cr->set_source_rgb(0.0, 0.8, 0.0);
            cr->move_to(0, 0);
            cr->line_to(width, 0);
            cr->line_to(width, height);
            cr->line_to(0, height);
            cr->line_to(0, 0);
            draw_number(cr, width, height, m_adjecent_count);
            cr->stroke();
        }

        void Tile::TileDrawingArea::draw_string(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height, std::string string) {
            static Pango::FontDescription font;
            font.set_family("Monospace");
            font.set_weight(Pango::WEIGHT_NORMAL);

            Glib::RefPtr<Pango::Layout> layout = create_pango_layout(string);
            layout->set_font_description(font);

            int text_width;
            int text_height;
            layout->get_pixel_size(text_width, text_height);

            const int text_xpos = (width - text_width) / 2;
            const int text_ypos = (height - text_height) / 2;
            cr->move_to(text_xpos, text_ypos);

            layout->show_in_cairo_context(cr);
        }

        void Tile::TileDrawingArea::draw_number(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height, int number) {
            const std::string string = std::to_string(number);
            draw_string(cr, width, height, string);
        }
    }
}

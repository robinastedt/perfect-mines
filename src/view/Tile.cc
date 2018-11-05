#include "Tile.hh"

#include <view/DrawingUtils.hh>

#include <gtkmm/window.h>

namespace intmines {
    namespace view {
        
        namespace {
            static const double TILE_HIDDEN_RED            = 0.2,
                                TILE_HIDDEN_GREEN          = 0.2,
                                TILE_HIDDEN_BLUE           = 0.2,
                                TILE_PRESSED_RED           = 0.3,
                                TILE_PRESSED_GREEN         = 0.3,
                                TILE_PRESSED_BLUE          = 0.3,
                                TILE_EMPTY_RED             = 0.8,
                                TILE_EMPTY_GREEN           = 0.8,
                                TILE_EMPTY_BLUE            = 0.8,
                                TILE_EMPTY_TEXT_RED        = 0.0,
                                TILE_EMPTY_TEXT_GREEN      = 0.0,
                                TILE_EMPTY_TEXT_BLUE       = 0.0,
                                TILE_FLAGGED_OVERLAY_RED   = 0.8,
                                TILE_FLAGGED_OVERLAY_GREEN = 0.0,
                                TILE_FLAGGED_OVERLAY_BLUE  = 0.0;
        }

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
        Tile::on_tile_pressed(GdkEventButton* event) {
            if (event->button == 1 or event->button == 3) {
                if (m_drawing_area->m_pressed_down) {
                    // Other button press: cancel action
                    m_drawing_area->m_pressed_down = false;
                }
                else {
                    m_drawing_area->m_pressed_down = true;
                }
                m_drawing_area->force_redraw();
            }
            
            return true;
        }

        bool
        Tile::on_tile_released(GdkEventButton* event) {
            if (event->button == 1 or event->button == 3) {
                if (m_drawing_area->m_pressed_down) {
                    m_drawing_area->m_pressed_down = false;
                    if (event->button == 1) {
                        m_callbacks->tile_left_clicked(m_x, m_y);
                    }
                    else {
                        m_callbacks->tile_right_clicked(m_x, m_y);
                    }
                    m_drawing_area->force_redraw();
                }
            }
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
                cr->set_source_rgb(TILE_PRESSED_RED,
                                   TILE_PRESSED_GREEN,
                                   TILE_PRESSED_BLUE);
            }
            else {
                cr->set_source_rgb(TILE_HIDDEN_RED,
                                   TILE_HIDDEN_GREEN,
                                   TILE_HIDDEN_BLUE);
            }
            drawing_utils::draw_curved_rectangle(cr, bounding_box, bounding_box.get_height() * 0.1);
        }

        void Tile::TileDrawingArea::draw_state_flagged(const Cairo::RefPtr<Cairo::Context>& cr) {
            drawing_utils::BoundingBox bounding_box = drawing_utils::get_outer_bounding_box(*this).scale_center(0.8);
            draw_state_hidden(cr);
            cr->set_source_rgb(TILE_FLAGGED_OVERLAY_RED,
                               TILE_FLAGGED_OVERLAY_GREEN,
                               TILE_FLAGGED_OVERLAY_BLUE);
            
            drawing_utils::BoundingBox cross_bounding_box = bounding_box.scale_center(0.8);
            cr->set_line_width(cross_bounding_box.get_height() * 0.1);
            cr->move_to(cross_bounding_box.x1, cross_bounding_box.y1);
            cr->line_to(cross_bounding_box.x2, cross_bounding_box.y2);
            cr->move_to(cross_bounding_box.x1, cross_bounding_box.y2);
            cr->line_to(cross_bounding_box.x2, cross_bounding_box.y1);
            cr->stroke();
        }

        void Tile::TileDrawingArea::draw_state_mine(const Cairo::RefPtr<Cairo::Context>&) {
        }

        void Tile::TileDrawingArea::draw_state_empty(const Cairo::RefPtr<Cairo::Context>& cr) {
            drawing_utils::BoundingBox bounding_box = drawing_utils::get_outer_bounding_box(*this).scale_center(0.8);
            cr->set_source_rgb(TILE_EMPTY_RED,
                               TILE_EMPTY_GREEN,
                               TILE_EMPTY_BLUE);
            drawing_utils::draw_curved_rectangle(cr, bounding_box, bounding_box.get_height() * 0.1);
            cr->set_source_rgb(TILE_EMPTY_TEXT_RED,
                               TILE_EMPTY_TEXT_GREEN,
                               TILE_EMPTY_TEXT_BLUE);
            drawing_utils::draw_number(cr, *this, bounding_box, m_adjecent_count);
        }
    }
}

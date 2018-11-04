#include "DrawingUtils.hh"

#include <pangomm/font.h>
#include <pangomm/layout.h>
#include <pangomm/context.h>

namespace intmines {
    namespace view {
        namespace drawing_utils {
            void draw_string(Gtk::Widget& widget, const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, std::string string) {
                static Pango::FontDescription font;
                font.set_family("Monospace");
                font.set_weight(Pango::WEIGHT_NORMAL);

                Glib::RefPtr<Pango::Layout> layout = widget.create_pango_layout(string);
                layout->set_font_description(font);

                int text_width;
                int text_height;
                layout->get_pixel_size(text_width, text_height);

                const int text_xpos = x - (text_width / 2);
                const int text_ypos = y - (text_height / 2);
                cr->move_to(text_xpos, text_ypos);

                layout->show_in_cairo_context(cr);
            }

            void draw_number(Gtk::Widget& widget, const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, int number) {
                const std::string string = std::to_string(number);
                draw_string(widget, cr, x, y, string);
            }
        }
        
    }
}
#pragma once

#include <gtkmm/widget.h>
#include <cairomm/context.h>

namespace intmines {
    namespace view {
        namespace drawing_utils {
            void draw_string(Gtk::Widget& widget, const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, std::string string);
            void draw_number(Gtk::Widget& widget, const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, int number);
        }
    }
}
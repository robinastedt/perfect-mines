#pragma once

#include <gtkmm/widget.h>

namespace pmines {
    namespace view {
        namespace drawing_utils {
            struct BoundingBox {
                double x1, y1, x2, y2;

                double get_center_x();
                double get_center_y();
                double get_width();
                double get_height();

                BoundingBox scale_center(double ratio);
            };

            BoundingBox get_outer_bounding_box(Gtk::Widget& widget);
            void draw_string(const Cairo::RefPtr<Cairo::Context>& cr, Gtk::Widget& widget, BoundingBox bounding_box, std::string string);
            void draw_number(const Cairo::RefPtr<Cairo::Context>& cr, Gtk::Widget& widget, BoundingBox bounding_box, int number);
            void draw_curved_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, BoundingBox bounding_box, double radius);
        }
    }
}
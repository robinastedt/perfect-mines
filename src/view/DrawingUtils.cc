#include "DrawingUtils.hh"

namespace pmines {
    namespace view {
        namespace drawing_utils {
            double BoundingBox::get_center_x() {
                return x1 + (x2 - x1) / 2.0;
            }

            double BoundingBox::get_center_y() {
                return y1 + (y2 - y1) / 2.0;
            }

            double BoundingBox::get_width() {
                return x2 - x1;
            }

            double BoundingBox::get_height() {
                return y2 - y1;
            }

            BoundingBox BoundingBox::scale_center(double ratio) {
                BoundingBox bounding_box;
                bounding_box.x1 = get_center_x() - (get_width() * 0.5 * ratio);
                bounding_box.x2 = get_center_x() + (get_width() * 0.5 * ratio);
                bounding_box.y1 = get_center_y() - (get_height() * 0.5 * ratio);
                bounding_box.y2 = get_center_y() + (get_height() * 0.5 * ratio);
                return bounding_box;
            }

            BoundingBox get_outer_bounding_box(Gtk::Widget& widget) {
                const Gtk::Allocation allocation = widget.get_allocation();
                BoundingBox bounding_box;
                bounding_box.x1 = 0.0;
                bounding_box.y1 = 0.0;
                bounding_box.x2 = allocation.get_width();
                bounding_box.y2 = allocation.get_height();
                return bounding_box;
            }

            void draw_string(const Cairo::RefPtr<Cairo::Context>& cr, Gtk::Widget& widget, BoundingBox bounding_box, std::string string) {
                Pango::FontDescription font;
                font.set_family("Monospace");
                font.set_weight(Pango::WEIGHT_NORMAL);
                font.set_absolute_size(bounding_box.get_height() * PANGO_SCALE);
                

                Glib::RefPtr<Pango::Layout> layout = widget.create_pango_layout(string);
                layout->set_font_description(font);

                int text_width;
                int text_height;
                layout->get_pixel_size(text_width, text_height);

                const double text_xpos = bounding_box.get_center_x() - (static_cast<double>(text_width) / 2.0);
                const double text_ypos = bounding_box.get_center_y() - (static_cast<double>(text_height) / 2.0);
                cr->move_to(text_xpos, text_ypos);

                layout->show_in_cairo_context(cr);
            }

            void draw_number(const Cairo::RefPtr<Cairo::Context>& cr, Gtk::Widget& widget, BoundingBox bounding_box, int number) {
                const std::string string = std::to_string(number);
                draw_string(cr, widget, bounding_box, string);
            }

            void draw_curved_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, BoundingBox bounding_box, double radius) {
                const double x1 = bounding_box.x1 + radius,
                             y1 = bounding_box.y1 + radius,
                             x2 = bounding_box.x2 - radius,
                             y2 = bounding_box.y2 - radius;
                
                cr->begin_new_sub_path();
                cr->arc(x2, y1, radius, -M_PI_2, 0);     // Top right
                cr->arc(x2, y2, radius, 0, M_PI_2);      // Bottom right
                cr->arc(x1, y2, radius, M_PI_2, M_PI);   // Bottom left
                cr->arc(x1, y1, radius, M_PI, 3*M_PI_2); // Top left
                cr->close_path();

                cr->fill();
            }

            void draw_circle(const Cairo::RefPtr<Cairo::Context>& cr, BoundingBox bounding_box, double radius) {
                const double x = bounding_box.get_center_x(),
                             y = bounding_box.get_center_y();
                
                cr->begin_new_sub_path();
                cr->arc(x, y, radius, -M_PI_2, 0);     // Top right
                cr->arc(x, y, radius, 0, M_PI_2);      // Bottom right
                cr->arc(x, y, radius, M_PI_2, M_PI);   // Bottom left
                cr->arc(x, y, radius, M_PI, 3*M_PI_2); // Top left
                cr->close_path();

                cr->fill();
            }
        }
        
    }
}
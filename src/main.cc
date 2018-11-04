#include <Controller.hh>

#include <gtkmm/application.h>
#include <View.hh>
#include <Controller.hh>

int main(int argc, char** argv) {
    
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    intmines::controller::Controller controller(window);
    window.set_title("Intelligent Mines");
    window.set_border_width(0);
    window.show_all_children();
    return app->run(window);
}


#include "View.hh"

#include <gtkmm/application.h>

namespace pmines {
    namespace view {
        View::View(std::shared_ptr<ViewCallbacks> callbacks) :
        m_callbacks(callbacks) {
        }

        View::~View() {

        }

        int View::run(int argc, char** argv) {
            Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
            Gtk::Window window;
            m_window = &window;
            window.set_title("Perfect Mines");
            window.set_border_width(0);
            m_container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
            window.add(*m_container);
            reset_gameboard(30, 16);
            window.show_all_children();
            return app->run(window);
        }

        void View::reset_gameboard(int width, int height) {
            m_gameboard = Gtk::manage(new Gameboard(m_callbacks, width, height));
            m_container->pack_start(*m_gameboard);
        }

        void View::set_tile_hidden(int x, int y) {
            m_gameboard->set_tile_state(x, y, Tile::DrawState::HIDDEN);
        }
        void View::set_tile_flagged(int x, int y) {
            m_gameboard->set_tile_state(x, y, Tile::DrawState::FLAGGED);
        }
        void View::set_tile_mine(int x, int y) {
            m_gameboard->set_tile_state(x, y, Tile::DrawState::MINE);
        }
        void View::set_tile_empty(int x, int y, int adjecent_count) {
            m_gameboard->set_tile_state(x, y, Tile::DrawState::EMPTY, adjecent_count);
        }
    }
}
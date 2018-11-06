#include <controller/Controller.hh>

#include <view/View.hh>

#include <gtkmm/application.h>


int main(int argc, char** argv) {
    pmines::controller::Controller controller;
    return controller.run(argc, argv);
}


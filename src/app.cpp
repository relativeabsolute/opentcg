#include "app.hpp"
#include "gui/main_window.hpp"

#include <iostream>
#include <exception>

using namespace open_tcg;
using namespace open_tcg::gui;

App::App()
	: Gtk::Application("org.open_tcg.app") {

}

Glib::RefPtr<App> App::create() {
	return Glib::RefPtr<App>(new App());
}

MainWindow *App::create_window() {
	auto window = MainWindow::create();

	add_window(*window);

	window->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(
		*this, &App::on_hide_window), window));

	return window;
}

void App::on_activate() {
	try {
	auto window = create_window();

	window->present();
	}
	catch (const std::exception &ex) {
		std::cerr << "App::on_activate(): " << ex.what() << std::endl;
	}
}

void App::on_hide_window(Gtk::Window *window) {
	delete window;
}

/*
MIT License

Copyright (c) 2017 Johan Burke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

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

#include "gui/main_window.hpp"
#include "gui/deck_editor.hpp"
#include "game/tcg.hpp"

using namespace open_tcg::gui;
using namespace open_tcg::game;
using namespace open_tcg::util;

MainWindow::MainWindow(BaseObjectType *cobject,
	const Glib::RefPtr<Gtk::Builder> &refBuilder, const TCG &tcg) 
	: Gtk::ApplicationWindow(cobject),
	builder(refBuilder), playButton(nullptr),
	deckEditButton(nullptr), viewProfileButton(nullptr),
	deckEditor(nullptr), currTCG(tcg) {

	imageManager = ImageManager::create();

	initControls();
	connectEvents();
}

MainWindow::~MainWindow() {
	if (deckEditor) {
		delete deckEditor;
		deckEditor = nullptr;
	}
}

void MainWindow::initControls() {
	builder->get_widget("play_button", playButton);
	if (!playButton) {
		throw std::runtime_error("Couldn't add play button.");
	}

	builder->get_widget("deck_edit_button", deckEditButton);
	if (!deckEditButton) {
		throw std::runtime_error("Couldn't add deck edit button.");
	}

	builder->get_widget("view_profile_button", viewProfileButton);
	if (!viewProfileButton) {
		throw std::runtime_error("Couldn't add view profile button.");
	}

	deckEditor = DeckEditor::create(&currTCG, imageManager);
}

void MainWindow::connectEvents() {
	playButton->signal_clicked().connect(sigc::mem_fun(*this,
		&MainWindow::onPlayButtonClicked));

	deckEditButton->signal_clicked().connect(sigc::mem_fun(*this,
		&MainWindow::onDeckEditButtonClicked));

	viewProfileButton->signal_clicked().connect(sigc::mem_fun(*this,
		&MainWindow::onViewProfileButtonClicked));
}

MainWindow *MainWindow::create() {
	// TODO: figure out resource based approach
	auto refBuilder = Gtk::Builder::create_from_file("main_window.glade");

	MainWindow *window = nullptr;

	// TODO: determine last game set
	TCG ex(TCG::readFromFile("example.xml"));
	std::cout << ex.getName() << std::endl;

	refBuilder->get_widget_derived("window", window, ex);

	if (!window) {
		throw std::runtime_error("No window in main_window.glade");
	}

	return window;
}

// TODO: add actual event handlers for these
void MainWindow::onPlayButtonClicked() {
	std::cout << "Play button clicked" << std::endl;
}

void MainWindow::onDeckEditButtonClicked() {
	deckEditor->show_all();
}

void MainWindow::onViewProfileButtonClicked() {
	std::cout << "View profile button clicked" << std::endl;
}

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

#include "gui/deck_editor.hpp"

#include <stdexcept>

using namespace open_tcg::gui;

DeckEditor::DeckEditor(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder)
	: Gtk::Window(cobject), builder(refBuilder) {
	
	initControls();
	connectEvents();
}

DeckEditor *DeckEditor::create() {
	auto refBuilder = Gtk::Builder::create_from_file("deck_editor.glade");

	DeckEditor *editor = nullptr;

	refBuilder->get_widget_derived("window", editor);

	if (!editor) {
		throw std::runtime_error("No window in deck_editor.glade");
	}

	return editor;
}

void DeckEditor::initControls() {

}

void DeckEditor::connectEvents() {

}

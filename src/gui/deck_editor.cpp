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
#include "gui/card_search.hpp"

using namespace open_tcg::gui;
using namespace open_tcg::game;

DeckEditor::DeckEditor(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder, TCG *currTCG)
	: Gtk::Window(cobject), builder(refBuilder), editorBox(nullptr), currTCG(currTCG) {
		initControls();
		connectEvents();
	}

DeckEditor *DeckEditor::create(TCG *currTCG) {
	auto refBuilder = Gtk::Builder::create_from_file("deck_editor.glade");

	DeckEditor *editor = nullptr;

	refBuilder->get_widget_derived("window", editor, currTCG);

	if (!editor) {
		throw std::runtime_error("No window in deck_editor.glade");
	}

	return editor;
}

void DeckEditor::initControls() {
	builder->get_widget("editor_box", editorBox);
	if (!editorBox) {
		throw std::runtime_error("No editor_box in deck_editor.glade");
	}

	deckView = new Gtk::Frame("Deck");
	initDeckViews();

	cardSearch = CardSearch::create();
	editorBox->pack_end(*cardSearch, false, false);
}

void DeckEditor::initDeckViews() {
	if (currTCG == nullptr) {
		std::cout << "Current TCG is null." << std::endl;
		// TODO: throw an exception
	} else {
		Gtk::Box *viewsBox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);

		for (DeckSectionInfo info : currTCG->getSections()) {
			Gtk::Frame *sectionFrame = new Gtk::Frame(info.getName());

			CardView *sectionView = CardView::create(info.getRowCount(), info.getColCount());
			sectionFrame->add(*sectionView);

			viewsBox->pack_start(*sectionFrame, false, false);
			cardViews.push_back(sectionView);
		}

		deckView->add(*viewsBox);
	}
}

void DeckEditor::connectEvents() {

}

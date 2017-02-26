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

#include "gui/card_view.hpp"

using namespace open_tcg::gui;
using namespace open_tcg::game;
using namespace open_tcg::util;

CardView::CardView(ImageManager *imgMgr, uint rowCount, uint colCount)
	: Gtk::Frame(), rows(rowCount), cols(colCount), imageManager(imgMgr) {
	initControls();
	connectEvents();
}

CardView *CardView::create(ImageManager *imgMgr) {
	uint defaultRows = 5;
	uint defaultCols = 4;
	return create(imgMgr, defaultRows, defaultCols);
}

CardView *CardView::create(ImageManager *imgMgr, uint rowCount, uint colCount) {
	return new CardView(imgMgr, rowCount, colCount);
}

void CardView::initControls() {
	boxes.reserve(rows * cols);
	images.reserve(rows * cols);

	for (uint i = 0; i < rows; i++) {
		for (uint j = 0; j < cols; j++) {
			uint index = i * cols + j;

			Gtk::Image *image = new Gtk::Image();
			images.push_back(image);

			Gtk::EventBox *box = new Gtk::EventBox();
			box->set_above_child(false);
			box->add(*images[index]);
			boxes.push_back(box);

			grid.attach(*box, (int)j, (int)i, 1, 1);
		}
	}

	imageManager->loadImage("proxy");

	std::vector<CardInfo> emptyVec;
	setCards(emptyVec);

	add(grid);
}

void CardView::connectEvents() {
	for (uint i = 0; i < rows; i++) {
		for (uint j = 0; j < cols; j++) {
			uint index = i * cols + j;
			boxes[i]->signal_motion_notify_event().connect(
					sigc::bind<uint>(sigc::mem_fun(*this, &CardView::onCardHover), index));
		}
	}
}

// TODO: set up drag and drop

bool CardView::onCardHover(GdkEventMotion *motionEvent, uint index) {
	// TODO: set up card display to change to the card being hovered over

	return false;	
}

void CardView::setCards(const std::vector<CardInfo> &cards) {
	size_t numImages = rows * cols;
	for (size_t i = 0; i < numImages; i++) {
		if (i < cards.size()) {
		} else {
			images[i]->set(imageManager->getImage("proxy").small);
		}
	}
}

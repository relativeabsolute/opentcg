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

#include "gui/card_display.hpp"

using namespace open_tcg::gui;
using namespace open_tcg::util;

CardDisplay::CardDisplay(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder,
	ImageManager *imgMgr)
	: Gtk::Frame(cobject), builder(refBuilder),
	cardName(nullptr), cardText(nullptr), cardImage(nullptr) {
	initControls();
	connectEvents();
}

CardDisplay *CardDisplay::create(ImageManager *imgMgr) {
	auto refBuilder = Gtk::Builder::create_from_file("card_display.glade");

	CardDisplay *display = nullptr;

	refBuilder->get_widget_derived("card_display", display, imgMgr);

	if (!display) {
		throw std::runtime_error("No card_display in card_display.glade");
	}

	return display;
}

void CardDisplay::initControls() {
	builder->get_widget("card_name_label", cardName);
	if (!cardName) {
		throw std::runtime_error("No card_name_label in card_display.glade");
	}

	builder->get_widget("card_text_view", cardText);
	if (!cardText) {
		throw std::runtime_error("No card_text_view in card_display.glade");
	}

	builder->get_widget("card_image", cardImage);
	if (!cardImage) {
		throw std::runtime_error("No card_image in card_display.glade");
	}
}

void CardDisplay::connectEvents() {

}

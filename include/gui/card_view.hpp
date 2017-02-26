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

#ifndef CARD_VIEW_HPP
#define CARD_VIEW_HPP

#include <gtkmm.h>

#include <vector>

#include "opentcg.hpp"
#include "util/image_manager.hpp"
#include "game/card.hpp"

namespace open_tcg {
	namespace gui {
		class CardView : public Gtk::Frame {
			public:
				CardView(open_tcg::util::ImageManager *imgMgr,
					uint rowCount, uint colCount);

				static CardView *create(open_tcg::util::ImageManager *imgMgr);
				static CardView *create(open_tcg::util::ImageManager *imgMgr,
					uint rowCount, uint colCount);

				void setCards(const std::vector<open_tcg::game::CardInfo> &cards);
			protected:

				void initControls();
				void connectEvents();

				bool onCardHover(GdkEventMotion *motionEvent, uint index);
				
				Gtk::Grid grid;
				std::vector<Gtk::EventBox *> boxes;
				std::vector<Gtk::Image *> images;

				uint rows, cols;

				open_tcg::util::ImageManager *imageManager;
		};
	}
}

#endif

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

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "opentcg.hpp"

namespace open_tcg {
	namespace gui {
		class DeckEditor;

		class MainWindow : public Gtk::ApplicationWindow {
			public:
				static MainWindow *create();
				MainWindow(BaseObjectType *cobject,
					const Glib::RefPtr<Gtk::Builder> &refBuilder);

				virtual ~MainWindow();

			protected:
				// setup functions
				void initControls();
				void connectEvents();

				// event handlers
				void onPlayButtonClicked();
				void onDeckEditButtonClicked();
				void onViewProfileButtonClicked();

				Gtk::Button *playButton;
				Gtk::Button *deckEditButton;
				Gtk::Button *viewProfileButton;
				Glib::RefPtr<Gtk::Builder> builder;

				DeckEditor *deckEditor;
		};
	}
}

#endif

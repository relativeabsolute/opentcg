#ifndef OPENTCG_APP_HPP
#define OPENTCG_APP_HPP

#include <gtkmm.h>

namespace open_tcg {
	namespace gui {
		class MainWindow;
	}

	class App : public Gtk::Application {
		public:
			static Glib::RefPtr<App> create();

		protected:
			App();

			gui::MainWindow *create_window();

			void on_activate() override;
			void on_hide_window(Gtk::Window *window);
	};
}

#endif

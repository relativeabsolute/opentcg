#include "gui/card_search.hpp"

using namespace open_tcg::gui;

CardSearch::CardSearch(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder)
	: Gtk::Frame(cobject), builder(refBuilder),
	cardNameSearch(nullptr), cardTextSearch(nullptr), updateButton(nullptr),
	clearButton(nullptr) {
		initControls();
		connectEvents();
}

CardSearch *CardSearch::create() {
	auto refBuilder = Gtk::Builder::create_from_file("card_search.glade");

	CardSearch *search = nullptr;

	refBuilder->get_widget_derived("card_search", search);

	if (!search) {
		throw std::runtime_error("No card_search in card_search.glade");
	}

	return search;
}

void CardSearch::initControls() {
	builder->get_widget("card_name_search", cardNameSearch);
	if (!cardNameSearch) {
		throw std::runtime_error("No card_name_search in card_search.glade");
	}
	
	builder->get_widget("card_text_search", cardTextSearch);
	if (!cardTextSearch) {
		throw std::runtime_error("No card_text_search in card_search.glade");
	}

	builder->get_widget("update_button", updateButton);
	if (!updateButton) {
		throw std::runtime_error("No update_button in card_search.glade");
	}

	builder->get_widget("clear_button", clearButton);
	if (!clearButton) {
		throw std::runtime_error("No clear_button in card_search.glade");
	}
}

void CardSearch::connectEvents() {
	updateButton->signal_clicked().connect(sigc::mem_fun(*this,
				&CardSearch::onUpdateClicked));

	clearButton->signal_clicked().connect(sigc::mem_fun(*this,
				&CardSearch::onClearClicked));
}

void CardSearch::onUpdateClicked() {
	// TODO: fill this in
}

void CardSearch::onClearClicked() {

}

#include "gui/card_search.hpp"
#include "gui/card_view.hpp"

#include <sqlite3.h>

using namespace open_tcg::gui;
using namespace open_tcg::util;

CardSearch::CardSearch(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder,
	ImageManager *imgMgr, sqlite3 *db)
	: Gtk::Frame(cobject), builder(refBuilder),
	cardNameSearch(nullptr), cardTextSearch(nullptr), updateButton(nullptr),
	clearButton(nullptr), imageManager(imgMgr), db(db) {
		initControls();
		connectEvents();
}

CardSearch *CardSearch::create(ImageManager *imgMgr, sqlite3 *db) {
	auto refBuilder = Gtk::Builder::create_from_file("card_search.glade");

	CardSearch *search = nullptr;

	refBuilder->get_widget_derived("card_search", search, imgMgr, db);

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

	builder->get_widget("search_items_box", searchItemsBox);
	if (!searchItemsBox) {
		throw std::runtime_error("No search_items_box in card_search.glade");
	}

	cardView = CardView::create(imageManager);
	searchItemsBox->pack_start(*cardView, false, false);
}

void CardSearch::connectEvents() {
	updateButton->signal_clicked().connect(sigc::mem_fun(*this,
				&CardSearch::onUpdateClicked));

	clearButton->signal_clicked().connect(sigc::mem_fun(*this,
				&CardSearch::onClearClicked));
}

void CardSearch::onUpdateClicked() {
	std::string query = "SELECT setcode from cards\nWHERE";
	std::string clauses = "";
	std::string name = cardNameSearch->get_text();
	std::vector<const char*> paramBindings;

	// TODO: change this as more fields are added
	size_t numParams = 2;
	paramBindings.reserve(numParams);
	if (!name.empty()) {
		clauses += " name LIKE ?";
		name = "%" + name + "%";
		const char *name_ptr = name.c_str();
		paramBindings.push_back(name_ptr);
	}
	std::string text = cardTextSearch->get_text();
	if (!text.empty()) {
		if (!clauses.empty()) {
			clauses += " AND ";
		}
		clauses += " text LIKE ?";
		text = "%" + text + "%";
		const char *text_ptr = text.c_str();
		paramBindings.push_back(text_ptr);
	}
	if (!clauses.empty()) {
			query += clauses;
		const char *query_stmt = query.c_str();
		sqlite3_stmt *res;
		int rc = sqlite3_prepare_v2(db, query_stmt, -1, &res, nullptr);
		if (rc == SQLITE_OK) {
			std::cout << "Query = " << query_stmt << std::endl;
			for (int i = 0; i < paramBindings.size(); i++) {
				rc = sqlite3_bind_text(res, i + 1, paramBindings[i], -1, SQLITE_STATIC);
				if (rc != SQLITE_OK) {
					std::cout << "There was an error in binding parameters." << std::endl;
					std::cout << "Error message: " <<
						sqlite3_errstr(sqlite3_extended_errcode(db)) << std::endl;
					return;
				}
			}
			std::cout << "Query after bindings: " << sqlite3_expanded_sql(res) << std::endl;
			int step = sqlite3_step(res);
			while (step == SQLITE_ROW) {
				// TODO: for now just print the resulting set codes
				std::cout << sqlite3_column_text(res, 0) << std::endl;
				step = sqlite3_step(res);
			}
		} else {
			std::cout << "There was an error." << std::endl;
			std::cout << "Error message: " << 
				sqlite3_errstr(sqlite3_extended_errcode(db)) << std::endl;
		}
	}
}

void CardSearch::onClearClicked() {

}

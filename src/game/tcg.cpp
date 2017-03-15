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

#include "game/tcg.hpp"
#include "game/card.hpp"
#include "game/deck.hpp"
#include "util/xml.hpp"

#include <libxml++/libxml++.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

using namespace open_tcg::game;
using namespace open_tcg::util;

namespace fs = boost::filesystem;

std::string TCG::getName() const {
	return name;
}

uint TCG::getCardLimit() const {
	return cardLimit;
}

// TODO: write C++ wrapper for SQLite?
void TCG::readInfo() {
	const char *query_stmt = "SELECT * FROM info";
	sqlite3_stmt *res;
	int rc = sqlite3_prepare_v2(db, query_stmt, -1, &res, nullptr);
	if (rc == SQLITE_OK) {
		int step = sqlite3_step(res);
		if (step == SQLITE_ROW) {
			name = reinterpret_cast<const char*>(sqlite3_column_text(res, 0));
			typeDir = reinterpret_cast<const char*>(sqlite3_column_text(res, 1));
			setNamesFile = reinterpret_cast<const char*>(sqlite3_column_text(res, 2));
			cardLimit = (uint)sqlite3_column_int(res, 3);
		}
	}
}

TCG TCG::readFromDB(sqlite3 *db) {
	TCG result;
	result.db = db;

	result.readInfo();

	return result;
}

DeckSections TCG::getSections() const {
	DeckSections result;
	const char *query_stmt = "SELECT * FROM sections";
	sqlite3_stmt *res;
	int rc = sqlite3_prepare_v2(db, query_stmt, -1, &res, nullptr);
	if (rc == SQLITE_OK) {
		int step = sqlite3_step(res);
		while (step == SQLITE_ROW) {
			DeckSectionInfo row;
			row.setName(reinterpret_cast<const char*>(sqlite3_column_text(res, 0)));
			row.setGroup((uint)sqlite3_column_int(res, 1));
			row.setMinSize((uint)sqlite3_column_int(res, 2));
			row.setMaxSize((uint)sqlite3_column_int(res, 3));
			row.setRowCount((uint)sqlite3_column_int(res, 4));
			row.setColCount((uint)sqlite3_column_int(res, 5));
			result.push_back(row);
			step = sqlite3_step(res);
		}
	}
	return result;
}

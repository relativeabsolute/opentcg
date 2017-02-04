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

TCG TCG::readFromFile(const std::string &fileName) {
	TCG result;

	const std::string rootStr = "TCG";
	const std::string nameStr = "Name";
	const std::string cardLimitStr = "CardLimit";
	const std::string setsStr = "SetFile";

	xmlpp::DomParser parser;
	parser.parse_file(fileName);
	if (parser) {
		const auto root = parser.get_document()->get_root_node();
		if (root->get_name().compare(rootStr) == 0) {
			const auto name = root->get_first_child(nameStr);
			result.name = getTextFromElement(name);
			const auto cardLimit = root->get_first_child(cardLimitStr);
			result.cardLimit = getUintFromElement(cardLimit);
			const auto setsName = root->get_first_child(setsStr);
			std::string setsFile = getTextFromElement(setsName);
			result.readSetFile(setsFile);
		}
	}

	return result;
}

void TCG::readSetFile(const std::string &setFile) {
	std::ifstream fileIn(setFile);
	std::string line;
	while (std::getline(fileIn, line)) {
		readSet(line);
	}
}

void TCG::readSet(const std::string &setName) {
	fs::path setDir(setName);
	if (fs::is_directory(setDir)) {
		for (fs::directory_entry &entry : fs::directory_iterator(setDir)) {
			CardInfo info = CardInfo::readFromFile(entry.path().string());
			std::cout << "Card name: " << info.getName() << std::endl;
			cards.insert(std::make_pair(info.getName(), info));
		}
	}
}

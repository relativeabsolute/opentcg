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

using namespace open_tcg::game;
using namespace open_tcg::util;

std::string TCG::getName() const {
	return name;
}

uint TCG::getCardLimit() const {
	return cardLimit;
}

TCG *TCG::readFromFile(const std::string &fileName) {
	TCG *result = new TCG();

	const std::string rootStr = "TCG";
	const std::string nameStr = "Name";

	xmlpp::DomParser parser;
	parser.parse_file(fileName);
	if (parser) {
		const auto root = parser.get_document()->get_root_node();
		if (root->get_name().compare(rootStr) == 0) {
			const auto name = root->get_first_child(nameStr);
			result->name = getTextFromElement(name);
			/*
			const auto nameContent = name->get_first_child();
			const auto nameText = dynamic_cast<const xmlpp::TextNode*>(nameContent);
			if (nameText) {
				std::string nameValue = nameText->get_content();
				boost::trim(nameValue);
				result->name = nameValue;
			}
			*/
			
		}
	}

	return result;
}

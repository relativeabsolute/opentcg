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

#include "game/card.hpp"
#include "util/xml.hpp"

#include <libxml++/libxml++.h>

using namespace open_tcg::game;
using namespace open_tcg::util;

std::string CardType::getName() const {
	return name;
}

CardInfo CardInfo::readFromFile(const std::string &fileName) {
	CardInfo result;

	const std::string rootStr = "Card";
	const std::string nameStr = "Name";
	const std::string setCodeStr = "SetCode";
	const std::string setNameStr = "SetName";
	const std::string textStr = "CardText";

	xmlpp::DomParser parser;
	parser.parse_file(fileName);
	if (parser) {
		const auto root = parser.get_document()->get_root_node();
		if (root->get_name().compare(rootStr) == 0) {
			const auto name = root->get_first_child(nameStr);
			result.name = getTextFromElement(name);
			const auto setCode = root->get_first_child(setCodeStr);
			result.setCode = getTextFromElement(setCode);
			const auto setName = root->get_first_child(setNameStr);
			result.setName = getTextFromElement(setName);
			const auto textEl = root->get_first_child(textStr);
			result.text = getTextFromElement(textEl);
		}
	}

	return result;
}

std::string CardInfo::getName() const {
	return name;
}

std::string CardInfo::getSetName() const {
	return setName;
}

std::string CardInfo::getSetCode() const {
	return setCode;
}

std::string CardInfo::getText() const {
	return text;
}

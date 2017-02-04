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

#ifndef TCG_HPP
#define TCG_HPP

#include "opentcg.hpp"
#include <string>
#include <vector>
#include <map>

#include "game/deck.hpp"
#include "game/card.hpp"

namespace open_tcg {
	namespace game {
		typedef std::vector<DeckSectionInfo> DeckSections;
		typedef std::map<std::string, CardInfo> CardMap;
		typedef std::map<std::string, CardType> CardTypesMap;

		class TCG {
			public:
				std::string getName() const;
				uint getCardLimit() const;

				static TCG readFromFile(const std::string &fileName);
			private:
				void readSetFile(const std::string &setFile);
				void readSet(const std::string &setName);

				std::string name;

				// represents the amount of copies of a card with
				// the same name that can be played in one deck
				uint cardLimit;

				DeckSections sections;

				CardMap cards;

				CardTypesMap cardTypes;
		};
	}
}

#endif

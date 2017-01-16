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

#include "opentcg.hpp"

#include <string>
#include <map>

namespace open_tcg {
	namespace util {
		const uint DEFAULT_SMALL_SCALE = 100;
		const uint DEFAULT_LARGE_SCALE = 250;

		struct ImageScale {
			Glib::RefPtr<Gdk::Pixbuf> small;
			Glib::RefPtr<Gdk::Pixbuf> large;
		};

		class ImageManager {
			public:
				ImageManager();

				void setSmallScale(uint newScale);
				uint getSmallScale() const;

				void setLargeScale(uint newScale);
				uint getLargeScale() const;

				ImageScale getImage(const std::string &name) const;
				void loadImage(const std::string &setCode);
			private:
				std::map<std::string, ImageScale> images;
				uint smallScale;
				uint largeScale;
		};
	}
}

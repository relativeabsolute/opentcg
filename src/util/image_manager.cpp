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

#include "util/image_manager.hpp"

using namespace open_tcg::util;

ImageManager::ImageManager()
	: smallScale(DEFAULT_SMALL_SCALE),
	largeScale(DEFAULT_LARGE_SCALE) {

}

void ImageManager::setSmallScale(uint newScale) {
	smallScale = newScale;
}

uint ImageManager::getSmallScale() const {
	return smallScale;
}

void ImageManager::setLargeScale(uint newScale) {
	largeScale = newScale;
}

uint ImageManager::getLargeScale() const {
	return largeScale;
}

ImageScale ImageManager::getImage(const std::string &name) const {
	ImageScale result;

	auto search = images.find(name);
	if (search != images.end()) {
		result = search->second;
	}

	return result;
}

void ImageManager::loadImage(const std::string &setCode) {
	auto search = images.find(setCode);
	if (search == images.end()) {
		std::string fullName = "images/" + setCode + ".png";
		auto small = Gdk::Pixbuf::create_from_file(fullName, smallScale, smallScale);
		if (!small) {
			throw std::runtime_error("Could not load image from file");
		}
		auto large = Gdk::Pixbuf::create_from_file(fullName, largeScale, largeScale);
		if (!large) {
			throw std::runtime_error("Could not load image from file");
		}
		// TODO: do scaling
		images.insert(std::make_pair(setCode, ImageScale{
					small, large}));
	}
}

ImageManager *ImageManager::create() {
	return new ImageManager();
}

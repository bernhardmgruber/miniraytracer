#include "Image.h"

#include "imagewrite/imagewrite.h"

namespace rt {
	Image::Image(unsigned int width, unsigned int height)
		: width(width), height(height), pixels(width * height) {}

	auto Image::operator()(unsigned int x, unsigned int y) -> Pixel& {
		return pixels[y * width + x];
	}

	auto Image::operator()(unsigned int x, unsigned int y) const -> const Pixel& {
		return pixels[y * width + x];
	}

	void Image::write(const boost::filesystem::path& filename) const {
		if (!writeImage(filename.string().c_str(), width, height, reinterpret_cast<const unsigned char*>(pixels.data())))
			throw std::runtime_error("Failed to write image " + filename.string());
	}
}

#include "Image.h"

#include <fstream>

namespace rt {
	Image::Image(unsigned int width, unsigned int height)
		: width(width), height(height), pixels(width * height) {}

	auto Image::operator()(unsigned int x, unsigned int y) -> Pixel& {
		return pixels[y * width + x];
	}

	auto Image::operator()(unsigned int x, unsigned int y) const -> const Pixel& {
		return pixels[y * width + x];
	}

	void Image::write(const std::filesystem::path& filename) const {
		std::ofstream f(filename, std::ios::binary);
		if (!f)
			throw std::ios::failure("Failed to open file " + filename.string() + " for writing");
		f << "P6\n";
		f << width << " " << height << '\n';
		f << "255\n";
		f.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(decltype(pixels)::value_type));
	}
}

#pragma once

#include <filesystem>
#include <vector>

#include "Vector.hpp"

namespace rt {
	class Image {
	public:
		using Pixel = math::Vector<unsigned char>;

		Image(unsigned int width, unsigned int height);

		auto operator()(unsigned int x, unsigned int y) -> Pixel&;
		auto operator()(unsigned int x, unsigned int y) const -> const Pixel&;

		void write(const std::filesystem::path& filename) const;

	private:
		unsigned int width;
		unsigned int height;
		std::vector<Pixel> pixels;
	};
}

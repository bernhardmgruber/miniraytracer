#include <fstream>
#include <string>
#include <cstdint>
#include <algorithm>

#include <filesystem>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace {
	// cf. https://en.wikipedia.org/wiki/Truevision_TGA
	// we need to pack the following structs to disallow the C++ compiler to add extra space
	// between the struct members or at the end of the struct (padding, alignment)
#pragma pack(1)
	struct TGAHeader {
		uint8_t id = 0;
		uint8_t colorMapType = 0;
		uint8_t imageType = 2;

		uint16_t colorMapFirstEntry = 0;
		uint16_t colorMapEntryCount = 0;
		uint8_t colorMapEntrySize = 0;

		uint16_t xorig = 0;
		uint16_t yorig = 0;
		uint16_t width = 0;
		uint16_t height = 0;
		uint8_t pixelDepth = 3 * 8;
		uint8_t imageDesc = 0x08;
	};
	static_assert(sizeof(TGAHeader) == 18, "");

	struct TGAFooter {
		uint32_t extensionOffset = 0;
		uint32_t developerAreaOffset = 0;
		uint8_t signature[18] = "TRUEVISION-XFILE.";
	};
	static_assert(sizeof(TGAFooter) == 26, "");
#pragma pack(pop)

	void writeImageTGA(const char* filename, unsigned int width, unsigned int height, const unsigned char* pixels) {
		// flip image vertically and swap R and B channels
		std::vector<unsigned char> data(pixels, pixels + width * height * 3);

		for (unsigned int y = 0; y < height / 2; ++y) {
			auto* row1 = &data[y * width * 3];
			auto* row2 = &data[(height - y - 1) * width * 3];
			std::swap_ranges(row1, row1 + width * 3, row2);
		}

		for (unsigned int y = 0; y < height; ++y) {
			for (unsigned int x = 0; x < width; ++x) {
				auto* pixel = &data[(y * width + x) * 3];
				std::swap(pixel[0], pixel[2]);
			}
		}

		// write
		std::ofstream f(filename, std::ios::binary);
		if (!f)
			throw std::ios::failure("Failed to open file " + std::string(filename) + " for writing");

		TGAHeader header;
		TGAFooter footer;
		header.width = width;
		header.height = height;
		f.write(reinterpret_cast<const char*>(&header), sizeof(TGAHeader));
		f.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(unsigned char));
		f.write(reinterpret_cast<const char*>(&footer), sizeof(TGAFooter));
	}
}

extern "C" {
	int writeImage(const char* filename, unsigned int width, unsigned int height, const unsigned char* pixels) {
		try {
			std::filesystem::path filepath(filename);

			if (filepath.extension() == ".tga")
				writeImageTGA(filename, width, height, pixels);
			else if (filepath.extension() == ".png")
				return stbi_write_png(filename, width, height, 3, pixels, 0);
			else if (filepath.extension() == ".jpg")
				return stbi_write_jpg(filename, width, height, 3, pixels, 90);
			else
				throw std::invalid_argument("unsupported file format: " + filepath.extension().string());

			return 1;
		}
		catch (...) {
			return 0;
		}
	}
}

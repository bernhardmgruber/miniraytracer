#include <iostream>
#include <chrono>

#include "Scene.h"
#include "Image.h"
#include "raytrace.h"

using boost::filesystem::path;

int main(int argc, const char* argv[]) {
	try {
		if (argc != 5) {
			std::cerr << "Invalid number of arguments. Usage:\n\n";
			std::cerr << argv[0] << " sceneFile imageFormat width height\n";
			return 1;
		}

		const path sceneFile = argv[1];
		const path imageFormat = argv[2];
		const unsigned int width = std::stoi(argv[3]);
		const unsigned int height = std::stoi(argv[4]);

		if (!sceneFile.has_stem())
			throw std::invalid_argument("Except scene file " + sceneFile.string() + " to have a stem");
		path imageFile = sceneFile;
		imageFile.replace_extension(imageFormat);

		rt::Scene scene(sceneFile);

		const auto start = std::chrono::high_resolution_clock::now();
		const auto image = rt::raytrace(scene, width, height);
		const auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Raycast took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

		image.write(imageFile);

		//std::getchar();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << '\n';
		return 2;
	}
}

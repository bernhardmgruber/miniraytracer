#include <iostream>
#include <chrono>

#include "Scene.h"
#include "Image.h"
#include "raytrace.h"

using std::filesystem::path;

int main(int argc, const char* argv[]) {
	try {
		if (argc != 2) {
			std::cerr << "Invalid number of arguments. Expecting a scene file!\n";
			return 1;
		}

		const path sceneFile = argv[1];
		if (!sceneFile.has_stem())
			throw std::invalid_argument("Except scene file " + sceneFile.string() + " to have a stem");
		path imageFile = sceneFile;
		imageFile.replace_extension("ppm");

		rt::Scene scene(sceneFile);

		const auto start = std::chrono::high_resolution_clock::now();
		const auto image = rt::raytrace(scene, 1024, 768);
		const auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Raycast took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

		image.write(imageFile);

		std::getchar();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << '\n';
		return 2;
	}
}

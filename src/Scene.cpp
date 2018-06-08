#include "Scene.h"

#include <fstream>
#include <sstream>

namespace rt {
	Scene::Scene(const boost::filesystem::path& filepath) {
		// read the scene file

		std::ifstream f(filepath.string());
		if (!f)
			throw std::ios::failure("Failed to open file " + filepath.string() + " for reading");
		
		int lineCounter = 0;
		std::string line;
		while (std::getline(f, line)) {
			if (line.empty())
				continue;
			lineCounter++;
			std::stringstream ss(line);
			std::string token;

			auto expect = [&](const std::string& s) {
				ss >> token;
				if (token != s)
					throw std::runtime_error("Excepted token: " + s + " on line " + std::to_string(lineCounter));
			};

			ss >> token;
			if (token == "sphere") {
				Sphere sphere;
				expect("radius");
				ss >> sphere.radius;
				expect("center");
				ss >> sphere.center;

				_spheres.push_back(sphere);
			} else if (token == "camera") {
				expect("fovy");
				ss >> _camera.fovy;
				expect("position");
				ss >> _camera.position;
				expect("lookAt");
				math::VectorF la;
				ss >> la;
				_camera.view = (la - _camera.position).normalized();
				expect("up");
				math::VectorF up;
				ss >> up;
				_camera.up = (_camera.view % (_camera.view % up)).normalized();
			} else
				throw std::runtime_error("Unrecognized line command: " + token + " at start of line " + std::to_string(lineCounter));
		}
	}

	auto Scene::camera() const -> const Camera& {
		return _camera;
	}

	auto Scene::spheres() const -> const std::vector<Sphere>& {
		return _spheres;
	}
}

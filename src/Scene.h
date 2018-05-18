#pragma once

#include <vector>
#include <filesystem>

#include "Vector.hpp"

namespace rt {
	struct Camera {
		float fovy; // in degree
		math::VectorF position;
		math::VectorF view;
		math::VectorF up;
	};

	struct Sphere {
		math::VectorF center;
		float radius;
	};

	class Scene {
	public:
		Scene(const std::filesystem::path& file);

		auto camera() const -> const Camera&;
		auto spheres() const -> const std::vector<Sphere>&;

	private:
		// we often have getters with the same names as data members
		// that is why many people prefix "_" or "m_" on the data members
		Camera _camera;
		std::vector<Sphere> _spheres;
	};
}

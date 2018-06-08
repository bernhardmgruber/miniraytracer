#pragma once

#include <boost/filesystem.hpp>
#include <vector>

#include "Vector.hpp"

namespace rt {
	struct Camera {
		float fovy; // in degree
		VectorF position;
		VectorF view;
		VectorF up;
	};

	struct Sphere {
		VectorF center;
		float radius;
	};

	class Scene {
	public:
		Scene(const boost::filesystem::path& file);

		auto camera() const -> const Camera&;
		auto spheres() const -> const std::vector<Sphere>&;

	private:
		// we often have getters with the same names as data members
		// that is why many people prefix "_" or "m_" on the data members
		Camera _camera;
		std::vector<Sphere> _spheres;
	};
}

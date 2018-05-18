#pragma once

namespace rt {
	class Scene;
	class Image;

	auto raytrace(const Scene& s, unsigned int width, unsigned int height) -> Image;
}

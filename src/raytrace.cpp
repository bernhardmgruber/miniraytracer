#define USE_MATH_DEFINES
#include "raytrace.h"

#include <algorithm>
#include <optional>

#include "Scene.h"
#include "Image.h"

namespace rt {
	constexpr auto pi = 3.14159265359f;

	struct Intersection {
		float distance;
		math::VectorF point;
		math::VectorF normal;
	};

	struct Ray {
		math::VectorF origin;
		math::VectorF direction;
	};

	auto createRay(const Camera& camera, unsigned int width, unsigned int height, unsigned int x, unsigned int y) -> Ray {
		// we imagine a plane with the image just 1 before the camera, and then we shoot at those pixels

		const auto center = camera.position + camera.view;
		const auto xVec = camera.view % camera.up;
		const auto yVec = camera.up;

		const auto delta = (std::tan(camera.fovy * pi / 180.0f) * 2) / (height - 1);
		const auto xDeltaVec = xVec * delta;
		const auto yDeltaVec = yVec * delta;

		const auto xRel = (x - static_cast<float>(width - 1) / 2);
		const auto yRel = (y - static_cast<float>(height - 1) / 2);

		const auto pixel = center + xDeltaVec * xRel + yDeltaVec * yRel;

		Ray r;
		r.origin = center;
		r.direction = (pixel - camera.position).normalized();
		return r;
	}

	auto intersect(const Ray& ray, const Sphere& sphere) -> std::optional<Intersection> {
		// from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

		// solve quadratic equation
		const auto a = 1;
		const auto b = 2 * (ray.direction * (ray.origin - sphere.center));
		const auto c = std::pow((ray.origin - sphere.center).length(), 2) - std::pow(sphere.radius, 2);

		const auto discriminat = std::pow(b, 2) - 4 * a * c;
		if (discriminat < 0)
			return std::nullopt;

		const auto x1 = (-b - std::sqrt(discriminat)) / 2 * a;
		const auto x2 = (-b + std::sqrt(discriminat)) / 2 * a;

		// report the closer intersection
		const auto t = std::min(x1, x2);

		Intersection inter;
		inter.distance = t;
		inter.point = ray.origin + t * ray.direction;
		inter.normal = (inter.point - sphere.center).normalized();
		return inter;
	}

	auto colorByRay(const Ray& ray) -> Image::Pixel {
		Image::Pixel c;
		for(int i = 0; i < 3; i++)
			c[i] = static_cast<unsigned char>(std::abs(ray.direction[i]) * 255);
		return c;
	}

	auto colorByNearestIntersectionNormal(const std::vector<Intersection>& hits) -> Image::Pixel {
		const auto it = std::min_element(std::begin(hits), std::end(hits), [](const auto& a, const auto& b) {
			return a.distance < b.distance;
		});

		if (it == std::end(hits)) {
			// no hit, black color
			return {};
		} else {
			Image::Pixel r;
			for (int i = 0; i < 3; i++)
				r[i] = static_cast<unsigned char>(std::abs(it->normal[i]) * 255);
			return r;
		}
	}

	auto colorByIntersectionNormal(std::vector<Intersection> hits) -> Image::Pixel {
		constexpr auto translucency = 0.5f;

		std::sort(std::begin(hits), std::end(hits), [](const auto& a, const auto& b) {
			return a.distance < b.distance;
		});

		auto t = translucency;
		Image::Pixel r;
		for (const auto& hit : hits) {
			// each hit contributes to the color, lesser with each iteration
			for (int i = 0; i < 3; i++)
				r[i] += static_cast<unsigned char>(std::abs(t * hit.normal[i]) * 255);
			t *= translucency;
		}

		for (int i = 0; i < 3; i++)
			r[i] = std::clamp<unsigned char>(r[i], 0, 255);

		return r;
	}

	auto raytrace(const Scene& scene, unsigned int width, unsigned int height) -> Image {
		Image img(width, height);

		for (auto y = 0u; y < height; y++) {
			for (auto x = 0u; x < width; x++) {

				const auto ray = createRay(scene.camera(), width, height, x, y);

				std::vector<Intersection> hits;
				for (const auto& sphere : scene.spheres())
					if (const auto hit = intersect(ray, sphere))
						hits.push_back(*hit);

				//img(x, y) = colorByRay(ray);
				img(x, y) = colorByNearestIntersectionNormal(hits);
				img(x, y) = colorByIntersectionNormal(hits);
			}
		}

		return img;
	}
}
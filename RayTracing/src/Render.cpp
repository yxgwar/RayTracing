#include "Render.h"
#include <iostream>

namespace RayTracing
{
	void Render::StartRendering(Image& image, int width, int height, int channels)
	{
		int index = 0;
		for (int j = 0; j < height; j++) {
#ifdef _DEBUG
			std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
#endif // _DEBUG
			for (int i = 0; i < width; i++) {
				glm::vec2 coord = { float(i) / (width), float(j) / (height)};
				coord = coord * 2.0f - 1.0f;
				coord.x *= (float)width / height;
				//glm::vec4 color({ float(i) / (width), float(j) / (height), 0.0f, 1.0f });
				image.SetPixelData(perPixel(coord), index);
				index += channels;
			}
		}
#ifdef _DEBUG
		std::clog << "\rDone.                 \n";
#endif // _DEBUG
	}

	glm::vec4 Render::perPixel(glm::vec2& coord)
	{
		glm::vec3 spherePosition(0.0f, 0.0f, 0.0f);
		glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);

		glm::vec3 oc = rayOrigin - spherePosition;
		glm::vec3 rayDirection(coord.x, coord.y, -1.0f);

		float radius = 0.5f;

		float a = glm::dot(rayDirection, rayDirection);
		float b = 2.0f * glm::dot(oc, rayDirection);
		float c = glm::dot(oc, oc) - radius * radius;

		float discriminant = b * b - 4.0f * a * c;

		if (discriminant >= 0.0f)
			return { 1.0f, 0.0f, 0.0f, 1.0f };
		else
			return { 0.0f, 0.0f, 0.0f, 1.0f };
	}
}
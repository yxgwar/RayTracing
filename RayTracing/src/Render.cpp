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
				coord = coord * 2.0f - 1.0f;								//将坐标调整到-1~1
				coord.x *= (float)width / height;							//适配长宽比
				coord.y *= -1;

				glm::vec4 color = perPixel(coord);
				color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));//将颜色限制在0~255
				image.SetPixelData(color, index);
			}
		}
#ifdef _DEBUG
		std::clog << "\rDone.                 \n";
#endif // _DEBUG
	}

	glm::vec4 Render::perPixel(glm::vec2& coord)
	{
		glm::vec3 spherePosition(0.0f, 0.0f, 0.0f);
		glm::vec3 rayOrigin(0.0f, 0.0f, 1.0f);

		glm::vec3 oc = rayOrigin - spherePosition;
		glm::vec3 rayDirection(coord.x, coord.y, -1.0f);

		float radius = 0.5f;

		glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f));

		/*
		* (x - sP.x)^2 + (y - sP.y)^2 + (z - sP.z)^2 = r^2
		* (position - spherePosition)^2 = r^2
		* position = rayOrigin + rayDirection * t
		* a = rDrD
		* b = 2rD(rO - sP)
		* c = (rO - sP)(rO - sP) - r^2
		*/

		float a = glm::dot(rayDirection, rayDirection);
		float b2 = glm::dot(oc, rayDirection);
		float c = glm::dot(oc, oc) - radius * radius;

		float discriminant = b2 * b2 - a * c;

		if(discriminant < 0)
			return { 0.0f, 0.0f, 0.0f, 1.0f };
		else
		{
			float t = (-b2 - glm::sqrt(discriminant)) / a;
			glm::vec3 hitPosition = rayOrigin + rayDirection * t;
			glm::vec3 normal = glm::normalize(hitPosition - spherePosition);

			float d = glm::max(glm::dot(normal, -lightDirection), 0.0f);
			glm::vec3 color = { 1.0f, 0.0f, 1.0f };
			return { color * d, 1.0f };
		}
	}
}
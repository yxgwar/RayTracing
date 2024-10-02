#pragma once

#include "Image.h"
#include "Camera.h"
#include <glm/glm.hpp>

namespace RayTracing
{
	class Render
	{
	public:
		static void StartRendering(Camera& camera, Image& image, int width, int height, int channels);
	private:
		static glm::vec4 perPixel(glm::vec3& rayOrigin, glm::vec3& rayDirection);
	};
}
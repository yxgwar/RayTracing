#pragma once

#include "Image.h"
#include <glm/glm.hpp>

namespace RayTracing
{
	class Render
	{
	public:
		static void StartRendering(Image& image, int width, int height, int channels);
	private:
		static glm::vec4 perPixel(glm::vec2& coord);
	};
}
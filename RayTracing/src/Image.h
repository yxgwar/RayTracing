#pragma once

#include "stb_img/stb_image.h"

namespace RayTracing
{
	class Image {
	public:
		Image(int width, int height, int channels = 4);
		~Image() = default;

		bool GenerateImage(stbi_uc* image);
	private:
		int m_Width, m_Height, m_Channels;
		//stbi_uc* m_Image = nullptr;
	};
}
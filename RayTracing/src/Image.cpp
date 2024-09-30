#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_img/stb_image_write.h"

namespace RayTracing
{
	//Image::Image()
	//{
		//m_Image = stbi_load("img/test/png", &m_Width, &m_Height, &m_Channels, 0);
	//}

	Image::Image(int width, int height, int channels)
		:m_Width(width), m_Height(height), m_Channels(channels)
	{
	}

	bool Image::GenerateImage(stbi_uc* image)
	{
		return stbi_write_png("./img/test.png", m_Width, m_Height, m_Channels, image, 0);
	}
}
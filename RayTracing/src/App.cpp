#include "App.h"
#include "Log.h"
#include "Image.h"
#include "Render.h"

namespace RayTracing
{
	App::App(int width, int height, int channels)
		:m_Width(width), m_Height(height), m_Channels(channels), m_AspectRatio((float)width / height)
	{
		RAY_INFO("Start!");
	}

	void App::Run()
	{
		Image image = Image(m_Width, m_Height);
		
		RAY_INFO("Start setting data!");
		Render::StartRendering(image, m_Width, m_Height, m_Channels);

		RAY_INFO("Start Generating image!");
		if (image.GenerateImage())
			RAY_INFO("Success!");
		else
			RAY_ERROR("Fail!");
	}
}
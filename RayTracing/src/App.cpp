#include "App.h"
#include "Log.h"
#include "Image.h"
#include "Render.h"
#include <chrono>

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
		auto start = std::chrono::high_resolution_clock::now();
		Render::StartRendering(image, m_Width, m_Height, m_Channels);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

		RAY_INFO("Start Generating image!");
		if (image.GenerateImage())
			RAY_INFO("Success!");
		else
			RAY_ERROR("Fail!");
	}
}
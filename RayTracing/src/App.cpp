#include "App.h"
#include "Log.h"
#include "Image.h"
#include "Render.h"
#include "RayMath.h"
#include <chrono>

namespace RayTracing
{
	App::App(int width, int height, int channels)
		:m_Width(width), m_Height(height), m_Channels(channels), m_AspectRatio((float)width / height),
		m_Camera(45.0f, 0.1f, 100.0f, width, height)
	{
		RAY_INFO("Start!");
	}

	void App::Run()
	{
		RayMath::Init();
		Image image = Image(m_Width, m_Height);
		m_Camera.SetPosition({ 0.0f, 0.0f, 3.0f });
		m_Scene.AddObjects(std::make_shared<Sphere>(glm::vec3{ 0.0f, 0.0f, 0.0f }, 0.5f, glm::vec4{ 1.0f }));
		m_Scene.AddObjects(std::make_shared<Sphere>(glm::vec3{ 0.0f, -100.5f, 0.0f }, 100.0f, glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }));

		RAY_INFO("Start setting data!");

		auto start = std::chrono::high_resolution_clock::now();
		Render::StartRendering(m_Scene, m_Camera, image, m_Width, m_Height, m_Channels);
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
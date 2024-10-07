#include "App.h"
#include "Log.h"
#include "Renderer/Image.h"
#include "Renderer/Render.h"
#include "Renderer/RayMath.h"
#include "Renderer/Material.h"
#include <chrono>

namespace RayTracing
{
	App::App(int width, int height, int channels)
		:m_Width(width), m_Height(height), m_Channels(channels), m_AspectRatio((float)width / height),
		m_Camera(45.0f, 0.1f, 100.0f, float(width), float(height))
	{
		RAY_INFO("Start!");
	}

	void App::Run()
	{
		RayMath::Init();
		Image image = Image(m_Width, m_Height);

		auto metal = std::make_shared<Metal>(glm::vec3(0.9f), 0.5f);
		auto center = std::make_shared<Lambertian>(glm::vec3{ 0.8f, 0.2f, 0.7f });
		auto land = std::make_shared<Lambertian>(glm::vec3{ 0.5f, 0.5f, 0.5f });
		m_Scene.AddMaterials(metal);
		m_Scene.AddMaterials(center);
		m_Scene.AddMaterials(land);
		m_Scene.AddObjects(std::make_shared<Sphere>(glm::vec3(0.0f), 0.5f, 1));
		m_Scene.AddObjects(std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, 0.0f), 0.5f, 0));
		m_Scene.AddObjects(std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, 0.0f), 0.5f, 0));
		m_Scene.AddObjects(std::make_shared<Sphere>(glm::vec3{ 0.0f, -100.5f, 0.0f }, 100.0f, 2));

		RAY_INFO("Start setting data!");

		auto start = std::chrono::high_resolution_clock::now();
		m_Camera.SetPosition({ 0.0f, 0.0f, 3.0f });
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
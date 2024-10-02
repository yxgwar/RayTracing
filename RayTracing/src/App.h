#pragma once

#include "Camera.h"

namespace RayTracing
{
	class App
	{
	public:
		App(int width = 1920, int height = 1080, int channels = 4);
		~App() = default;

		void Run();
	private:
		Camera camera;

		int m_Width, m_Height, m_Channels;
		float m_AspectRatio;
	};
}
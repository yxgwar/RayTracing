#pragma once

namespace RayTracing
{
	class App
	{
	public:
		App(int width = 1920, int height = 1080, int channels = 4);
		~App() = default;

		void Run();
	private:
		int m_Width, m_Height, m_Channels;
		float m_AspectRatio;
	};
}
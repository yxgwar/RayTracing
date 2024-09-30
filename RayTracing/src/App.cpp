#include "App.h"
#include "Log.h"
#include "Image.h"

namespace RayTracing
{
	App::App(int width, int height)
		:m_Width(width), m_Height(height)
	{
		RAY_INFO("Start!");
	}

	void App::Run()
	{
		Image image = Image(m_Width, m_Height);
		
		unsigned char* data = new unsigned char[m_Width * m_Height * 4];
		RAY_INFO("Start setting data!");
		int index = 0;
		for (int j = 0; j < m_Height; j++) {
			for (int i = 0; i < m_Width; i++) {
				auto r = double(i) / (m_Width - 1);
				auto g = double(j) / (m_Height - 1);
				auto b = 0.0;

				int ir = int(255.999 * r);
				int ig = int(255.999 * g);
				int ib = int(255.999 * b);

				data[index++] = ir;
				data[index++] = ig;
				data[index++] = ib;
				data[index++] = 255;
			}
		}

		RAY_INFO("Start Generating image!");
		if (image.GenerateImage(data))
			RAY_INFO("Success!");
		else
			RAY_ERROR("Fail!");

		delete[] data;
	}
}
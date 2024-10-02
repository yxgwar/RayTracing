#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace RayTracing
{
	Camera::Camera(float FOV, float nearClip, float farClip, float viewportWidth, float viewportHeight)
		:m_FOV(FOV), m_NearClip(nearClip), m_FarClip(farClip), m_ViewportWidth(viewportWidth), m_ViewportHeight(viewportHeight)
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		calculateViewMatrix();
		calculateProjectionMatrix();
		calculateRayDirections();
	}

	void Camera::calculateViewMatrix()
	{
		//暂时使用glm::lookat
		//m_Transform = glm::translate(glm::mat4(1.0f), m_Position);
		//m_ViewMatrix = glm::inverse(m_Transform);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));
		m_InverseViewMatrix = glm::inverse(m_ViewMatrix);
	}

	void Camera::calculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		m_InverseProjectionMatrix = glm::inverse(m_ProjectionMatrix);
	}

	void Camera::calculateRayDirections()
	{
		m_RayDirections.resize(m_ViewportWidth * m_ViewportHeight);
		for (int j = 0; j < m_ViewportHeight; j++) {
			for (int i = 0; i < m_ViewportWidth; i++) {
				glm::vec2 coord = { float(i) / (m_ViewportWidth), float(j) / (m_ViewportHeight) };
				coord = coord * 2.0f - 1.0f;								//将坐标调整到-1~1
				coord.y *= -1;

				//二维投影坐标 = ProjectionM * 三维空间坐标， 三维空间坐标 = (ProjectionM)^-1 * 二维投影坐标
				glm::vec4 target = m_InverseProjectionMatrix * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
				glm::vec3 targetP = glm::vec3(target) / target.w;  //齐次

				//摄像机空间坐标 = ViewM * 世界空间坐标
				//使用1扩充会得到位置坐标
				//glm::vec4 world = m_InverseViewMatrix * glm::vec4(targetP, 1.0f);
				//glm::vec3 worldP = glm::vec3(world) / world.w;
				//m_RayDirections[i + j * m_ViewportWidth] = glm::normalize(worldP - m_Position);

				//使用0扩充至四维向量可以保证变换时不受平移影响，直接得到方向向量
				glm::vec3 rayDirection = glm::vec3(m_InverseViewMatrix * glm::vec4(glm::normalize(targetP), 0.0f));
				m_RayDirections[i + j * m_ViewportWidth] = rayDirection;
			}
		}
	}


}
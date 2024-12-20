#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RayTracing
{
	class Camera
	{
	public:
		Camera(float FOV, float nearClip, float farClip, float viewportWidth, float viewportHeight);

		inline const glm::vec3& GetOrigin() const { return m_Position; }
		inline const std::vector<glm::vec3>& GetRayDirections() const { return m_RayDirections; }
		inline glm::vec3& GetRightD() { return m_RightD; }
		inline glm::vec3& GetDownD() { return m_DownD; }

		void SetPosition(glm::vec3 position) { m_Position = position;  calculateViewMatrix(); calculateRayDirections();}
	private:
		void calculateViewMatrix();
		void calculateProjectionMatrix();
		void calculateRayDirections();
	private:
		glm::vec3 m_Position{ 0.0f };
		glm::vec3 m_Direction{ 0.0f, 0.0f, -1.0f };
		//glm::mat4 m_Transform;

		std::vector<glm::vec3> m_RayDirections;
		glm::vec3 m_RightD;
		glm::vec3 m_DownD;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_InverseViewMatrix;
		glm::mat4 m_InverseProjectionMatrix;

		float m_FOV = 45.0f;
		float m_NearClip = 0.1f;
		float m_FarClip = 100.0f;

		float m_ViewportWidth, m_ViewportHeight;
		float m_AspectRatio;
	};
}
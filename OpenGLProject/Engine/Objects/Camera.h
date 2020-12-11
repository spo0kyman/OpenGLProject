#pragma once
#include "Object.h"

namespace nc
{
	class Camera : public Object
	{
	public:
		Camera(const std::string& name, const Transform& transform = Transform{}) : Object{ name, transform } {}

		void Update(float dt) override;

		void SetLookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up = glm::vec3{ 0, 1, 0 }, bool initialize = false);
		void SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
		{
			m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		}

		const glm::mat4& projection() { return m_projection; }
		const glm::mat4& view() { return m_view; }

	protected:
		glm::mat4 m_projection{ glm::mat4{1} };
		glm::mat4 m_view{ glm::mat4{1} };
		glm::quat m_rotation{ glm::vec3{0} };
	};
}
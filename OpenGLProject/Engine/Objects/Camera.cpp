#include "pch.h"
#include "Camera.h"
#include "Scene.h"

namespace nc {

	void Camera::Update(float dt) {
		glm::vec3 rotate{ 0 };
		if (m_scene->engine()->GetSystem<InputSystem>()->GetMouseButtonState(SDL_BUTTON_RIGHT) == InputSystem::eButtonState::HELD) {
			glm::vec2 axis = m_scene->engine()->GetSystem<InputSystem>()->GetMouseRelative() * 0.005f;
			rotate.x -= axis.y;
			rotate.y -= axis.x;
		}

		m_rotation = m_rotation * glm::quat{rotate};

		glm::vec3 translation{ 0 };
		if (m_scene->engine()->GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_A) == InputSystem::eButtonState::HELD) {
			translation.x -= 1;
		}
		if (m_scene->engine()->GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_D) == InputSystem::eButtonState::HELD) {
			translation.x += 1;
		}
		if (m_scene->engine()->GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_W) == InputSystem::eButtonState::HELD) {
			translation.z -= 1;
		}
		if (m_scene->engine()->GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_S) == InputSystem::eButtonState::HELD) {
			translation.z += 1;
		}
		if (m_scene->engine()->GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_E) == InputSystem::eButtonState::HELD) {
			translation.y += 1;
		}
		if (m_scene->engine()->GetSystem<InputSystem>()->GetButtonState(SDL_SCANCODE_Q) == InputSystem::eButtonState::HELD) {
			translation.y -= 1;
		}

		m_transform.translation = m_transform.translation + ((m_rotation * translation) * 8.0f) * dt;
		SetLookAt(m_transform.translation, m_transform.translation + (m_rotation * glm::vec3{ 0, 0, -1 }));
	}

	void Camera::SetLookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, bool initialize) {
		m_view = glm::lookAt(eye, target, up);
		m_transform = glm::inverse(m_view);
	}
}
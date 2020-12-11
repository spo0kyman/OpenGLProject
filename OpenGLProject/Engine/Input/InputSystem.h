#pragma once
#include "../Core/System.h"

namespace nc
{
	class InputSystem : public System
	{
	public:
		enum class eButtonState
		{
			IDLE,
			PRESSED,
			HELD,
			RELEASED
		};

	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		eButtonState GetButtonState(int id);
		bool GetButtonDown(int id);
		bool GetPreviousButtonDown(int id);

		eButtonState GetMouseButtonState(int id);
		const glm::vec2& GetMouseAbsolute() { return m_mousePosition; }
		const glm::vec2& GetMouseRelative() { return m_mouseRelative; }

	protected:
		// keyboard
		int m_numKeys;
		Uint8* m_keystate;
		Uint8* m_prevKeystate;

		// mouse
		Uint32 m_mouseButtonstate;
		Uint32 m_prevMouseButtonstate;

		glm::vec2 m_mousePosition;
		glm::vec2 m_prevMousePosition;
		glm::vec2 m_mouseRelative;
	};
}
#include "pch.h"
#include "InputSystem.h"

namespace nc
{
	bool InputSystem::Startup()
	{
		const Uint8* keystate = SDL_GetKeyboardState(&m_numKeys);

		// allocate memory for current and previous keystate
		m_keystate = new Uint8[m_numKeys];
		m_prevKeystate = new Uint8[m_numKeys];
		// copy current keystate
		memcpy(m_keystate, keystate, m_numKeys);
		memcpy(m_prevKeystate, m_keystate, m_numKeys);

		SDL_Point axis;
		m_mouseButtonstate = SDL_GetMouseState(&axis.x, &axis.y);
		m_prevMouseButtonstate = m_mouseButtonstate;
		m_mousePosition = glm::vec2(axis.x, axis.y);
		m_prevMousePosition = m_mousePosition;

		return true;
	}

	void InputSystem::Shutdown()
	{
		delete[] m_keystate;
		delete[] m_prevKeystate;
	}

	void InputSystem::Update()
	{
		// copy keystate to prev keystate
		memcpy(m_prevKeystate, m_keystate, m_numKeys);
		// get current keystate
		const Uint8* keystate = SDL_GetKeyboardState(nullptr);
		// copy current keystate to keystate
		memcpy(m_keystate, keystate, m_numKeys);

		// set previous mouse state
		m_prevMouseButtonstate = m_mouseButtonstate;
		m_prevMousePosition = m_mousePosition;

		// get current mouse state
		SDL_Point axis;
		m_mouseButtonstate = SDL_GetMouseState(&axis.x, &axis.y);
		m_mousePosition = glm::vec2(axis.x, axis.y);
		m_mouseRelative = m_mousePosition - m_prevMousePosition;
	}

	InputSystem::eButtonState InputSystem::GetMouseButtonState(int id)
	{
		eButtonState state = eButtonState::IDLE;

		bool buttonDown = m_mouseButtonstate & SDL_BUTTON(id);
		bool prevButtonDown = m_prevMouseButtonstate & SDL_BUTTON(id);

		if (buttonDown)
		{
			state = (prevButtonDown) ? eButtonState::HELD : eButtonState::PRESSED;
		}
		else
		{
			state = (prevButtonDown) ? eButtonState::RELEASED : eButtonState::IDLE;
		}

		return state;
	}

	InputSystem::eButtonState InputSystem::GetButtonState(int id)
	{
		eButtonState state = eButtonState::IDLE;

		bool buttonDown = GetButtonDown(id);
		bool prevButtonDown = GetPreviousButtonDown(id);

		if (buttonDown)
		{
			state = (prevButtonDown) ? eButtonState::HELD : eButtonState::PRESSED;
		}
		else
		{
			state = (prevButtonDown) ? eButtonState::RELEASED : eButtonState::IDLE;
		}

		return state;
	}

	bool InputSystem::GetButtonDown(int id)
	{
		return m_keystate[id];
	}

	bool InputSystem::GetPreviousButtonDown(int id)
	{
		return m_prevKeystate[id];
	}
}

#pragma once

#include "Event.h"

#include <sstream>

namespace Engine {

	class ENGINE_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_keyCode; }

		// Key Event is categorized as both keyboard OR type input
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class ENGINE_API KeyPressedEvent : public KeyEvent {
	public: 
		KeyPressedEvent(int keycode, int repeatCount)
		: KeyEvent(keycode), m_repeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class ENGINE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
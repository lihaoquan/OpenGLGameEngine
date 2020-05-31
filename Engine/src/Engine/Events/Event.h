#pragma once
#include "egpch.h"
#include "Engine/Core.h"

namespace Engine {

	// Events are currently blocking calls and are not buffered
	// for future, need to be able to buffer events into a queue and process
	// those event as part of an update tick

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Set as bits so that including multiple events together by masking is possible
	// e.g MouseButton is a Mouse event category, Keyboard is also an Input Event Category
	enum EventCategory {
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

// GetStaticType is static so that we do not need an instance of the event to actually know what it is
// Will be useful for polymorphism
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class ENGINE_API Event 
	{
		// EventDispatcher class can have special access to Event functions and variables when declared as a friend class
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// Inline is used to reduce function call overhead. Use only for small commonly-used functions
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		// Boolean to specify if this event has been handled already. If it is, stop propagating to other layers e.g Game itself
		// An example would be a UI click button, if the click event happens to land on the UI, it will be consumed and will not
		// interact with the game itself
		bool m_Handled = false;
	};

	// Dispatches event by matching its type. If it receives an event that is not its target type, it will ignore it
	// If event received matches its type, it will execute that function and set that m_Handled to be true so that this
	// event will not be further propagated to other layers
	class EventDispatcher 
	{
		template<typename T>
		// Declaring EventFn as an empty function that is expected to return a boolean
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			// Type checking instead of using a bunch of if else / switch statements
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event); // cast the event to be its actual type and execute it
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// An output stream for the logger to output the Events string representation
	inline std::ostream& operator << (std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
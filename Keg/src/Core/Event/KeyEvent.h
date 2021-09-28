#pragma once

#include "Event.h"
#include "Core/KeyCodes.h"

namespace Keg
{

	class KeyEvent : public Event
	{

	public:
		KeyCode GetKey() { return m_Key;  }

	protected:
		KeyCode m_Key;
		KeyEvent(const KeyCode kc) : m_Key(kc) {}


	};

	class KeyPressedEvent : public KeyEvent
	{
	
	public:
		KeyPressedEvent(const KeyCode kc, bool repeated) :
			KeyEvent(kc), m_IsRepeated(repeated) {};

		bool IsRepeated() { return m_IsRepeated;  }
		EVENT_STATIC_TYPE("KeyPressed");
	public:
		bool m_IsRepeated;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode kc) : KeyEvent(kc) {}
		EVENT_STATIC_TYPE("KeyReleased");
	};
}
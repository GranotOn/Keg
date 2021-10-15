#pragma once

#include "Event.h"

namespace Keg
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_STATIC_TYPE("WindowClose");
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

		int GetWidth() { return m_Width;  }
		int GetHeight() { return m_Height; }
		bool IsMinimized() { return m_Width == 0 && m_Height == 0; }

		std::pair<int, int> GetSize() { return { m_Width, m_Height }; }

		EVENT_STATIC_TYPE("WindowResize");
	private:
		int m_Width;
		int m_Height;
	};
}


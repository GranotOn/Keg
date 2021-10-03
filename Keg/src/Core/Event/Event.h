#pragma once

#include <string>


#define EVENT_STATIC_TYPE(type) static std::string GetStaticType() { return type; } \
								virtual std::string GetEventType() const override { return GetStaticType(); }
namespace Keg
{

	class Event
	{
	public:
		bool m_Handled;
		virtual std::string GetEventType() const = 0;
	};

	class EventDispatcher
	{
	public:
		class EventDispatcher(Event& e) : m_Event(e) {};
		

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType().compare(T::GetStaticType()) == 0)
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event &m_Event;
	};

}
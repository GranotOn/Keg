#pragma once
#include <string>
#include "Core/Application/Time.h"
#include "Core/Event/Event.h"

namespace Keg
{
	class Layer
	{
	public:
		// Hooks
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time& time) {}
		virtual void OnEvent(Event &e) {}
		virtual void OnImGuiUpdate() {}

#ifdef KEG_DEBUG
		virtual std::string GetDebugName() = 0;
#endif
	};
}
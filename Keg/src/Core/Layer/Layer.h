#pragma once
#include <string>
#include "Core/Event/Event.h"

namespace Keg
{
	class Layer
	{
	public:
		// Hooks
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event &e) {}
		virtual void OnImGuiUpdate() {}

#ifdef KEG_DEBUG
		virtual std::string GetDebugName() = 0;
#endif
	};
}
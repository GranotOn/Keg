#pragma once
#include <string>
#include "Core/Event/Event.h"

namespace Keg
{
	class Layer
	{
	public:
		// Hooks
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event &e) = 0;

#ifdef KEG_DEBUG
		virtual std::string GetDebugName() = 0;
#endif
	};
}
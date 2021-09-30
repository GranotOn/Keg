#pragma once
#include "Core/Event/Event.h"
#include <string>
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


	class TestLayer : public Layer
	{
		virtual void OnAttach() { KEG_ENGINE_TRACE("({0}): OnAttach", this->GetDebugName()); }
		virtual void OnDetach() { KEG_ENGINE_TRACE("({0}): OnDetach", this->GetDebugName()); }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event &e) { KEG_ENGINE_TRACE("({0}): OnEvent", this->GetDebugName()); }

#ifdef KEG_DEBUG
		std::string GetDebugName() { return "TestLayer"; }
#endif
	};

	class TestOverlay : public Layer
	{
		virtual void OnAttach() { KEG_ENGINE_TRACE("({0}): OnAttach", this->GetDebugName()); }
		virtual void OnDetach() { KEG_ENGINE_TRACE("({0}): OnDetach", this->GetDebugName()); }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event &e) { KEG_ENGINE_TRACE("({0}): OnEvent", this->GetDebugName()); }

#ifdef KEG_DEBUG
		std::string GetDebugName() { return "TestOverlay"; }
#endif
	};
}
#pragma once
#include <string>

#include "Core/Layer/Layer.h"


namespace Keg
{
	class ImGuiLayer : public Layer
	{
	public:
		// Hooks
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnEvent(Event& e);

		// ImGui Lifecycle
		virtual void Begin();
		virtual void End();

#ifdef KEG_DEBUG
		virtual std::string GetDebugName();
#endif
	};
}

#pragma once
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Core/Layer/Layer.h"


namespace Keg
{
	class ImGuiLayer : public Layer
	{
	public:
		// Hooks
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);

#ifdef KEG_DEBUG
		virtual std::string GetDebugName();
#endif
	private:
		ImGuiIO m_IO;
		bool m_ShowDemoWindow = true;
	};
}

#pragma once

#include "Time.h"

#include "Core/Event/KeyEvent.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Layer/LayerStack.h"
#include "Core/ImGui/ImGuiLayer.h"

#include "Platform/Window.h"


// Defnition for main (imported in EntryPoint.h)
int main(int argc, char** argv);

namespace Keg
{
	class Application
	{
	public:
		Application();
		~Application();

		// Event handlers
		bool OnKeyPress(KeyPressedEvent &e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnResize(WindowResizeEvent& e);

		static Application* GetInstance() { return s_Instance;  }
		Window* GetWindow();

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }


	protected:
		bool m_Running;
		Window* m_Window;
		LayerStack* m_Layers;
		ImGuiLayer* m_ImGuiLayer;


	private:
		friend int ::main(int argc, char** argv);
		void Run(); // Main loop is here
		void OnEvent(Event& e);
	
	private:
		static Application* s_Instance;
		Time m_LastUpdate;
	};

	// This is the client application
	Application* CreateApplication();
}


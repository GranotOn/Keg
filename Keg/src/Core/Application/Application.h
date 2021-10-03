#pragma once

#include "Platform/Window.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Layer/LayerStack.h"

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

		static Application* GetInstance() { return s_Instance;  }
		Window* GetWindow();


	protected:
		bool m_Running;
		Window* m_Window;
		LayerStack* m_Layers;


	private:
		friend int ::main(int argc, char** argv);
		void Run(); // Main loop is here
		void OnEvent(Event& e);
	
	private:
		static Application* s_Instance;
	};

	// This is the client application
	Application* CreateApplication();
}
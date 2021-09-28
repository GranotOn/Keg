#pragma once

#include "Platform/Window.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/WindowEvent.h"

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
		bool OnWindowResize(WindowResizeEvent& e);


	protected:
		bool m_Running;
		Window* m_Window;


	private:
		friend int ::main(int argc, char** argv);
		void Run(); // Main loop is here
		void OnEvent(Event& e);
	};

	// This is the client application
	Application* CreateApplication();
}
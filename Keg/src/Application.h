#pragma once

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


	private:
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
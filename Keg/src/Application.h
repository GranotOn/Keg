#pragma once


#include "Keg.h"

// Defnition for main (imported in EntryPoint.h)
int main(int argc, char** argv);

namespace Keg
{
	class Application
	{
	public:
		Application();
		~Application();

		void OnWindowCloseEvent(GLFWwindow* window);

	private:
		bool m_Running;

		// FPS stuff
		double m_Frames;
		double m_LastTime;

	private:
		friend int ::main(int argc, char** argv);
		void Run(); // Main loop is here

	};

	// This is the client application
	Application* CreateApplication();
}
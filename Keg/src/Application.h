#pragma once

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
		friend int ::main(int argc, char** argv);
		void Run(); // Main loop is here
	};

	// This is the client application
	Application* CreateApplication();
}
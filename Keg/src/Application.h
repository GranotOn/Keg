#pragma once

int main(int argc, char** argv);

namespace Keg
{
	class Application
	{
	public:
		Application();
		~Application();
		void Run();

	private:
		friend int ::main(int argc, char** argv);
	};


	Application* CreateApplication();
}
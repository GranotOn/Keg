#include <Keg.h>
#include <EntryPoint.h>
#include <iostream>

class SandboxApplication : public Keg::Application
{

public:

	SandboxApplication()
	{
		std::cout << "Hello from Sandbox" << std::endl;
	}

};

Keg::Application* Keg::CreateApplication()
{
	return new SandboxApplication();
}
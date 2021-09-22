#include "Keg.h"
#include <EntryPoint.h>

class SandboxApplication : public Keg::Application
{

public:

	SandboxApplication()
	{
	}

};

Keg::Application* Keg::CreateApplication()
{
	return new SandboxApplication();
}
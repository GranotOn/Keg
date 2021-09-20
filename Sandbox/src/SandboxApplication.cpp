#include <Keg.h>
#include <EntryPoint.h>

class SandboxApplication : public Keg::Application
{

public:

	SandboxApplication()
	{
		KEG_APP_TRACE("Trace from, {0}", "Application");
		KEG_APP_INFO("Info from, {0}", "Application");
		KEG_APP_WARN("Warn from, {0}", "Application");
		KEG_APP_ERROR("Error from, {0}", "Application");
	}

};

Keg::Application* Keg::CreateApplication()
{
	return new SandboxApplication();
}
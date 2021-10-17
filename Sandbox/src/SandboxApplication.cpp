#include <Keg.h>
#include <EntryPoint.h>

#include "./ExampleLayer.h"

class SandboxApplication : public Keg::Application
{

public:

	SandboxApplication()
	{
		m_Layers->AddLayer(new TestLayer());
	}

};

Keg::Application* Keg::CreateApplication()
{
	return new SandboxApplication();
}
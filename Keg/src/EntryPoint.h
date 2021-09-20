#pragma once

#include "Keg.h"

extern Keg::Application* Keg::CreateApplication();

int main(int argc, char** argv)
{
	Keg::Logger::Init();

	KEG_ENGINE_TRACE("Trace from, {0}", "Engine");
	KEG_ENGINE_INFO("Info from, {0}", "Engine");
	KEG_ENGINE_WARN("Warn from, {0}", "Engine");
	KEG_ENGINE_ERROR("Error from, {0}", "Engine");

	auto app = Keg::CreateApplication();
	app->Run();

	delete app;
}


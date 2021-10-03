#pragma once

#include "Core/Application/Application.h"
#include "Core/Logger/Logger.h"

extern Keg::Application* Keg::CreateApplication();

int main(int argc, char** argv)
{
	Keg::Logger::Init();

	auto app = Keg::CreateApplication();
	app->Run();

	delete app;
}


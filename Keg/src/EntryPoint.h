#pragma once

#include "Application.h"
#include <iostream>

extern Keg::Application* Keg::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Hello from Keg" << std::endl;
	auto app = Keg::CreateApplication();
	app->Run();

	delete app;
}


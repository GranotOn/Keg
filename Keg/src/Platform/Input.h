#pragma once

#include <utility>

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

namespace Keg
{
	class Input
	{
	public:
		virtual std::pair<double, double>  GetMousePosition() = 0;
		virtual double GetMouseX() = 0;
		virtual double GetMouseY() = 0;

		virtual bool IsMousePressed(MouseCode button) = 0;
		virtual bool IsKeyPressed(KeyCode key) = 0;
	};
}
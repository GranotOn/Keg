#pragma once

#include "Input.h"

namespace Keg
{
	class WindowsInput : public Input
	{
	public:
		virtual std::pair<double, double> GetMousePosition();
		virtual double GetMouseX();
		virtual double GetMouseY();

		virtual bool IsMousePressed(MouseCode button);
		virtual bool IsKeyPressed(KeyCode key);
	};
}
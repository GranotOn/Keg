#pragma once

#include "Window.h"
#include "WindowsWindow.h"

namespace Keg
{
	class WindowBuilder
	{
	public:
		static Window* GetInstance()
		{
			if (!s_Instance)
			{
				s_Instance = new WindowsWindow();
			}

			return s_Instance;
		}
	private:
		inline static Window* s_Instance = nullptr;
	};
}
#pragma once

#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Keg
{
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const char* title = "Keg Engine", int width = 800, int height = 600);
		// Initialization & Destruction
		virtual void Init() override;
		virtual ~WindowsWindow() override;
		virtual void Shutdown() const override;

		// Runtime handeling
		virtual void SetEventCallback(const EventCallbackFn& cb) override;
		virtual void SwapBuffers() const override;
		virtual void PollEvents() const override;
		virtual bool HasWindow() const override;
		virtual void OnUpdate() const override;

		GLFWwindow* GetWindow() { return m_Window;  }


	private:
		// This WindowData will be passed as a GLFW user pointer (for context saving)
		struct WindowData
		{
			const char* title;
			int width;
			int height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;
	};
}


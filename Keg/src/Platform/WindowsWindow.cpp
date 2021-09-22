#include "Keg.h"
#include "WindowsWindow.h"

namespace Keg
{

	GLFWwindow* WindowsWindow::m_Window = NULL;

	void WindowsWindow::Init() const {

		/* Initialize GLFW */
		if (!glfwInit())
		{
			KEG_ENGINE_ERROR("WindowsWindow glfwInit() Error");
			return;
		}

		KEG_ENGINE_INFO("glfwInit successfull");

		/* Specify hints */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		WindowsWindow::m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title, NULL, NULL);

		if (!WindowsWindow::m_Window)
		{
			KEG_ENGINE_ERROR("WindowsWindow glfwCreateWindow() Error");
			return;
		}

		KEG_ENGINE_INFO("glfwCreateWindow succesfull");

		/* Make the window's context current */
		glfwMakeContextCurrent(WindowsWindow::m_Window);

		// Set the user pointer (the window data). This step is crucial so that we can query
		// this data on each event.
		glfwSetWindowUserPointer(m_Window, (void *) &m_Data);

		// TOOD: Move this to the renderer possibly (Because it's glad)
		/* Load GLAD */
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			KEG_ENGINE_ERROR("glad load gl proc");
		}

		KEG_ENGINE_INFO("gladLoadGLLoader succesfull");

		///////////////////////
		//// Callbacks
		///////////////////////

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				// The context we stored
				WindowData *data = (WindowData*) glfwGetWindowUserPointer(window);
				
				Event e = Event();
				data->EventCallback(e);
			});

	}

	void WindowsWindow::OnUpdate() const
	{
		SwapBuffers();
		PollEvents();
	}

	WindowsWindow::WindowsWindow(const char* title, int width, int height)
	{
		m_Data.height = height;
		m_Data.width = width;
		m_Data.title = title;
	}

	void WindowsWindow::Shutdown() const
	{
		glfwTerminate();
	}
	
	void WindowsWindow::SetEventCallback(const EventCallbackFn& cb)
	{
		m_Data.EventCallback = cb;
	}

	void WindowsWindow::PollEvents() const
	{
		glfwPollEvents();
	}

	void WindowsWindow::SwapBuffers() const
	{
		glfwSwapBuffers(WindowsWindow::m_Window);
	}

	bool WindowsWindow::HasWindow() const
	{
		return (WindowsWindow::m_Window != NULL);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

}

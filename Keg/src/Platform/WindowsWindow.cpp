#include "Keg.h"
#include "WindowsWindow.h"

namespace Keg
{

	GLFWwindow* WindowsWindow::m_Window = NULL;

	static void GLFWErrorCallback(int error, const char* description)
	{
		KEG_ENGINE_ERROR("GLFW Error ({0}): {1}", error, description);
	}


	void WindowsWindow::Init() const {

		/* Initialize GLFW */
		if (!glfwInit())
		{
			KEG_ENGINE_ERROR("WindowsWindow glfwInit() Error");
			return;
		}

		KEG_ENGINE_TRACE("glfwInit successfull");


		/* Specify hints */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		WindowsWindow::m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title, NULL, NULL);

		if (!WindowsWindow::m_Window)
		{
			KEG_ENGINE_ERROR("WindowsWindow glfwCreateWindow() Error");
			return;
		}

		KEG_ENGINE_TRACE("glfwCreateWindow succesfull");

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


		KEG_ENGINE_TRACE("gladLoadGLLoader succesfull");
		KEG_ENGINE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
		
		///////////////////////
		//// Callbacks
		///////////////////////

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				// The context we stored
				WindowData *data = (WindowData*) glfwGetWindowUserPointer(window);
				
				bool isPressed = action == GLFW_PRESS;
				bool isReleased = action == GLFW_RELEASE;
				bool isRepeated = action == GLFW_REPEAT;

				if (isPressed || isRepeated)
				{
					KeyPressedEvent e = KeyPressedEvent(key, isRepeated);
					data->EventCallback(e);
				}
				else if (isReleased)
				{
					KeyReleasedEvent e = KeyReleasedEvent(key);
					data->EventCallback(e);
				}
			});

		

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

				CursorMovedEvent e = CursorMovedEvent(xpos, ypos);
				data->EventCallback(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				if (action == GLFW_PRESS)
				{
					MousePressedEvent e = MousePressedEvent(xpos, ypos, button);
					data->EventCallback(e);
				}

				else if (action == GLFW_RELEASE)
				{
					MouseReleasedEvent e = MouseReleasedEvent(xpos, ypos, button);
					data->EventCallback(e);
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);

				MouseScrolledEvent e = MouseScrolledEvent(xpos, ypos, xoffset, yoffset);
				data->EventCallback(e);
			});

		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			if (entered)
			{
				CursorEnteredEvent e = CursorEnteredEvent(xpos, ypos);
				data->EventCallback(e);
			}
			else
			{
				CursorLeftEvent e = CursorLeftEvent(xpos, ypos);
				data->EventCallback(e);
			}
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e = WindowCloseEvent();
				data->EventCallback(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
				WindowResizeEvent e = WindowResizeEvent(width, height);
				data->EventCallback(e);

			});

		glfwSetErrorCallback(GLFWErrorCallback);
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

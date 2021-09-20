#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include "Application.h"

namespace Keg
{
	Application::Application() {
        m_Frames = 0;
        m_Running = true;
        m_LastTime = glfwGetTime();
	}

	Application::~Application() {

	}

    void Application::OnWindowCloseEvent(GLFWwindow* window)
    {
        m_Running = false;
    }

	void Application::Run()
	{
		GLFWwindow* window;

		/* Initialize the library */
        if (!glfwInit())
        {
            m_Running = false;
            KEG_ENGINE_ERROR("GLFW Init");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            m_Running = false;
            KEG_ENGINE_ERROR("GLFW glfwCreateWindow");
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            KEG_ENGINE_ERROR("glad load gl proc");
        }


        // Window Callbacks
        auto f = std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1);
        glfwSetWindowCloseCallback(window, f);

        m_LastTime = glfwGetTime();


        /* Loop until the user closes the window */
        while (m_Running)
        {
            double currentTime = glfwGetTime();
            double delta = currentTime - m_LastTime;
            m_Frames++;

            if (delta >= 1.0 / 4) // Show once every 1/4 second
            {
                double fps = (double)m_Frames / delta;
                
                std::stringstream stringstream;
                stringstream << fps;
                
                glfwSetWindowTitle(window, stringstream.str().c_str());
                m_Frames = 0;
                m_LastTime = currentTime;
            
            }



            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
		
	}
}
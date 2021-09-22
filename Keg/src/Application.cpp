#include <glad/glad.h>
#include <functional>

#include "Keg.h"
#include "Application.h"

namespace Keg
{
    Application::Application()
    {
        m_Running = true;
        m_Window = NULL;
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& e)
    {
        KEG_APP_TRACE("Event");
    }


    void Application::Run()
    {
        // Create & Initialize Window
        m_Window = new WindowsWindow();
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_Window->Init();

        // Assert that a window exists
        if (!m_Window->HasWindow())
        {
            KEG_ENGINE_ERROR("Can't start application - window isn't intialized");
            m_Running = false;
        }


        /* Loop until the user closes the window */
        while (m_Running)
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();
        
        }

        delete m_Window;
	}
}
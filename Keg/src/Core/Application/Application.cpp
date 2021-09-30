#include <functional>
#include <string>
#include <utility>

#include "Keg.h"
#include "Application.h"

#define EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace Keg
{
    Application::Application()
    {
        m_Running = true;
        m_Window = NULL;
        m_Layers = new LayerStack();
    }

    Application::~Application()
    {

    }

    bool Application::OnKeyPress(KeyPressedEvent& e) 
    {
        if (e.GetKey() == Key::Escape)
        {
            KEG_APP_INFO("Application closing because user clicked on Escape");
            m_Running = false;
        }

        return true;
    }


    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        KEG_APP_INFO("Window is closing per callback from window class");
        m_Running = false;
        return true;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher = EventDispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(EVENT_FUNC(Application::OnKeyPress));
        dispatcher.Dispatch<WindowCloseEvent>(EVENT_FUNC(Application::OnWindowClose));

        for (auto it = m_Layers->rbegin(); it != m_Layers->rend(); ++it)
        {
            (*it)->OnEvent(e);
        }
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

            
            // Update layers
            for (auto& layer : *m_Layers)
            {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }

        delete m_Window;
	}
}
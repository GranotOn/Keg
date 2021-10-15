#include <functional>
#include <string>
#include <utility>

#include "Application.h"
#include "Platform/WindowsWindow.h"

#define EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace Keg
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        if (s_Instance)
        {
            KEG_ENGINE_ERROR("Application already exists!");
        }

        m_Running = true;
        m_Layers = new LayerStack();
        s_Instance = this;

        m_Window = new WindowsWindow();
        m_Window->SetEventCallback(EVENT_FUNC(Application::OnEvent));

        m_Renderer = new OpenGLRenderer();
        
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
        // Initialize Window
        m_Window->Init();

        // Initialize Renderer
        // IMPORTANT: Must happen after m_Window->Init();
        m_Renderer->Init(m_Window->GetProcAddress());

        // Assert that a window exists
        if (!m_Window->HasWindow())
        {
            KEG_ENGINE_ERROR("Can't start application - window isn't intialized");
            m_Running = false;
        }


        /* Loop until the user closes the window */
        while (m_Running)
        {

            m_Renderer->Update();
            

            
            // Update layers
            for (auto& layer : *m_Layers)
            {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }

        delete m_Window;
	}

    Window* Application::GetWindow()
    {
        return m_Window;
    }

    Application::~Application()
    {

    }
}
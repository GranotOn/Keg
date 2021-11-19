#include "stadx.h"

#include "Application.h"

#include "Platform/WindowBuilder.h"
#include "Renderer/RendererBuilder.h"
#include "Audio/AudioBuilder.h"

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

        m_Window = WindowBuilder::GetInstance();
        m_Window->SetEventCallback(EVENT_FUNC(Application::OnEvent));
        
        m_LastUpdate = { m_Window->GetTime(), 0 };

        m_ImGuiLayer = new ImGuiLayer();
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

    bool Application::OnResize(WindowResizeEvent& e)
    {
        RendererBuilder::GetInstance()->GetRenderer()->OnViewportChange(e.GetWidth(), e.GetHeight());
        return false;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher = EventDispatcher(e);

        dispatcher.Dispatch<KeyPressedEvent>(EVENT_FUNC(Application::OnKeyPress));
        dispatcher.Dispatch<WindowCloseEvent>(EVENT_FUNC(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(EVENT_FUNC(Application::OnResize));

        for (auto it = m_Layers->rbegin(); it != m_Layers->rend(); ++it)
        {
            (*it)->OnEvent(e);
        }
    }


    void Application::Run()
    {
        ///////////////////////
        // Initialization Stage
        ///////////////////////
        
        // Initialize Window
        m_Window->Init();
        m_Window->SetWindowIcon("C:\\Users\\grano\\Desktop\\Keg\\Keg\\assets\\Images\\icon.jpg");
        // Initialize Renderer
        // IMPORTANT: Must happen after m_Window->Init();
        RendererBuilder::GetInstance()->GetRenderer()->Init(m_Window->GetProcAddress());
        // Initialize Audio
        AudioBuilder::GetAudio()->Init();

        // Assert that a window exists
        if (!m_Window->HasWindow())
        {
            KEG_ENGINE_ERROR("Can't start application - window isn't intialized");
            m_Running = false;
        }

        m_Layers->AddOverlay(m_ImGuiLayer);

        // Activate OnAttach on each layer because no renderer is initialized
        for (Layer* layer : m_Layers->GetLayers())
        {
            layer->OnAttach();
        }

        m_Layers->SetRunning(true);


        //////////////
        // Engine Loop
        //////////////

        while (m_Running)
        {
            double time = m_Window->GetTime();
            m_LastUpdate = { time , m_LastUpdate - time };
            
            // Update layers
            for (auto& layer : *m_Layers)
            {
                layer->OnUpdate(m_LastUpdate);
            }

            // ImGui Rendering
            m_ImGuiLayer->Begin();
            {
                for (auto& layer : *m_Layers)
                {
                    layer->OnImGuiUpdate();
                }
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }

        m_Layers->SetRunning(false);

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
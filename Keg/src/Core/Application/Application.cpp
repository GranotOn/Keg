#include <functional>
#include <string>
#include <utility>
#include <glad/glad.h>
#include <glm.hpp>

#include "Application.h"
#include "Platform/WindowsWindow.h"
#include "Renderer/Vertex.h"
#include "Renderer/OpenGLTextureManager.h"
#include "Renderer/RendererBuilder.h"

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

        m_Renderer = RendererBuilder::GetInstance()->GetRenderer();

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

        m_Layers->AddOverlay(m_ImGuiLayer);

        // Activate OnAttach on each layer because no renderer is initialized
        for (Layer* layer : m_Layers->GetLayers())
        {
            layer->OnAttach();
        }

        m_Layers->SetRunning(true);

        /* Loop until the user closes the window */
        while (m_Running)
        {
            m_Renderer->Update();
            
            // Update layers
            for (auto& layer : *m_Layers)
            {
                layer->OnUpdate();
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
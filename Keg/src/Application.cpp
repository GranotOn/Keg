#include <glad/glad.h>
#include <functional>
#include <string>
#include <utility>

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

        // WindowCloseCallback()
        if (e.GetStaticType().compare("KeyPressedEvent") == 0)
        {
            KeyPressedEvent* ke = dynamic_cast<KeyPressedEvent*>(&e);
            
            KEG_APP_TRACE("{0} was pressed, repeated: {1}", ke->GetKey(), ke->IsRepeated());
            
            if (ke->GetKey() == Key::Escape)
            {
                KEG_APP_INFO("Application closing because user clicked on Escape");
                m_Running = false;
            }

        }

        else if (e.GetStaticType().compare("KeyReleasedEvent") == 0)
        {
            KeyReleasedEvent* ke = dynamic_cast<KeyReleasedEvent*>(&e);

            KEG_APP_TRACE("{0} was released", ke->GetKey());
        }

        else if (e.GetStaticType().compare("CursorMovedEvent") == 0)
        {
            CursorMovedEvent* me = dynamic_cast<CursorMovedEvent*>(&e);

            KEG_APP_TRACE("Cursor moved: x({0}) y({1})", me->GetXPosition(), me->GetYPosition());
        }

        else if (e.GetStaticType().compare("MousePressedEvent") == 0)
        {
            MousePressedEvent* me = dynamic_cast<MousePressedEvent*>(&e);

            KEG_APP_TRACE("Mouse clicked: x({0}) y({1}) button({2})", me->GetXPosition(), me->GetYPosition(), me->GetButton());
        }

        else if (e.GetStaticType().compare("MouseReleasedEvent") == 0)
        {
            MouseReleasedEvent* me = dynamic_cast<MouseReleasedEvent*>(&e);

            KEG_APP_TRACE("Mouse released: x({0}) y({1}) button({2})", me->GetXPosition(), me->GetYPosition(), me->GetButton());
        }

        else if (e.GetStaticType().compare("MouseScrolledEvent") == 0)
        {
            MouseScrolledEvent* me = dynamic_cast<MouseScrolledEvent*>(&e);

            KEG_APP_TRACE("Mouse scrolled: x({0}) y({1}) xOff({2}) yOff({3})", me->GetXPosition(), me->GetYPosition(), me->GetXOffset(), me->GetYOffset());
        }

        else if (e.GetStaticType().compare("CursorEnteredEvent") == 0)
        {
            CursorEnteredEvent* me = dynamic_cast<CursorEnteredEvent*>(&e);

            KEG_APP_TRACE("Cursor entered window: x({0}) y({1})", me->GetXPosition(), me->GetYPosition());
        }

        else if (e.GetStaticType().compare("CursorLeftEvent") == 0)
        {
            CursorLeftEvent* me = dynamic_cast<CursorLeftEvent*>(&e);

            KEG_APP_TRACE("Cursor left window: x({0}) y({1})", me->GetXPosition(), me->GetYPosition());
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

            m_Window->OnUpdate();

            
        }

        delete m_Window;
	}
}
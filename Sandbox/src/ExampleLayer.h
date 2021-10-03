#pragma once

#include "Keg.h"

class TestLayer : public Keg::Layer
{
	virtual void OnAttach() { }
	virtual void OnDetach() { }
	virtual void OnUpdate() { }

	bool OnKeyPress(Keg::KeyPressedEvent& e)
	{
		Keg::WindowsInput *wi = new Keg::WindowsInput();

		KEG_APP_TRACE("MouseX ({0}) MouseY ({1}) Is-ALT-Pressed({2}) Is-MB0-Pressed({3})", wi->GetMouseX(), wi->GetMouseY(),
																							wi->IsKeyPressed(Keg::Key::LeftAlt),
																							wi->IsMousePressed(Keg::Key::Button0));

		KEG_APP_TRACE("Key Pressed: ({0})", e.GetKey());
		return true;
	}

	virtual void OnEvent(Keg::Event& e) {
		Keg::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Keg::KeyPressedEvent>(std::bind(&TestLayer::OnKeyPress, this, std::placeholders::_1));


	}

#ifdef KEG_DEBUG
	std::string GetDebugName() { return "TestLayer"; }
#endif
};
#pragma once

#include "Keg.h"

class TestLayer : public Keg::Layer
{
	virtual void OnAttach()
	{
		std::vector<Keg::Vertex> vertices({
			Keg::Vertex(-1.0f, -0.5f, 0.0f,
					0.0f, 0.0f),
			Keg::Vertex(0.0f, -0.5f, 0.0f,
					1.0f, 0.0f),
			Keg::Vertex(-1.0f, 0.5f, 0.0f,
					0.0f, 1.0f),
			Keg::Vertex(0.0f, 0.5f, 0.0f,
					1.0f, 1.0f),
			});

		std::vector<uint32_t> elements({ 0, 1, 2,
										1, 2, 3 });

		std::vector<Keg::Vertex> vertices2({
			Keg::Vertex(0.0f, -0.5f, 0.0f,
					0.0f, 0.0f),
			Keg::Vertex(1.0f, -0.5f, 0.0f,
					1.0f, 0.0f),
			Keg::Vertex(0.0f, 0.5f, 0.0f,
					0.0f, 1.0f),
			Keg::Vertex(1.0f, 0.5f, 0.0f,
					1.0f, 1.0f),
			});

		std::vector<uint32_t> elements2({ 0, 1, 2,
										 1, 2, 3 });

		Keg::Renderer* renderer = Keg::RendererBuilder::GetInstance()->GetRenderer();
		// Loading a texture to TextureManager
		Keg::OpenGLTextureManager::GetInstance()->LoadTexture("container", std::string(std::string(KEG_ASSETS) + "/Textures/container.jpg").c_str());
		Keg::OpenGLTexture* t = Keg::OpenGLTextureManager::GetInstance()->GetTexture("container");

		Keg::DrawDetails d = renderer->CreateDrawable(vertices, elements);
		d.SetTexture(t);

		Keg::DrawDetails d1 = renderer->CreateDrawable(vertices2, elements2);
		d1.SetColor(1.0f, 1.0f, 0.0f);

		renderer->AddDrawable(d);
		renderer->AddDrawable(d1);
	}

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

		delete wi;
	}

	virtual void OnEvent(Keg::Event& e) {
		Keg::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Keg::KeyPressedEvent>(std::bind(&TestLayer::OnKeyPress, this, std::placeholders::_1));
	}

#ifdef KEG_DEBUG
	std::string GetDebugName() { return "TestLayer"; }
#endif

};
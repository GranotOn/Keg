#pragma once

#include "Keg.h"
#include <imgui.h>

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

		Keg::Renderer* renderer = Keg::RendererBuilder::GetInstance()->GetRenderer();
		// Loading a texture to TextureManager

		Keg::OpenGLTextureManager::GetInstance()->LoadTexture("container", std::string(std::string(KEG_ASSETS) + "/Textures/container.jpg").c_str());
		Keg::OpenGLTexture* t = Keg::OpenGLTextureManager::GetInstance()->GetTexture("container");


		Keg::Scene* scene = Keg::Scene::Create();
		auto e = scene->CreateEntity();

		Keg::TransformComponent tc;
		
		Keg::MeshComponent mesh = renderer->CreateMesh(vertices, elements);

		e.AddComponent(tc);
		e.AddComponent(mesh);
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

	virtual void OnEvent(Keg::Event& e) 
	{
		Keg::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Keg::KeyPressedEvent>(std::bind(&TestLayer::OnKeyPress, this, std::placeholders::_1));
	}

	virtual void OnImGuiUpdate()
	{
		static bool showDemo = true;
		//static float f[3] = { d->GetColor().x, d->GetColor().y, d->GetColor().z };
		//static float s[3] = { d->GetScale().x, d->GetScale().y, d->GetScale().z };
		//static float r[3] = { d->GetRotation().x, d->GetRotation().y, d->GetRotation().z };
		//d->SetColor(f[0], f[1], f[2]);
		//d->SetScale(s[0], s[1], s[2]);
		//d->SetRotate(r[0], r[1], r[2]);

		
		ImGui::Begin("Test");                          // Create a window called "Hello, world!" and append into it.
		ImGui::Text("Controlling an entity");							// Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &showDemo);						// Edit bools storing our window open/close state

		/*ImGui::SliderFloat3("Color", &f[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Scale", &s[0], 1.0f, 3.0f);
		ImGui::SliderFloat3("Rotation", &r[0], 0.0f, 1.0f);*/

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

#ifdef KEG_DEBUG
	std::string GetDebugName() { return "TestLayer"; }
#endif

};
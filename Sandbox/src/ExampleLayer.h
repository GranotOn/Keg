#pragma once

#include "Keg.h"
#include <imgui.h>


class TestLayer : public Keg::Layer
{
public:

	virtual void OnAttach()
	{
		std::vector<Keg::Vertex> vertices({
Keg::Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
Keg::Vertex(0.5f, -0.5f, -0.5f,  1.0f, 0.0f),
Keg::Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
Keg::Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
Keg::Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f),
Keg::Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
Keg::Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
Keg::Vertex(0.5f,  0.5f,  0.5f,  1.0f, 1.0f),
Keg::Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 1.0f),
Keg::Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
Keg::Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(-0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
Keg::Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
Keg::Vertex(-0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
Keg::Vertex(0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
Keg::Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(0.5f, -0.5f, -0.5f,  1.0f, 1.0f),
Keg::Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(0.5f, -0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(-0.5f, -0.5f,  0.5f,  0.0f, 0.0f),
Keg::Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
Keg::Vertex(0.5f,  0.5f, -0.5f,  1.0f, 1.0f),
Keg::Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(0.5f,  0.5f,  0.5f,  1.0f, 0.0f),
Keg::Vertex(-0.5f,  0.5f,  0.5f,  0.0f, 0.0f),
Keg::Vertex(-0.5f,  0.5f, -0.5f,  0.0f, 1.0f),
			});

		std::vector<uint32_t> elements({});

		Keg::Renderer* renderer = Keg::RendererBuilder::GetInstance()->GetRenderer();
		// Loading a texture to TextureManager

		Keg::OpenGLTextureManager::GetInstance()->LoadTexture("container", std::string(std::string(KEG_ASSETS) + "/Textures/container.jpg").c_str());
		Keg::OpenGLTexture* containerTexture = Keg::OpenGLTextureManager::GetInstance()->GetTexture("container");

		Keg::OpenGLVAO vao(vertices, elements);

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (int i = 0; i < 10; ++i)
		{
			auto e = m_Scene->CreateEntity();
			
			Keg::TransformComponent &tra = e.GetComponent<Keg::TransformComponent>();
			tra.Rotation = { 0.5f, 1.0f, 0.0f };
			tra.Translation = cubePositions[i];
			tra.RotationAngle = 20.0f * (float) i;

			Keg::ColorComponent& color = e.GetComponent<Keg::ColorComponent>();
			
			if (i < 3)
			{
				e.AddComponent<Keg::TextureComponent>(containerTexture);
			}
			else if (i < 6)
			{
				color.Color = glm::vec3(0.0f, 0.3f, 1.0f);
			}
			else
			{
				color.Color = glm::vec3(0.2f, 1.0f, 0.2f);
			}

			e.AddComponent<Keg::MeshComponent>(vao, static_cast<int>(elements.size()), static_cast<int>(vertices.size()));

		}

	}

	virtual void OnDetach() { }
	virtual void OnUpdate(Time &time)
	{
		constexpr auto SPEED = 10.0f;

		auto movement = (float) ((double)SPEED * time.deltaTime);

		Keg::WindowsInput* wi = new Keg::WindowsInput();

		if (wi->IsKeyPressed(Keg::Key::A))
		{
			Keg::TransformComponent& tc = m_Camera.GetComponent<Keg::TransformComponent>();
			Keg::CameraComponent& cc = m_Camera.GetComponent<Keg::CameraComponent>();
			cc.Target += glm::vec3(movement, 0.0f, 0.0f);
			tc.Translation += glm::vec3(movement, 0.0f, 0.0f);
		}
		if (wi->IsKeyPressed(Keg::Key::D))
		{
			Keg::TransformComponent& tc = m_Camera.GetComponent<Keg::TransformComponent>();
			Keg::CameraComponent& cc = m_Camera.GetComponent<Keg::CameraComponent>();
			cc.Target += glm::vec3(-movement, 0.0f, 0.0f);
			tc.Translation += glm::vec3(-movement, 0.0f, 0.0f);
		}
		if (wi->IsKeyPressed(Keg::Key::S))
		{
			Keg::TransformComponent& tc = m_Camera.GetComponent<Keg::TransformComponent>();
			Keg::CameraComponent& cc = m_Camera.GetComponent<Keg::CameraComponent>();
			cc.Target += glm::vec3(0.0f, 0.0f, -movement);
			tc.Translation += glm::vec3(0.0f, 0.0f, -movement);
		}
		if (wi->IsKeyPressed(Keg::Key::W))
		{
			Keg::TransformComponent& tc = m_Camera.GetComponent<Keg::TransformComponent>();
			Keg::CameraComponent& cc = m_Camera.GetComponent<Keg::CameraComponent>();
			cc.Target += glm::vec3(0.0f, 0.0f, movement);
			tc.Translation += glm::vec3(0.0f, 0.0f, movement);
		}
		
		delete wi;

		m_Scene->OnUpdate();
	
	
	}

	bool OnKeyPress(Keg::KeyPressedEvent& e)
	{
		/*Keg::WindowsInput *wi = new Keg::WindowsInput();

		KEG_APP_TRACE("MouseX ({0}) MouseY ({1}) Is-ALT-Pressed({2}) Is-MB0-Pressed({3})", wi->GetMouseX(), wi->GetMouseY(),
																							wi->IsKeyPressed(Keg::Key::LeftAlt),
																							wi->IsMousePressed(Keg::Key::Button0));

		KEG_APP_TRACE("Key Pressed: ({0})", e.GetKey());*/
		//delete wi;

		return true;
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

	TestLayer() : m_Scene(Keg::Scene::Create()), m_Camera(m_Scene->CreateEntity())
	{
		auto &tc = m_Camera.AddComponent<Keg::TransformComponent>();
		tc.Translation = { 0.0f, 0.0f, -10.0f };
		m_Camera.AddComponent<Keg::CameraComponent>();
	}

private:
	Keg::Scene* m_Scene;
	Keg::Entity m_Camera;

#ifdef KEG_DEBUG
	std::string GetDebugName() { return "TestLayer"; }
#endif

};
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
			
			if (i == 1)
			{
				m_DemoEntity = e;
			}

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

		Keg::Audio* audio = Keg::AudioBuilder::GetAudio();
		Keg::Effect* e1 = audio->AddEffect((std::string(KEG_ASSETS) + "/AudioFiles/sample.ogg").c_str());
		//e1->Play();

		Keg::Scene::Serialize(m_Scene);
		std::string c = (std::string(KEG_ASSETS) + "/Scenes/Scene.json");
		Keg::Scene::Deserialize(c.c_str());

	}

	virtual void OnDetach() { }
	virtual void OnUpdate(Time &time)
	{
		Keg::WindowsInput* wi = new Keg::WindowsInput();

		m_CameraController->OnCursorUpdate((float) wi->GetMouseX(), (float) wi->GetMouseY());
		
		if (wi->IsKeyPressed(Keg::Key::A))
			m_CameraController->MoveLeft(time);
		
		if (wi->IsKeyPressed(Keg::Key::D))
			m_CameraController->MoveRight(time);
		
		if (wi->IsKeyPressed(Keg::Key::S))
			m_CameraController->MoveBackward(time);
		
		if (wi->IsKeyPressed(Keg::Key::W))
			m_CameraController->MoveForward(time);
		
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
	
	bool OnCursorMovement(Keg::CursorMovedEvent& e)
	{
		//m_CameraController->OnCursorUpdate(e.GetXPosition(), e.GetYPosition());
		return true;
	}

	virtual void OnEvent(Keg::Event& e) 
	{
		Keg::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Keg::KeyPressedEvent>(std::bind(&TestLayer::OnKeyPress, this, std::placeholders::_1));
		dispatcher.Dispatch<Keg::CursorMovedEvent>(std::bind(&TestLayer::OnCursorMovement, this, std::placeholders::_1));
	}

	virtual void OnImGuiUpdate()
	{
		static bool showDemo = true;
		auto e = m_DemoEntity;
		Keg::TransformComponent& tc = e.GetComponent<Keg::TransformComponent>();


		//// View
		//HierarchyPanel.OnImGuiUpdate()
		//{
		//	// std::vector
		//	ImGui::EndImGui::Begin
		//	{

		//	}
		//	ImGui::End
		//}

		//auto ActiveEntity = HierarchyPanel.GetActiveEntity()

		//InspectorPanel.OnImGuiUpdate(ActiveEntity)
		//{
		//	ImGui::Begin
		//	{

		//	}
		//}



		if (showDemo)
		{
			ImGui::Begin("Test");                          // Create a window called "Hello, world!" and append into it.
			{
				ImGui::Text("Controlling an entity");							// Display some text (you can use a format strings too)
				ImGui::Text(m_DemoEntity.GetComponent<Keg::TagComponent>().Tag.c_str());
				ImGui::InputFloat3("Change Transform", &tc.Translation[0]);
				ImGui::InputFloat3("Change Scale", &tc.Scale[0]);
				ImGui::InputFloat3("Change Rotation", &tc.Rotation[0]);
				ImGui::Checkbox("Demo Window", &showDemo);						// Edit bools storing our window open/close state
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			ImGui::End();
		}
	}

	TestLayer() : m_Scene(Keg::Scene::Create()), m_DemoEntity(m_Scene->CreateEntity())
	{

		m_CameraController = new Keg::CameraController(m_Scene);
	}

private:
	Keg::Scene* m_Scene;
	Keg::CameraController* m_CameraController;
	Keg::Entity m_DemoEntity;

#ifdef KEG_DEBUG
	std::string GetDebugName() { return "TestLayer"; }
#endif

};
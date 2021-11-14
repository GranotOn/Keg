#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Renderer/Renderer.h"
#include "Core/Application/Application.h"

namespace Keg
{

	void Scene::OnUpdate()
	{

		/////////////////////
		// Rendering Entities
		/////////////////////
		Renderer* renderer = Application::GetInstance()->GetRenderer();


		auto cameras = m_Registery.view<TransformComponent, CameraComponent>();

		if (cameras.size_hint() == 1)
		{
			cameras.each([&renderer](TransformComponent& tc, CameraComponent& cc)
				{ // This should really only be 1 component
					glm::mat4 viewMatrix = cc.GetViewMatrix(tc.Translation);
					renderer->BeginRender(viewMatrix);
				});
		}
		else
		{
			renderer->BeginRender();
		}


		{
			auto view = m_Registery.view<TransformComponent, MeshComponent>();

			view.each([&renderer](TransformComponent& tc, MeshComponent& mc)
				{
					renderer->Render(tc, mc);
				});

		}

		renderer->EndRender();
	}

	Entity Scene::CreateEntity(std::string tag)
	{
		Entity entity = { this, m_Registery.create() };

		entity.AddComponent<TagComponent>(tag);
	
		return entity;
	}

	bool Scene::DeleteEntity(Entity entity)
	{
		m_Registery.release(entity.m_Handle);
		return !m_Registery.valid(entity.m_Handle);
	}

	Scene* Scene::Create()
	{
		return new Scene();
		return nullptr;
	}

	Scene::Scene(std::string name)
	{
		m_Tag = name;
	}

	Scene* Scene::Deserialize(char* file)
	{
		return new Scene();
	}
	bool Scene::Serialize(Scene* scene)
	{
		return false;
	}
	std::string Scene::SetName(std::string newName)
	{
		m_Tag = newName;
		return m_Tag;
	}
	std::string Scene::GetName()
	{
		return m_Tag;
	}
}
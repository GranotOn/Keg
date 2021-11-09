#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"

namespace Keg
{
	Entity Scene::CreateEntity(std::string tag)
	{
		Entity entity = { this, m_Registery.create() };

		//entity.AddComponent<TagComponent>(tag);
	
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
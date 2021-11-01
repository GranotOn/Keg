#include "Scene/Scene.h"
#include "Scene/Entity.h"

namespace Keg
{
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
	Scene Scene::Deserialize(char* file)
	{
		return Scene();
	}
	bool Scene::Serialize(Scene* scene)
	{
		return false;
	}
}
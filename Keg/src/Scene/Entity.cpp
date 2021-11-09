#include "Entity.h"
#include "Scene/Scene.h"

namespace Keg
{
	Entity::Entity(Scene* scene, entt::entity handle)
	{
		m_Scene = scene;
		m_Handle = handle;
	}


	template<typename T>
	T& Entity::GetComponent()
	{
		return m_Scene->m_Registery.get<T>(m_Handle);
	}

	template<typename T, typename ...Args>
	T& Entity::AddComponent(Args && ...args)
	{
		if (!HasComponent<T>)
		{
			m_Scene->m_Registery.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		return GetComponent<T>();
	}

	template<typename T>
	bool Entity::RemoveComponent()
	{
		if (HasComponent<T>)
		{
			m_Scene->m_Registery.erase<T>(m_Handle);
			return true;
		}

		return false;
	}

	template<typename T>
	bool Entity::HasComponent()
	{
		return !!m_Scene->m_Registery.get<T>(m_Handle);
	}
}
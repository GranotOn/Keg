#pragma once

#include <entt.hpp>

#include <string>

#include "Scene/Scene.h"
#include "Scene/Components.h"

namespace Keg
{
	class Scene;
	class Entity
	{
	public:
		Entity(Scene* scene, entt::entity handle);

		template <typename T>
		bool HasComponent()
		{
			T* t = m_Scene->m_Registery.try_get<T>(m_Handle);
			return !(t == nullptr);
		}

		template <typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registery.get<T>(m_Handle);
		}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (!HasComponent<T>())
			{
				m_Scene->m_Registery.emplace<T>(m_Handle, std::forward<Args>(args)...);
			}

			return GetComponent<T>();
		}

		template <typename T>
		bool RemoveComponent() 
		{
			if (HasComponent<T>)
			{
				m_Scene->m_Registery.erase<T>(m_Handle);
				return true;
			}

			return false;
		}

		inline entt::entity GetHandle() { return m_Handle; }

		
	private:
		entt::entity m_Handle;
		Scene* m_Scene;

		friend class Scene;
	};
}
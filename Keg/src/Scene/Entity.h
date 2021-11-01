#pragma once

#include <entt.hpp>

#include <string>

#include "Scene/Scene.h"
#include "Scene/Components.h"

namespace Keg
{
	class Entity
	{
	public:
		Entity(Scene* scene, entt::entity handle);

		template <typename T>
		T& GetComponent();

		template <typename T, typename... Args>
		T& AddComponent(Args&& ...args);

		template <typename T>
		bool RemoveComponent();

		template <typename T>
		bool HasComponent();
		

	private:
		entt::entity m_Handle;
		Scene* m_Scene;

		friend class Scene;
	};
}
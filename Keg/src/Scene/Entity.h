#pragma once

#include <entt.hpp>

#include <string>
#include "Scene/Components.h"

namespace Keg
{
	class Scene;
	class Entity
	{
	public:
		Entity(Scene* scene, entt::entity handle);

		template <typename T>
		T& GetComponent();

		void AddComponent(TransformComponent& tc);
		void AddComponent(MeshComponent& mc);

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
#pragma once

#include <entt.hpp>

#include <string>

namespace Keg
{
	class Entity;
	class Scene
	{
	public:
		Entity CreateEntity(std::string tag = "Entity");
		bool DeleteEntity(Entity entity);

		static Scene Deserialize(char* file);
		static bool Serialize(Scene* scene);

	private:
		Scene();

		entt::registry m_Registery;
		std::string m_Tag;

		friend class Entity;
	};
}

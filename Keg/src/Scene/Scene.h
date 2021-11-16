#pragma once

#include <entt.hpp>
#include <string>
#include <json.hpp>

namespace Keg
{
	class Entity;
	class Scene
	{
	public:
		Entity CreateEntity(std::string tag = "Entity");
		bool DeleteEntity(Entity entity);

		static Scene* Create();
		static Scene* Deserialize(char* file);
		static bool Serialize(Scene* scene);
		void OnUpdate();

		std::string SetName(std::string newName);
		std::string GetName();
		entt::registry* GetRegistery();

	private:
		Scene(std::string name = "Scene");

		entt::registry m_Registery;
		std::string m_Tag;
		std::string m_Path;
		friend class Entity;
	};
}

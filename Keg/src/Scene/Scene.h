#pragma once

#include <entt.hpp>

namespace Keg
{
	class Entity;
	class Scene
	{
	public:
		Entity CreateEntity(std::string tag = "Entity");
		bool DeleteEntity(Entity entity);

		static Scene* Create();
		static Scene* Deserialize(const char* file);
		static bool Serialize(Scene* scene);

		void OnUpdate();

		std::string SetName(std::string newName);
		std::string GetName();
		std::string GetPath();
		void SetPath(std::string newPath);
		entt::registry* GetRegistery();
		void SetRegistery(entt::registry* newRegistery);


	private:
		Scene(std::string name = "Scene");

		entt::registry m_Registery;
		std::string m_Tag;
		std::string m_Path;

		friend class Entity;
	};
}

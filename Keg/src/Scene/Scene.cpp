#include "stadx.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererBuilder.h"
#include "json.hpp"
#include <iostream>

namespace Keg
{

	void Scene::OnUpdate()
	{

		/////////////////////
		// Rendering Entities
		/////////////////////
		Renderer* renderer = RendererBuilder::GetInstance()->GetRenderer();


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
			auto view = m_Registery.view<MeshComponent>();

			for (auto entity : view)
			{
				// TODO: Ignore LightComponent, should be in a former rendering loop
				auto [color, transform, mesh] = m_Registery.get<ColorComponent, TransformComponent, MeshComponent>(entity);
				auto texture = m_Registery.try_get<TextureComponent>(entity);

				bool hasTexture = !!texture;

				if (texture)
					renderer->Render(transform, mesh, color, m_Registery.get<TextureComponent>(entity));
				
				else
					renderer->Render(transform, mesh, color);

			}
		}

		renderer->EndRender();
	}

	Entity Scene::CreateEntity(std::string tag)
	{
		Entity entity = { this, m_Registery.create() };

		/////////////////////
		// Default Components
		/////////////////////
		entity.AddComponent<TagComponent>(tag);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<ColorComponent>();

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

	Scene* Scene::Deserialize(const char* file)
	{
		Scene* scene = new Scene();
		std::string s;
		std::ifstream sceneFile;
		//	Open the file for read
		sceneFile.open(file, std::ios::in);
		if (!sceneFile) {
			KEG_APP_ERROR("Scene class: Deserialize: File not created!");
			return NULL;
		}
		nlohmann::json js;
		sceneFile >> js;
		std::string name = js.at("tag");
		scene->SetName(name);
		// one directory back
		std::string path = file;
		int index = path.find_last_of("/");
		path = path.substr(0, index);
		scene->SetPath(path);
		nlohmann::json jsEntities;
		jsEntities = js.at("entities");
		entt::registry registry;
		for (nlohmann::json::iterator it = jsEntities.begin(); it != jsEntities.end(); ++it) {
			nlohmann::json entity;
			entity = *it;
			for (nlohmann::json::iterator itEnt = entity.begin(); itEnt != entity.end(); ++itEnt) {
				nlohmann::json inEntity;
				inEntity = *itEnt;
				int size = inEntity.size();
				entt::entity entity = registry.create();
				for (int i = 0; i < size; i++) {
					if (inEntity[i].at("name") == "TagComponent") {
						registry.emplace<TagComponent>(entity, inEntity[i].at("tag"));
					}
					else if (inEntity[i].at("name") == "TransformComponent") {
						TransformComponent tra;
						tra.Rotation[0] = inEntity[i].at("rotation").at("0");
						tra.Rotation[1] = inEntity[i].at("rotation").at("1");
						tra.Rotation[2] = inEntity[i].at("rotation").at("2");
						tra.Translation[0] = inEntity[i].at("translation").at("0");
						tra.Translation[1] = inEntity[i].at("translation").at("1");
						tra.Translation[2] = inEntity[i].at("translation").at("2");
						tra.Scale[0] = inEntity[i].at("scale").at("0");
						tra.Scale[1] = inEntity[i].at("scale").at("1");
						tra.Scale[2] = inEntity[i].at("scale").at("2");
						registry.emplace<TransformComponent>(entity, tra);
					}
					//else if (inEntity[i].at("name") == "MeshComponent") {
					//    MeshComponent mesh;
					//    mesh.Elements = inEntity[i].at("elements");
					//    mesh.Vertices = inEntity[i].at("vertices");
					//    registry.emplace<MeshComponent>(entity, mesh);
					//}
					else if (inEntity[i].at("name") == "ColorComponent") {
						ColorComponent color;
						color.Alpha = inEntity[i].at("alpha");
						color.Color[0] = inEntity[i].at("color").at("0");
						color.Color[1] = inEntity[i].at("color").at("1");
						color.Color[2] = inEntity[i].at("color").at("2");
						registry.emplace<ColorComponent>(entity, color);
					}
					else if (inEntity[i].at("name") == "CameraComponent") {
						CameraComponent camera;
						camera.CameraFront[0] = inEntity[i].at("cameraFront").at("0");
						camera.CameraFront[1] = inEntity[i].at("cameraFront").at("1");
						camera.CameraFront[2] = inEntity[i].at("cameraFront").at("2");
						camera.CameraUp[0] = inEntity[i].at("cameraUp").at("0");
						camera.CameraUp[1] = inEntity[i].at("cameraUp").at("1");
						camera.CameraUp[2] = inEntity[i].at("cameraUp").at("2");
						registry.emplace<CameraComponent>(entity, camera);
					}
					/*else if (inEntity[i].at("name") == "TextureComponent") {
						TextureComponent text;
					}*/
				}
			}
			scene->SetRegistery(&registry);
			/////////////// print : how to get inner

			//auto t = registry.view<TransformComponent>();
			//t.each([](TransformComponent& tc)
			//    { // This should really only be 1 component
			//        std::cout << tc.Translation[0] << '\n';
			//    });
		}
		return scene;
	}

	bool Scene::Serialize(Scene* scene)
	{
		entt::registry* registry = scene->GetRegistery();
		std::string tag = scene->GetName();
		std::string path = scene->GetPath();

		nlohmann::json j;
		j["tag"] = tag;
		j["version"] = 1.0;
		j["entities"] = nlohmann::json::array();

		registry->each([&scene, &j](auto entity) {
			//  // create entity with scene
			Entity e(scene, entity);
			nlohmann::json ent;
			ent["components"] = nlohmann::json::array();

			//auto arr_comp = e.GetComponent();

			if (e.HasComponent<TagComponent>()) {
				nlohmann::json comp;
				TagComponent cc = e.GetComponent<TagComponent>();
				comp["name"] = "TagComponent";
				comp["tag"] = cc.Tag;
				ent["components"].emplace_back(comp);
			}
			if (e.HasComponent<TransformComponent>()) {
				nlohmann::json comp;
				TransformComponent cc = e.GetComponent<TransformComponent>();
				comp["name"] = "TransformComponent";

				nlohmann::json vec;
				vec["0"] = cc.Scale.x;
				vec["1"] = cc.Scale.y;
				vec["2"] = cc.Scale.z;
				comp["scale"] = vec;

				nlohmann::json vec1;
				vec1["0"] = cc.Rotation.x;
				vec1["1"] = cc.Rotation.y;
				vec1["2"] = cc.Rotation.z;
				comp["rotation"] = vec1;

				nlohmann::json vec2;
				vec2["0"] = cc.Translation.x;
				vec2["1"] = cc.Translation.y;
				vec2["2"] = cc.Translation.z;
				comp["translation"] = vec2;

				ent["components"].emplace_back(comp);
			}
			if (e.HasComponent<MeshComponent>()) {
				nlohmann::json comp;
				MeshComponent& cc = e.GetComponent<MeshComponent>();
				comp["name"] = "MeshComponent";
				comp["elements"] = cc.Elements;
				comp["vertices"] = cc.Vertices;
				ent["components"].emplace_back(comp);
			}
			if (e.HasComponent<CameraComponent>()) {
				nlohmann::json comp;
				CameraComponent cc = e.GetComponent<CameraComponent>();
				comp["name"] = "CameraComponent";

				nlohmann::json vec1;
				vec1["0"] = cc.CameraFront.x;
				vec1["1"] = cc.CameraFront.y;
				vec1["2"] = cc.CameraFront.z;
				comp["cameraFront"] = vec1;

				nlohmann::json vec2;
				vec2["0"] = cc.CameraUp.x;
				vec2["1"] = cc.CameraUp.y;
				vec2["2"] = cc.CameraUp.z;
				comp["cameraUp"] = vec2;

				ent["components"].emplace_back(comp);
			}
			if (e.HasComponent<ColorComponent>()) {
				nlohmann::json comp;
				ColorComponent cc = e.GetComponent<ColorComponent>();
				comp["name"] = "ColorComponent";

				nlohmann::json vec1;
				vec1["0"] = cc.Color.x;
				vec1["1"] = cc.Color.y;
				vec1["2"] = cc.Color.z;
				comp["color"] = vec1;

				comp["alpha"] = cc.Alpha;
				ent["components"].emplace_back(comp);
			}
			if (e.HasComponent<TextureComponent>()) {
				nlohmann::json comp;
				TextureComponent cc = e.GetComponent<TextureComponent>();
				comp["name"] = "TextureComponent";
				ent["components"].emplace_back(comp);
			}

			// Add component to components array
			j["entities"].emplace_back(ent);
			});
		std::string s = j.dump(4);

		// save json scene to file
		std::ofstream outSceneFile;
		outSceneFile.open((std::string(KEG_ASSETS) + "/Scenes/" + scene->GetName() + ".json").c_str());
		outSceneFile << s << std::endl;
		outSceneFile.close();
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
	std::string Scene::GetPath()
	{
		return m_Path;
	}
	entt::registry* Scene::GetRegistery()
	{
		return &m_Registery;
	}
	void Scene::SetPath(std::string newPath)
	{
		m_Path = newPath;
	}
	void Scene::SetRegistery(entt::registry* newRegistery)
	{
		//   m_Registery = newRegistery;
	}
}
#include "stadx.h"
#include <glad/glad.h>

#include "OpenGLRenderer.h"
#include "Core/Logger/Logger.h"

#include "Renderer/OpenGLTexture.h"
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"

#include "Core/Application/Application.h"


namespace Keg
{
	OpenGLRenderer* OpenGLRenderer::s_Renderer = nullptr;

	OpenGLRenderer* OpenGLRenderer::GetInstance()
	{
		if (s_Renderer == nullptr)
		{
			s_Renderer = new OpenGLRenderer();
		}

		return s_Renderer;
	}

	//////////////////////
	/// Rendering Sequence
	//////////////////////

	///////////////
	/// BeginRender
	///////////////

	void OpenGLRenderer::BeginRender(glm::mat4& view, Shader* shader)
	{
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Use();
		m_UsedShader = shader;

		/////////////////////
		/// 3D Space Uniforms
		/////////////////////
		glm::mat4 projection = m_Projection;

		int viewLocation = glGetUniformLocation(shader->GetID(), "view");
		int projectionLocation = glGetUniformLocation(shader->GetID(), "projection");

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void OpenGLRenderer::BeginRender(glm::mat4 &view)
	{
		BeginRender(view, GetShader(RENDERER_LIGHTSOURCE_SHADER));
	}


	void OpenGLRenderer::BeginRender()
	{
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		BeginRender(view);
	}


	/////////////
	/// EndRender
	/////////////
	void OpenGLRenderer::EndRender()
	{

	}

	//////////
	/// Render
	//////////
	void OpenGLRenderer::Draw(entt::registry& registery, entt::entity& entity, Shader* shader)
	{
		auto [transform, mesh] = registery.get<TransformComponent, MeshComponent>(entity);
		auto texture = registery.try_get<TextureComponent>(entity);
		auto material = registery.try_get<MaterialComponent>(entity);
		bool hasMaterial = !!material;
		bool hasTexture = !!texture;

		if (!hasMaterial)
			material = new MaterialComponent();


		shader->SetVec3("material.ambient", material->ambient.x, material->ambient.y, material->ambient.z);
		shader->SetVec3("material.diffuse", material->diffuse.x, material->diffuse.y, material->diffuse.z);
		shader->SetVec3("material.specular", material->specular.x, material->specular.y, material->specular.z);
		shader->SetFloat("material.shininess", material->shininess * 100);

		int modelLocation = glGetUniformLocation(shader->GetID(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transform.GetTransform()));

		OpenGLVAO vao = mesh.VAO;

		int textureSampleLocation = glGetUniformLocation(shader->GetID(), "hasTexture");
		glUniform1i(textureSampleLocation, (hasTexture ? 1 : 0));

		if (hasTexture)
			texture->Texture->Bind();

		vao.Bind();

		int n_Elements = mesh.Elements;

		if (n_Elements > 0)
		{
			glDrawElements(GL_TRIANGLES, n_Elements, GL_UNSIGNED_INT, nullptr);
		}

		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mesh.Vertices);
		}

		if (hasTexture)
			texture->Texture->UnBind();

		vao.UnBind();
	}

	void OpenGLRenderer::Render(entt::registry& registery)
	{
		Shader* shader = m_UsedShader;
		Shader* defaultShader = GetShader(RENDERER_DEFAULT_SHADER);

		auto LightView = registery.view<LightComponent>();
		auto CameraView = registery.view<CameraComponent>();
		auto view = registery.view<MeshComponent>();
		
		shader->Use();
		int viewPositionLocation = glGetUniformLocation(shader->GetID(), "viewPos");

		{
			for (auto entity : CameraView)
			{
				auto& cc = registery.get<CameraComponent>(entity);
				auto& tc = registery.get<TransformComponent>(entity);

				if (cc.IsMainCamera)
				{
					glm::vec3 trans = tc.Translation;
					glUniform3f(viewPositionLocation, trans.x, trans.y, trans.z);
				}
			}
		}

		{
			// Calculate Lights
			for (auto entity : LightView)
			{
				auto &lightComponent = registery.get<LightComponent>(entity);
				auto &transformComponent = registery.get<TransformComponent>(entity);
				glm::vec3 color = lightComponent.LightColor;
				glm::vec3 pos = transformComponent.Translation;
				glm::vec3 ambient = lightComponent.ambient;
				glm::vec3 diffuse = lightComponent.diffuse;
				glm::vec3 specular = lightComponent.specular;
				shader->SetVec3("light.ambient", ambient.x, ambient.y, ambient.z);
				shader->SetVec3("light.diffuse", diffuse.x, diffuse.y, diffuse.z);
				shader->SetVec3("light.specular", specular.x, specular.y, specular.z);
				shader->SetVec3("light.position", pos.x, pos.y, pos.z);
				shader->SetVec3("LightColor", color.x, color.y, color.z);
			}

			for (auto entity : view)
			{
				// Pass on light components
				auto lightComponent = registery.try_get<LightComponent>(entity);
				bool hasLightComponent = !!lightComponent;

				if (hasLightComponent)
					continue;

				Draw(registery, entity, shader);
			}
		}

		// Render Light Sources
		{
			for (auto entity : LightView)
			{
				shader->SetVec3("LightColor", 1.0f, 1.0f, 1.0f);
				shader->SetVec3("light.ambient", 1.0f, 1.0f, 1.0f);
				shader->SetVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
				shader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
				Draw(registery, entity, shader);
			}
		}
	}
	
	void OpenGLRenderer::Init(void* glfwGetProcAddress)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			KEG_ENGINE_ERROR("glad load glfw proc in OpenGLRenderer.cpp");
		}

		else
		{
			KEG_ENGINE_TRACE("gladLoadGLLoader succesfull");
			KEG_ENGINE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
		}

		glEnable(GL_DEPTH_TEST);

		//////////
		// Shaders
		//////////
		AddShader(RENDERER_DEFAULT_SHADER, std::string(KEG_ASSETS) + "/Shaders/RegularShader/4.6.shader.vs", std::string(KEG_ASSETS) + "/Shaders/RegularShader/4.6.shader.fs");
		AddShader(RENDERER_LIGHTSOURCE_SHADER, std::string(KEG_ASSETS) + "/Shaders/LightSourceShader/4.6.shader.vs", std::string(KEG_ASSETS) + "/Shaders/LightSourceShader/4.6.shader.fs");
	
		/////////////
		// Properties
		/////////////
		m_FOV = 45.0;
		
		Window* w = Application::GetInstance()->GetWindow();
		int width = w->GetWidth();
		int height = w->GetHeight();

		UpdateProjection(m_FOV, width, height, RENDERER_NEAR_PLANE, RENDERER_FAR_PLANE);
	}

	void OpenGLRenderer::UpdateProjection(float fov, int width, int height, float nearPlane, float farPlane)
	{
		m_Projection = glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane);
	}


	void OpenGLRenderer::AddShader(const std::string &name, const std::string &vs, const std::string &fs)
	{
		Shader *s = new Shader(vs.c_str(), fs.c_str());

		if (s->GetID() == -1)
		{
			KEG_ENGINE_ERROR("OpenGLRenderer::AddShader : Can't add shader because can't load shader correctly");
			return;
		}

		AddShader(name, s);
	}

	void OpenGLRenderer::AddShader(const std::string &name, Shader *s)
	{
		m_Shaders.insert_or_assign(name, s);
	}

	void OpenGLRenderer::RemoveShader(const std::string& name)
	{
		KEG_ENGINE_INFO("Removing Shader: {0}", name);
		m_Shaders.erase(name);
	}

	Shader* OpenGLRenderer::GetShader(const std::string& name)
	{
		auto it = m_Shaders.find(name);

		if (it == m_Shaders.end())
		{
			return nullptr;
		}
		else
		{
			return it->second;
		}
	}

	void OpenGLRenderer::Shutdown()
	{
		for (auto it : m_Shaders)
		{
			delete it.second;
		}
	}

	void OpenGLRenderer::OnViewportChange(int width, int height)
	{
		glViewport(0, 0, (GLsizei) width, (GLsizei) height);
		UpdateProjection(m_FOV, width, height, RENDERER_NEAR_PLANE, RENDERER_FAR_PLANE);
	}

	void OpenGLRenderer::SetFOV(float fov)
	{
		m_FOV = fov > 45 && fov < 121 ? fov : m_FOV;
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		Shutdown();
	}
}
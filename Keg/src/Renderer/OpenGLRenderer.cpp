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
		BeginRender(view, GetShader(RENDERER_DEFAULT_SHADER));
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

	void OpenGLRenderer::Render(TransformComponent& transformComponent, MeshComponent& meshComponent,
		ColorComponent& colorComponent, TextureComponent& textureComponent)
	{
		Shader* shader = m_UsedShader;

		// Color
		int colorLocation = glGetUniformLocation(shader->GetID(), "Color");
		glUniform4f(colorLocation, colorComponent.Color.x, colorComponent.Color.y, colorComponent.Color.z, colorComponent.Alpha);

		int modelLocation = glGetUniformLocation(shader->GetID(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transformComponent.GetTransform()));

		OpenGLVAO vao = meshComponent.VAO;

		int textureSampleLocation = glGetUniformLocation(shader->GetID(), "hasTexture");
		glUniform1i(textureSampleLocation, 1);

		OpenGLTexture* tex = textureComponent.Texture;
		tex->Bind();

		vao.Bind();

		int n_Elements = meshComponent.Elements;

		if (n_Elements > 0)
		{
			glDrawElements(GL_TRIANGLES, n_Elements, GL_UNSIGNED_INT, nullptr);
		}

		else
		{
			glDrawArrays(GL_TRIANGLES, 0, meshComponent.Vertices);
		}

		tex->UnBind();
		vao.UnBind();

	}


	void OpenGLRenderer::Render(TransformComponent& transformComponent, MeshComponent& meshComponent,
		ColorComponent& colorComponent)
	{

		Shader* shader = m_UsedShader;
		// Color
		int colorLocation = glGetUniformLocation(shader->GetID(), "Color");
		glUniform4f(colorLocation, colorComponent.Color.x, colorComponent.Color.y, colorComponent.Color.z, colorComponent.Alpha);

		int modelLocation = glGetUniformLocation(shader->GetID(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transformComponent.GetTransform()));
	
		OpenGLVAO vao = meshComponent.VAO;

		int textureSampleLocation = glGetUniformLocation(shader->GetID(), "hasTexture");
		glUniform1i(textureSampleLocation, 0);

		vao.Bind();

		int n_Elements = meshComponent.Elements;

		if (n_Elements > 0)
		{
			glDrawElements(GL_TRIANGLES, n_Elements, GL_UNSIGNED_INT, nullptr);
		}

		else
		{
			glDrawArrays(GL_TRIANGLES, 0, meshComponent.Vertices);
		}

		vao.UnBind();
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
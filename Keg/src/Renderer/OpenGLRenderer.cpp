#include <string>
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

	void OpenGLRenderer::BeginRender()
	{
		glClearColor(0.079f, 0.079f, 0.079f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		Shader* CC = GetShader(RENDERER_SHADER_COLOR);
		m_Shader = CC;
		CC->Use();

		/////////////////////
		/// 3D Space Uniforms
		/////////////////////
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = m_Projection;


		int viewLocation = glGetUniformLocation(CC->GetID(), "view");
		int projectionLocation = glGetUniformLocation(CC->GetID(), "projection");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void OpenGLRenderer::EndRender()
	{

	}

	void OpenGLRenderer::Render(TransformComponent& transformComponent, MeshComponent& meshComponent)
	{
		// Color
		int colorLocation = glGetUniformLocation(m_Shader->GetID(), "Color");
		glUniform4f(colorLocation, 1.0f, 0.0f, 0.0f, 1.0f);

		int modelLocation = glGetUniformLocation(m_Shader->GetID(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transformComponent.GetTransform()));
	
		OpenGLVAO vao = meshComponent.VAO;

		//OpenGLTexture* tex = drawable->GetTexture();

		// To indicate if a texture exists or not
		/*int textureSampleLocation = glGetUniformLocation(CC->GetID(), "hasTexture");

		if (tex)
		{
			tex->Bind();
			glUniform1i(textureSampleLocation, 1);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			glUniform1i(textureSampleLocation, 0);
		}*/

		vao.Bind();

		glDrawElements(GL_TRIANGLES, meshComponent.Elements, GL_UNSIGNED_INT, nullptr);

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

		//////////
		// Shaders
		//////////
		AddShader(RENDERER_SHADER_COLOR, std::string(KEG_ASSETS) + "/Shaders/4.6.shader.vs", std::string(KEG_ASSETS) + "/Shaders/4.6.shader.fs");
	
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

	OpenGLVAO OpenGLRenderer::CreateVAO(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
	{
		GLuint VBO, EBO;
		OpenGLVAO vao;

		vao.Bind();

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint32_t), elements.data(), GL_STATIC_DRAW);


		// Attribs linking:
		// Position attribute
		vao.LinkAttrib(0, 3, GL_FLOAT, sizeof(Vertex), 0);
		// Texture attribute
		vao.LinkAttrib(1, 2, GL_FLOAT, sizeof(Vertex), 3 * sizeof(float));
		
		return vao;
	}

	MeshComponent OpenGLRenderer::CreateMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
	{
		OpenGLVAO VAO = CreateVAO(vertices, elements);

		MeshComponent m(vertices, VAO, static_cast<int>(elements.size()));
		return m;
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
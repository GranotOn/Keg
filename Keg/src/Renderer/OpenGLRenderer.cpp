#include <string>
#include <glad/glad.h>

#include "OpenGLRenderer.h"
#include "Core/Logger/Logger.h"

#include "Renderer/OpenGLTexture.h"
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"


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
	void OpenGLRenderer::Update()
	{
		/* Render here */
		glClearColor(0.079f, 0.079f, 0.079f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		for (auto& drawable : m_Drawables)
		{

			Shader* CC = GetShader(RENDERER_SHADER_COLOR);

			// ----------
			// Color Uniform
			// ----------
			int colorLocation = glGetUniformLocation(CC->GetID(), "Color");
			CC->Use();
			glUniform4f(colorLocation, drawable->GetColor().x, 
						drawable->GetColor().y, drawable->GetColor().z, 1.0f);


			OpenGLVAO vao = drawable->GetVAO();

			OpenGLTexture* tex = drawable->GetTexture();

			// To indicate if a texture exists or not
			int textureSampleLocation = glGetUniformLocation(CC->GetID(), "textureSample");

			if (tex)
			{
				tex->Bind();
				glUniform1i(textureSampleLocation, 1);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(textureSampleLocation, 0);
			}
			
			vao.Bind();

			glDrawElements(GL_TRIANGLES, drawable->GetElementsCount(), GL_UNSIGNED_INT, nullptr);

			vao.UnBind();
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

		// Shader Init
		AddShader(RENDERER_SHADER_COLOR, std::string(KEG_ASSETS) + "/Shaders/4.6.shader.vs", std::string(KEG_ASSETS) + "/Shaders/4.6.shader.fs");
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

	DrawDetails* OpenGLRenderer::CreateDrawable(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
	{
		OpenGLVAO VAO = CreateVAO(vertices, elements);
		return new DrawDetails(vertices, VAO, static_cast<uint32_t>(elements.size()));
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

	void OpenGLRenderer::AddDrawable(DrawDetails *d)
	{
		m_Drawables.push_back(d);
	}

	void OpenGLRenderer::Shutdown()
	{
		for (auto it : m_Shaders)
		{
			delete it.second;
		}
	}

	OpenGLRenderer::~OpenGLRenderer() 
	{
		Shutdown();
	}
}
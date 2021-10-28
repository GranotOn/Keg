#pragma once

#include <map>
#include <vector>
#include <string>
#include "Renderer/Renderer.h"
#include "Renderer/DrawDetails.h"
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffers/OpenGLVAO.h"

namespace Keg
{
	class OpenGLRenderer : public Renderer
	{
	public:

		static OpenGLRenderer* GetInstance();

		virtual void Update();
		virtual void Init(void* glfwGetProcAddress);
		virtual void Shutdown();

		virtual void AddDrawable(DrawDetails& d);
		virtual DrawDetails CreateDrawable(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

		virtual void AddShader(const std::string& name, const std::string& vs, const std::string& fs);
		virtual void AddShader(const std::string& name, Shader* s);
		virtual void RemoveShader(const std::string& name);
		virtual Shader* GetShader(const std::string& name);

		~OpenGLRenderer();

	private:
		OpenGLRenderer() = default;
		std::vector<DrawDetails> m_Drawables;
		std::map<std::string, Shader*> m_Shaders;
		static OpenGLRenderer* s_Renderer;
		
	private:
		OpenGLVAO CreateVAO(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);
	};
}
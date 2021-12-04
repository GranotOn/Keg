#pragma once

#include <map>
#include <vector>
#include <string>
#include "Renderer/Renderer.h"
#include "Renderer/DrawDetails.h"
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffers/OpenGLVAO.h"

#include "Core/Logger/Logger.h"


namespace Keg
{
	class OpenGLRenderer : public Renderer
	{
	public:
		static OpenGLRenderer* GetInstance();

		virtual void Init(void* glfwGetProcAddress);
		virtual void Shutdown();

		virtual void OnViewportChange(int width, int height);
		virtual void SetFOV(float fov);

		virtual void AddShader(const std::string& name, const std::string& vs, const std::string& fs);
		virtual void AddShader(const std::string& name, Shader* s);
		virtual void RemoveShader(const std::string& name);
		virtual Shader* GetShader(const std::string& name);

		virtual void BeginRender();
		virtual void BeginRender(glm::mat4& viewMatrix);
		virtual void EndRender();

		virtual void Render(TransformComponent &transformComponent, MeshComponent &meshComponent,
			ColorComponent& colorComponent);
		virtual void Render(TransformComponent& transformComponent, MeshComponent& meshComponent,
			ColorComponent& colorComponent, TextureComponent& textureComponent);

		~OpenGLRenderer();
	private:
		OpenGLRenderer()
		{
			m_FOV = RENDERER_FOV;
			m_Projection = glm::mat4(1.0f);
			m_UsedShader = RENDERER_DEFAULT_SHADER;
		}

		std::map<std::string, Shader*> m_Shaders;
		std::string m_UsedShader;
		static OpenGLRenderer* s_Renderer;

		float m_FOV;
		glm::mat4 m_Projection;
		
	private:
		virtual void UpdateProjection(float fov, int width, int height, float nearPlan, float farPlane);
	};
}
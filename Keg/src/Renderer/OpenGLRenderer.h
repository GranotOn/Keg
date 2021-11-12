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

		virtual MeshComponent CreateMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

		virtual void AddShader(const std::string& name, const std::string& vs, const std::string& fs);
		virtual void AddShader(const std::string& name, Shader* s);
		virtual void RemoveShader(const std::string& name);
		virtual Shader* GetShader(const std::string& name);

		virtual void BeginRender();
		virtual void EndRender();
		virtual void Render(TransformComponent &transformComponent, MeshComponent &meshComponent);

		~OpenGLRenderer();

	private:
		OpenGLRenderer() = default;
		std::map<std::string, Shader*> m_Shaders;
		Shader* m_Shader;
		static OpenGLRenderer* s_Renderer;

		float m_FOV;
		glm::mat4 m_Projection;
		
	private:
		virtual void UpdateProjection(float fov, int width, int height, float nearPlan, float farPlane);
		OpenGLVAO CreateVAO(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);
	};
}
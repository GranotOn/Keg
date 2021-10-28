#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <memory>
#include <vector>

#include "Renderer/OpenGLTexture.h"
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffers/OpenGLVAO.h"

namespace Keg
{
	class DrawDetails
	{
	public:
		DrawDetails(std::vector<Vertex>& vertices, OpenGLVAO vao, GLuint elements) : 
			m_Vertices(vertices), m_VAO(vao), m_Elements(elements)
		{
			m_Color = { 1.0, 1.0, 1.0 };
			m_Texture = nullptr;
		};

		~DrawDetails();

		virtual std::vector<Vertex> GetVertices();
		virtual GLuint GetElementsCount();

		inline glm::vec3 GetColor() { return m_Color; }
		inline void SetColor(glm::vec3& v) { m_Color = v; }
		inline void SetColor(float r, float g, float b) { m_Color = glm::vec3(r, g, b); }

		inline void SetTexture(OpenGLTexture *tex) { m_Texture = tex; }
		inline void SetTexture(const char* texLocation) { m_Texture = new OpenGLTexture(texLocation); }
		inline OpenGLTexture* GetTexture() { return m_Texture; }

		inline OpenGLVAO GetVAO() { return m_VAO; };

	private:
		OpenGLVAO m_VAO;

		std::vector<Vertex>& m_Vertices;
		GLuint m_Elements;
		OpenGLTexture* m_Texture;

		glm::vec3 m_Color;

		
	};
}
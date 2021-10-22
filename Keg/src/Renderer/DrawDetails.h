#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm.hpp>

#include <Renderer/Vertex.h>
#include <Renderer/Shader.h>
#include <Renderer/Buffers/OpenGLVAO.h>

namespace Keg
{
	class DrawDetails
	{
	public:
		DrawDetails(std::vector<Vertex>& vertices, OpenGLVAO vao, GLuint elements) : 
			m_Vertices(vertices), m_VAO(vao), m_Elements(elements)
		{
			m_Color = glm::vec3(1.0, 1.0, 1.0);
		};
		~DrawDetails();

		virtual std::vector<Vertex> GetVertices();
		virtual GLuint GetElementsCount();

		inline glm::vec3 GetColor() { return m_Color; }
		inline void SetColor(glm::vec3& v) { m_Color = v; }
		inline void SetColor(float r, float g, float b) { m_Color = glm::vec3(r, g, b); }

		inline OpenGLVAO GetVAO() { return m_VAO; };

	private:
		OpenGLVAO m_VAO;

		std::vector<Vertex>& m_Vertices;
		GLuint m_Elements;

		glm::vec3 m_Color;

		
	};
}
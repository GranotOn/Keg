#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
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
			m_Scale = { 1.0f, 1.0f, 1.0f };
			m_Rotate = { 0.0f, 0.0f, 1.0f };
			m_Transform = glm::mat4(1.0f);
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

		inline void SetRotate(float x, float y, float z) { m_Rotate = glm::vec3(x, y, z); }
		inline void SetRotate(glm::vec3& v) { m_Rotate = v; }
		
		inline void SetScale(float x, float y, float z) { m_Scale = glm::vec3(x, y, z); }
		inline void SetScale(glm::vec3 &v) { m_Scale = v; }

		inline glm::vec3 GetRotation() { return m_Rotate; }
		inline glm::vec3 GetScale() { return m_Scale; }

		inline glm::mat4 GetTransform() { UpdateTransform(); return m_Transform; }

		inline OpenGLVAO GetVAO() { return m_VAO; };

	private:
		inline void UpdateTransform()
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::rotate(transform, glm::radians(1.0f), m_Rotate);
			transform = glm::scale(transform, m_Scale);

			m_Transform = transform;
		}

	private:
		OpenGLVAO m_VAO;

		std::vector<Vertex>& m_Vertices;
		GLuint m_Elements;
		OpenGLTexture* m_Texture;

		glm::vec3 m_Color;
		glm::vec3 m_Rotate;
		glm::vec3 m_Scale;
		glm::mat4 m_Transform;

		
	};
}
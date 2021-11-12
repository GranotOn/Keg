#pragma once

#include "Renderer/Vertex.h"
#include "Renderer/Buffers/OpenGLVAO.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>


namespace Keg
{
	struct TagComponent
	{
		TagComponent(const std::string& tag = "Entity") : Tag(tag) {}
		TagComponent(const TagComponent& o) = default;

		std::string Tag;
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(TransformComponent&&) = default;
		TransformComponent& operator=(const TransformComponent&) = default;
		TransformComponent& operator=(TransformComponent&&) = default;
		virtual ~TransformComponent() = default;
		
		glm::mat4 GetTransform()
		{ // Returns model matrix

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::rotate(transform, glm::radians(-55.0f), Rotation);
			transform = glm::scale(transform, Scale);

			return transform;
		}
	};

	struct MeshComponent
	{
		std::vector<Vertex>& Vertices;
		OpenGLVAO VAO;
		int Elements;

		MeshComponent(std::vector<Vertex>& vertices, OpenGLVAO &vao, int elements)
			: VAO(vao), Vertices(vertices), Elements(elements)
		{}

		MeshComponent(MeshComponent&&) = default;
		MeshComponent(const MeshComponent&) = delete;
		MeshComponent& operator=(const MeshComponent&) = delete;
		MeshComponent& operator=(MeshComponent&&) = default;
	};
}
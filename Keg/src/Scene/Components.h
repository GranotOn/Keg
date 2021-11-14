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
		
		float RotationAngle = 0.0f;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(TransformComponent&&) = default;
		TransformComponent& operator=(const TransformComponent&) = default;
		TransformComponent& operator=(TransformComponent&&) = default;
		
		glm::mat4 GetTransform()
		{ // Returns model matrix

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, Translation);
			transform = glm::rotate(transform, glm::radians(RotationAngle), Rotation);
			transform = glm::scale(transform, Scale);

			return transform;
		}
	};

	struct MeshComponent
	{
		OpenGLVAO VAO;
		int Elements;
		int Vertices;

		MeshComponent(OpenGLVAO& v, int elements, int vertices) : VAO(v), Elements(elements), Vertices(vertices) {}

		MeshComponent(MeshComponent&&) = default;
		MeshComponent(const MeshComponent&) = delete;
		MeshComponent& operator=(const MeshComponent&) = delete;
		MeshComponent& operator=(MeshComponent&&) = default;
	};

	struct CameraComponent
	{
		glm::vec3 Target = { 0.0f, 0.0f, 0.0f };

		inline glm::vec3 GetDirection(glm::vec3& position) { return glm::normalize(position - Target); }
		inline glm::vec3 GetRightVector(glm::vec3& direction) { return glm::normalize(glm::cross({0.0f, 1.0f, 0.0f}, direction)); }
		inline glm::vec3 GetUpVector(glm::vec3& direction, glm::vec3& rightVector) { return glm::cross(direction, rightVector); }
		
		inline glm::mat4 GetViewMatrix(glm::vec3& position)
		{
			glm::vec3 direction = GetDirection(position);
			glm::vec3 rightVector = GetRightVector(direction);
			glm::vec3 upVector = GetUpVector(direction, rightVector);
			
			return glm::lookAt(position, Target, upVector);
		}

		CameraComponent() {}
	};
}
#pragma once

#include "Renderer/Vertex.h"
#include "Renderer/Buffers/OpenGLVAO.h"
#include "Renderer/OpenGLTexture.h"

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

	struct LightComponent
	{
		glm::vec3 LightColor = { 1.0f, 1.0f, 1.0f };
		float Intensity = 1.0f;
	};


	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.5f, 1.0f, 0.0f };
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
		MeshComponent(const MeshComponent&) = default;
		MeshComponent& operator=(const MeshComponent&) = default;
		MeshComponent& operator=(MeshComponent&&) = default;
	};

	struct CameraComponent
	{
		glm::vec3 CameraFront = { 0.0f, 0.0f, 0.0f };
		glm::vec3 CameraUp = { 0.0f, 1.0f, 0.0f };
		bool IsMainCamera = false;

		inline glm::mat4 GetViewMatrix(glm::vec3& position)
		{
			return glm::lookAt(position, CameraFront + position, CameraUp);
		}

		CameraComponent() {}
	};

	struct ColorComponent
	{
		glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
		float Alpha = 1.0f;

		ColorComponent() {}
	};

	struct TextureComponent
	{
		OpenGLTexture* Texture;

		TextureComponent(OpenGLTexture *texture) : Texture(texture) {}
	};
}
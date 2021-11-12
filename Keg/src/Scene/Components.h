#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>


namespace Keg
{
	struct TagComponent
	{
		TagComponent(const std::string& tag = "Entity") : Tag(tag) {}

		std::string Tag;
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		
		glm::mat4 GetTransform()
		{ // Returns model matrix

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::rotate(transform, glm::radians(90.0f), Rotation);
			transform = glm::scale(transform, Scale);

			return transform;
		}
	};
}
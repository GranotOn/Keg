#include "stadx.h"

#include "CameraController.h"
#include "Scene/Components.h"

namespace Keg
{
	void CameraController::MoveForward(double& deltaTime)
	{
		float movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		tc.Translation += cc.CameraFront * movement;
	}

	void CameraController::MoveBackward(double& deltaTime)
	{
		float movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		tc.Translation -= cc.CameraFront * movement;
	}

	void CameraController::MoveLeft(double& deltaTime)
	{
		float movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		tc.Translation -= glm::normalize(glm::cross(cc.CameraFront, cc.CameraUp)) * movement;
	}
	
	void CameraController::MoveRight(double& deltaTime)
	{
		float movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		tc.Translation += glm::normalize(glm::cross(cc.CameraFront, cc.CameraUp)) * movement;
	}
	void CameraController::OnCursorUpdate(float x, float y)
	{
		if (m_FirstMouseMovement)
		{
			m_LastMouseX = x;
			m_LastMouseY = y;
			m_FirstMouseMovement = false;
		}

		float xDelta = (x - m_LastMouseX) * m_MouseSensitivity;
		float yDelta = (m_LastMouseY - y) * m_MouseSensitivity;
		m_LastMouseX = x;
		m_LastMouseY = y;
		
		m_Yaw += xDelta;
		m_Pitch += yDelta;

		// Pitch boundries
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;

		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		CameraComponent& cc = m_CameraEntity.GetComponent<CameraComponent>();
		cc.CameraFront = direction;
	}
}
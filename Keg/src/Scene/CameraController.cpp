#include "stadx.h"

#include "CameraController.h"
#include "Scene/Components.h"

namespace Keg
{
	void CameraController::MoveForward(double& deltaTime)
	{
		double movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		cc.Target += glm::vec3(0.0f, 0.0f, movement);
		tc.Translation += glm::vec3(0.0f, 0.0f, movement);
	}

	void CameraController::MoveBackward(double& deltaTime)
	{
		double movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		cc.Target += glm::vec3(0.0f, 0.0f, -movement);
		tc.Translation += glm::vec3(0.0f, 0.0f, -movement);
	}

	void CameraController::MoveLeft(double& deltaTime)
	{
		double movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		cc.Target += glm::vec3(movement, 0.0f, 0.0f);
		tc.Translation += glm::vec3(movement, 0.0f, 0.0f);
	}
	
	void CameraController::MoveRight(double& deltaTime)
	{
		double movement = (double)m_CameraSpeed * deltaTime;
		Keg::TransformComponent& tc = m_CameraEntity.GetComponent<Keg::TransformComponent>();
		Keg::CameraComponent& cc = m_CameraEntity.GetComponent<Keg::CameraComponent>();
		cc.Target += glm::vec3(-movement, 0.0f, 0.0f);
		tc.Translation += glm::vec3(-movement, 0.0f, 0.0f);
	}
}
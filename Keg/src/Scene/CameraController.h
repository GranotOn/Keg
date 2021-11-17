#pragma once
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Core/Application/Time.h"

namespace Keg
{
	class CameraController
	{
	public:
		CameraController(Scene& scene) : m_CameraEntity(scene.CreateEntity())
		{
			auto& tc = m_CameraEntity.AddComponent<Keg::TransformComponent>();
			m_CameraEntity.AddComponent<Keg::CameraComponent>();
			tc.Translation = { 0.0f, 0.0f, -10.0f };
		}

		CameraController(Scene* scene) : m_CameraEntity(scene->CreateEntity())
		{
			auto& tc = m_CameraEntity.AddComponent<Keg::TransformComponent>();
			m_CameraEntity.AddComponent<Keg::CameraComponent>();
			tc.Translation = { 0.0f, 0.0f, -10.0f };
		}

		CameraController(Entity& e) : m_CameraEntity(e) {};

		inline void SetEntity(Entity& entity) { m_CameraEntity = entity; }
		inline Entity GetEntity() { return m_CameraEntity; }

		inline float GetMouseSensitivity() { return m_MouseSensitivity; }
		inline void SetMouseSensitivity(float& sensitivity) { m_MouseSensitivity = sensitivity; }

		inline float GetCameraSpeed() { return m_CameraSpeed; }
		inline void SetCameraSpeed(float& speed) { m_CameraSpeed = speed; }

		virtual void MoveForward(double& deltaTime);
		virtual inline void MoveForward(Time& time) { MoveForward(time.deltaTime); }

		virtual void MoveBackward(double& deltaTime);
		virtual inline void MoveBackward(Time& time) { MoveBackward(time.deltaTime); }

		virtual void MoveLeft(double& deltaTime);
		virtual inline void MoveLeft(Time& time) { MoveLeft(time.deltaTime); }

		virtual void MoveRight(double& deltaTime);
		virtual inline void MoveRight(Time& time) { MoveRight(time.deltaTime); }

	private:
		Entity m_CameraEntity;
		float m_MouseSensitivity = 1.0f;
		float m_CameraSpeed = 10.0f;
	};
}


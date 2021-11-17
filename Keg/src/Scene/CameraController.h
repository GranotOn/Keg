#pragma once
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Core/Application/Time.h"

namespace Keg
{
	class CameraController
	{
	public:
		///////////////
		// Constructors
		///////////////
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
			tc.Translation = { 0.0f, 0.0f, 3.0f };
		}

		CameraController(Entity& e) : m_CameraEntity(e) {};

		////////////////////
		// Setters & Getters
		////////////////////
		void SetEntity(Entity& entity) { m_CameraEntity = entity; }
		Entity GetEntity() { return m_CameraEntity; }

		float GetMouseSensitivity() { return m_MouseSensitivity; }
		void SetMouseSensitivity(float& sensitivity) { m_MouseSensitivity = sensitivity; }

		float GetCameraSpeed() { return m_CameraSpeed; }
		void SetCameraSpeed(float& speed) { m_CameraSpeed = speed; }


		///////////
		// Movement
		///////////
		void MoveForward(double& deltaTime);
		inline void MoveForward(Time& time) { MoveForward(time.deltaTime); }

		void MoveBackward(double& deltaTime);
		inline void MoveBackward(Time& time) { MoveBackward(time.deltaTime); }

		void MoveLeft(double& deltaTime);
		inline void MoveLeft(Time& time) { MoveLeft(time.deltaTime); }

		void MoveRight(double& deltaTime);
		inline void MoveRight(Time& time) { MoveRight(time.deltaTime); }

		///////////
		/// Updates
		///////////
		void OnCursorUpdate(float x, float y);


	private:
		Entity m_CameraEntity;
		float m_MouseSensitivity = 0.1f;
		float m_CameraSpeed = 10.0f;

		float m_FirstMouseMovement = true; // Avoids the large jump when application starts
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;

		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
	};
}


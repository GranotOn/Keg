#pragma once

#include "Renderer/Renderer.h"

namespace Keg
{
	class OpenGLRenderer : public Renderer
	{
	public:
		virtual void Update();
		virtual void Init(void* glfwGetProcAddress);
		virtual void Shutdown();

		~OpenGLRenderer();
		OpenGLRenderer() = default;
	};
}
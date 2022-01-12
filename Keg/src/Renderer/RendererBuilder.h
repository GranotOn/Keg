#pragma once
#include "Renderer/Renderer.h"
#include "Renderer/OpenGLRenderer.h"

namespace Keg
{
	
	class RendererBuilder
	{
	public:
		static RendererBuilder* GetInstance();

		Renderer* GetRenderer()
		{
			return OpenGLRenderer::GetInstance();
		}

	private:
		static RendererBuilder *s_Builder;
	};

}
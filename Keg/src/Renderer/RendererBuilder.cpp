#include "Renderer/RendererBuilder.h"

namespace Keg
{
	RendererBuilder* RendererBuilder::s_Builder = nullptr;

	RendererBuilder* RendererBuilder::GetInstance()
	{
		if (s_Builder == nullptr)
		{
			s_Builder = new RendererBuilder();
		}

		return s_Builder;
	}

	Renderer* GetRenderer()
	{
		return OpenGLRenderer::GetInstance();
	}
}
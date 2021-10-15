#include "Core/Logger/Logger.h"
#include "OpenGLRenderer.h"
#include <glad/glad.h>

namespace Keg
{
	void OpenGLRenderer::Update()
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::Init(void* glfwGetProcAddress)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			KEG_ENGINE_ERROR("glad load glfw proc in OpenGLRenderer.cpp");
		}
	}
	void OpenGLRenderer::Shutdown() {}

	OpenGLRenderer::~OpenGLRenderer() 
	{
		Shutdown();
	}
}
#include "OpenGLRenderer.h"
#include "Core/Logger/Logger.h"
#include <glad/glad.h>

#include "Vertex.h"

namespace Keg
{
	void OpenGLRenderer::Update()
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Vertex vertices[] = {
			Vertex(-0.5f, -0.5f, 0.0f),
			Vertex(0.5f, -0.5f, 0.0f),
			Vertex(0.0f, 0.5f, 0.0f)
		};

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
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
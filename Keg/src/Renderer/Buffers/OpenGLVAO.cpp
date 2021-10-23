#include <glad/glad.h>
#include "OpenGLVAO.h"

namespace Keg
{

	OpenGLVAO::OpenGLVAO()
	{
		glGenVertexArrays(1, &m_ID);
	}

	void OpenGLVAO::Bind()
	{
		if (m_ID)
		{
			glBindVertexArray(m_ID);
		}
	}

	void OpenGLVAO::UnBind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVAO::LinkAttrib(uint32_t layout, uint32_t size, uint32_t type, int stride, uint32_t offset)
	{
		if (m_ID)
		{
			Bind();
			glVertexAttribPointer(layout, size, type, GL_FALSE, stride, (void*)offset);
			glEnableVertexAttribArray(layout);
		}
	}

}

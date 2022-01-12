#include "stadx.h"
#include <glad/glad.h>
#include "OpenGLVAO.h"

namespace Keg
{
	OpenGLVAO::OpenGLVAO(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements)
	{
		GLuint VBO, EBO;
		glGenVertexArrays(1, &m_ID);

		Bind();

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint32_t), elements.data(), GL_STATIC_DRAW);

		/////////////
		// Attributes
		/////////////
		
		// Position attribute
		LinkAttrib(0, 3, GL_FLOAT, sizeof(Vertex), 0);
		
		// Texture attribute
		LinkAttrib(1, 2, GL_FLOAT, sizeof(Vertex), 3 * sizeof(float));

		// Normal attribute
		LinkAttrib(2, 3, GL_FLOAT, sizeof(Vertex), 5 * sizeof(float));
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

	void OpenGLVAO::LinkAttrib(uint32_t layout, uint32_t size, uint32_t type, int stride, uint64_t offset)
	{
		if (m_ID)
		{
			Bind();
			glVertexAttribPointer(layout, size, type, GL_FALSE, stride, (void*)offset);
			glEnableVertexAttribArray(layout);
		}
	}

}

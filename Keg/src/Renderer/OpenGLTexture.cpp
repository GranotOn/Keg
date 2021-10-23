#include "OpenGLTexture.h"
#include "stb_image.cpp"

#include <glad/glad.h>
#include "Core/Logger/Logger.h"


namespace Keg
{
	OpenGLTexture::OpenGLTexture(const char* texLocation)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texLocation, &width, &height, &nrChannels, 0);

		if (data)
		{
			KEG_ENGINE_INFO("Loaded texture in location {0}", texLocation);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			KEG_ENGINE_ERROR("Failed to load texture in location {0}", texLocation);
		}

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void OpenGLTexture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
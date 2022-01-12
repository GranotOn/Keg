#pragma once
#include <cstdint>



namespace Keg
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture(const char* texLocation);

		virtual void Bind();
		virtual void UnBind();

		inline uint32_t GetID() { return m_ID; }

	private:
		uint32_t m_ID;
	};
}


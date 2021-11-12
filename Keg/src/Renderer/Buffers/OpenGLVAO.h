#pragma once
#include <cstdint>

namespace Keg
{
	class OpenGLVAO
	{
	public:
		OpenGLVAO();

		virtual void Bind();
		virtual void UnBind();
		virtual void LinkAttrib(uint32_t layout, uint32_t size, uint32_t type, int stride, uint64_t offset);
		inline uint32_t GetID() { return m_ID; }

	private:
		uint32_t m_ID;
	};
}


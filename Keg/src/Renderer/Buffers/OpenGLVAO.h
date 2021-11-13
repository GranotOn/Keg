#pragma once
#include <cstdint>
#include <vector>

#include "Renderer/Vertex.h"

namespace Keg
{
	class OpenGLVAO
	{
	public:
		OpenGLVAO() = delete;
		OpenGLVAO(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

		virtual void Bind();
		virtual void UnBind();
		virtual void LinkAttrib(uint32_t layout, uint32_t size, uint32_t type, int stride, uint64_t offset);
		inline uint32_t GetID() { return m_ID; }

	private:
		uint32_t m_ID;
	};
}


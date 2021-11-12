#include "DrawDetails.h"

namespace Keg
{
	DrawDetails::~DrawDetails()
	{

	}

	std::vector<Vertex> DrawDetails::GetVertices()
	{
		return m_Vertices;
	}

	GLuint DrawDetails::GetElementsCount()
	{
		return m_Elements;
	}
}
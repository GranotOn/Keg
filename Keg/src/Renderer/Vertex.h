#pragma once

namespace Keg
{
	struct Vertex
	{
		Vertex(float x, float y, float z)
		{ 
			position[0] = x;
			position[1] = y;
			position[2] = z;
		}

		float position[3];
	};
}
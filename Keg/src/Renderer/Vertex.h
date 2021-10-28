#pragma once

namespace Keg
{
	struct Vertex
	{
		Vertex(float x, float y, float z, float textureX, float textureY)
		{ 
			position[0] = x;
			position[1] = y;
			position[2] = z;
			
			position[3] = textureX;
			position[4] = textureY;
		}

		float position[5];
	};
}
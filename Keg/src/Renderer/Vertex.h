#pragma once

namespace Keg
{
	struct Vertex
	{
		Vertex(float x, float y, float z, float textureX = 0.0f, float textureY = 0.0f, float normalX = 0.0f, float normalY = 0.0f, float normalZ = 0.0f)
		{ 
			// Position
			position[0] = x;
			position[1] = y;
			position[2] = z;
			
			// Texture
			position[3] = textureX;
			position[4] = textureY;

			// Normals
			position[5] = normalX;
			position[6] = normalY;
			position[7] = normalZ;
		}

		float position[8];
	};
}
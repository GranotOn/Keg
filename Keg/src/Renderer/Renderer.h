#pragma once

#include <string>
#include <vector>
#include "Renderer/Vertex.h"
#include "Renderer/DrawDetails.h"

namespace Keg
{
	class Renderer
	{
	public:
		virtual void Update() = 0;
		virtual void Init(void* procAddress) = 0;
		virtual void Shutdown() = 0;
		virtual void OnViewportChange(int width, int height) = 0;
		
		// Drawables
		virtual void AddDrawable(DrawDetails *d) = 0;
		virtual DrawDetails* CreateDrawable(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) = 0;
		virtual std::vector<DrawDetails *> GetDrawables() = 0;
		virtual DrawDetails* GetDrawable(int index) = 0;

		// Shaders
		virtual void AddShader(const std::string& name, const std::string& vs, const std::string& fs) = 0;
		virtual void AddShader(const std::string& name, Shader* s) = 0;
		virtual void RemoveShader(const std::string& name) = 0;
		virtual Shader* GetShader(const std::string &name) = 0;
	};
}

#define RENDERER_SHADER_COLOR "ColorShader"
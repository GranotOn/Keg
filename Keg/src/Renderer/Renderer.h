#pragma once

namespace Keg
{
	class Renderer
	{
	public:
		virtual void Update() = 0;
		virtual void Init(void* procAddress) = 0;
		virtual void Shutdown() = 0;
	};
}
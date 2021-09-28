#pragma once

namespace Keg
{
	class Layer
	{
	public:
		// Hooks
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent() = 0;
	};
}
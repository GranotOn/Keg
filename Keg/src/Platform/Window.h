#pragma once
#include "Core/Event/Event.h"
#include "Core/Event/KeyEvent.h"
#include <functional>



namespace Keg
{
	
	class Window
	{
	
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		// Constructor/Destructor
		virtual ~Window() = default;

		// Runtime handeling
		virtual bool HasWindow() const = 0;
		virtual void SwapBuffers() const = 0;
		virtual void PollEvents() const = 0;
		virtual void OnUpdate() const = 0;
		virtual void SetEventCallback(const EventCallbackFn &cb) = 0;

		// Initialization & Destruction
		virtual void Init() const = 0;
		virtual void Shutdown() const = 0;
	};
}
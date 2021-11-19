#pragma once
#include "stadx.h"
#include "Core/Event/Event.h"

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
		virtual void* GetProcAddress() = 0;
		virtual void* GetNativeWindow() = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual double GetTime() = 0;
		virtual void SetCursorVisibility(bool& mode) = 0;
		virtual void SetWindowIcon(const char* path) = 0;

		// Initialization & Destruction
		virtual void Init() = 0;
		virtual void Shutdown() const = 0;

	};

	
}
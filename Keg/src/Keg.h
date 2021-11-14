#pragma once

#include "Core/Application/Application.h"
#include "Core/Logger/Logger.h"

// Events & Input
#include "Core/Event/Event.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Event/WindowEvent.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

// Layers
#include "Core/Layer/Layer.h"
#include "Core/ImGui/ImGuiLayer.h"

// Window & Input
#include "Platform/Window.h"
#include "Platform/WindowsWindow.h"
#include "Platform/WindowsInput.h"

// Renderer
#include "Renderer/Renderer.h"
#include "Renderer/OpenGLRenderer.h"
#include "Renderer/RendererBuilder.h"

// Rendering Items
#include "Renderer/Vertex.h"
#include "Renderer/Shader.h"
#include "Renderer/OpenGLTexture.h"
#include "Renderer/OpenGLTextureManager.h"
#include "Renderer/DrawDetails.h"

// Scene & Entity
#include "Scene/Components.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

// ETC
#include "Core/Application/Time.h"
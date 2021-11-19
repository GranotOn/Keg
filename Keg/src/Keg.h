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
#include "Scene/CameraController.h"

// ETC
#include "Core/Time/Time.h"
#include "Scene/Components.h"

// Audio
#include "Audio/Audio.h"
#include "Audio/Effect.h"
#include "Audio/OpenAlAudio.h"
#include "Audio/AudioBuilder.h"

// FileSystem
#include "FileSystem/FileSystem.h"


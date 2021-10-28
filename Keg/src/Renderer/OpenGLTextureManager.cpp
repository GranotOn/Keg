#include "OpenGLTextureManager.h"

namespace Keg
{
	OpenGLTextureManager* OpenGLTextureManager::s_Instance = nullptr;

	OpenGLTextureManager::~OpenGLTextureManager()
	{
		// Delete all texture pointers and free up memory
		for (auto &kv : m_Textures)
			delete kv.second;
	}

	OpenGLTextureManager::OpenGLTextureManager()
	{
	}

	OpenGLTextureManager* OpenGLTextureManager::GetInstance()
	{
		if (!s_Instance)
		{
			s_Instance = new OpenGLTextureManager();
		}

		return s_Instance;
	}

	void OpenGLTextureManager::LoadTexture(const std::string& tag, OpenGLTexture* t)
	{
		m_Textures.insert_or_assign(tag, t);
	}

	void OpenGLTextureManager::LoadTexture(const std::string& tag, const char* path)
	{
		LoadTexture(tag, new OpenGLTexture(path));
	}

	OpenGLTexture* OpenGLTextureManager::GetTexture(const std::string& tag)
	{
		auto it = m_Textures.find(tag);

		if (it != m_Textures.end())
		{
			return it->second;
		}

		return nullptr;
	}

	void OpenGLTextureManager::RemoveTexture(const std::string& tag)
	{
		auto it = m_Textures.find(tag);

		if (it != m_Textures.end())
		{
			m_Textures.erase(it);
		}
	}


}
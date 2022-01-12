#pragma once

#include <map>
#include <string>
#include "Renderer/OpenGLTexture.h"

namespace Keg
{
    class OpenGLTextureManager
    {
    public:
        static OpenGLTextureManager* GetInstance();

        void LoadTexture(const std::string& tag, OpenGLTexture* t);
        void LoadTexture(const std::string& tag, const char* path);
        OpenGLTexture* GetTexture(const std::string& tag);
        void RemoveTexture(const std::string& tag);

        ~OpenGLTextureManager();

    private:
        OpenGLTextureManager();
        static OpenGLTextureManager *s_Instance;
        std::map<std::string, OpenGLTexture*> m_Textures;
    };
}

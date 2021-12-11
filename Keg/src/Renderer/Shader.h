#pragma once

namespace Keg
{
	class Shader
	{
	public:
		int m_ID; // -1 == failed

		Shader(const char* vertexPath, const char* fragmentPath);

		// Activate shader
		void Use();

		// Utils
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec3(const std::string& name, float x, float y, float z) const;
		void SetVec4(const std::string& name, float x, float y, float z, float w) const;

		inline int GetID() { return m_ID; }
	};
}
#include <sstream>
#include <fstream>

#include "Shader.h"
#include "Core/Logger/Logger.h"
#include <glad/glad.h>

namespace Keg
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		KEG_ENGINE_INFO("Attempting to load shaders \n\
							\tVertex: {0} \n\
							\tFragment: {1}", vertexPath, fragmentPath);

		std::string vertexCode, fragmentCode;
		std::ifstream vShaderFile, fShaderFile;

		// Set exception detection
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;
			
			// Read files to streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			KEG_ENGINE_ERROR("Shader::Shader(): File not succesfully read");
			m_ID = -1;
			return;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Compile shaders
		unsigned int vertex, fragment;
		int success;
		char log[512];

		// -----
		// Vertex
		// -----
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, 0);
		glCompileShader(vertex);

		// Error handeling
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, 0, log);
			KEG_ENGINE_ERROR("Shader::Shader(): VERTEX_COMPILATION_FAILED ({0})", log);
		}
		
		// -----
		// Fragment
		// -----
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, 0);
		glCompileShader(fragment);

		// Error handeling
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, 0, log);
			KEG_ENGINE_ERROR("Shader::Shader(): FRAGMENT_COMPILATION_FAILED ({0})", log)
		}

		// -----
		// Shader Program
		// -----

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);

		glLinkProgram(m_ID);

		// Error (linking) handeling
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, 0, log);
			KEG_ENGINE_ERROR("Shader::Shader(): PROGRAM_LINK_FAILED ({0})", log)
		}

		// -----
		// Cleanup
		// -----

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::Use()
	{
		glUseProgram(m_ID);
	}

	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

}

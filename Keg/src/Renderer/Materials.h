#pragma once
#include "Scene/Components.h"

namespace Keg
{
	namespace Material
	{
		static MaterialComponent Emerlad()
		{ 
			MaterialComponent m;
			m.ambient = { 0.0215f, 0.1745f, 0.0215f };
			m.diffuse = { 0.07568f, 0.61424f, 0.07568f };
			m.specular = { 0.633f, 0.727811f, 0.633f };
			m.shininess = 0.6f;
			return m;
		}

		static MaterialComponent Jade()
		{
			MaterialComponent m;
			m.ambient = { 0.135f, 0.2225f, 0.1575f };
			m.diffuse = { 0.54f, 0.89f, 0.63f };
			m.specular = { 0.316228f, 0.316228f, 0.316228f};
			m.shininess = 0.1f;
			return m;
		}

		static MaterialComponent Obsidian()
		{
			MaterialComponent m;
			m.ambient = { 0.5375f, 0.05f, 0.06625f };
			m.diffuse = { 0.18275f, 0.17f, 0.22525f};
			m.specular = { 0.332741f, 0.328634f, 0.34635f};
			m.shininess = 0.3f;
			return m;
		}

		static MaterialComponent Pearl()
		{
			MaterialComponent m;
			m.ambient = { 0.25f, 0.20725f, 0.20725f };
			m.diffuse = { 1.0f, 0.829f, 0.829f };
			m.specular = { 0.296448f, 0.296448f, 0.296448f };
			m.shininess = 0.088f;
			return m;
		}

		static MaterialComponent Ruby()
		{
			MaterialComponent m;
			m.ambient = { 0.1745f, 0.01175f, 0.01175f };
			m.diffuse = { 0.61424f, 0.04136f, 0.04136f };
			m.specular = { 0.727811f, 0.626959f, 0.626959f };
			m.shininess = 0.6f;
			return m;
		}

		static MaterialComponent Turqouoise()
		{
			MaterialComponent m;
			m.ambient = { 0.1f, 0.18725f, 0.1745f };
			m.diffuse = { 0.396f, 0.74151f, 0.69102f };
			m.specular = { 0.297254f, 0.30829f, 0.306678f };
			m.shininess = 0.1f;
			return m;
		}

		static MaterialComponent Brass()
		{
			MaterialComponent m;
			m.ambient = { 0.329412f, 0.223529f, 0.027451f };
			m.diffuse = { 0.780392f, 0.568627f, 0.113725f };
			m.specular = { 0.992157f, 0.941176f, 0.807843f };
			m.shininess = 0.21794872f;
			return m;
		}

		static MaterialComponent Bronze()
		{
			MaterialComponent m;
			m.ambient = { 0.2125f, 0.1275f, 0.054f };
			m.diffuse = { 0.714f, 0.4284f, 0.18144f };
			m.specular = { 0.393548f, 0.271906f, 0.166721f};
			m.shininess = 0.2f;
			return m;
		}
		
		static MaterialComponent Chrome()
		{
			MaterialComponent m;
			m.ambient = { 0.25f, 0.25f, 0.25f };
			m.diffuse = { 0.4f, 0.4f, 0.4f };
			m.specular = { 0.774597f, 0.774597f, 0.774597f };
			m.shininess = 0.6f;
			return m;
		}

		static MaterialComponent Copper()
		{
			MaterialComponent m;
			m.ambient = { 0.19125f, 0.0735f, 0.0225f };
			m.diffuse = { 0.7038f, 0.27048f, 0.0828f };
			m.specular = { 0.256777f , 0.137622f, 0.086014f};
			m.shininess = 0.1f;
			return m;
		}

		static MaterialComponent Gold()
		{
			MaterialComponent m;
			m.ambient = { 0.24725f, 0.1995f, 0.0745f };
			m.diffuse = { 0.75164f, 0.60648f, 0.22648f };
			m.specular = { 0.628281f, 0.555802f, 0.366065f };
			m.shininess = 0.4f;
			return m;
		}

		static MaterialComponent Silver()
		{
			MaterialComponent m;
			m.ambient = { 0.19225f, 0.19225f, 0.19225f };
			m.diffuse = { 0.50754f, 0.50754f, 0.50754f };
			m.specular = { 0.508273f, 0.508273f, 0.508273f };
			m.shininess = 0.4f;
			return m;
		}

		static MaterialComponent BlackPlastic()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.0f, 0.0f };
			m.diffuse = { 0.01f, 0.01f, 0.01f };
			m.specular = { 0.5f, 0.5f, 0.5f };
			m.shininess = 0.25f;
			return m;
		}

		static MaterialComponent CyanPlastic()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.1f, 0.6f };
			m.diffuse = { 0.0f, 0.50980392f, 0.50980392f };
			m.specular = { 0.50196078f, 0.50196078f, 0.50196078f };
			m.shininess = 0.25f;
			return m;
		}

		static MaterialComponent GreenPlastic()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.0f, 0.0f };
			m.diffuse = { 0.1f, 0.35f, 0.1f };
			m.specular = { 0.45f, 0.55f, 0.45f };
			m.shininess = 0.25f;
			return m;
		}

		static MaterialComponent RedPlastic()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.0f, 0.0f };
			m.diffuse = { 0.5f, 0.0f, 0.0f };
			m.specular = { 0.7f, 0.6f, 0.6f };
			m.shininess = 0.25f;
			return m;
		}

		static MaterialComponent WhitePlastic()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.0f, 0.0f };
			m.diffuse = { 0.55f, 0.55f, 0.55f };
			m.specular = { 0.7f, 0.7f, 0.7f };
			m.shininess = 0.25f;
			return m;
		}

		static MaterialComponent YellowPlastic()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.0f, 0.0f };
			m.diffuse = { 0.5f, 0.5f, 0.0f };
			m.specular = { 0.6f, 0.6f, 0.5f };
			m.shininess = 0.25f;
			return m;
		}

		static MaterialComponent BlackRubber()
		{
			MaterialComponent m;
			m.ambient = { 0.02f, 0.02f, 0.02f };
			m.diffuse = { 0.01f, 0.01f, 0.01f };
			m.specular = { 0.4f, 0.4f, 0.4f };
			m.shininess = 0.078125f;
			return m;
		}

		static MaterialComponent CyanRubber()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.05f, 0.05f };
			m.diffuse = { 0.4f, 0.5f, 0.5f};
			m.specular = { 0.04f, 0.7f, 0.7f };
			m.shininess = 0.078125f;
			return m;
		}

		static MaterialComponent GreenRubber()
		{
			MaterialComponent m;
			m.ambient = { 0.0f, 0.05f, 0.0f };
			m.diffuse = { 0.4f, 0.5f, 0.4f };
			m.specular = { 0.04f, 0.7f, 0.04f };
			m.shininess = 0.078125f;
			return m;
		}

		static MaterialComponent RedRubber()
		{
			MaterialComponent m;
			m.ambient = { 0.05f, 0.0f, 0.0f };
			m.diffuse = { 0.5f, 0.4f, 0.4f };
			m.specular = { 0.7f, 0.04f, 0.04f };
			m.shininess = 0.078125f;
			return m;
		}

		static MaterialComponent WhiteRubber()
		{
			MaterialComponent m;
			m.ambient = { 0.05f, 0.05f, 0.05f };
			m.diffuse = { 0.5f, 0.5f, 0.5f };
			m.specular = { 0.7f, 0.7f, 0.7f };
			m.shininess = 0.078125f;
			return m;
		}

		static MaterialComponent YellowRubber()
		{
			MaterialComponent m;
			m.ambient = { 0.05f, 0.05f, 0.0f };
			m.diffuse = { 0.5f, 0.5f, 0.4f };
			m.specular = { 0.7f, 0.7f, 0.4f };
			m.shininess = 0.078125f;
			return m;
		}
	}
}
#pragma once

#include <string>


namespace Keg
{
	struct TagComponent
	{
		TagComponent(std::string& tag) : tag(tag) {}

		std::string tag;
	};
}
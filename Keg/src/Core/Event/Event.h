#pragma once

#include <string>

namespace Keg
{
	
	class Event
	{
	public:
		virtual std::string GetStaticType() = 0;
	};

}
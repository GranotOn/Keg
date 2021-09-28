#include "Logger.h"


namespace Keg
{
	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ApplicationLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^ [%r] (%n): %v %$"); // [Timestamp (12 hour clock)] (Name): String

		s_EngineLogger = spdlog::stderr_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);
		s_ApplicationLogger = spdlog::stderr_color_mt("Applicaiton");
		s_ApplicationLogger->set_level(spdlog::level::trace);
	}
}



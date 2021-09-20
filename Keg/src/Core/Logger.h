#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Keg
{
	class Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return s_ApplicationLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ApplicationLogger;
	};
}

// Logger macros

// Engine (Core) Logging
#define KEG_ENGINE_TRACE(...) Keg::Logger::GetEngineLogger()->trace(__VA_ARGS__);
#define KEG_ENGINE_INFO(...) Keg::Logger::GetEngineLogger()->info(__VA_ARGS__);
#define KEG_ENGINE_WARN(...) Keg::Logger::GetEngineLogger()->warn(__VA_ARGS__);
#define KEG_ENGINE_ERROR(...) Keg::Logger::GetEngineLogger()->error(__VA_ARGS__);


// Application Logging

#define KEG_APP_TRACE(...) Keg::Logger::GetApplicationLogger()->trace(__VA_ARGS__);
#define KEG_APP_INFO(...) Keg::Logger::GetApplicationLogger()->info(__VA_ARGS__);
#define KEG_APP_WARN(...) Keg::Logger::GetApplicationLogger()->warn(__VA_ARGS__);
#define KEG_APP_ERROR(...) Keg::Logger::GetApplicationLogger()->error(__VA_ARGS__);

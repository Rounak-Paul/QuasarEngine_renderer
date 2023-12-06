/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		Wraper for spdlog. Trace methods are not compiled in 
					Release.
-------------------------------------------------------------------------------
*/

#pragma once

#include "Quasar/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Quasar {

	class QUASAR_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define QS_CORE_ERROR(...)	::Quasar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QS_CORE_WARN(...)	::Quasar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QS_CORE_INFO(...)	::Quasar::Log::GetCoreLogger()->info(__VA_ARGS__)

#define QS_ERROR(...)	::Quasar::Log::GetClientLogger()->error(__VA_ARGS__)
#define QS_WARN(...)	::Quasar::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QS_INFO(...)	::Quasar::Log::GetClientLogger()->info(__VA_ARGS__)

#ifdef QS_DEBUG
#define QS_CORE_TRACE(...)	::Quasar::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define QS_TRACE(...)	::Quasar::Log::GetClientLogger()->trace(__VA_ARGS__)

#else
#define QS_CORE_TRACE(...)

#define QS_TRACE(...)

#endif




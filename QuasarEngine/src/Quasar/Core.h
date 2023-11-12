#pragma once

#ifdef QS_PLATFORM_WINDOWS
	#ifdef QS_BUILD_DLL 
		#define QUASAR_API __declspec(dllexport) 
	#else 
		#define QUASAR_API __declspec(dllimport) 
	#endif
#else 
	#error Quasar only supports Windows!
#endif

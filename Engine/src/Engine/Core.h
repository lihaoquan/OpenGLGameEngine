#pragma once

// _declspec(dllexport) specifies that the function is to be exported as part of the built .dll library

#ifdef EG_PLATFORM_WINDOWS
	#ifdef EG_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Engine only support Windows!
#endif

#define BIT(x) (1 << x)
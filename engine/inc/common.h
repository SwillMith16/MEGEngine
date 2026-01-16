//
// Created by Will on 16/01/2026.
//

#ifndef MEGENGINE_COMMON_H
#define MEGENGINE_COMMON_H

#ifdef _WIN32
  #ifdef ENGINE_BUILD
	#define ENGINE_API __declspec(dllexport)
  #else
	#define ENGINE_API __declspec(dllimport)
  #endif
#else
  #define ENGINE_API
#endif

#endif //MEGENGINE_COMMON_H
#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

#include "common.h"

inline std::string g_resourcesDir = "../../../engine/resources";

namespace MEGEngine {
	class ENGINE_API Settings {
	public:
		static int maxFPS;
	};
}


#endif //SETTINGS_H
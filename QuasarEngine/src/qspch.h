#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE




#include <iostream>
#include <chrono>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <set>

#include <Quasar/Log/Log.h>
#include <Quasar/EventSystem/EventSystem.h>
#include <Quasar/Camera/Camera.h>
#include <Quasar/GameObject/GameObject.h>


#ifdef QS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <set>

#include <Quasar/Log/Log.h>
#include <Quasar/Window/Window.h>
#include <Quasar/Device/Device.h>
#include <Quasar/Pipeline/Pipeline.h>
#include <Quasar/SwapChain/SwapChain.h>
#include <Quasar/Model/Model.h>

#ifdef QS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

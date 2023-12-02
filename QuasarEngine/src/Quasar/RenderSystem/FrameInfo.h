#pragma once
#include "qspch.h"

#include <Quasar/Camera/Camera.h>

namespace Quasar {
	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		Camera& camera;
	};
}

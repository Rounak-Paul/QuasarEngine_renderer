#pragma once
#include "qspch.h"

#include <Core/Camera/Camera.h>

namespace Quasar {
	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		Camera& camera;
		VkDescriptorSet globalDescriptorSet;
	};
}

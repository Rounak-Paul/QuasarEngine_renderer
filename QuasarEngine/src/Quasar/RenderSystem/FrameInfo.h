#pragma once
#include "qspch.h"

#include <Quasar/Camera/Camera.h>
#include <Quasar/GameObject/GameObject.h>

namespace Quasar {
	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		Camera& camera;
		VkDescriptorSet globalDescriptorSet;
		GameObject::Map& gameObjects;
	};
}

#pragma once
#include "qspch.h"

#include <Quasar/Core.h>

#include "Model.h"
#include "Device.h"
#include "Pipeline.h"
#include <Quasar/Window/Window.h>
#include "Renderer.h"
#include "SwapChain.h"
#include "FrameInfo.h"
#include <Quasar/GameObject/GameObject.h>

namespace Quasar {

	class RenderSystem
	{
	public:
		RenderSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~RenderSystem();

		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;

		void RenderGameObjects(FrameInfo& frameInfo, std::vector<GameObject>& gameObjects);
	private:
		void CreatePipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void CreatePipeline(VkRenderPass renderPass);
		

		Device& _device;

		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
	};
}



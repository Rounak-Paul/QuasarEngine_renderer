#pragma once
#include "qspch.h"

#include <Quasar/Core.h>

#include <Quasar/Model/Model.h>
#include "Device.h"
#include "Pipeline.h"
#include "Window.h"
#include "Renderer.h"
#include "SwapChain.h"
#include "Window.h"
#include <Quasar/GameObject/GameObject.h>

namespace Quasar {

	class RenderSystem
	{
	public:
		RenderSystem(Device& device, VkRenderPass renderPass);
		~RenderSystem();

		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;

		void RenderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject>& gameObjects);
	private:
		void CreatePipelineLayout();
		void CreatePipeline(VkRenderPass renderPass);
		

		Device& _device;

		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
	};
}



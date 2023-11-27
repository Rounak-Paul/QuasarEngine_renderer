#pragma once

#include "Window.h"
#include "Device.h"
#include "SwapChain.h"

#include "qspch.h"

namespace Quasar
{
	class Renderer
	{
	public:
		Renderer(Window& window, Device& device);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		VkRenderPass GetSwapChainRenderPass() const { return swapChain->getRenderPass(); }
		bool IsFrameInProgress() const { return isFrameStarted; }
		VkCommandBuffer GetCurrentCommandBuffer() const 
		{ 
			assert(isFrameStarted && "Can not get command buffer when frame is not in progress!");
			return commandBuffers[currentFrameIndex];
		}

		int GetFrameIndex()
		{
			assert(isFrameStarted && "Can not get frame index when frame is not in progress!");
			return currentFrameIndex;
		}

		VkCommandBuffer BeginFrame();
		void EndFrame();
		void BeginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void EndSwapChainRenderPass(VkCommandBuffer commandBuffer);

	private:
		void CreateCommandBuffers();
		void FreeCommandBuffers();
		void RecreateSwapChain();

		Window& _window;
		Device& _device;
		std::unique_ptr<SwapChain> swapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex{ 0 };
		bool isFrameStarted{false};
	};
}



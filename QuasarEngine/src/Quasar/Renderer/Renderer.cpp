#include "qspch.h"
#include "Renderer.h"

namespace Quasar
{
	Renderer::Renderer(Window& window, Device& device) : _window{window}, _device{device}
	{
		RecreateSwapChain();
		CreateCommandBuffers();
	}

	Renderer::~Renderer()
	{
		FreeCommandBuffers();
	}

	void Renderer::CreateCommandBuffers()
	{
		commandBuffers.resize(swapChain->imageCount());

		VkCommandBufferAllocateInfo allocateInfo{};
		allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocateInfo.commandPool = _device.getCommandPool();
		allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(_device.device(), &allocateInfo, commandBuffers.data()) !=
			VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to cllocate command buffers!");
		}
	}

	void Renderer::RecreateSwapChain()
	{
		auto extent = _window.GetExtent();
		while (extent.width == 0 || extent.height == 0)
		{
			extent = _window.GetExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(_device.device());

		if (swapChain == nullptr)
		{
			swapChain = std::make_unique<SwapChain>(_device, extent);
		}
		else
		{
			swapChain = std::make_unique<SwapChain>(_device, extent, std::move(swapChain));
			if (swapChain->imageCount() != commandBuffers.size())
			{
				FreeCommandBuffers();
				CreateCommandBuffers();
			}
		}

		//
	}

	

	

	void Renderer::FreeCommandBuffers()
	{
		vkFreeCommandBuffers(
			_device.device(),
			_device.getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()),
			commandBuffers.data());
		commandBuffers.clear();
	}

	
	VkCommandBuffer Renderer::BeginFrame()
	{
		assert(!isFrameStarted && "Can not call begin frame while already in progress");

		auto result = swapChain->acquireNextImage(&currentImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();
			return nullptr;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			QS_CORE_ERROR("Failed to acquire swap chain image!");
		}

		isFrameStarted = true;

		auto commandBuffer = GetCurrentCommandBuffer();
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to begin recording command buffer!");
		}
		return commandBuffer;
	}

	void Renderer::EndFrame()
	{
		assert(isFrameStarted && "Can not call end frame while frame not in progress");
		auto commandBuffer = GetCurrentCommandBuffer();
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to record command buffer!");
		}
		auto result = swapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);

		// Resize window event
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _window.WasWindowResized())
		{
			_window.ResetWindowResizedFlag();
			RecreateSwapChain();
		}
		if (result != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to present swap chain image!");
		}

		isFrameStarted = false;
	}

	void Renderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer)
	{
		assert(isFrameStarted && "Can not call BeginSwapChainRenderPass while frame not in progress");
		assert(commandBuffer == GetCurrentCommandBuffer() && "Can not begin Render Pass on Command Buffer from a different frame");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = swapChain->getRenderPass();
		renderPassInfo.framebuffer = swapChain->getFrameBuffer(currentImageIndex);

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChain->getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(swapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, swapChain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
	}
	void Renderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer)
	{
		assert(isFrameStarted && "Can not call EndSwapChainRenderPass while frame not in progress");
		assert(commandBuffer == GetCurrentCommandBuffer() && "Can not end Render Pass on Command Buffer from a different frame");

		vkCmdEndRenderPass(commandBuffer);
	}
}

#include "qspch.h"
#include "Application.h"

namespace Quasar {

	Application::Application() 
	{
		LoadModels();
		CreatePipelineLayout();
		RecreateSwapChain();
		CreateCommandBuffers();
	}

	Application::~Application() 
	{
		vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
	}

	void Application::Run() 
	{
		while (!window.ShouldClose())
		{
			glfwPollEvents();
			DrawFrame();

			vkDeviceWaitIdle(device.device());
		}
	}

	void Application::LoadModels()
	{
		std::vector<Model::Vertex> vertices{};
		vertices = {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		};
		//Sierpinski(vertices, 6, { -0.5f, 0.5f }, { 0.5f, 0.5f }, { 0.0f, -0.5f });
		model = std::make_unique<Model>(device, vertices);
	}

	void Application::Sierpinski(
		std::vector<Model::Vertex>& vertices,
		int depth,
		glm::vec2 left,
		glm::vec2 right,
		glm::vec2 top)
	{
		if (depth <= 0) {
			vertices.push_back({ top });
			vertices.push_back({ right });
			vertices.push_back({ left });
		}
		else {
			auto leftTop = 0.5f * (left + top);
			auto rightTop = 0.5f * (right + top);
			auto leftRight = 0.5f * (left + right);
			Sierpinski(vertices, depth - 1, left, leftRight, leftTop);
			Sierpinski(vertices, depth - 1, leftRight, right, rightTop);
			Sierpinski(vertices, depth - 1, leftTop, rightTop, top);
		}
	}

	void Application::CreatePipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
			VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to create pipeline layout");
		}
	}
	void Application::CreatePipeline()
	{
		assert(swapChain != nullptr && "Can not create pipeline before swap chain");
		assert(pipelineLayout != nullptr && "Can not create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig{};
		Pipeline::DefaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = swapChain->getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<Pipeline>
			(
				device,
				"D:/Code/QuasarEngine/QuasarEngine/Shader/bin/simple_shader.vert.spv",
				"D:/Code/QuasarEngine/QuasarEngine/Shader/bin/simple_shader.frag.spv",
				pipelineConfig
			);
	}
	void Application::CreateCommandBuffers()
	{
		commandBuffers.resize(swapChain->imageCount());

		VkCommandBufferAllocateInfo allocateInfo{};
		allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocateInfo.commandPool = device.getCommandPool();
		allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(device.device(), &allocateInfo, commandBuffers.data()) !=
			VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to cllocate command buffers!");
		}
	}

	void Application::RecreateSwapChain()
	{
		auto extent = window.GetExtent();
		while (extent.width == 0 || extent.height == 0)
		{
			extent = window.GetExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(device.device());

		if (swapChain == nullptr)
		{
			swapChain = std::make_unique<SwapChain>(device, extent);
		}
		else
		{
			swapChain = std::make_unique<SwapChain>(device, extent, std::move(swapChain));
			if (swapChain->imageCount() != commandBuffers.size())
			{
				FreeCommandBuffers();
				CreateCommandBuffers();
			}
		}

		CreatePipeline();
	}

	void Application::RecordCommandBuffer(int imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = swapChain->getRenderPass();
		renderPassInfo.framebuffer = swapChain->getFrameBuffer(imageIndex);

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChain->getSwapChainExtent();

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(swapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, swapChain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

		pipeline->Bind(commandBuffers[imageIndex]);
		model->Bind(commandBuffers[imageIndex]);
		model->Draw(commandBuffers[imageIndex]);

		vkCmdEndRenderPass(commandBuffers[imageIndex]);
		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to record command buffer!");
		}
	}

	void Application::FreeCommandBuffers()
	{
		vkFreeCommandBuffers(
			device.device(),
			device.getCommandPool(),
			static_cast<uint32_t>(commandBuffers.size()),
			commandBuffers.data());
		commandBuffers.clear();
	}

	void Application::DrawFrame()
	{
		uint32_t imageIndex;
		auto result = swapChain->acquireNextImage(&imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			RecreateSwapChain();
			return;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			QS_CORE_ERROR("Failed to acquire swap chain image!");
		}

		RecordCommandBuffer(imageIndex);
		result = swapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

		// Resize window event
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window.WasWindowResized())
		{
			window.ResetWindowResizedFlag();
			RecreateSwapChain();
			return;
		}
		if (result != VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to present swap chain image!");
		}
	}

}

#include "qspch.h"
#include "Application.h"

namespace Quasar {

	Application::Application() 
	{
		CreatePipelineLayout();
		CreatePipeline();
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
		auto pipelineConfig =
			Pipeline::DefaultPipelineConfigInfo(swapChain.width(), swapChain.height());
		pipelineConfig.renderPass = swapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<Pipeline>
			(
				device,
				"D:/Code/QuasarEngine/QuasarEngine/Shader/simple_shader.vert.spv",
				"D:/Code/QuasarEngine/QuasarEngine/Shader/simple_shader.frag.spv",
				pipelineConfig
			);
	}
	void Application::CreateCommandBuffers()
	{

	}
	void Application::DrawFrame()
	{

	}

}

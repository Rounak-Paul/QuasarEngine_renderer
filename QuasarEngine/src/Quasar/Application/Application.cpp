#include "qspch.h"
#include "Application.h"

namespace Quasar {

	struct SimplePushConstantData
	{
		glm::mat2 transform{1.0f};
		glm::vec2 offset;
		alignas(16) glm::vec3 color;
	};

	Application::Application() 
	{
		LoadGameObjects();
		CreatePipelineLayout();
		CreatePipeline();
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

			if (auto commandBuffer = renderer.BeginFrame())
			{
				renderer.BeginSwapChainRenderPass(commandBuffer);
				RenderGameObjects(commandBuffer);
				renderer.EndSwapChainRenderPass(commandBuffer);
				renderer.EndFrame();
			}

			vkDeviceWaitIdle(device.device());
		}
	}

	void Application::LoadGameObjects()
	{
		std::vector<Model::Vertex> vertices{};
		vertices = {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		};
		//Sierpinski(vertices, 6, { -0.5f, 0.5f }, { 0.5f, 0.5f }, { 0.0f, -0.5f });
		auto model = std::make_shared<Model>(device, vertices);

		auto triangle = GameObject::CreateGameObject();
		triangle.model = model;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2d.translation.x = .2f;
		triangle.transform2d.scale = { 2.0f, .5f };
		triangle.transform2d.rotation = .25 * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}

	void Application::CreatePipelineLayout()
	{
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushConstantData);

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
			VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to create pipeline layout");
		}
	}
	void Application::CreatePipeline()
	{
		assert(pipelineLayout != nullptr && "Can not create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig{};
		Pipeline::DefaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = renderer.GetSwapChainRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<Pipeline>
			(
				device,
				"D:/Code/QuasarEngine/QuasarEngine/Shader/bin/simple_shader.vert.spv",
				"D:/Code/QuasarEngine/QuasarEngine/Shader/bin/simple_shader.frag.spv",
				pipelineConfig
			);
	}

	void Application::RenderGameObjects(VkCommandBuffer commandBuffer)
	{
		pipeline->Bind(commandBuffer);

		for (auto& obj : gameObjects)
		{
			obj.transform2d.rotation = glm::mod(obj.transform2d.rotation + .01f, glm::two_pi<float>());

			SimplePushConstantData push{};
			push.offset = obj.transform2d.translation;
			push.color = obj.color;
			push.transform = obj.transform2d.mat2();

			vkCmdPushConstants(
				commandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(SimplePushConstantData),
				&push);

			obj.model->Bind(commandBuffer);
			obj.model->Draw(commandBuffer);
		}
	}

}

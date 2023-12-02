#include "qspch.h"
#include "RenderSystem.h"

#ifdef QS_DEBUG
	#define QS_SHADER_VERT_PATH "D:/CODE/QuasarEngine/bin/Debug-windows-x86_64/Sandbox/Shader/simple_shader.vert.spv"
	#define QS_SHADER_FRAG_PATH "D:/CODE/QuasarEngine/bin/Debug-windows-x86_64/Sandbox/Shader/simple_shader.frag.spv"
#else
	#define QS_SHADER_VERT_PATH "Shader/simple_shader.vert.spv"
	#define QS_SHADER_FRAG_PATH "Shader/simple_shader.frag.spv"
#endif

namespace Quasar {

	struct SimplePushConstantData
	{
		glm::mat4 transform{ 1.0f };
		glm::mat4 normalMatrix{ 1.0f };
	};

	RenderSystem::RenderSystem(Device& device, VkRenderPass renderPass) : _device(device)
	{
		CreatePipelineLayout();
		CreatePipeline(renderPass);
	}

	RenderSystem::~RenderSystem()
	{
		vkDestroyPipelineLayout(_device.device(), pipelineLayout, nullptr);
	}

	void RenderSystem::CreatePipelineLayout()
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
		if (vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
			VK_SUCCESS)
		{
			QS_CORE_ERROR("Failed to create pipeline layout");
		}
	}

	void RenderSystem::CreatePipeline(VkRenderPass renderPass)
	{
		assert(pipelineLayout != nullptr && "Can not create pipeline before pipeline layout");

		PipelineConfigInfo pipelineConfig{};
		Pipeline::DefaultPipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;

		pipeline = std::make_unique<Pipeline>
			(
				_device,
				QS_SHADER_VERT_PATH,
				QS_SHADER_FRAG_PATH,
				pipelineConfig
			);
	}

	void RenderSystem::RenderGameObjects(FrameInfo& frameInfo, std::vector<GameObject>& gameObjects)
	{
		pipeline->Bind(frameInfo.commandBuffer);

		auto projectionView = frameInfo.camera.GetProjection() * frameInfo.camera.GetView();

		for (auto& obj : gameObjects)
		{
			SimplePushConstantData push{};
			auto modelMatrix = obj.transform.mat4();
			if (obj.space == CAMERA_SPACE) 
			{
				push.transform = projectionView * modelMatrix;
			}
			if (obj.space == SCREEN_SPACE)
			{
				push.transform = frameInfo.camera.GetProjection() * modelMatrix;
			}
			push.normalMatrix = obj.transform.normalMatrix();
			vkCmdPushConstants(
				frameInfo.commandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(SimplePushConstantData),
				&push);

			obj.model->Bind(frameInfo.commandBuffer);
			obj.model->Draw(frameInfo.commandBuffer);
		}
	}
}

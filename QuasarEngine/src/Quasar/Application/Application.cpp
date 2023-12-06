/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		Quasar::Application implementation
-------------------------------------------------------------------------------
*/

#include "qspch.h"
#include "Application.h"

#include <Quasar/Input/KeyboardMovementController.h>

namespace Quasar {

	
	struct GlobalUbo
	{
		glm::mat4 projectionView{ 1.0f };

		glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f };  // w is intensity
		glm::vec3 lightPosition{ -1.f };
		alignas(16) glm::vec4 lightColor{ 1.f };  // w is light intensity
	};

	Application::Application() {
		globalPool =
			DescriptorPool::Builder(device)
			.setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();
		LoadGameObjects();
	}

	Application::~Application() {}

	void Application::Run()
	{
		std::vector<std::unique_ptr<Buffer>> uboBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);

		for (int i = 0; i < uboBuffers.size(); i++) {
			uboBuffers[i] = std::make_unique<Buffer>(
				device,
				sizeof(GlobalUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
			uboBuffers[i]->Map();
		}

		auto globalSetLayout =
			DescriptorSetLayout::Builder(device)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
			.build();

		std::vector<VkDescriptorSet> globalDescriptorSets(SwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalDescriptorSets.size(); i++) {
			auto bufferInfo = uboBuffers[i]->DescriptorInfo();
			DescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &bufferInfo)
				.build(globalDescriptorSets[i]);
		}

		RenderSystem renderSystem{
			device,
			renderer.GetSwapChainRenderPass(),
			globalSetLayout->getDescriptorSetLayout() };

		Camera camera{};
		//camera.SetViewDirection(glm::vec3{ 0.f }, glm::vec3{ .5f, .0f, 1.f });
		camera.SetViewTarget(glm::vec3{ -1.f, -2.f, 2.f }, glm::vec3{ 0.0f, 0.0f, 2.5f });

		auto viewerObject = GameObject::CreateGameObject();
		viewerObject.transform.translate.z = -2.5f;
		KeyboardMovementController cameraController{};

		// Initialize variables for FPS calculation
		auto startTime = std::chrono::high_resolution_clock::now();
		int frames = 0;

		auto currentTime = std::chrono::high_resolution_clock::now();

		// main game loop
		while (!window.ShouldClose())
		{
			glfwPollEvents();

			auto newTime = std::chrono::high_resolution_clock::now();
			float dt = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			currentTime = newTime;

			cameraController.MoveInPlaneXZ(window.GetGLFWwindow(), dt, viewerObject);
			camera.SetViewYXZ(viewerObject.transform.translate, viewerObject.transform.rotation);

			float aspect = renderer.GetAspectRatio();
			camera.SetPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 100.0f);

			if (auto commandBuffer = renderer.BeginFrame())
			{
				int frameIndex = renderer.GetFrameIndex();
				FrameInfo frameInfo
				{ 
					frameIndex, 
					dt, 
					commandBuffer, 
					camera, 
					globalDescriptorSets[frameIndex],
					gameObjects
				};

				// update
				GlobalUbo ubo{};
				ubo.projectionView = camera.GetProjection() * camera.GetView();
				uboBuffers[frameIndex]->WriteToBuffer(&ubo);
				uboBuffers[frameIndex]->Flush();

				// render
				renderer.BeginSwapChainRenderPass(commandBuffer);
				renderSystem.RenderGameObjects(frameInfo);
				renderer.EndSwapChainRenderPass(commandBuffer);

				renderer.EndFrame();
			}

			vkDeviceWaitIdle(device.device());

			FPS(frames, startTime);
		}
	}

	void Application::LoadGameObjects()
	{
		std::shared_ptr<Model> cubeModel = Model::CreateModelFromFile(device, "D:/CODE/QuasarEngine/Sandbox/models/smooth_vase.obj");
		auto cube = GameObject::CreateGameObject();
		cube.model = cubeModel;
		cube.transform.translate = { 0.0f, 0.5f, 0.f };
		cube.transform.scale = { 0.5f, 0.5f, 0.5f };
		gameObjects.emplace(cube.GetId(), std::move(cube));

		std::shared_ptr<Model> quadModel = Model::CreateModelFromFile(device, "D:/CODE/QuasarEngine/Sandbox/models/quad.obj");
		auto floor = GameObject::CreateGameObject();
		floor.model = quadModel;
		floor.transform.translate = { 0.0f, 0.5f, 0.f };
		floor.transform.scale = { 3.f, 1.f, 3.f };
		gameObjects.emplace(floor.GetId(), std::move(floor));
	}

	void Application::FPS(int& frames, std::chrono::time_point<std::chrono::high_resolution_clock>& startTime)
	{
		frames++;
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

		if (duration >= 1) {
			QS_CORE_TRACE("FPS: {0}", frames);

			frames = 0;
			startTime = currentTime;
		}
		
	}

}

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
		glm::vec3 lightDirection = glm::normalize(glm::vec3{ 1.f, -3.f, -1.f });
	};

	Application::Application() { LoadGameObjects(); }

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

		RenderSystem renderSystem{device, renderer.GetSwapChainRenderPass()};

		Camera camera{};
		//camera.SetViewDirection(glm::vec3{ 0.f }, glm::vec3{ .5f, .0f, 1.f });
		camera.SetViewTarget(glm::vec3{ -1.f, -2.f, 2.f }, glm::vec3{ 0.0f, 0.0f, 2.5f });

		auto viewerObject = GameObject::CreateGameObject();
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
			camera.SetPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 10.0f);

			if (auto commandBuffer = renderer.BeginFrame())
			{
				int frameIndex = renderer.GetFrameIndex();
				FrameInfo frameInfo{ frameIndex, dt, commandBuffer, camera };

				// update
				GlobalUbo ubo{};
				ubo.projectionView = camera.GetProjection() * camera.GetView();
				uboBuffers[frameIndex]->WriteToBuffer(&ubo);
				uboBuffers[frameIndex]->Flush();

				// render
				renderer.BeginSwapChainRenderPass(commandBuffer);
				renderSystem.RenderGameObjects(frameInfo, gameObjects);
				renderer.EndSwapChainRenderPass(commandBuffer);

				renderer.EndFrame();
			}

			vkDeviceWaitIdle(device.device());

			FPS(frames, startTime);
		}
	}

	void Application::LoadGameObjects()
	{
		std::shared_ptr<Model> model = Model::CreateModelFromFile(device, "D:/CODE/QuasarEngine/Sandbox/models/smooth_vase.obj");

		auto cube = GameObject::CreateGameObject();
		cube.model = model;
		cube.transform.translate = { 0.0f, 0.0f, 2.5f };
		cube.transform.scale = { 0.5f, 0.5f, 0.5f };

		gameObjects.push_back(std::move(cube));

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

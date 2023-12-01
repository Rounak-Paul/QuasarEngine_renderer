#include "qspch.h"
#include "Application.h"

#include <Quasar/Input/KeyboardMovementController.h>

namespace Quasar {

	Application::Application() 
	{
		LoadGameObjects();
	}

	Application::~Application() {}

	void Application::Run()
	{
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

		while (!window.ShouldClose())
		{
			glfwPollEvents();

			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			currentTime = newTime;

			cameraController.MoveInPlaneXZ(window.GetGLFWwindow(), frameTime, viewerObject);
			camera.SetViewYXZ(viewerObject.transform.translate, viewerObject.transform.rotation);

			float aspect = renderer.GetAspectRatio();
			camera.SetPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 10.0f);

			if (auto commandBuffer = renderer.BeginFrame())
			{
				renderer.BeginSwapChainRenderPass(commandBuffer);
				renderSystem.RenderGameObjects(commandBuffer, gameObjects, camera);
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

#include "qspch.h"
#include "Application.h"

namespace Quasar {

	Application::Application() 
	{
		LoadGameObjects();
	}

	Application::~Application() {}

	void Application::Run()
	{
		RenderSystem renderSystem{device, renderer.GetSwapChainRenderPass()};

		// Initialize variables for FPS calculation
		auto startTime = std::chrono::high_resolution_clock::now();
		int frames = 0;

		while (!window.ShouldClose())
		{
			glfwPollEvents();

			if (auto commandBuffer = renderer.BeginFrame())
			{
				renderer.BeginSwapChainRenderPass(commandBuffer);
				renderSystem.RenderGameObjects(commandBuffer, gameObjects);
				renderer.EndSwapChainRenderPass(commandBuffer);
				renderer.EndFrame();
			}

			vkDeviceWaitIdle(device.device());

			FPS(frames, startTime);
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
		triangle.transform2d.rotation = .01 * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
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

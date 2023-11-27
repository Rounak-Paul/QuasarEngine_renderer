#pragma once

#include <Quasar/Core.h>

#include <Quasar/Model/Model.h>
#include <Quasar/Window/Window.h>
#include <Quasar/Renderer/Device.h>
#include <Quasar/Renderer/Pipeline.h>
#include <Quasar/Renderer/Renderer.h>
#include <Quasar/GameObject/GameObject.h>

#include "qspch.h"


namespace Quasar {

	class QUASAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Run();

		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

	private:
		void LoadGameObjects();
		void CreatePipelineLayout();
		void CreatePipeline();
		void RenderGameObjects(VkCommandBuffer commandBuffer);

		Window window{ WIDTH, HEIGHT, "QuasarEngine" };
		Device device{ window };
		Renderer renderer{ window, device };

		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<GameObject> gameObjects;
	};

	// To be defined in Client
	Application* CreateApplication();

}



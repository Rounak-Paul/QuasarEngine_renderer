#pragma once

#include <Quasar/Core.h>

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
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void DrawFrame();

		Window window{ WIDTH, HEIGHT, "QuasarEngine" };
		Device device{ window };
		SwapChain swapChain{ device, window.getExtent() };
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};

	// To be defined in Client
	Application* CreateApplication();

}



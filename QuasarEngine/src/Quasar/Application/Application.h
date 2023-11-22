#pragma once

#include <Quasar/Core.h>

#include "qspch.h"


namespace Quasar {

	class QUASAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

	private:
		Window window{ WIDTH, HEIGHT, "QuasarEngine" };
		Device device{ window };
		Pipeline pipeline{
			device,
			"",
			"",
			Pipeline::DefaultPipelineConfigInfo(WIDTH, HEIGHT)
		};
	};

	// To be defined in Client
	Application* CreateApplication();

}



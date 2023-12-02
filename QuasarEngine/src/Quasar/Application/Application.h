#pragma once
#include "qspch.h"

#include <Quasar/Core.h>

#include <Quasar/RenderSystem/Model.h>
#include <Quasar/RenderSystem/RenderSystem.h>
#include <Quasar/RenderSystem/Buffer.h>
#include <Quasar/RenderSystem/FrameInfo.h>
#include <Quasar/GameObject/GameObject.h>

namespace Quasar {

	/// <summary>
	/// Create and Run main Application
	/// </summary>
	class QUASAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		/// <summary>
		/// Performs update and draw calls.
		/// </summary>
		void Run();

		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

	private:
		void LoadGameObjects();

		/// <summary>
		/// Prints FPS in Debug mode every 1s, To be called in a Loop.
		/// </summary>
		/// <param name="frames"></param>
		/// <param name="startTime"></param>
		void FPS(int& frames, std::chrono::time_point<std::chrono::high_resolution_clock>& startTime);

		Window window{ WIDTH, HEIGHT, "QuasarEngine" };
		Device device{ window };
		Renderer renderer{ window, device };

		std::vector<GameObject> gameObjects;
	};

	// To be defined in Client
	Application* CreateApplication();

}



/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		The Application class is the main interface between the 
					Urse Application and Quasar Engine. Create an instance of 
					this class and call Run() to start the Main Engine. 
-------------------------------------------------------------------------------
*/

#pragma once
#include "qspch.h"

#include <Core/Core.h>

#include <Core/RenderSystem/Model.h>
#include <Core/RenderSystem/RenderSystem.h>
#include <Core/RenderSystem/Buffer.h>
#include <Core/RenderSystem/FrameInfo.h>
#include <Core/RenderSystem/Descriptors.h>
#include <Core/GameObject/GameObject.h>

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

		// note: order of declarations matters
		std::unique_ptr<DescriptorPool> globalPool{};
		std::vector<GameObject> gameObjects;
	};

	// To be defined in Client
	Application* CreateApplication();

}



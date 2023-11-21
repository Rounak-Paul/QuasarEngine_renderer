#pragma once

#include "Quasar/Core.h"

#include "Quasar/Window/Window.h"

namespace Quasar {

	class QUASAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		Window window{ 800, 600, "QuasarEngine" };
	};

	// To be defined in Client
	Application* CreateApplication();

}



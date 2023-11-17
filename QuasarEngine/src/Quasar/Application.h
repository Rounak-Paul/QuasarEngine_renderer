#pragma once

#include "Core.h"

namespace Quasar {

	class QUASAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();

}



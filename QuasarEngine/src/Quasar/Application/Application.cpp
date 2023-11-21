#include "qspch.h"
#include "Application.h"

namespace Quasar {

	Application::Application() 
	{

	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{
		while (!window.shouldClose())
		{
			glfwPollEvents();
		}
	}

}

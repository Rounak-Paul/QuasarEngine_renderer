#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "qspch.h"

namespace Quasar 
{
	class Window
	{
	public:
		Window(int w, int h, std::string name);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		inline bool shouldClose() { return glfwWindowShouldClose(window); }

	private:
		void InitWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};
}



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

		inline bool ShouldClose() { return glfwWindowShouldClose(window); }
		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

	private:
		void InitWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};
}



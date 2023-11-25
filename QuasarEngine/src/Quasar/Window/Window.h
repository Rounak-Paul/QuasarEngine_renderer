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
		VkExtent2D GetExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }
		
		bool WasWindowResized() { return framebufferResized; }
		void ResetWindowResizedFlag() { framebufferResized = false; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

	private:
		static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);
		
		void InitWindow();

		int width;
		int height;
		bool framebufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};
}



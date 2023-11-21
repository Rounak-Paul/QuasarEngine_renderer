
-- Quasar Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["glm"] = "%{wks.location}/QuasarEngine/vendor/glm"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["GLFW"] = "%{wks.location}/QuasarEngine/vendor/glfw-3.3.8.bin.WIN64/include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["GLFWSDK"] = "%{wks.location}/QuasarEngine/vendor/glfw-3.3.8.bin.WIN64/lib-vc2022"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["GLFW"] = "%{LibraryDir.GLFWSDK}/glfw3.lib"


-- Quasar Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")
SHADER_COMPILER_SCRIPT = "%{wks.location}Sandbox/src/Shader/compile.bat"

IncludeDir = {}
IncludeDir["glm"] = "%{wks.location}/QuasarEngine/vendor/glm"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["GLFW"] = "%{wks.location}/QuasarEngine/vendor/glfw/include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["GLFWSDK"] = "%{wks.location}/QuasarEngine/vendor/glfw/lib-vc2022"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["GLFW"] = "%{LibraryDir.GLFWSDK}/glfw3.lib"

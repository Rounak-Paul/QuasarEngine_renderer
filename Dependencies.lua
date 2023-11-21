
-- Quasar Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["glm"] = "%{wks.location}/QuasarEngine/vendor/glm"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["GLFW"] = "%{wks.location}/QuasarEngine/vendor/GLFW/include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

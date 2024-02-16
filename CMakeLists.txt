cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
else()
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()

project(QuasarEngine)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DQS_DEBUG")
set(VULKAN_PATH "/Users/duke/VulkanSDK/1.3.275.0/macOS")
set(ENV{VK_ICD_FILENAMES} "${VULKAN_PATH}/share/vulkan/icd.d/MoltenVK_icd.json")
set(ENV{VK_LAYER_PATH} "${VULKAN_PATH}/share/vulkan/explicit_layer.d")

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/GLM)
add_subdirectory(vendor/LOGGER/SPDLOG)
add_subdirectory(vendor/DEARIMGUI)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(Quasar)
add_subdirectory(Editor)
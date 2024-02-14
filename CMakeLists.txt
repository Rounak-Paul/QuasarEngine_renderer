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

add_subdirectory(Vendor/GLFW)
add_subdirectory(Vendor/GLM)
add_subdirectory(Vendor/LOGGER/SPDLOG)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(Quasar)
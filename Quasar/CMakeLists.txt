file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/**/*.cpp
    src/**/*.h
    src/*.cpp
    src/*.h
)

# message (STATUS "Files in Quasar: ${SOURCES}")

add_library(Quasar SHARED ${SOURCES})
set_target_properties(Quasar PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(Quasar PUBLIC QS_BUILD_DLL)

target_precompile_headers(Quasar PUBLIC src/qspch.h)

target_include_directories(Quasar PUBLIC src)
target_include_directories(Quasar PUBLIC ${PROJECT_SOURCE_DIR}/Vendor/GLFW/include)
target_include_directories(Quasar PUBLIC ${PROJECT_SOURCE_DIR}/Vendor/GLM)
target_include_directories(Quasar PUBLIC ${PROJECT_SOURCE_DIR}/Vendor/LOGGER/SPDLOG/include)
target_include_directories(Quasar PUBLIC ${VULKAN_PATH}/include)

target_link_directories(Quasar PUBLIC ${VULKAN_PATH}/lib)

target_link_libraries(Quasar PUBLIC glfw)
target_link_libraries(Quasar PUBLIC glm)
target_link_libraries(Quasar PUBLIC spdlog)
target_link_libraries(Quasar PUBLIC ${VULKAN_PATH}/lib/libvulkan.1.dylib)
target_link_libraries(Quasar PUBLIC ${VULKAN_PATH}/lib/libvulkan.1.3.275.dylib)

add_custom_target(
    BuildShaders ALL
    COMMAND chmod +x "${PROJECT_SOURCE_DIR}/Quasar/src/Shader/compile.sh"
    COMMAND "${PROJECT_SOURCE_DIR}/Quasar/src/Shader/compile.sh" ${VULKAN_PATH} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shader
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Compile Shaders"
)
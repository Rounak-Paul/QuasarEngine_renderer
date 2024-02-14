file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/**/*.cpp
    src/**/*.h
)

# message (STATUS "Files in Quasar: ${SOURCES}")

add_library(Quasar SHARED ${SOURCES})
set_target_properties(Quasar PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(Quasar PRIVATE QS_BUILD_DLL)

target_precompile_headers(Quasar PRIVATE src/qspch.h)

target_include_directories(Quasar PRIVATE src)
target_include_directories(Quasar PUBLIC ${PROJECT_SOURCE_DIR}/Vendor/GLFW/include)
target_include_directories(Quasar PUBLIC ${PROJECT_SOURCE_DIR}/Vendor/GLM)
target_include_directories(Quasar PUBLIC ${PROJECT_SOURCE_DIR}/Vendor/SPDLOG/include)
target_include_directories(Quasar PUBLIC /Users/duke/VulkanSDK/1.3.275.0/macOS/include)

target_link_libraries(Quasar PUBLIC GLFW)
target_link_libraries(Quasar PUBLIC glm)
target_link_libraries(Quasar PUBLIC spdlog)
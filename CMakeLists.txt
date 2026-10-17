cmake_minimum_required(VERSION 3.22)
project(KaoMBShaderBridge LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    preloader_android
    GIT_REPOSITORY https://github.com/LiteLDev/preloader-android.git
    GIT_TAG 0.2.2
)
FetchContent_MakeAvailable(preloader_android)

add_library(kao_mb_shader_bridge SHARED
    src/KaoMBShaderBridge.cpp
)
target_compile_features(kao_mb_shader_bridge PRIVATE cxx_std_20)
target_link_libraries(kao_mb_shader_bridge PRIVATE preloader log android dl)
set_target_properties(kao_mb_shader_bridge PROPERTIES
    OUTPUT_NAME "kao_mb_shader_bridge"
)

set(PACKAGE_DIR "${CMAKE_BINARY_DIR}/levipack-root")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/dist")
file(MAKE_DIRECTORY "${PACKAGE_DIR}")
add_custom_target(package_levipack
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PACKAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/manifest.json" "${PACKAGE_DIR}/manifest.json"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:kao_mb_shader_bridge>" "${PACKAGE_DIR}/libkao_mb_shader_bridge.so"
    COMMAND ${CMAKE_COMMAND} -E tar cf "${OUTPUT_DIR}/KaoMBShaderBridge.levipack" --format=zip manifest.json libkao_mb_shader_bridge.so
    WORKING_DIRECTORY "${PACKAGE_DIR}"
    DEPENDS kao_mb_shader_bridge
    COMMENT "Packaging Levi native mod"
    VERBATIM
)

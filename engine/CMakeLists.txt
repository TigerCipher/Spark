#cmake_minimum_required(VERSION 3.23)
#project(Spark C)

set(CMAKE_C_STANDARD 17)

add_library(Engine SHARED src/Spark/Common.h src/Spark/Core/Logger.h src/Spark/Core/Logger.c src/Spark/Core/Asserts.h src/Spark/Platform/Platform.h src/Spark/Platform/PlatformWindows.c)
set_target_properties(Engine PROPERTIES LINKER_LANGUAGE C)
target_include_directories(Engine PRIVATE src)

if (WIN32)

    target_include_directories(Engine PRIVATE $ENV{VULKAN_SDK}/Include)
    target_link_directories(Engine PUBLIC $ENV{VULKAN_SDK}/Lib)
    target_link_libraries(Engine user32 vulkan-1)
    add_compile_definitions(_DEBUG SEXPORT _CRT_SECURE_NO_WARNINGS S_WINDOWS)

endif (WIN32)

if (UNIX)
    # linux vulkan includes, libs, etc
    add_compile_definitions(_DEBUG SEXPORT S_UNIX)
endif (UNIX)
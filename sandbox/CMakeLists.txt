set(CMAKE_C_STANDARD 17)

add_executable(sandbox src/main.c src/Game.h src/Game.c)
target_include_directories(sandbox PRIVATE src ../engine/src)
target_link_libraries(sandbox Engine)
add_compile_definitions(_DEBUG SIMPORT)

#add_custom_command(TARGET sandbox POST_BUILD        # Adds a post-build event to MyTest
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#        "${PROJECT_SOURCE_DIR}/cmake-build-debug/bin/engine/Engine.dll"      # <--this is in-file
#        $<TARGET_FILE_DIR:sandbox>)                 # <--this is out-file path
cmake_minimum_required(VERSION 3.22)
project(Janus)

set(CMAKE_CXX_STANDARD 20)

# Dependencies
# raylib
find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

include_directories(include)

set(SOURCES src/main.cpp
        include/world.hpp
        include/game.hpp
        include/tilemap.hpp
        include/game_camera.hpp
        src/world.cpp
        src/game.cpp
        src/tilemap.cpp
        src/game_camera.cpp
        include/global_values.hpp
        include/chunk.hpp src/chunk.cpp
        include/tile_data.hpp
        include/systems/tilemap_tick_system.hpp
        include/tile_math_helper.hpp
        include/systems/tilemap_render_system.hpp
        include/entities/entity.hpp
        include/components/components.hpp
        include/entities/player_entity.hpp
        include/systems/actor_render_system.hpp
        include/systems/tick_system.hpp
        include/systems/render_system.hpp
        include/systems/actor_tick_system.hpp
        include/physics/collisions.hpp
        src/physics/collisions.cpp
        src/noise/perlin_generator.cpp
        include/noise/perlin_generator.hpp
        include/systems/movement_system.hpp
        include/systems/player_tick_system.hpp
        include/renderer/chunk_renderer.hpp
        src/renderer/chunk_renderer.cpp
        include/renderer/block_tile_renderer.hpp
        src/renderer/block_tile_renderer.cpp
        include/texture_manager.hpp
        src/texture_manager.cpp
        src/tile_math_helper.cpp
        include/input_manager.hpp
        src/input_manager.cpp include/systems/startup_system.hpp include/systems/tilemap_preload_system.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

#resource files
function(copy_resources)
    foreach(arg IN LISTS ARGN)
        configure_file(${arg} ${arg} COPYONLY)
    endforeach()
endfunction()
copy_resources( resources/player.png
                resources/stone_wall_sheet.png
                resources/slime.png)

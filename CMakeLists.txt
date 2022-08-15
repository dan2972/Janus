cmake_minimum_required(VERSION 3.22)
project(Janus VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

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

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG v4.2.2
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

include_directories(include)

set(SOURCES src/main.cpp include/game_object.hpp include/entity_handler.hpp src/entity_handler.cpp include/player.hpp include/texture_manager.hpp src/texture_manager.cpp include/actor.hpp src/actor.cpp include/physics/collisions.hpp src/physics/collisions.cpp include/tile.hpp include/tilemap.hpp include/chunk.hpp include/game.hpp src/game.cpp include/game_camera.hpp include/random_generator.hpp src/random_generator.cpp src/tilemap.cpp src/chunk.cpp include/entity_renderer.hpp src/entity_renderer.cpp include/ground_tile.hpp include/object_tile.hpp include/tile_math_helper.hpp include/noise/perlin_generator.hpp src/noise/perlin_generator.cpp include/global_values.hpp include/drone.hpp include/chunk_renderer.hpp src/chunk_renderer.cpp src/game_camera.cpp include/wall_tile_renderer.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib raylib_cpp)

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
copy_resources(
        resources/slime.png
        resources/stone_wall_sheet.png
        resources/player.png
        )
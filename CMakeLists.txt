cmake_minimum_required(VERSION 2.8.4)
project(FallingBlocks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
main.cpp
lib/Allegro/source/display.cpp
lib/Allegro/source/event_queue.cpp
lib/Allegro/source/font.cpp
lib/Allegro/source/timer.cpp
lib/Allegro/display.h
lib/Allegro/event_queue.h
lib/Allegro/font.h
lib/Allegro/timer.h
lib/dashboard/small_blocks_visuals.h
lib/block.h
lib/block_basket.h
lib/constants.h
lib/dashboard.h
lib/enum_names.h
lib/game_grid.h
lib/game_handler.h
lib/global_states.h
lib/input_handler.h
lib/menu.h
lib/score.h
lib/simple_encryption.h
lib/speed_level.h
lib/text.h
)
add_executable(FallingBlocks ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

# Allegro5 includes directory
INCLUDE_DIRECTORIES( /usr/local/include/allegro5/ )

target_link_libraries(FallingBlocks -lallegro -lallegro_font -lallegro_ttf -lallegro_main -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec)

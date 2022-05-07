cmake_minimum_required(VERSION 3.23)
project(gregchess)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(spdlog REQUIRED)
include_directories(gregchess ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(gregchess src/main.cpp src/ui/Window.cpp src/ui/Window.h src/ui/Renderable.h src/ui/Board.cpp src/ui/Board.h src/ui/Game.cpp src/ui/Game.h src/ui/Renderable.cpp src/GameState.cpp src/GameState.h src/CompactPiece.cpp src/CompactPiece.h src/ui/ColoredPiece.cpp src/ui/ColoredPiece.h src/common.h src/Move.cpp src/Move.h src/Coord.h src/Coord.cpp)
target_link_libraries(gregchess ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} spdlog::spdlog)
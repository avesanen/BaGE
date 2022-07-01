cmake_minimum_required(VERSION 3.22)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

# Lua
find_package(Lua 5.4 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

include_directories(include)

set(SOURCE_FILES src/main.cpp src/Engine.cpp)

add_executable(Engine ${SOURCE_FILES})
target_link_libraries(Engine ${LUA_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

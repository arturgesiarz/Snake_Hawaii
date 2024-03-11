cmake_minimum_required(VERSION 3.27)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake src/main.cpp
        src/Button.cpp
        include/Button.h
        src/Screen.cpp
        include/Screen.h
        include/GameParameters.h
        include/Snake.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include/SFML)
target_link_libraries(Snake sfml-system sfml-window sfml-graphics sfml-audio)
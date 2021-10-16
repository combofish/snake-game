cmake_minimum_required(VERSION 3.5)
project(Snake LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
find_package(FLTK REQUIRED NO_MODULE)
add_executable(${PROJECT_NAME} WIN32
  main.cpp
  dot.cpp
  snake.cpp
  snake_window.cpp
  GUI_Interface/Graph.cpp
  GUI_Interface/GUI.cpp
  GUI_Interface/Window.cpp )
target_link_libraries(${PROJECT_NAME} fltk fltk_images)  


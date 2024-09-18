cmake_minimum_required(VERSION 3.28)

project("BrokenWorld" VERSION 0.0.3)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH ./lib/SDL2-2.30.7/x86_64-w64-mingw32)

find_package(SDL2 REQUIRED)
find_library(NAME SDL2_image REQUIRED)
find_library(NAME SDL2_mix REQUIRED)
find_library(NAME SDL2_ttf REQUIRED)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS})

link_libraries(SDL2_image)
link_libraries(SDL2_ttf)
#link_libraries(SDL2_mix)


add_executable(${PROJECT_NAME} src/main.cpp src/main_menu.cpp src/texture_library.cpp src/war.cpp)

target_link_libraries(${PROJECT_NAME}  ${SDL2_LIBRARIES})

cmake_minimum_required(VERSION 3.27)
project(SFML)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_TOOLCHAIN_FILE C:/Users/user/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(SFML_DIR C:/Users/user/.vcpkg-clion/vcpkg/installed/x64-windows/share/sfml)

add_executable(SFML main.cpp)

#include(C:/Users/user/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/share/sfml)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(SFML PRIVATE sfml-system sfml-window sfml-graphics sfml-network)
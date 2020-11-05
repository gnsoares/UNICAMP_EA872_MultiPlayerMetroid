# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(metroid)

#
add_executable(metroid src/main.cpp)

# Especificar onde estao os header files
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(models src/models.cpp)
target_link_libraries(metroid models)

add_library(views src/views.cpp)
target_link_libraries(metroid views)

add_library(controllers src/samusController.cpp)
target_link_libraries(metroid controllers)

add_library(utils src/utils.cpp)
target_link_libraries(metroid utils)


# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_link_libraries(metroid SDL2)
target_link_libraries(metroid SDL2_image)



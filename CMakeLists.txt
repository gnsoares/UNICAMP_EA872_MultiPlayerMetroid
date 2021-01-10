# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(metroid)

#
add_executable(metroid src/main.cpp)

# Especificar onde estao os header files
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(controllers src/controllers.cpp)
target_link_libraries(metroid controllers)

add_library(models src/models.cpp)
target_link_libraries(metroid models)

add_library(receivers src/receivers.cpp)
target_link_libraries(metroid receivers)


add_library(utils src/utils.cpp)
target_link_libraries(metroid utils)

add_library(views src/views.cpp)
target_link_libraries(metroid views)

# Bibliotecas externas
target_link_libraries(metroid SDL2)
target_link_libraries(metroid SDL2_image)
target_link_libraries(metroid pthread)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

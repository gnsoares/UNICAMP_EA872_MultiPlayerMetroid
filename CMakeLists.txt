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

add_library(controllers src/controllers.cpp)
target_link_libraries(metroid controllers)


# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

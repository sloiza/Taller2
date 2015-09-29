cmake_minimum_required(VERSION 2.8)
project(Servidor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")

enable_testing()

option(INCLUIR_TEST ON)

# defino una target por carpeta. cada target contiene las clases de cada carpeta.
file(GLOB SRC src/main.cpp)
file(GLOB SRC_CONEXION "src/conexion/*.cpp" src/conexion/mongoose.c)
file(GLOB SRC_CONEXION_REQUEST "src/conexion/request/*.cpp")
file(GLOB SRC_UTILES "src/utiles/*.cpp")

file(GLOB SRC_COMPLETO ${SRC} ${SRC_CONEXION} ${SRC_CONEXION_REQUEST} ${SRC_UTILES})

add_executable(servidor ${SRC_COMPLETO})

if(INCLUIR_TEST)
	add_subdirectory(test)
	target_link_libraries(servidor "-fprofile-arcs -ftest-coverage")
endif()

install(TARGETS servidor DESTINATION bin)

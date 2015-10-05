cmake_minimum_required(VERSION 2.8)
project(Servidor)

#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread -lrocksdb")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")

enable_testing()

option(INCLUIR_TEST ON)


# defino una target por carpeta. cada target contiene las clases de cada carpeta.
file(GLOB SRC src/main.cpp)
file(GLOB SRC_CONEXION "src/conexion/*.cpp" src/conexion/mongoose.c)
file(GLOB SRC_CONEXION_REQUEST "src/conexion/request/*.cpp")
file(GLOB SRC_UTILES "src/utiles/*.cpp")
file(GLOB SRC_DB_ROCKS "src/database/*.cpp")

file(GLOB SRC_COMPLETO ${SRC} ${SRC_CONEXION} ${SRC_CONEXION_REQUEST} ${SRC_UTILES} ${SRC_DB_ROCKS})

add_executable(servidor ${SRC_COMPLETO})
include_directories(libz)
add_library(libz STATIC IMPORTED)
set_property(TARGET libz PROPERTY IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libz.a)

include_directories(snappy)
add_library(snappy STATIC IMPORTED)
set_property(TARGET snappy PROPERTY IMPORTED_LOCATION /usr/lib/libsnappy.a)

include_directories(bz2)
add_library(bz2 STATIC IMPORTED)
set_property(TARGET bz2 PROPERTY IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libbz2.a)

target_link_libraries(servidor rocksdb libz snappy bz2)


if(INCLUIR_TEST)
	add_subdirectory(test)
	target_link_libraries(servidor "-fprofile-arcs -ftest-coverage")
endif()

install(TARGETS servidor DESTINATION bin)

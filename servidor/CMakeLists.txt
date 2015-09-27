cmake_minimum_required(VERSION 2.8)
project(Servidor)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread -lrocksdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")

#set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage -g -O0 --coverage ${CMAKE_CXX_FLAGS}")

enable_testing()

option(INCLUIR_TEST ON)

add_executable(servidor src/main.cpp src/conexion/Servidor.cpp src/conexion/HandlerEventos.cpp src/conexion/mongoose.c src/utiles/LectorParametros.cpp)

## esto es igual a lo que estamos haciendo: agregar '-lrocksdb' a los flags ###
#include_directories(rocksdb)
#add_library(rocksdb STATIC IMPORTED)
#set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION /usr/local/lib/librocksdb.a)

#include_directories(libz)
#add_library(libz STATIC IMPORTED)
#set_property(TARGET libz PROPERTY IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libz.a)

#include_directories(snappy)
#add_library(snappy STATIC IMPORTED)
#set_property(TARGET snappy PROPERTY IMPORTED_LOCATION /usr/lib/libsnappy.a)

#include_directories(bz2)
#add_library(bz2 STATIC IMPORTED)
#set_property(TARGET bz2 PROPERTY IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libbz2.a)

#target_link_libraries(servidor rocksdb libz snappy bz2)

if(INCLUIR_TEST)
	add_subdirectory(test)
	target_link_libraries(servidor "-fprofile-arcs -ftest-coverage")
endif()

install(TARGETS servidor DESTINATION bin)

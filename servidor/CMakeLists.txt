cmake_minimum_required(VERSION 2.8)
project(Servidor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread -fprofile-arcs -ftest-coverage -DMONGOOSE_ENABLE_THREADS --coverage ")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -DMONGOOSE_ENABLE_THREADS")

enable_testing()

option(INCLUIR_TEST ON)

# defino una target por carpeta. cada target contiene las clases de cada carpeta.
file(GLOB SRC src/main.cpp)
file(GLOB SRC_CONEXION "src/conexion/*.cpp" src/conexion/mongoose.c)
file(GLOB SRC_CONEXION_REQUEST "src/conexion/request/*.cpp")
file(GLOB SRC_UTILES "src/utiles/*.cpp")
file(GLOB SRC_BD "src/bd/*.cpp")
file(GLOB SRC_BD_ENTIDADES "src/bd/entidades/*.cpp")
file(GLOB SRC_ARCHIVOS "src/archivos/*.cpp")
file(GLOB SRC_OPERACIONES "src/operaciones/*.cpp")

file(GLOB SRC_COMPLETO ${SRC} ${SRC_CONEXION} ${SRC_ARCHIVOS} ${SRC_OPERACIONES} ${SRC_CONEXION_REQUEST} ${SRC_UTILES} ${SRC_BD} ${SRC_BD_ENTIDADES})

add_executable(servidor ${SRC_COMPLETO})

target_link_libraries(servidor /usr/local/lib/librocksdb.a)
target_link_libraries(servidor /usr/lib/x86_64-linux-gnu/libz.so)
target_link_libraries(servidor /usr/lib/libsnappy.so)
target_link_libraries(servidor /usr/lib/x86_64-linux-gnu/libbz2.so)
target_link_libraries(servidor /usr/local/lib/libjsoncpp.a)

if(INCLUIR_TEST)
	add_subdirectory(test)
	target_link_libraries(servidor /usr/lib/gcc/x86_64-linux-gnu/4.8/libgcov.a)
endif()

install(TARGETS servidor DESTINATION bin)

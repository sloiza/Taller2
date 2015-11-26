include(FindPkgConfig)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread -fprofile-arcs -ftest-coverage --coverage")
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${SRC_DIR})
include_directories(${GTEST_INCLUDE_DIR})

find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test/tmp)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test/tmp/carpetaVacia)

file(GLOB TEST correrTests.cpp)
file(GLOB TEST_CONEXION "conexion/*.cpp" conexion/mongoose.cpp)
file(GLOB TEST_BD "bd/*.cpp")
file(GLOB TEST_ARCHIVOS "archivos/*.cpp")
file(GLOB TEST_OPERACIONES "operaciones/*.cpp")
file(GLOB TEST_BD_ENTIDADES "bd/entidades/*.cpp")
file(GLOB SRC_CONEXION "../src/conexion/*.cpp" ../src/conexion/mongoose.cpp)
file(GLOB SRC_CONEXION_REQUEST "../src/conexion/request/*.cpp" )
file(GLOB SRC_UTILES "../src/utiles/*.cpp")
file(GLOB SRC_BD "../src/bd/*.cpp")
file(GLOB SRC_ARCHIVOS "../src/archivos/*.cpp")
file(GLOB SRC_OPERACIONES "../src/operaciones/*.cpp")
file(GLOB SRC_BD_ENTIDADES "../src/bd/entidades/*.cpp")

file(GLOB TEST_COMPLETO ${TEST} ${TEST_CONEXION} ${TEST_BD} ${TEST_ARCHIVOS} ${TEST_OPERACIONES} ${TEST_BD_ENTIDADES} ${SRC_CONEXION} ${SRC_CONEXION_REQUEST} ${SRC_UTILES} ${SRC_BD} ${SRC_ARCHIVOS} ${SRC_OPERACIONES} ${SRC_BD_ENTIDADES})

add_executable(tests ${TEST_COMPLETO})

target_link_libraries(tests ${GTEST_LIBRARY})
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(tests /usr/local/lib/librocksdb.a)
target_link_libraries(tests /usr/lib/x86_64-linux-gnu/libz.so)
target_link_libraries(tests /usr/lib/libsnappy.so)
target_link_libraries(tests /usr/lib/x86_64-linux-gnu/libbz2.so)
#target_link_libraries(tests /usr/local/lib/libjsoncpp.a)
#target_link_libraries(tests /usr/lib/gcc/x86_64-linux-gnu/4.8/libgcov.a)
add_test(CorrerTestUnitarios tests)
#install(TARGETS tests DESTINATION bin)
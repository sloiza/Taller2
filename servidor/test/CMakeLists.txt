include(FindPkgConfig)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${SRC_DIR})
include_directories(${GTEST_INCLUDE_DIR})

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

file(GLOB TEST correrTests.cpp)
file(GLOB TEST_CONEXION "conexion/*.cpp" conexion/mongoose.c)
file(GLOB SRC_CONEXION "../src/conexion/*.cpp" ../src/conexion/mongoose.c)
file(GLOB SRC_CONEXION_REQUEST "../src/conexion/request/*.cpp" )
file(GLOB SRC_UTILES "../src/utiles/*.cpp")

file(GLOB TEST_COMPLETO ${TEST} ${TEST_CONEXION} ${SRC_CONEXION} ${SRC_CONEXION_REQUEST} ${SRC_UTILES})

add_executable(tests ${TEST_COMPLETO})

target_link_libraries(tests ${GTEST_LIBRARY})
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT})
add_test(CorrerTestUnitarios tests)
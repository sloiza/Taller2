include(FindPkgConfig)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${SRC_DIR})
include_directories(${GTEST_INCLUDE_DIR})

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

#SET(SRC_SOURCES ${SRC_DIR}/expression.cpp ${SRC_DIR}/expressionparser.cpp ${SRC_DIR}/operator.cpp)

SET(SRC_SOURCES ${SRC_DIR}/conexion/Servidor.cpp ${SRC_DIR}/conexion/HandlerEventos.cpp ${SRC_DIR}/conexion/mongoose.c)

add_executable(tests correrTests.cpp conexion/ConexionTest.cpp ${SRC_SOURCES})
target_link_libraries(tests ${GTEST_LIBRARY})
target_link_libraries(tests ${CMAKE_THREAD_LIBS_INIT})
add_test(CorrerTestUnitarios tests)
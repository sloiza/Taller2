#!/usr/bin/env bash

# borro cobertura anterior
rm -r Documentation/cov/

mkdir Documentation/cov/

lcov --capture --directory servidor/build/test/CMakeFiles/tests.dir/__/src/ --output-file Documentation/cov/coverage.info

# saco lo q no esta cubierto
lcov -r Documentation/cov/coverage.info /usr/include/\* -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info /usr/local/include/\* -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info operaciones/Op\* -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info operaciones/Acciones.cpp -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info bd/json\* -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info conexion/mongoose.cpp -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info conexion/HandlerEventos.cpp -o Documentation/cov/coverage.info
lcov -r Documentation/cov/coverage.info utiles/LectorParametros.cpp -o Documentation/cov/coverage.info

#lcov -r servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/Op* -o coverage.info
#lcov -r servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/Info* -o coverage.info
#lcov -r servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/bd/jsoncpp.cpp -o coverage.info
#lcov -r servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/bd/json/* -o coverage.info

genhtml Documentation/cov/coverage.info --output-directory Documentation/cov/
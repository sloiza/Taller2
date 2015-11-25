
# borro cobertura anterior
rm -r Documentation/cov/

mkdir Documentation/cov/

lcov --capture --directory servidor/build/test/CMakeFiles/tests.dir/__/src --output-file Documentation/cov/coverage.info

# saco lo q no esta cubierto
lcov -r coverage.info /usr/\* -o coverage.info
#lcov -r coverage.info servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/Op\* -o coverage.info
#lcov -r coverage.info servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/Info\* -o coverage.info
#lcov -r coverage.info servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/bd/jsoncpp.cpp -o coverage.info
#lcov -r coverage.info servidor/build/test/CMakeFiles/tests.dir/__/src/operaciones/bd/json/\* -o coverage.info

genhtml Documentation/cov/coverage.info --output-directory Documentation/cov/
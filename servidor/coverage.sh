#!/usr/bin/env bash
cd /Taller2-master/servidor/build
make
make test
#coveralls --exclude lib --exclude tests --gcov-options '\-lp'

cd /Taller2-master/servidor/

coveralls -i src -i test -E '.*\/mongoose\/mongoose\.[hc]' -E '.*CMakeFiles/feature_tests\..*' -E '.*CMakeCXXCompilerId\.cpp' -E '.*CMakeCCompilerId\.c' -E '.*\/test\/.*\.(h|hpp|cpp)$' -r ./
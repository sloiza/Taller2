
mkdir Documentation/cov/

lcov --capture --directory servidor/build/CMakeFiles/servidor.dir/src/ --output-file Documentation/cov/coverage.info

genhtml Documentation/cov/coverage.info --output-directory Documentation/cov/
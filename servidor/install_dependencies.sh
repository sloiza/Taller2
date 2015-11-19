#!/usr/bin/env bash

mkdir installs/
cd installs/
wget https://github.com/open-source-parsers/jsoncpp/archive/master.zip
unzip master.zip 
ls
echo "install jsoncpp"
cd jsoncpp-master/ 
mkdir -p build/debug 
cd build/debug/ 
cmake -DCMAKE_BUILD_TYPE=debug -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G "Unix Makefiles" ../.. 
make
make install
cd ../..
cd /usr/src/gtest
cmake .
cmake --build . 
mv libg* /usr/local/lib/ ; cd -
wget https://github.com/sloiza/rocksdb-travis/archive/master.zip
unzip master.zip
echo "install rocks"
cd rocksdb-travis-master/ROCKS/ 
make
sudo make install
rm master.zip
cd ../../..
echo "install server"
ls
cd Taller2-master/servidor/
mkdir build/
cd build
cmake ..
make
cd ..
ls

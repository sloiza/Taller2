#!/usr/bin/env bash

mkdir -p installs/
cd installs/
if [ ! -d "jsoncpp-master/" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
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
fi
cd /usr/src/gtest
cmake .
cmake --build . 
mv libg* /usr/local/lib/ ; cd -
if [ ! -d "rocksdb-travis-master/" ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
	wget https://github.com/sloiza/rocksdb-travis/archive/master.zip
	unzip master.zip
	echo "install rocks"
	cd rocksdb-travis-master/ROCKS/ 
	make
	make static_lib
	rm master.zip
	cd ../../..
fi

echo "install server"
ls
cd Taller2-master/servidor/
mkdir build/
cd build
cmake ..
make
cd ..
ls

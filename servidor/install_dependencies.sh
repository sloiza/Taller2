#!/usr/bin/env bash

mkdir -p installs/
cd installs/
if [ ! -d "jsoncpp-master/" ]; then
  	wget https://github.com/open-source-parsers/jsoncpp/archive/master.zip
	unzip master.zip 
	echo "install jsoncpp"
	cd jsoncpp-master/ 
	python amalgamate.py
	mkdir -p build/debug
	cd build/debug
	cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" ../..
	make
	sudo make install
	rm ../master.zip
	cd ../../..
fi
if [ ! -d "rocksdb-master/" ]; then
  	wget https://github.com/NickCis/rocksdb/archive/master.zip
	unzip master.zip
	echo "install rocks"
	cd rocksdb-master
	make static_lib
	make shared_lib
	sudo make install
	rm ../master.zip
fi
cd /usr/src/gtest
cmake .
cmake --build . 
sudo mv libg* /usr/local/lib/ ; cd -
cd
echo "install server"
ls
cd Taller2-master/servidor/
mkdir build/
cd build
cmake ..
make
cd ..
ls

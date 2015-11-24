#!/usr/bin/env bash

mkdir -p installs/
cd installs/
echo "install rocks"
if [ ! -d "rocksdb-master/" ]; then
  	wget https://github.com/NickCis/rocksdb/archive/master.zip
	unzip master.zip
	cd rocksdb-master
	make static_lib
	make shared_lib
	sudo make install
	cd ..
	ls
	rm master.zip
fi
cd /usr/src/gtest
cmake .
cmake --build . 
sudo mv libg* /usr/local/lib/ ; cd -
cd
echo "install server"
ls
cd /Taller2-master/servidor/
mkdir build/
cd build
cmake ..
make

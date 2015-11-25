#!/usr/bin/env bash

mkdir -p installs/
cd installs/
echo "install rocks"
if [ ! -d "rocksdb-master/" ]; then
  	wget https://github.com/NickCis/rocksdb/archive/master.zip
	unzip master.zip
	rm master.zip
	cd rocksdb-master
	make static_lib
	sudo cp librocksdb.a /usr/local/lib/
	ls
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
cmake -DINCLUIR_TEST=ON ..
make

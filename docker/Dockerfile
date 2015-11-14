FROM ubuntu:14.04
RUN sudo apt-get -y install software-properties-common
RUN sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
RUN sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
RUN sudo add-apt-repository -y ppa:fkrull/deadsnakes
RUN sudo apt-get update
RUN sudo apt-get install -y wget
RUN sudo apt-get install -y -qq gcc-4.9 g++-4.9 libgtest-dev zlib1g-dev libbz2-dev libsnappy-dev
RUN sudo apt-get install python2.7
RUN sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 50
RUN sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 50
RUN wget https://github.com/sloiza/rocksdb-travis/archive/master.zip
RUN sudo apt-get install unzip 
RUN unzip master.zip
RUN cd rocksdb-travis-master/ROCKS/ 
RUN sudo make clean && \
	sudo make install && \
	sudo rm master.zip
RUN wget https://github.com/open-source-parsers/jsoncpp/archive/master.zip && \
    unzip master.zip && \
    cd jsoncpp-master/ && \
    mkdir -p build/ && \
    cd build/ && \
    cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" ../.. && \
    sudo make install && \
    sudo make
RUN cd ../..
	cd /usr/src/gtest && \
	sudo cmake . && \
	sudo cmake --build . && \
	sudo mv libg* /usr/local/lib/ ; cd -
RUN sudo pip install cpp-coveralls
RUN mkdir servidor/build
RUN cd servidor/build && \
	cmake -DINCLUIR_TEST=ON .. && \
	make && \
	make test
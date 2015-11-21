FROM ubuntu:14.04
RUN  apt-get -y install software-properties-common
RUN  add-apt-repository --yes ppa:ubuntu-toolchain-r/test
RUN  add-apt-repository -y ppa:george-edison55/cmake-3.x
RUN  add-apt-repository -y ppa:fkrull/deadsnakes
RUN  update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 50
RUN  update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 50
RUN  apt-get update
RUN  apt-get install -y wget
RUN  apt-get install -y cmake
RUN  apt-get install -y unzip 
RUN  apt-get install -y -qq gcc-4.9 g++-4.9 libgtest-dev zlib1g-dev libbz2-dev libsnappy-dev
RUN  apt-get install -y python2.7
RUN  apt-get install -y python-pip
RUN  pip install cpp-coveralls
RUN  unzip master.zip
RUN  wget https://github.com/sloiza/Taller2/archive/master.zip 
CMD  ./Taller2-master/servidor/install_dependencies.sh
CMD  ./Taller2-master/servidor/build/servidor

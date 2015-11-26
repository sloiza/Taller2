Guía de Administrador
=======================

Guía para: instalación, configuración, ejecución

Instalación
------------

Desde la linea de comando descarge el codigo e instale su propia copia:

.. code-block:: bash

   $ git clone https://github.com/sloiza/Taller2.git 


Dependencias
------------

Instalación rocksdb:

.. code-block:: bash
   $ wget https://github.com/facebook/rocksdb/archive/v4.1.zip
   $ unzip v4.1.zip
   $ cd rocksdb-4.1
   $ make static_lib
   $ sudo make install

El resto de las dependencias:

.. code-block:: bash

   $ sudo apt-get install libsnappy-dev
   $ sudo apt-get install zlib1g-dev
   $ sudo apt-get install libbz2-dev

Compilación
------------

En la carpeta root del proyecto:

.. code-block:: bash

   $ cd /servidor
   $ mkdir build  
   $ cd /build  
   $ cmake ..  
   $ make  

   En caso que ejecutemos los test debemos compilar con:

   $ cmake -DINCLUIR_TEST=ON ..

Ejecución
-----------

Una vez finalizado, ejecutar el servidor:

.. code-block:: bash

   $ ./servidor

Ejecución con docker
---------------------

Si no fue instalado previamente:

   $ sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D

Abrir '/etc/apt/sources.list.d/docker.list' y agregar 'deb https://apt.dockerproject.org/repo ubuntu-trusty main' si el OS es Ubuntu 14.04

   $ sudo apt-get update
   $ sudo apt-get purge lxc-docker
   $ sudo apt-cache policy docker-engine

   $ sudo apt-get install linux-image-extra-$(uname -r)
   $ sudo apt-get update
   $ sudo apt-get install linux-image-generic-lts-trusty
   $ sudo reboot
   $ sudo apt-get install docker-engine
   $ sudo service docker start

Para obtener la imagen correcta:   

   $ sudo docker pull samiloiza/Taller2:latest

   Para correr la imagen:

   $ sudo docker run -t -i samiloiza/Taller2:latest /bin/bash  ./Taller2-master/servidor/run.sh



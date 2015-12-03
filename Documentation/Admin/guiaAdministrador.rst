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

   $ sudo apt-get install libgflags-dev
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

.. code-block:: bash

   $ cmake -DINCLUIR_TEST=ON ..

Ejecución
-----------

Una vez finalizado, ejecutar el servidor:

.. code-block:: bash

   $ ./servidor

Ejecución con docker
---------------------

Si no fue instalado previamente:

`Install Docker`_.

.. _Install Docker: https://docs.docker.com/engine/installation/ubuntulinux/

Para obtener la imagen correcta:   

.. code-block:: bash

   $ sudo docker pull samiloiza/Taller2:latest

Para correr la imagen:

.. code-block:: bash

   $ sudo docker run -t -i samiloiza/Taller2:latest /bin/bash  ./Taller2-master/servidor/run.sh



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
   
   $ wget https://github.com/sloiza/rocksdb-travis/archive/master.zip
   $ unzip master.zip
   $ cd rocksdb-travis-master/ROCKS/ 
   $ make
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


Ejecución
-----------

Una vez finalizado, ejecutar el servidor:

.. code-block:: bash

   $ ./servidor



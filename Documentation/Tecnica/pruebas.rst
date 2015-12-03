Pruebas y Cobertura
=====================

Instrucciones para correr los test unitarios y calcular el coverage del código

Pruebas
------------

Sobre la carpeta Servidor/build ejecutar:

.. code-block:: bash

   $ make test


Si no se ha compilado el servidor, antes debe ejecutarse sobre la carpeta servidor/build:

.. code-block:: bash

   $ cmake -DINCLUIR_TEST=ON ..
   $ make 


Cobertura
----------

Desde la consola ingresar:

.. code-block:: bash

   $ sudo apt-get install lcov

Se ha agregado un script que recoge la información de cobertura a través de las pruebas y la muestra en un explorador web. Para correr este script, dirigirse desde la consola a la carpeta de servidor/build e ingresar:

.. code-block:: bash

   $ cd /
   $ bash generar_doc_cov.sh




Pruebas y Cobertura
=====================

Instrucciones para correr los test unitarios y calcular el coverage del código

Pruebas
------------

Sobre la carpeta Servidor/build ejecutar:

.. code-block:: bash

   $ make tests 


Si no se ha compilado el servidor, antes debe ejecutarse sobre la carpeta servidor/build:

.. code-block:: bash

   $ cmake -DINCLUIR_TEST=ON ..
   $ make 


Pruebas REST API
-----------------


.. code-block:: bash

   $ python restTester.py


Cobertura
----------


Desde la consola ingresar:

.. code-block:: bash

   $ sudo apt-get install lcov

Se ha agregado un script que recoge la información de cobertura a través de las pruebas y la muestra en un explorador web. Para correr este script, dirigirse desde la consola a la carpeta de Servidor/ e ingresar:

.. code-block:: bash

   $ sh cobertura.sh

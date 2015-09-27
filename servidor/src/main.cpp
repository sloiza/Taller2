/*
 * main.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

// Conexion Servidor
#include "conexion/Servidor.h"
#include "utiles/LectorParametros.h"
#include "database/rocks_db.h"
 
 //to test db
#include <cstdio>
#include <string>
#include <iostream>
#include <assert.h>


using namespace rocksdb;

namespace test{
  int test_db() {
    rocks_db* rocks = new rocks_db();
    cout << "After create " << endl;
    // DB* db = rocks->get_db();
    cout << "paso  \n";
    Status s;
    // Put key-value
    s = rocks->put("key1","apolo");
    assert(s.ok());
    cout << "INSERT \n";
    string value;
    // get value
    s = rocks->get("key1", &value);
    assert(s.ok());
    assert(value == "apolo");
    printf("%s \n",value.c_str());
    cout << "LEYO, delete rocks "<< endl;
    printf(" db pointer defore %p\n", rocks);
    delete rocks;
    printf(" db pointer after %p\n", rocks);

    return 0;

  }
}



int main(int argc, char** argv)
{
	using namespace test;
	ConexionServidor::LectorParametros lector;
	test_db();

	lector.leerParametros(argc, argv);

	if( lector.getAyuda() )
	{
		Utiles::imprimirAyuda();
		return 0;
	}

	ConexionServidor::Servidor servidor;

	servidor.crear(lector.getPuertoInt());

	std::cout << "Servidor creado!\n";

	while( servidor.estaCorriendo() )
	{
		servidor.correr(1000);
	}
	std::cout << "\nServidor cerrado. Saliendo...\n";
	servidor.destruir();
}




/*
 * main.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

// Conexion Servidor
#include "conexion/Servidor.h"
#include "utiles/LectorParametros.h"
#include "utiles/Log.h"
#include "database/rocks_db.h"
#include "testDB.cpp"
 
 //to test db
#include <cstdio>
#include <string>
#include <iostream>
#include <assert.h>


using namespace rocksdb;



int main(int argc, char** argv)
{
	using namespace test;
	ConexionServidor::LectorParametros lector;
	//test_db();
//testUser();

	lector.leerParametros(argc, argv);

	if( lector.getAyuda() )
	{
		Utiles::imprimirAyuda();
		return 0;
	}

	ConexionServidor::Servidor servidor;

	servidor.crear(lector.getPuertoInt());

	std::cout << "Servidor creado!\n";
	Utiles::Log::instancia()->info("Servidor creado!", "main.cpp");

	while( servidor.estaCorriendo() )
	{
		servidor.correr(1000);
	}
	std::cout << "\nServidor cerrado. Saliendo...\n";
	Utiles::Log::instancia()->info("Servidor cerrado.", "main.cpp");
	servidor.destruir();
}




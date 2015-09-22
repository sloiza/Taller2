/*
 * main.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

// Conexion Servidor
#include "conexion/Servidor.h"
#include "utiles/LectorParametros.h"

int main(int argc, char** argv)
{
	ConexionServidor::LectorParametros lector;

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


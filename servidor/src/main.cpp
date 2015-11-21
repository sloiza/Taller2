/*
 * main.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

// Conexion Servidor
#include "conexion/Servidor.h"
#include "conexion/ServidorMultihilo.h"
#include "utiles/LectorParametros.h"
#include "utiles/Log.h"

int main(int argc, char** argv)
{
	ConexionServidor::LectorParametros lector;

	lector.leerParametros(argc, argv);

	if( lector.getAyuda() )
	{
		Utiles::Metodos::imprimirAyuda();
		return 0;
	}

	ConexionServidor::ServidorMultihilo servidor;
	servidor.setPuerto(8080);
	//servidor.setNumeroDeHilos(lector.getNumeroDeHilos());
	servidor.setNumeroDeHilos(3);

	servidor.crear();

	std::cout << "Servidor creado!\n";
	Utiles::Log::instancia()->info("Servidor creado!", "main.cpp");

	servidor.comenzarAEscuchar();

	while( servidor.estaCorriendo() )
	{
		// pongo este hilo a dormir mientras los demas escuchas las llamadas...
		// lo pongo a dormir 10 segundos para asegurar que no coma la cpu.
		sleep(10);
	}

	std::cout << "\nServidor cerrado. Saliendo...\n";
	Utiles::Log::instancia()->info("Servidor cerrado.", "main.cpp");
	servidor.destruir();
}



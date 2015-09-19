/*
 * main.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

#include "conexion/Servidor.h"

int main()
{
	ConexionServidor::Servidor servidor;

	servidor.crear();

	std::cout << "Servidor creado!\n";
	while( servidor.estaCorriendo() )
	{
		servidor.correr(1000);
	}
	std::cout << "\nServidor cerrado. Saliendo...\n";
	servidor.destruir();
}


/*
 * Acciones.cpp
 *
 *  Created on: 21/11/2015
 *      Author: manuel
 */

#include "Acciones.h"

using namespace ConexionServidor::Operaciones;

Acciones::Acciones() {}

Acciones::~Acciones() {}

bool Acciones::darDeAltaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	std::string valorRecuperado = archivoLogico->recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si ya existe un archivo con esos datos devuelvo FALSE.
		return false;
	}

	archivoLogico->guardar();

	return true;
}
bool Acciones::darDeAltaArchivoFisico(ConexionServidor::BaseDeDatos::Archivo* archivo)
{
	if ( archivo->existeFisicamente() )
	{// si ya existe el archivo devuelvo FALSE.
		return false;
	}

	archivo->guardarFisicamente();

	if ( archivo->existeFisicamente() == false )
	{// si no se guardo el archivo devuelvo FALSE.
		return false;
	}

	return true;
}

/*
 * ManagerBD.cpp
 *
 *  Created on: 9/10/2015
 *      Author: manuel
 */

#include "ManagerBD.h"

using namespace ConexionServidor::BaseDeDatos;

rocks_db* ManagerBD::db = NULL;

ManagerBD::ManagerBD() {}

ManagerBD::~ManagerBD() {}

void ManagerBD::inicializar()
{
	db = new rocks_db();
}

void ManagerBD::cerrar()
{
	if ( db != NULL )
	{
		delete db;
	}
}

void ManagerBD::insertar(ClaveRocksDB clave, std::string valor)
{
	db->put(clave.columna, clave.clave, valor);
}

void ManagerBD::eliminar(ClaveRocksDB clave)
{
	//db->delet(clave.columna, clave.clave);
}

std::string ManagerBD::recuperar(ClaveRocksDB clave)
{
	std::string valorRecuperado;
	db->get(clave.columna, clave.clave, &valorRecuperado);

	return valorRecuperado;
}


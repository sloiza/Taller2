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

ManagerBD::~ManagerBD()
{
	this->cerrar();
}

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
	db = NULL;
}

bool ManagerBD::estaAbierta()
{
	if ( db != NULL )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ManagerBD::insertar(ClaveRocksDB clave, std::string valor)
{
	if ( estaAbierta() == false)
	{
		inicializar();
	}

	db->put(clave.columna, Slice(clave.clave), Slice(valor));
}

void ManagerBD::eliminar(ClaveRocksDB clave)
{
	//db->delet(clave.columna, clave.clave);
}

std::string ManagerBD::recuperar(ClaveRocksDB clave)
{
	std::string valorRecuperado;
	db->get(clave.columna, Slice(clave.clave), &valorRecuperado);

	return valorRecuperado;
}


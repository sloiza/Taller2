/*
 * Entidad.cpp
 *
 *  Created on: 8/10/2015
 *      Author: manuel
 */

#include "EntidadBD.h"

using namespace ConexionServidor::BaseDeDatos;

EntidadDB::EntidadDB() : info(NULL) {}

EntidadDB::~EntidadDB()
{
	if( this->info != NULL )
	{
		delete this->info;
	}
}

void EntidadDB::crear()
{
	ClaveRocksDB clave = getClaveRocksDB();
	std::string valor = getValor();

	ManagerBD::insertar(clave, valor);
}

void EntidadDB::modificar()
{
	ClaveRocksDB clave = this->getClaveRocksDB();
	std::string valorNuevo = this->getValor();

	ManagerBD::eliminar(clave);
	ManagerBD::insertar(clave, valorNuevo);
}

void EntidadDB::eliminar()
{
	ClaveRocksDB clave = this->getClaveRocksDB();

	ManagerBD::eliminar(clave);
}

std::string EntidadDB::recuperar()
{
	ClaveRocksDB clave = this->getClaveRocksDB();

	std::string valorRecuperado = ManagerBD::recuperar(clave);

	return valorRecuperado;
}

ClaveRocksDB EntidadDB::getClaveRocksDB()
{
	ClaveRocksDB clave;
	clave.columna = this->getColumnaDeFamilia();
	clave.clave = this->getClave();

	return clave;
}

void EntidadDB::setJsonInfo(JsonInfo* info)
{
	this->info = info;
}

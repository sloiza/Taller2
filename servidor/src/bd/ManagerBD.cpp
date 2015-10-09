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

void ManagerBD::insertar(ClaveRocksDB clave, std::string valor)
{

}

void ManagerBD::eliminar(ClaveRocksDB clave)
{

}

std::string ManagerBD::recuperar(ClaveRocksDB clave)
{
	return std::string("valor_recuperado");
}



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
	if ( estaAbierta() == false)
	{
		inicializar();
	}
	db->delet(clave.columna, clave.clave);
}

std::string ManagerBD::recuperar(ClaveRocksDB clave)
{
	if ( estaAbierta() == false)
	{
		inicializar();
	}
	std::string valorRecuperado;
	db->get(clave.columna, Slice(clave.clave), &valorRecuperado);

	return valorRecuperado;
}


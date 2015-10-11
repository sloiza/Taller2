/*
 * ManagerBD.h
 *
 *  Created on: 9/10/2015
 *      Author: manuel
 */

#ifndef MANAGERBD_H_
#define MANAGERBD_H_

// Base de datos
#include "ClaveRocksDB.h"
#include "rocks_db.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class ManagerBD {
public:
	ManagerBD();
	virtual ~ManagerBD();

	void inicializar();
	void cerrar();

	static void insertar(ClaveRocksDB clave, std::string valor);
	static void eliminar(ClaveRocksDB clave);
	static std::string recuperar(ClaveRocksDB clave);

private:
	static rocks_db* db;
};
};
};

#endif /* MANAGERBD_H_ */

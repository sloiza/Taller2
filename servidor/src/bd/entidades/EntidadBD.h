/*
 * Entidad.h
 *
 *  Created on: 8/10/2015
 *      Author: manuel
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_

// Base de datos
#include "ClaveRocksDB.h"
#include "../ManagerBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class EntidadDB {
public:
	EntidadDB();
	virtual ~EntidadDB();

	virtual ClaveRocksDB getClaveRocksDB();
	virtual std::string getValor() = 0;

	virtual void crear(); 		// PUT
	virtual void modificar(); 	// POST
	virtual void eliminar(); 	// DELETE
	virtual std::string recuperar(); 	// GET

private:
	virtual std::string getColumnaDeFamilia() = 0;
	virtual std::string getClave() = 0;
};
};
};

#endif /* ENTIDAD_H_ */

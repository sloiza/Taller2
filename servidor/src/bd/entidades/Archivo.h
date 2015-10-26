/*
 * Archivo.h
 *
 *  Created on: 25/10/2015
 *      Author: manuel
 */

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class Archivo: public ConexionServidor::BaseDeDatos::EntidadDB {

public:
	Archivo();
	virtual ~Archivo();

};
};
};

#endif /* ARCHIVO_H_ */

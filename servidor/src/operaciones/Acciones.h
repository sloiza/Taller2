/*
 * Acciones.h
 *
 *  Created on: 21/11/2015
 *      Author: manuel
 */

#ifndef ACCIONES_H_
#define ACCIONES_H_

// base de datos
#include "../archivos/Archivo.h"
// entidades
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
// Operaciones
#include "InfoOperaciones.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class Acciones
{
public:
	Acciones();
	virtual ~Acciones();

	bool darDeAltaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool darDeAltaArchivoFisico(ConexionServidor::BaseDeDatos::Archivo*);

};
};
};

#endif /* ACCIONES_H_ */

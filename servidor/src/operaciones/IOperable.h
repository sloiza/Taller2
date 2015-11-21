/*
 * IOperable.h
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#ifndef IOPERABLE_H_
#define IOPERABLE_H_

// respuesta
#include "../conexion/Respuesta.h"

// utiles
#include "../utiles/Bytes.h"
// operaciones
#include "Acciones.h"

// STL
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class IOperable {
public:
	IOperable() {}
	virtual ~IOperable() {}

	virtual ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query) = 0;
	virtual ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query) = 0;
	virtual ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query) = 0;
	virtual ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query) = 0;

	virtual void imprimir() = 0;

protected:

	Acciones acciones;
};
};
};



#endif /* IOPERABLE_H_ */

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

	virtual ConexionServidor::Respuesta delet(std::string contenido) = 0;
	virtual ConexionServidor::Respuesta get(std::string contenido) = 0;
	virtual ConexionServidor::Respuesta post(std::string contenido) = 0;
	virtual ConexionServidor::Respuesta put(std::string contenido) = 0;

	virtual void imprimir() = 0;
};
};
};



#endif /* IOPERABLE_H_ */
